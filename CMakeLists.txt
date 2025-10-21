cmake_minimum_required(VERSION 3.18)
project(MSCL
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

# Append the custom CMake directory so the files can be imported
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Include some utilities used for MicroStrain projects
include(microstrain_utilities)

# Create the common dependencies directory in the project root
if(NOT DEPS_BASE_DIR)
    set(DEPS_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}/_deps")
endif()

# Detect if this is a x64 or x86 build
microstrain_get_architecture(MSCL_ARCH_NAME)
if (${MSCL_ARCH_NAME} STREQUAL "x64")
    # This needs to be enabled to properly find OpenSSL for x64 builds
    set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
endif()

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

# Dependencies root/include paths (these are optional and will be downloaded if not set)

set(Boost_ROOT "" CACHE PATH "Location to search for the Boost libraries")
set(OPENSSL_ROOT_DIR "" CACHE PATH "Location to search for the OpenSSL libraries")
set(SWIG_ROOT "" CACHE PATH "Location to search for the Swig executable")
set(NaturalDocs_ROOT "" CACHE PATH "Location of Natural Docs used to generate the documentation")

if(UNIX AND NOT APPLE)
    set(DPKG_ROOT "" CACHE PATH "Location of the dpkg executable")
    set(RPMBUILD_ROOT "" CACHE PATH "Location of the rpmbuild executable")
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

# Custom variable used in this CMake file, not used by FindBoost.cmake
set(Boost_REQUESTED_VERSION "1.89.0" CACHE STRING "Requested version of Boost")
set(Boost_REQUESTED_COMPONENTS filesystem)

# Older versions of Boost require the system component
if(Boost_REQUESTED_VERSION VERSION_LESS_EQUAL 1.84.0)
    list(APPEND Boost_REQUESTED_COMPONENTS "system")
endif()

# Find the static version of boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

# Make sure both Boost root variables are set if only 1 of them has been set by the user
# Different versions of CMake uses one implementation over the other, this guarantees both ways are supported
if(NOT Boost_ROOT AND BOOST_ROOT)
    set(Boost_ROOT "${BOOST_ROOT}" CACHE PATH "Location to search for the Boost libraries" FORCE)
endif()

if(NOT BOOST_ROOT AND Boost_ROOT)
    set(BOOST_ROOT "${Boost_ROOT}")
endif()

# Attempt to find Boost before manually downloading it (this assumes Boost_ROOT was set by the user)
find_package(Boost ${Boost_REQUESTED_VERSION} COMPONENTS ${Boost_REQUESTED_COMPONENTS} CONFIG QUIET)

# Manually download and install Boost
if(NOT Boost_FOUND)
    # Replace the periods in the version with underscores for the URL
    string(REGEX REPLACE "([0-9])\\.([0-9])" "\\1_\\2" Boost_PACKAGE_VERSION "${Boost_REQUESTED_VERSION}")
    set(Boost_ARCHIVE_DIR "boost_${Boost_PACKAGE_VERSION}")

    set(Boost_ARCHIVE_URL "https://archives.boost.io/release/${Boost_REQUESTED_VERSION}")
    if(MSVC)
        string(APPEND Boost_ARCHIVE_URL "/binaries/${Boost_ARCHIVE_DIR}-bin-msvc-all-32-64.7z")
    else()
        string(APPEND Boost_ARCHIVE_URL "/source/${Boost_ARCHIVE_DIR}.tar.bz2")
    endif()

    microstrain_download_and_extract_archive(
        NAME "Boost"
        URL "${Boost_ARCHIVE_URL}"
        DEPS_BASE_DIR "${DEPS_BASE_DIR}"
        EXTRACTED_DIR "${Boost_ARCHIVE_DIR}"
    )

    if(UNIX)
        # TODO: Install Boost on Linux
    endif()

    # Boost_ROOT is required to include/find the Boost binaries
    set(Boost_ROOT "${DEPS_BASE_DIR}/${BOOST_ARCHIVE_DIR}" CACHE PATH "Location to search for the Boost libraries" FORCE)
    set(BOOST_ROOT "${Boost_ROOT}")
endif()

find_package(Boost ${Boost_REQUESTED_VERSION} REQUIRED COMPONENTS ${Boost_REQUESTED_COMPONENTS} CONFIG)

set(Boost_STATIC_LIBRARIES ${Boost_LIBRARIES})

# Find the shared version of boost
if(BUILD_SHARED_LIBS OR (UNIX AND MSCL_BUILD_PYTHON3) OR (UNIX AND MSCL_BUILD_PYTHON2))
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_STATIC_RUNTIME OFF)

    find_package(Boost ${Boost_REQUESTED_VERSION} REQUIRED COMPONENTS ${Boost_REQUESTED_COMPONENTS} CONFIG)

    set(Boost_SHARED_LIBRARIES ${Boost_LIBRARIES}) # Save the shared libraries, so they will not be overridden when we find the static libraries
