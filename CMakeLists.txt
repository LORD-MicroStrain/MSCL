option(BUILD_SHARED_LIBS "Whether or not to build the shared version of the library." OFF)
option(MSCL_BUILD_PYTHON2 "Whether to build the python 2 bindings." OFF)
option(MSCL_BUILD_PYTHON3 "Whether to build the python 3 bindings." OFF)
option(MSCL_LINK_STATIC_DEPS "Whether to link the dependencies statically. Please note that this means that OpenSSL and Boost must be built with -fPIC on Linux" ON)
option(MSCL_BUILD_TESTS "Whether to build the unit tests." OFF)
option(MSCL_WITH_SSL "Whether or not to compile the library with SSL support" ON)# Shared libraries are required on Linux for Python builds

# Allow the user to use a pre-installed version of Boost
option(MSCL_DOWNLOAD_BOOST "MSCL can download Boost if not already installed. Set Boost_ROOT to the Boost directory if this is turned off" ON)

if(MSCL_WITH_SSL)
    # Allow the user to use a pre-installed version of OpenSSL
    option(MSCL_DOWNLOAD_OPENSSL "MSCL can download OpenSSL if not already installed. Set OPENSSL_ROOT_DIR to the OpenSSL directory if this is turned off" ON)
endif()

# Helper to check if Python is requested
set(MSCL_BUILD_PYTHON OFF)
if(MSCL_BUILD_PYTHON3 OR MSCL_BUILD_PYTHON2)
    set(MSCL_BUILD_PYTHON ON)
endif()

if(NOT BUILD_SHARED_LIBS AND UNIX AND MSCL_BUILD_PYTHON)
    set(BUILD_SHARED_LIBS ON)
endif()

# Dependencies should be linked statically if MSCL is built statically
if(NOT BUILD_SHARED_LIBS AND NOT MSCL_LINK_STATIC_DEPS)
    set(MSCL_LINK_STATIC_DEPS ON)
endif()

#
# Setup and use vcpkg
#

if(MSCL_LINK_STATIC_DEPS)
    # Link dependencies statically on Windows. Windows links dynamically by default in vcpkg
    if(WIN32)
        if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
            set(VCPKG_TARGET_TRIPLET "x86-windows-static" CACHE STRING "Vcpkg target triplet")
        else()
            set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "Vcpkg target triplet")
        endif()

        set(VCPKG_HOST_TRIPLET "${VCPKG_TARGET_TRIPLET}" CACHE STRING "Vcpkg host triplet")
    endif()
elseif(UNIX AND NOT APPLE)
    # Link dependencies dynamically on Linux. Linux links statically by default in vcpkg
    set(VCPKG_TARGET_TRIPLET "x64-linux-dynamic" CACHE STRING "Vcpkg target triplet")
    set(VCPKG_HOST_TRIPLET "${VCPKG_TARGET_TRIPLET}" CACHE STRING "Vcpkg host triplet")
endif()

# Include any Boost dependencies with vcpkg
if(MSCL_DOWNLOAD_BOOST)
    list(APPEND VCPKG_MANIFEST_FEATURES "boost")

    # Include any testing dependencies with vcpkg
    if(MSCL_BUILD_TESTS)
        list(APPEND VCPKG_MANIFEST_FEATURES "testing")
    endif()
endif()

# Include any OpenSSL dependencies with vcpkg
if(MSCL_DOWNLOAD_OPENSSL)
    list(APPEND VCPKG_MANIFEST_FEATURES "openssl")
endif()

# Force vcpkg to output our dependencies to the install directory. This should handle sub dependencies too
option(X_VCPKG_APPLOCAL_DEPS_INSTALL
    "(experimental) Automatically copy dependencies into the install target directory for executables. Requires CMake 3.14."
    ON
)

# Make sure vcpkg uses the correct generator options
if(CMAKE_GENERATOR)
    set(Z_VCPKG_CMAKE_GENERATOR "${CMAKE_GENERATOR}")
endif()

if(CMAKE_GENERATOR_TOOLSET)
    set(VCPKG_PLATFORM_TOOLSET "${CMAKE_GENERATOR_TOOLSET}")
    set(Z_VCPKG_PLATFORM_TOOLSET "${CMAKE_GENERATOR_TOOLSET}")
endif()

set(MSCL_VCPKG_DIR "${CMAKE_CURRENT_LIST_DIR}/deps/vcpkg")

