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

if(MSCL_BUILD_PYTHON2)
    # Allow the user to request a certain version of Python2
    # If using a version not supported by the build system then the user must have the requested version installed already
    set(MSCL_PYTHON2_REQUESTED_VERSION "2.7" CACHE STRING "The requested version of Python2 to use for bindings")

    # Allow the user to use a pre-installed version of Python2
    option(MSCL_DOWNLOAD_PYTHON2 "MSCL can download Python2 if not already installed. Set Python2_ROOT to the Python2 directory if this is turned off" ON)

    # List of supported Python2 versions
    set(MSCL_SUPPORTED_PYTHON2_VERSIONS
        "2.7"
    )

    # Add only the requested version or all supported versions of Python2 to be built
    if("${MSCL_PYTHON2_REQUESTED_VERSION}" STREQUAL "")
        list(APPEND MSCL_PYTHON_REQUESTED_VERSIONS ${MSCL_SUPPORTED_PYTHON2_VERSIONS})
    else()
        list(APPEND MSCL_PYTHON_REQUESTED_VERSIONS "${MSCL_PYTHON2_REQUESTED_VERSION}")
    endif()
endif()

if(MSCL_BUILD_PYTHON3)
    # Allow the user to request a certain version of Python3
    # If using a version not supported by the build system then the user must have the requested version installed already
    set(MSCL_PYTHON3_REQUESTED_VERSION "3.12" CACHE STRING "The requested version of Python3 to use for bindings")

    # Allow the user to use a pre-installed version of Python3
    option(MSCL_DOWNLOAD_PYTHON3 "MSCL can download Python3 if not already installed. Set Python3_ROOT to the Python3 directory if this is turned off" ON)

    # List of supported Python3 versions
    set(MSCL_SUPPORTED_PYTHON3_VERSIONS
        "3.10"
        "3.11"
        "3.12"
    )

    # Add only the requested version or all supported versions of Python3 to be built
    if("${MSCL_PYTHON3_REQUESTED_VERSION}" STREQUAL "")
        list(APPEND MSCL_PYTHON_REQUESTED_VERSIONS ${MSCL_SUPPORTED_PYTHON3_VERSIONS})
    else()
        list(APPEND MSCL_PYTHON_REQUESTED_VERSIONS "${MSCL_PYTHON3_REQUESTED_VERSION}")
    endif()
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


