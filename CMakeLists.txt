cmake_minimum_required(VERSION 3.16.0)
project(MSCL
        LANGUAGES CXX
        VERSION 67.1.0
)

set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Supported configuration types" FORCE)

# Export compile commands by default (helpful for clang-tidy and autocomplete for certain IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Append the custom CMake directory so the files can be imported
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Set some global C++ options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If a build type was not specified, default to debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Add our custom modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Include some utilities used for MicroStrain projects
include(microstrain_utilities)

# Detect if this is a x64 or x86 build
microstrain_get_architecture(MSCL_ARCH_NAME)

# This will make windows create a .lib file with all the symbols of the .dll files exported
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Parse some flags
# These are all ON/OFF flags. For example, -DBUILD_SHARED_LIBS="ON"
option(BUILD_SHARED_LIBS "Whether or not to build the shared version of the library." OFF)
option(MSCL_WITH_SSL "Whether or not to compile the library with SSL support" ON)
option(MSCL_WITH_WEBSOCKETS "Whether or not to compile the library with Websocket support" ON)
option(MSCL_BUILD_PYTHON2 "Whether to build the python 2 bindings." OFF)
option(MSCL_BUILD_PYTHON3 "Whether to build the python 3 bindings." OFF)
option(MSCL_BUILD_TESTS "Whether to build the unit tests." OFF)
option(MSCL_BUILD_EXAMPLES "Whether to build the examples." OFF)
option(MSCL_ZIP_EXAMPLES "Whether to zip the examples source code." OFF)
option(MSCL_BUILD_PACKAGE "Whether to build a package from the resulting binaries" OFF)

if(WIN32)
    option(MSCL_BUILD_CSHARP "Whether to build the C# bindings. Only supported on Windows" OFF)
    option(MSCL_BUILD_DOCUMENTATION "Whether to build the documentation" OFF)

    if(DEFINED MSCL_LINK_STATIC_DEPS)
        message(WARNING "Linking static dependencies is for Linux. Making sure this is off for Windows")
        set(MSCL_LINK_STATIC_DEPS OFF)
    endif()
elseif(UNIX)
    option(MSCL_LINK_STATIC_DEPS "Whether to link the dependencies statically. Please note that this means that OpenSSL and boost must be built with -fPIC" OFF)

    if(DEFINED MSCL_BUILD_CSHARP)
        message(WARNING "Building .NET is only supported on Windows. Making sure this is off for Linux")
        set(MSCL_BUILD_CSHARP OFF)
    endif()

    if(DEFINED MSCL_BUILD_DOCUMENTATION)
        message(WARNING "Building documentation is only supported on Windows. Making sure this is off for Linux")
        set(MSCL_BUILD_DOCUMENTATION OFF)
    endif()
endif()

# Allow the user to override the location where most dependencies are installed on Windows
if(WIN32)
    if(DEFINED ENV{LIB_PATH})
        set(MICROSTRAIN_LIB_DIR "$ENV{LIB_PATH}" CACHE STRING "Directory where most dependencies are installed")
    else()
        set(MICROSTRAIN_LIB_DIR "C:/lib" CACHE STRING "Directory where most dependencies are installed")
    endif()
endif()

if(WIN32)
    set(DEFAULT_BOOST_ROOT "${MICROSTRAIN_LIB_DIR}/boost")
    set(DEFAULT_OPENSSL_ROOT_DIR "${MICROSTRAIN_LIB_DIR}/openssl/lib")

    if(${MSCL_ARCH_NAME} STREQUAL "x64")
        string(APPEND DEFAULT_OPENSSL_ROOT_DIR "64")
    endif()

    set(DEFAULT_SWIG_ROOT "${MICROSTRAIN_LIB_DIR}/swig/swigwin-4.0.0")
endif()

set(TURTLE_INCLUDE_DIR "${MICROSTRAIN_LIB_DIR}/turtle/include" CACHE STRING "Location to search for the turtle include files. Only used when building tests")
set(NATURAL_DOCS_ROOT "${MICROSTRAIN_LIB_DIR}/NaturalDocs" CACHE STRING "Location of NaturalDocs used to generate the documentation")

if(UNIX AND NOT APPLE)
    set(DPKG_ROOT "" CACHE STRING "Location of the dpkg executable")
    set(RPMBUILD_ROOT "" CACHE STRING "Location of the rpmbuild executable")
endif()

# Use Git to find the version and commit of this repo
microstrain_get_git_version(MSCL_GIT_VERSION MSCL_GIT_VERSION_CLEAN)
microstrain_get_git_commit(MSCL_GIT_COMMIT)

# Make the Output directory which is where we will copy all of the build artifacts on a successful build
set(MSCL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Output)
file(MAKE_DIRECTORY ${MSCL_OUTPUT_DIR})