# Prefer vcpkg if we can find it. Fallback if CMake presets aren't used
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    # Different vcpkg roots depending on OS
    if(WIN32)
        set(MSCL_VCPKG_ROOTS
            "${MSCL_VCPKG_DIR}"
            "C:/Program Files/vcpkg"
            "C:/Program Files (x86)/vcpkg"
        )
    elseif(UNIX OR OSX)
        set(MSCL_VCPKG_ROOTS
            "${MSCL_VCPKG_DIR}"
            "/opt/vcpkg"
        )
    endif()

    # See if we can find the vcpkg toolchain file
    find_file(MSCL_VCPKG_TOOLCHAIN
        NAMES "scripts/buildsystems/vcpkg.cmake"
        PATHS ${MSCL_VCPKG_ROOTS}
        NO_DEFAULT_PATH
    )
    if(MSCL_VCPKG_TOOLCHAIN)
        message(STATUS "Using vcpkg toolchain file ${MSCL_VCPKG_TOOLCHAIN}")
    endif()

    # Tell cmake about the toolchain file
    set(CMAKE_TOOLCHAIN_FILE ${MSCL_VCPKG_TOOLCHAIN})
endif()

message(WARNING "
    BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}
    MSCL_BUILD_PACKAGE: ${MSCL_BUILD_PACKAGE}
    MSCL_BUILD_CSHARP: ${MSCL_BUILD_CSHARP}
    MSCL_BUILD_DOCUMENTATION: ${MSCL_BUILD_DOCUMENTATION}
    MSCL_BUILD_PYTHON2: ${MSCL_BUILD_PYTHON2}
    MSCL_BUILD_PYTHON3: ${MSCL_BUILD_PYTHON3}
    MSCL_BUILD_TESTS: ${MSCL_BUILD_TESTS}
    MSCL_WITH_SSL: ${MSCL_WITH_SSL}
    MSCL_WITH_WEBSOCKETS: ${MSCL_WITH_WEBSOCKETS}
    MSCL_PYTHON2_REQUESTED_VERSION: ${MSCL_PYTHON2_REQUESTED_VERSION}
    MSCL_PYTHON3_REQUESTED_VERSION: ${MSCL_PYTHON3_REQUESTED_VERSION}
")

cmake_minimum_required(VERSION 3.23)
project("MSCL"
    LANGUAGES CXX
    VERSION 67.1.0
)

# Enable the use of organizing projects into folders for IDEs that support it
set_property(GLOBAL PROPERTY
    USE_FOLDERS ON
)

set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Supported configuration types" FORCE)

# Export compile commands by default (helpful for clang-tidy and autocomplete for certain IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set some global C++ options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If a build type was not specified, default to debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Create the common dependencies directory in the project root
# This is for use by downloaded dependencies during project configuration
if(NOT DEPS_BASE_DIR)
    set(DEPS_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}/_deps")
endif()