endif()

# Find the threading library
find_package(Threads REQUIRED)

# If we were requested to build with SSL, find OpenSSL
if(MSCL_WITH_SSL)
    set(OPENSSL_REQUESTED_VERSION "1.1.0f" CACHE STRING "Requested version of OpenSSL")

    # For some reason, FindOpenSSL does not look for the libraries again, so unset the variables to force it to search again
    unset(OPENSSL_SSL_LIBRARY CACHE)
    unset(OPENSSL_LIBRARIES CACHE)
    unset(OPENSSL_CRYPTO_LIBRARY CACHE)
    unset(LIB_EAY_DEBUG CACHE)
    unset(LIB_EAY_RELEASE CACHE)
    unset(SSL_EAY_DEBUG CACHE)
    unset(SSL_EAY_RELEASE CACHE)

    # Attempt to find OpenSSL before manually downloading it (this assumes OPENSSL_ROOT_DIR was set by the user)
    find_package(OpenSSL QUIET)

    # Manually download and install OpenSSL
    if(NOT OPENSSL_FOUND)
        if(MSVC)
            if(MSVC_VERSION LESS 1900 OR MSVC_VERSION GREATER_EQUAL 1920)
                message(FATAL_ERROR "${PROJECT_NAME} is only compatible with MSVC 2015 and 2017")
            endif()

            if(MSVC_VERSION EQUAL 1900)
                set(SC_VS_VERSION 2015)
            elseif(MSVC_VERSION GREATER_EQUAL 1910 AND MSVC_VERSION LESS 1920)
                set(SC_VS_VERSION 2017)
            endif()
        endif()

        set(OPENSSL_ARCHIVE_DIR "openssl-${OPENSSL_REQUESTED_VERSION}-vs${SC_VS_VERSION}")
        microstrain_download_and_extract_archive(
            NAME "OpenSSL"
            URL "https://www.npcglib.org/~stathis/downloads/${OPENSSL_ARCHIVE_DIR}.7z"
            DEPS_BASE_DIR "${DEPS_BASE_DIR}"
            EXTRACTED_DIR "${OPENSSL_ARCHIVE_DIR}"
        )

        # OPENSSL_ROOT_DIR is required to include/find the OpenSSL binaries
        set(OPENSSL_ROOT_DIR "${DEPS_BASE_DIR}/${OPENSSL_ARCHIVE_DIR}/lib" CACHE PATH "Location to search for the OpenSSL libraries" FORCE)
        set(OPENSSL_INCLUDE_DIR "${DEPS_BASE_DIR}/${OPENSSL_ARCHIVE_DIR}/include")

        if(${MSCL_ARCH_NAME} STREQUAL "x64")
            string(APPEND OPENSSL_ROOT_DIR "64")
            string(APPEND OPENSSL_INCLUDE_DIR "64")
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

    # Shared OpenSSL
    if(BUILD_SHARED_LIBS)
        # For some reason, FindOpenSSL does not look for the libraries again, so unset the variables to force it to search again
        unset(OPENSSL_SSL_LIBRARY CACHE)
        unset(OPENSSL_LIBRARIES CACHE)
        unset(OPENSSL_CRYPTO_LIBRARY CACHE)
        unset(LIB_EAY_DEBUG CACHE)
        unset(LIB_EAY_RELEASE CACHE)
        unset(SSL_EAY_DEBUG CACHE)
        unset(SSL_EAY_RELEASE CACHE)

        set(OPENSSL_USE_STATIC_LIBS FALSE)
        set(OPENSSL_MSVC_STATIC_RT FALSE)
        find_package(OpenSSL REQUIRED)
        set(OPENSSL_SHARED_LIBRARIES ${OPENSSL_LIBRARIES})
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

    # Attempt to find Swig before manually downloading it (this assumes SWIG_ROOT was set by the user)
    find_package(SWIG ${SWIG_REQUESTED_VERSION} QUIET)

    # Set a default swig executable location and try again
    if(NOT SWIG_FOUND)
        set(SWIG_PACKAGE_NAME "swig")
        if(MSVC)
            string(APPEND SWIG_PACKAGE_NAME "win")
        endif()

        set(SWIG_ARCHIVE_DIR "${SWIG_PACKAGE_NAME}-${SWIG_REQUESTED_VERSION}")
        set(SWIG_ARCHIVE_URL "https://sourceforge.net/projects/swig/files/${SWIG_PACKAGE_NAME}/${SWIG_ARCHIVE_DIR}/${SWIG_ARCHIVE_DIR}")

        if(MSVC)
            string(APPEND SWIG_ARCHIVE_URL ".zip")
        else()
            string(APPEND SWIG_ARCHIVE_URL ".tar.gz")
        endif()

        microstrain_download_and_extract_archive(
            NAME "Swig"
            URL "${SWIG_ARCHIVE_URL}"
            DEPS_BASE_DIR "${DEPS_BASE_DIR}"
            EXTRACTED_DIR "${SWIG_ARCHIVE_DIR}"
        )

        set(SWIG_ROOT "${DEPS_BASE_DIR}/${SWIG_ARCHIVE_DIR}" CACHE PATH "Location to search for the Swig executable" FORCE)
    endif()

    find_package(SWIG ${SWIG_REQUESTED_VERSION} REQUIRED)