if(MSVC)
    # Parallel build options for Windows
    add_compile_options(/MP)

    # Ignore warnings from the linker when it can't find a pdb file
    add_link_options(/ignore:4099)

    # On Windows, add a few flags for compatibility with the old solution files
    add_compile_definitions(
        _USRDLL
        NOMINMAX
        _WIN32_WINNT=0x0501
    )
endif()

# Don't let boost figure out the libraries to link
add_compile_definitions(BOOST_ALL_NO_LIB)

# Also find the dependencies for MSCL

# Setup the boost root variable
if(NOT Boost_ROOT)
    set(Boost_ROOT "${DEFAULT_BOOST_ROOT}")
endif()

# Custom variable used in this CMake file, not used by FindBoost.cmake
set(Boost_REQUESTED_VERSION "1.68.0")
set(Boost_REQUESTED_COMPONENTS system filesystem)

# Find the static version of boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

# Disable CMake policy for Boost config find_package
# CMake 3.30+ uses Boost Config for Boost 1.70+
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

# Use the old FindBoost module to find the Boost directory
find_package(Boost ${Boost_REQUESTED_VERSION} REQUIRED COMPONENTS ${Boost_REQUESTED_COMPONENTS})

set(Boost_STATIC_LIBRARIES ${Boost_LIBRARIES})

# Find the shared version of boost
if(BUILD_SHARED_LIBS OR (UNIX AND MSCL_BUILD_PYTHON3) OR (UNIX AND MSCL_BUILD_PYTHON2))
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_STATIC_RUNTIME OFF)

    find_package(Boost ${Boost_REQUESTED_VERSION} REQUIRED COMPONENTS ${Boost_REQUESTED_COMPONENTS})

    set(Boost_SHARED_LIBRARIES ${Boost_LIBRARIES}) # Save the shared libraries, so they will not be overridden when we find the static libraries
endif()

# Find the threading library
find_package(Threads REQUIRED)

# If we were requested to build with SSL, find OpenSSL
if(MSCL_WITH_SSL)
    # Ultra mega hack since we are finding the lib path of OpenSSL, we need to manually set the include path...
    if(NOT DEFINED OPENSSL_ROOT_DIR)
        set(OPENSSL_ROOT_DIR "${DEFAULT_OPENSSL_ROOT_DIR}")
        if(${MSCL_ARCH_NAME} STREQUAL "x64")
            set(OPENSSL_INCLUDE_DIR ${DEFAULT_OPENSSL_ROOT_DIR}/../include64 CACHE INTERNAL "")
        else()
            set(OPENSSL_INCLUDE_DIR ${DEFAULT_OPENSSL_ROOT_DIR}/../include CACHE INTERNAL "")
        endif()
    endif()

    # For some reason, FindOpenSSL does not look for the libraries again, so unset the variables to force it to search again
    unset(OPENSSL_SSL_LIBRARY CACHE)
    unset(OPENSSL_LIBRARIES CACHE)
    unset(OPENSSL_CRYPTO_LIBRARY CACHE)
    unset(LIB_EAY_DEBUG CACHE)
    unset(LIB_EAY_RELEASE CACHE)
    unset(SSL_EAY_DEBUG CACHE)
    unset(SSL_EAY_RELEASE CACHE)

    # Shared OpenSSL
    if(BUILD_SHARED_LIBS)
        set(OPENSSL_USE_STATIC_LIBS FALSE)
        set(OPENSSL_MSVC_STATIC_RT FALSE)
        find_package(OpenSSL REQUIRED)
        set(OPENSSL_SHARED_LIBRARIES ${OPENSSL_LIBRARIES})
    endif()

    # For some reason, FindOpenSSL does not look for the libraries again, so unset the variables to force it to search again
    unset(OPENSSL_SSL_LIBRARY CACHE)
    unset(OPENSSL_LIBRARIES CACHE)
    unset(OPENSSL_CRYPTO_LIBRARY CACHE)
    unset(LIB_EAY_DEBUG CACHE)
    unset(LIB_EAY_RELEASE CACHE)
    unset(SSL_EAY_DEBUG CACHE)
    unset(SSL_EAY_RELEASE CACHE)

    # Static OpenSSL
    set(OPENSSL_USE_STATIC_LIBS TRUE)
    set(OPENSSL_MSVC_STATIC_RT TRUE)
    find_package(OpenSSL REQUIRED)
    set(OPENSSL_STATIC_LIBRARIES ${OPENSSL_LIBRARIES})

    # If linking on Windows, we will also need the windows crypto library
    if(WIN32)
        list(APPEND OPENSSL_STATIC_LIBRARIES CRYPT32.lib)
        list(APPEND OPENSSL_SHARED_LIBRARIES CRYPT32.lib)
    endif()
endif()

# Find language libraries if building them
if(MSCL_BUILD_PYTHON3)
    set(Python3_USE_STATIC_LIBS OFF)
    find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