# Set the module directory for ease of use in other parts of the configuration
set(MSCL_MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Get the current year to make sure the file copyright is up-to-date in any generated files that use it
string(TIMESTAMP MSCL_CURRENT_YEAR "%Y")

# Append the custom CMake directory so the files can be imported
list(APPEND CMAKE_MODULE_PATH "${MSCL_MODULE_DIR}")

# Include some utilities used for MicroStrain projects
include(microstrain_utilities)

# Detect if this is a x64 or x86 build
microstrain_get_architecture(MSCL_ARCH_NAME)
if(${MSCL_ARCH_NAME} STREQUAL "x64")
    # This needs to be enabled to properly find any libraries that use the lib64 naming convention
    set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
endif()

# This will make windows create a .lib file with all the symbols of the .dll files exported
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Parse some flags
# These are all ON/OFF flags. For example, -DBUILD_SHARED_LIBS="ON"
option(MSCL_WITH_WEBSOCKETS "Whether or not to compile the library with Websocket support" ON)
option(MSCL_BUILD_EXAMPLES "Whether to build the examples." OFF)
option(MSCL_ZIP_EXAMPLES "Whether to zip the examples source code." OFF)
option(MSCL_BUILD_PACKAGE "Whether to build a package from the resulting binaries" OFF)

if(WIN32)
    option(MSCL_BUILD_CSHARP "Whether to build the C# bindings. Only supported on Windows" OFF)
    option(MSCL_BUILD_DOCUMENTATION "Whether to build the documentation" OFF)
endif()

# Dependencies root/include paths (these are optional and will be downloaded if not set)

if(UNIX AND NOT APPLE)
    set(DPKG_ROOT "" CACHE PATH "Location of the dpkg executable")
    set(RPMBUILD_ROOT "" CACHE PATH "Location of the rpmbuild executable")
endif()

# Use Git to find the version and commit of this repo
microstrain_get_git_version(MSCL_GIT_VERSION MSCL_GIT_VERSION_CLEAN)
microstrain_get_git_commit(MSCL_GIT_COMMIT)

# Configure packaging before including all the targets with add_subdirectory
# Subdirectories depend on most of these options
if(MSCL_BUILD_PACKAGE)
    # Configure the generators to use
    if(UNIX)
        if(CYGWIN)
            set(CPACK_BINARY_CYGWIN OFF)

            set(CPACK_SOURCE_CYGWIN OFF)
        else()
            if(NOT APPLE)
                set(CPACK_BINARY_TZ OFF)
            endif()

            set(CPACK_BINARY_DEB ON)
            # TODO: Determine system to turn on DEB or RPM
            set(CPACK_BINARY_RPM OFF)
            set(CPACK_BINARY_STGZ OFF)
            set(CPACK_BINARY_TGZ OFF)

            set(CPACK_SOURCE_TBZ2 OFF)
            set(CPACK_SOURCE_TGZ OFF)
            set(CPACK_SOURCE_TXZ OFF)
            set(CPACK_SOURCE_TZ OFF)
        endif()
    else()
        set(CPACK_BINARY_ZIP ON)
        set(CPACK_BINARY_NSIS OFF)

        set(CPACK_SOURCE_7Z OFF)
        set(CPACK_SOURCE_ZIP OFF)
    endif()

    set(CPACK_PACKAGE_VENDOR "MicroStrain by HBK")
    set(CPACK_PACKAGE_CONTACT "MicroStrain Support <microstrainsupport@hbkworld.com>")

    # Don't group packages
    set(CPACK_COMPONENTS_GROUPING IGNORE)

    # Turn on automatic dependency detection for Linux packages (RPM has this option enabled by default)
    if(UNIX AND NOT APPLE)
        # Allow dpkg to determine the package dependencies
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

        # Create one package per component
        set(CPACK_DEBIAN_COMPONENT_INSTALL ON)
    else()
        # Create one package per component
        set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
    endif()


    microstrain_get_package_architecture(CPACK_SYSTEM_NAME)
    microstrain_get_git_branch(MSCL_GIT_BRANCH MSCL_BRANCH) # Second param is used to set a cache variable

    if("${MSCL_GIT_BRANCH}" STREQUAL "master")
        # Use the project version for assets built on master
        set(CPACK_PACKAGE_VERSION "v${PROJECT_VERSION}")
    else()
        # Use the tag for all other assets
        set(CPACK_PACKAGE_VERSION "${MSCL_GIT_VERSION}")
    endif()
endif()

if(MSVC)
    # Set the runtime library linking for all projects in MSVC
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<NOT:$<BOOL:${MSCL_LINK_STATIC_DEPS}>>:DLL>")
endif()

string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)

# Use common installation directory naming conventions
include(GNUInstallDirs)

# Setup the install prefix for all packages
if(WIN32)
    string(APPEND CMAKE_INSTALL_PREFIX "/${PROJECT_NAME_LOWER}")
endif()

# Set the proper library install directories for release and debug libraries
set(MSCL_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}$<$<CONFIG:Debug>:/debug>")

# Set the library install directory for x86 builds
if(${MSCL_ARCH_NAME} STREQUAL "x86")
    string(APPEND MSCL_INSTALL_LIBDIR "32")
endif()

# Set the library install directory for debug builds
string(APPEND MSCL_INSTALL_LIBDIR "$<$<CONFIG:Debug>:/debug>")

# Build the library
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/MSCL")

# Build the documentation
if(MSCL_BUILD_DOCUMENTATION)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/docs")
endif()

## Build the examples
#if(MSCL_BUILD_EXAMPLES)
#    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples")
#endif()

# Build the testing suite
if(MSCL_BUILD_TESTS)
    enable_testing()
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tests")
endif()

# Build one or more of the bindings
if(MSCL_BUILD_PYTHON OR MSCL_BUILD_CSHARP)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/bindings")
endif()

# Include the CPack module for packaging
# Package options are configured before including any subdirectories to ensure proper configurations
if(MSCL_BUILD_PACKAGE)
    # NOTE: CPack requires all configuration variables to be set before including this module
    include(CPack)

    get_property(GENERATOR_IS_MULTI_CONFIG GLOBAL
        PROPERTY GENERATOR_IS_MULTI_CONFIG
    )

    # Add the packaging configuration file to the build directory for single-config generators
    # This allows easy access to the file from the build directory
    if(NOT GENERATOR_IS_MULTI_CONFIG)
        file(
            COPY "${MSCL_MODULE_DIR}/microstrain_package_all.cmake"
            DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
        )
    endif()
endif()