endif()

# If we were asked to build the docs, try to find NaturalDocs
if(MSCL_BUILD_DOCUMENTATION)
    set(NaturalDocs_NAME "NaturalDocs")

    # Attempt to find Natural Docs before manually downloading it (this assumes NaturalDocs_ROOT was set by the user)
    find_program(NaturalDocs_EXECUTABLE
        NAMES "${NaturalDocs_NAME}"
        PATHS "${NaturalDocs_ROOT}"
        DOC "Natural Docs command line client"
    )

    # Manually download and install Natural Docs
    if(NOT NaturalDocs_EXECUTABLE)
        set(NaturalDocs_REQUESTED_VERSION "2.3.1" CACHE STRING "Requested version of Natural Docs")
        set(NaturalDocs_ARCHIVE_DIR "Natural Docs")

        set(NaturalDocs_ARCHIVE_URL "https://naturaldocs.org/download/natural_docs/${NaturalDocs_REQUESTED_VERSION}/Natural_Docs_${NaturalDocs_REQUESTED_VERSION}.zip")

        microstrain_download_and_extract_archive(
            NAME "${NaturalDocs_NAME}"
            URL "${NaturalDocs_ARCHIVE_URL}"
            DEPS_BASE_DIR "${DEPS_BASE_DIR}"
            EXTRACTED_DIR "${NaturalDocs_ARCHIVE_DIR}"
        )

        # NaturalDocs_ROOT is required to find the Natural Docs program
        set(NaturalDocs_ROOT "${DEPS_BASE_DIR}/${NaturalDocs_ARCHIVE_DIR}" CACHE PATH "Location of Natural Docs used to generate the documentation" FORCE)
    endif()

    find_program(NaturalDocs_EXECUTABLE
        NAMES "${NaturalDocs_NAME}"
        PATHS "${NaturalDocs_ROOT}"
        DOC "Natural Docs command line client"
    )

    if(NOT NaturalDocs_EXECUTABLE)
        message(FATAL_ERROR "Unable to build docs as we were unable to find Natural Docs in ${NaturalDocs_ROOT}")
    else()
        message(STATUS "Found Natural Docs: ${NaturalDocs_EXECUTABLE}")
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