endif()

if(MSCL_BUILD_PYTHON2)
    set(Python2_USE_STATIC_LIBS OFF)
    find_package(Python2 REQUIRED COMPONENTS Interpreter Development)
endif()

if(MSCL_BUILD_CSHARP)
    enable_language(CSharp)
endif()

if(MSCL_BUILD_PYTHON2 OR MSCL_BUILD_PYTHON3 OR MSCL_BUILD_CSHARP)
    # Make sure we can find swig
    cmake_policy(SET CMP0078 NEW)
    cmake_policy(SET CMP0086 NEW)
    if(MSCL_BUILD_CSHARP AND WIN32)
        cmake_policy(SET CMP0122 NEW)
    endif()

    set(SWIG_REQUESTED_VERSION "4.0.0" CACHE STRING "")

    # Attempt to find swig with a user set location
    find_package(SWIG ${SWIG_REQUESTED_VERSION} QUIET)

    # Set a default swig executable location and try again
    if(NOT SWIG_FOUND)
        set(SWIG_EXECUTABLE "${DEFAULT_SWIG_ROOT}/swig.exe")
        find_package(SWIG ${SWIG_REQUESTED_VERSION} QUIET REQUIRED)
    endif()

    # Display a found swig message since we set quiet above
    message(STATUS "Found SWIG: ${SWIG_EXECUTABLE} (found suitable version \"${SWIG_VERSION}\", minimum required is \"${SWIG_REQUESTED_VERSION}\")")
endif()

# If we were asked to build the docs, try to find NaturalDocs
if(MSCL_BUILD_DOCUMENTATION)
    find_program(NaturalDocs_EXECUTABLE
        NAMES NaturalDocs
        PATHS ${NATURAL_DOCS_ROOT}
        DOC "NaturalDocs command line client"
    )
    if(${NaturalDocs_EXECUTABLE} STREQUAL "NaturalDocs_EXECUTABLE-NOTFOUND")
        message(FATAL_ERROR "Unable to build docs as we were unable to find NaturalDocs in ${NATURAL_DOCS_ROOT}")
    else()
        message(STATUS "Found NaturalDocs: ${NaturalDocs_EXECUTABLE}")
    endif()
endif()

# If we were asked to package, find the generators we can use
if(MSCL_BUILD_PACKAGE AND UNIX AND NOT APPLE)
    set(FOUND_CPACK_GENERATORS "")
    find_program(DPKG_EXECUTABLE
        NAMES dpkg
        PATHS ${DPKG_ROOT}
        DOC "dpkg command line client"
    )
    if(NOT ${DPKG_EXECUTABLE} STREQUAL "DPKG_EXECUTABLE-NOTFOUND")
        list(APPEND FOUND_CPACK_GENERATORS "DEB")
    endif()
    find_program(RPMBUILD_EXECUTABLE
        NAMES rpmbuild
        PATHS ${RPMBUILD_ROOT}
        DOC "rpmbuild command line client"
    )
    if(NOT ${RPMBUILD_EXECUTABLE} STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")
        list(APPEND FOUND_CPACK_GENERATORS "RPM")
    endif()
    if(NOT FOUND_CPACK_GENERATORS)
        message(FATAL_ERROR "Unable to find either dpkg or rpmbuild, but we were requested to build a package. Make sure these exist on the system")
    endif()
endif()

if(MSCL_ZIP_EXAMPLES)
    set(MSCL_EXAMPLES_OUTPUT_DIR "${MSCL_OUTPUT_DIR}/Examples")

    # Also copy the test source and build files to the output directory so it can be compressed
    set(MSCL_EXAMPLES_TARGET MSCL_Examples_Zip)
    add_custom_target(${MSCL_EXAMPLES_TARGET}
        ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${MSCL_EXAMPLES_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${MSCL_EXAMPLES_OUTPUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindMSCL.cmake ${MSCL_EXAMPLES_OUTPUT_DIR}/cmake/FindMSCL.cmake
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindMSCL_Managed.cmake ${MSCL_EXAMPLES_OUTPUT_DIR}/cmake/FindMSCL_Managed.cmake
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/MSCL_Examples ${MSCL_EXAMPLES_OUTPUT_DIR}/MSCL_Examples
    )

    set(MSCL_EXAMPLES_INSTALL_COMPONENT ${PROJECT_NAME}_EXAMPLES)
    install(
        DIRECTORY "${MSCL_EXAMPLES_OUTPUT_DIR}/"
        DESTINATION .
        COMPONENT ${MSCL_EXAMPLES_INSTALL_COMPONENT}
    )
endif()

# Add the underlying CMake files
if(MSCL_BUILD_EXAMPLES)
    add_subdirectory(MSCL_Examples)
endif()

add_subdirectory(MSCL)

if(MSCL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(MSCL_Unit_Tests)
endif()