cmake_minimum_required(VERSION 3.23)
project("MSCL"
    LANGUAGES CXX
    VERSION 67.1.0
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
if (${MSCL_ARCH_NAME} STREQUAL "x64")
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
    # Enable certain generators to use
    if(UNIX)
        if(CYGWIN)
            set(CPACK_BINARY_CYGWIN OFF)

            set(CPACK_SOURCE_CYGWIN OFF)
        else()
            if(NOT APPLE)
                set(CPACK_BINARY_DEB ON)
                set(CPACK_BINARY_RPM ON)
                set(CPACK_BINARY_TZ OFF)
            endif()

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

    # NOTE: CPack requires all these variables to be set before importing the module. Do not move them after the include(CPack) line
    set(CPACK_PACKAGE_VENDOR "MicroStrain by HBK")
    set(CPACK_PACKAGE_CONTACT "MicroStrain Support <microstrainsupport@hbkworld.com>")

    # Create a packer per component
    set(CPACK_COMPONENTS_GROUPING IGNORE)

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
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<BOOL:${BUILD_SHARED_LIBS}>:DLL>")
endif()

# Use common installation directory naming conventions
include(GNUInstallDirs)

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
if(MSCL_BUILD_PYTHON2 OR MSCL_BUILD_PYTHON3 OR MSCL_BUILD_CSHARP)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/bindings")
endif()

# If we were asked to build packages, include CPack and set up packaging
if(MSCL_BUILD_PACKAGE)

#    if(WIN32)
#        set(MSCL_FILE_NAME_PREFIX "${MSCL_LIBRARY}_Windows_${MSCL_ARCH}")
#    else()
#        set(MSCL_FILE_NAME_PREFIX "${MSCL_LIBRARY}_${MSCL_ARCH}")
#    endif()

    # Archive specific configuration
    set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

    # Deb specific configuration
    set(CPACK_DEB_COMPONENT_INSTALL ON)

    # Most packages share these dependencies
    set(CPACK_DEBIAN_COMMON_DEPS libboost-system-dev libboost-filesystem-dev)

    if(MSCL_WITH_SSL)
        list(APPEND CPACK_DEBIAN_COMMON_DEPS libssl-dev)
    endif()

    string(REPLACE ";" ", " CPACK_DEBIAN_COMMON_DEPS "${CPACK_DEBIAN_COMMON_DEPS}")

    # RPM specific configuration
    set(CPACK_RPM_COMPONENT_INSTALL ON)
    set(CPACK_RPM_PACKAGE_AUTOREQ OFF)

    # Most packages share these dependencies
    set(CPACK_RPM_COMMON_DEPS boost-filesystem boost-system boost-devel)

    if(MSCL_WITH_SSL)
        list(APPEND CPACK_RPM_COMMON_DEPS openssl-devel)
    endif()

    string(REPLACE ";" ", " CPACK_RPM_COMMON_DEPS "${CPACK_RPM_COMMON_DEPS}")

#    if(BUILD_SHARED_LIBS)
#        set(PACKAGE_FILE_NAME "Shared_C++")
#    else()
#        set(PACKAGE_FILE_NAME "Static_C++")
#    endif()

#    microstrain_set_cpack_component_file_name(
#        COMPONENT_NAME ${MSCL_LIBRARY}
#        FILE_NAME_PREFIX ${MSCL_FILE_NAME_PREFIX}
#        FILE_NAME "${PACKAGE_FILE_NAME}"
#        FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#    )
    set(CPACK_DEBIAN_${MSCL_LIBRARY}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
    set(CPACK_RPM_${MSCL_LIBRARY}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")

    if(MSCL_BUILD_PYTHON3)
#        microstrain_set_cpack_component_file_name(
#            COMPONENT_NAME ${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}
#            FILE_NAME_PREFIX ${MSCL_FILE_NAME_PREFIX}
#            FILE_NAME "Python${MSCL_PYTHON3_VERSION}"
#            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#        )
        set(CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "python${MSCL_PYTHON3_VERSION}")
        set(CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "python3")

        if(NOT MSCL_LINK_STATIC_DEPS)
            list(APPEND CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
            string(REPLACE ";" ", " CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS}")

            list(APPEND CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
            string(REPLACE ";" ", " CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES}")
        endif()
    endif()

    if(MSCL_BUILD_PYTHON2)
#        microstrain_set_cpack_component_file_name(
#            COMPONENT_NAME ${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}
#            FILE_NAME_PREFIX ${MSCL_FILE_NAME_PREFIX}
#            FILE_NAME "Python${MSCL_PYTHON2_VERSION}"
#            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#        )
        set(CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "python${MSCL_PYTHON2_VERSION}")
        set(CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "python2")

        if(NOT MSCL_LINK_STATIC_DEPS)
            list(APPEND CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
            string(REPLACE ";" ", " CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS}")

            list(APPEND CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
            string(REPLACE ";" ", " CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES}")
        endif()
    endif()

#    if(MSCL_BUILD_CSHARP)
#        microstrain_set_cpack_component_file_name(
#            COMPONENT_NAME ${MSCL_CSHARP_INSTALL_COMPONENT}
#            FILE_NAME_PREFIX ${MSCL_FILE_NAME_PREFIX}
#            FILE_NAME "DotNet"
#            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#        )
#    endif()
#
#    if(MSCL_BUILD_DOCUMENTATION)
#        microstrain_set_cpack_component_file_name(
#            COMPONENT_NAME ${MSCL_DOCS_INSTALL_COMPONENT}
#            FILE_NAME_PREFIX ${MSCL_LIBRARY}
#            FILE_NAME "Documentation"
#            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#        )
#    endif()
#
#    if(MSCL_ZIP_EXAMPLES)
#        microstrain_set_cpack_component_file_name(
#            COMPONENT_NAME ${MSCL_EXAMPLES_INSTALL_COMPONENT}
#            FILE_NAME_PREFIX ${MSCL_LIBRARY}
#            FILE_NAME "Examples"
#            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#        )
#    endif()

    # Finally include cpack which should have taken all of the previous variables into consideration
    include(CPack)

#    cpack_add_component(${MSCL_LIBRARY}
#        DESCRIPTION "MSCL library and header files"
#        GROUP ${MSCL_LIBRARY}
#    )
#
#    if(MSCL_BUILD_PYTHON3)
#        cpack_add_component(${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}
#            DESCRIPTION "MSCL python bindings for ${MSCL_PYTHON3_VERSION}"
#            GROUP ${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}
#        )
#    endif()
#
#    if(MSCL_BUILD_PYTHON2)
#        cpack_add_component(${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}
#            DESCRIPTION "MSCL python bindings for ${MSCL_PYTHON2_VERSION}"
#            GROUP ${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}
#        )
#    endif()
#
#    if(MSCL_BUILD_CSHARP)
#        cpack_add_component(${MSCL_CSHARP_INSTALL_COMPONENT}
#            DESCRIPTION "MSCL CSharp bindings"
#            GROUP ${MSCL_CSHARP_INSTALL_COMPONENT}
#        )
#    endif()
#
#    if(MSCL_BUILD_DOCUMENTATION)
#        cpack_add_component(${MSCL_DOCS_INSTALL_COMPONENT}
#            DESCRIPTION "MSCL documentation"
#            GROUP ${MSCL_DOCS_INSTALL_COMPONENT}
#        )
#    endif()
#
#    if(MSCL_ZIP_EXAMPLES)
#        cpack_add_component(${MSCL_EXAMPLES_INSTALL_COMPONENT}
#            DESCRIPTION "MSCL examples"
#            GROUP ${MSCL_EXAMPLES_INSTALL_COMPONENT}
#        )
#    endif()
endif()
















## Make the Output directory which is where we will copy all of the build artifacts on a successful build
#set(MSCL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Output)
#file(MAKE_DIRECTORY ${MSCL_OUTPUT_DIR})

#if(MSVC)
#    # Parallel build options for Windows
#    add_compile_options(/MP)
#
#    # Ignore warnings from the linker when it can't find a pdb file
#    add_link_options(/ignore:4099)
#
#    # On Windows, add a few flags for compatibility with the old solution files
#    add_compile_definitions(
#        _USRDLL
#        NOMINMAX
#        _WIN32_WINNT=0x0501
#    )
#endif()

# Also find the dependencies for MSCL

#set(Boost_REQUESTED_COMPONENTS
#    "asio"
#    "beast"
#    "circular_buffer"
#    "crc"
#    "filesystem"
#    "lambda"
#    "math"
#)
#
## Find the static version of boost
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_STATIC_RUNTIME ON)
#
## Find the shared version of boost
#if(BUILD_SHARED_LIBS OR NOT MSCL_LINK_STATIC_DEPS)
#    set(Boost_USE_STATIC_LIBS OFF)
#    set(Boost_USE_STATIC_RUNTIME OFF)
#endif()
#
#find_package(Boost COMPONENTS ${Boost_REQUESTED_COMPONENTS} CONFIG)
#
## Find the threading library
#find_package(Threads REQUIRED)
#
## If we were requested to build with SSL, find OpenSSL
#if(MSCL_WITH_SSL)
#    set(OPENSSL_REQUESTED_VERSION "1.1.0f" CACHE STRING "Requested version of OpenSSL")
#
#    # For some reason, FindOpenSSL does not look for the libraries again, so unset the variables to force it to search again
#    unset(OPENSSL_SSL_LIBRARY CACHE)
#    unset(OPENSSL_LIBRARIES CACHE)
#    unset(OPENSSL_CRYPTO_LIBRARY CACHE)
#    unset(LIB_EAY_DEBUG CACHE)
#    unset(LIB_EAY_RELEASE CACHE)
#    unset(SSL_EAY_DEBUG CACHE)
#    unset(SSL_EAY_RELEASE CACHE)
#
#    # Attempt to find OpenSSL before manually downloading it (this assumes OPENSSL_ROOT_DIR was set by the user)
#    find_package(OpenSSL QUIET)
#
#    # Manually download and install OpenSSL
#    if(NOT OPENSSL_FOUND)
#        if(MSVC)
#            #            if(MSVC_VERSION LESS 1900 OR MSVC_VERSION GREATER_EQUAL 1920)
#            #                message(FATAL_ERROR "${PROJECT_NAME} is only compatible with MSVC 2015 and 2017")
#            #            endif()
#
#            if(MSVC_VERSION EQUAL 1900)
#                set(SC_VS_VERSION 2015)
#            elseif(MSVC_VERSION GREATER_EQUAL 1910#[[ AND MSVC_VERSION LESS 1920]])
#                set(SC_VS_VERSION 2017)
#            endif()
#        endif()
#
#        set(OPENSSL_ARCHIVE_DIR "openssl-${OPENSSL_REQUESTED_VERSION}-vs${SC_VS_VERSION}")
#        microstrain_download_and_extract_archive(
#            NAME "OpenSSL"
#            URL "https://www.npcglib.org/~stathis/downloads/${OPENSSL_ARCHIVE_DIR}.7z"
#            DEPS_BASE_DIR "${DEPS_BASE_DIR}"
#            EXTRACTED_DIR "${OPENSSL_ARCHIVE_DIR}"
#        )
#
#        # OPENSSL_ROOT_DIR is required to include/find the OpenSSL binaries
#        set(OPENSSL_ROOT_DIR "${DEPS_BASE_DIR}/${OPENSSL_ARCHIVE_DIR}/lib" CACHE PATH "Location to search for the OpenSSL libraries" FORCE)
#        set(OPENSSL_INCLUDE_DIR "${DEPS_BASE_DIR}/${OPENSSL_ARCHIVE_DIR}/include")
#
#        if(${MSCL_ARCH_NAME} STREQUAL "x64")
#            string(APPEND OPENSSL_ROOT_DIR "64")
#            string(APPEND OPENSSL_INCLUDE_DIR "64")
#        endif()
#    endif()
#
#    # For some reason, FindOpenSSL does not look for the libraries again, so unset the variables to force it to search again
#    unset(OPENSSL_SSL_LIBRARY CACHE)
#    unset(OPENSSL_LIBRARIES CACHE)
#    unset(OPENSSL_CRYPTO_LIBRARY CACHE)
#    unset(LIB_EAY_DEBUG CACHE)
#    unset(LIB_EAY_RELEASE CACHE)
#    unset(SSL_EAY_DEBUG CACHE)
#    unset(SSL_EAY_RELEASE CACHE)
#
#    # Static OpenSSL
#    set(OPENSSL_USE_STATIC_LIBS TRUE)
#    set(OPENSSL_MSVC_STATIC_RT TRUE)
#
#    # Shared OpenSSL
#    if(BUILD_SHARED_LIBS OR NOT MSCL_LINK_STATIC_DEPS)
#        set(OPENSSL_USE_STATIC_LIBS FALSE)
#        set(OPENSSL_MSVC_STATIC_RT FALSE)
#    endif()
#
#    find_package(OpenSSL REQUIRED)
#
#    # If linking on Windows, we will also need the windows crypto library
#    if(WIN32)
#        list(APPEND OPENSSL_LIBRARIES crypt32.lib)
#    endif()
#endif()
#
### Find language libraries if building them
##if(MSCL_BUILD_PYTHON3)
##    set(Python3_USE_STATIC_LIBS OFF)
##    find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
##endif()
##
##if(MSCL_BUILD_PYTHON2)
##    set(Python2_USE_STATIC_LIBS OFF)
##    find_package(Python2 REQUIRED COMPONENTS Interpreter Development)
##endif()
##
##if(MSCL_BUILD_CSHARP)
##    enable_language(CSharp)
##endif()
#
#set(MSCL_BUILD_BINDINGS OFF)
#
#if(MSCL_BUILD_PYTHON2 OR MSCL_BUILD_PYTHON3 OR MSCL_BUILD_CSHARP)
##    # Make sure we can find swig
##    cmake_policy(SET CMP0078 NEW)
##    cmake_policy(SET CMP0086 NEW)
##    if(MSCL_BUILD_CSHARP AND WIN32)
##        cmake_policy(SET CMP0122 NEW)
##    endif()
#
#    set(SWIG_REQUESTED_VERSION "4.0.0" CACHE STRING "")
#
#    # Attempt to find Swig before manually downloading it (this assumes SWIG_ROOT was set by the user)
#    find_package(SWIG ${SWIG_REQUESTED_VERSION} QUIET)
#
#    # Set a default swig executable location and try again
#    if(NOT SWIG_FOUND)
#        set(SWIG_PACKAGE_NAME "swig")
#        if(MSVC)
#            string(APPEND SWIG_PACKAGE_NAME "win")
#        endif()
#
#        set(SWIG_ARCHIVE_DIR "${SWIG_PACKAGE_NAME}-${SWIG_REQUESTED_VERSION}")
#        set(SWIG_ARCHIVE_URL "https://sourceforge.net/projects/swig/files/${SWIG_PACKAGE_NAME}/${SWIG_ARCHIVE_DIR}/${SWIG_ARCHIVE_DIR}")
#
#        if(MSVC)
#            string(APPEND SWIG_ARCHIVE_URL ".zip")
#        else()
#            string(APPEND SWIG_ARCHIVE_URL ".tar.gz")
#        endif()
#
#        microstrain_download_and_extract_archive(
#            NAME "Swig"
#            URL "${SWIG_ARCHIVE_URL}"
#            DEPS_BASE_DIR "${DEPS_BASE_DIR}"
#            EXTRACTED_DIR "${SWIG_ARCHIVE_DIR}"
#        )
#
#        set(SWIG_ROOT "${DEPS_BASE_DIR}/${SWIG_ARCHIVE_DIR}" CACHE PATH "Location to search for the Swig executable" FORCE)
#    endif()
#
#    find_package(SWIG ${SWIG_REQUESTED_VERSION} REQUIRED)
#endif()
#
## If we were asked to package, find the generators we can use
#if(MSCL_BUILD_PACKAGE AND UNIX AND NOT APPLE)
#    set(FOUND_CPACK_GENERATORS "")
#    find_program(DPKG_EXECUTABLE
#        NAMES dpkg
#        PATHS ${DPKG_ROOT}
#        DOC "dpkg command line client"
#    )
#    if(NOT ${DPKG_EXECUTABLE} STREQUAL "DPKG_EXECUTABLE-NOTFOUND")
#        list(APPEND FOUND_CPACK_GENERATORS "DEB")
#    endif()
#    find_program(RPMBUILD_EXECUTABLE
#        NAMES rpmbuild
#        PATHS ${RPMBUILD_ROOT}
#        DOC "rpmbuild command line client"
#    )
#    if(NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")
#        list(APPEND FOUND_CPACK_GENERATORS "RPM")
#    endif()
#    if(NOT FOUND_CPACK_GENERATORS)
#        message(FATAL_ERROR "Unable to find either dpkg or rpmbuild, but we were requested to build a package. Make sure these exist on the system")
#    endif()
#endif()
#
#if(MSCL_ZIP_EXAMPLES)
#    set(MSCL_EXAMPLES_OUTPUT_DIR "${MSCL_OUTPUT_DIR}/Examples")
#
#    # Also copy the test source and build files to the output directory so it can be compressed
#    set(MSCL_EXAMPLES_TARGET MSCL_Examples_Zip)
#    add_custom_target(${MSCL_EXAMPLES_TARGET}
#        ALL
#        COMMAND ${CMAKE_COMMAND} -E remove_directory "${MSCL_EXAMPLES_OUTPUT_DIR}"
#        COMMAND ${CMAKE_COMMAND} -E make_directory ${MSCL_EXAMPLES_OUTPUT_DIR}
#        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindMSCL.cmake ${MSCL_EXAMPLES_OUTPUT_DIR}/cmake/FindMSCL.cmake
#        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindMSCL_Managed.cmake ${MSCL_EXAMPLES_OUTPUT_DIR}/cmake/FindMSCL_Managed.cmake
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/examples ${MSCL_EXAMPLES_OUTPUT_DIR}/MSCL_Examples
#    )
#
#    set(MSCL_EXAMPLES_INSTALL_COMPONENT ${PROJECT_NAME}_EXAMPLES)
#    install(
#        DIRECTORY "${MSCL_EXAMPLES_OUTPUT_DIR}/"
#        DESTINATION .
#        COMPONENT ${MSCL_EXAMPLES_INSTALL_COMPONENT}
#    )
#endif()
