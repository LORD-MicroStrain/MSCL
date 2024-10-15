cmake_minimum_required(VERSION 3.16.0)
project(MSCL LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Supported configuration types" FORCE)

# Append the custom CMake directory so the files can be imported
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Set some global C++ options
set(CMAKE_CXX_STANDARD 11)

# If a build type was not specified, default to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# Detect if this is a x64 or x86 build
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(MSCL_X64 ON)
  set(MSCL_ARCH_NAME "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(MSCL_X86 ON)
  set(MSCL_ARCH_NAME "x86")
endif()

# This will make windows create a .lib file with all the symbols of the .dll files exported
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Parse some flags
# These are all ON/OFF flags. For example, -DBUILD_SHARED_LIBS="ON"
option(BUILD_SHARED_LIBS "Whether or not to build the shared version of the library." OFF)
option(WITH_SSL "Whether or not to compile the library with SSL support" ON)
option(WITH_WEBSOCKETS "Whether or not to compile the library with Websocket support" ON)
option(BUILD_PYTHON2 "Whether to build the python 2 bindings." OFF)
option(BUILD_PYTHON3 "Whether to build the python 3 bindings." OFF)
option(BUILD_TESTS "Whether to build the unit tests." OFF)
option(BUILD_EXAMPLES "Whether to build the examples." OFF)

if(WIN32)
  option(BUILD_CSHARP "Whether to build the C# bindings. Only supported on Windows" OFF)
  option(BUILD_DOCUMENTATION "Whether to build the documentation" OFF)
elseif(UNIX)
  option(LINK_STATIC_DEPS "Whether to link the dependencies statically. Please note that this means that OpenSSL and boost must be built with -fPIC" OFF)
  option(BUILD_PACKAGE "Whether to build a package from the resulting binaries" OFF)
endif()

# Allow the user to override the location where most dependencies are installed on Windows
if(WIN32)
  if(DEFINED ENV{LIB_PATH})
    set(MICROSTRAIN_LIB_DIR "$ENV{LIB_PATH}" CACHE STRING "Directory where most dependencies are installed")
  else()
    set(MICROSTRAIN_LIB_DIR "C:/lib" CACHE STRING "Directory where most dependencies are installed")
  endif()
endif()

# These flags can be passed string values. For example, -DOPENSSL_ROOT_DIR="/usr/lib"
# Different default search paths for windows
set(Boost_REQUESTED_VERSION "1.68.0" CACHE INTERNAL "Required version of boost")

if(WIN32)
  string(REPLACE "." "_" Boost_REQUESTED_VERSION_UNDERSCORE ${Boost_REQUESTED_VERSION})
  set(DEFAULT_BOOST_ROOT "${MICROSTRAIN_LIB_DIR}/boost")
  if(MSCL_X64)
    set(DEFAULT_OPENSSL_ROOT_DIR "${MICROSTRAIN_LIB_DIR}/openssl/lib64")
  elseif(MSCL_X86)
    set(DEFAULT_OPENSSL_ROOT_DIR "${MICROSTRAIN_LIB_DIR}/openssl/lib")
  endif()
  set(DEFAULT_SWIG_ROOT "${MICROSTRAIN_LIB_DIR}/swig/swigwin-4.0.0")
endif()

set(TURTLE_INCLUDE_DIR "${MICROSTRAIN_LIB_DIR}/turtle/include" CACHE STRING "Location to search for the turtle include files. Only used when building tests")
set(NATURAL_DOCS_ROOT "${MICROSTRAIN_LIB_DIR}/NaturalDocs" CACHE STRING "Location of NaturalDocs used to generate the documentation")

if(UNIX AND NOT APPLE)
  set(DPKG_ROOT "" CACHE STRING "Location of the dpkg executable")
  set(RPMBUILD_ROOT "" CACHE STRING "Location of the rpmbuild executable")
endif()

# Use Git to find the version of this repo
find_package(Git)
set(DEFAULT_MSCL_GIT_VERSION "v0.0.0")
if(NOT GIT_FOUND)
  message(WARNING "Unable to find git, will build with unknown version")
  set(MSCL_GIT_VERSION ${DEFAULT_MSCL_GIT_VERSION})
else()
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E env ${GIT_EXECUTABLE} describe --tags
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE MSCL_GIT_VERSION_OUT
    ERROR_VARIABLE MSCL_GIT_VERSION_ERR
    RESULT_VARIABLE MSCL_GIT_VERSION_RET
  )
  if(NOT ${MSCL_GIT_VERSION_RET} EQUAL 0)
    message(WARNING "Unable to determine version from Git, defaulting to version ${DEFAULT_MSCL_GIT_VERSION}")
    set(MSCL_GIT_VERSION ${DEFAULT_MSCL_GIT_VERSION})
  else()
    set(MSCL_GIT_VERSION ${MSCL_GIT_VERSION_OUT})
    string(REGEX REPLACE "\n" "" MSCL_GIT_VERSION "${MSCL_GIT_VERSION}")
    message(STATUS "MSCL Version: ${MSCL_GIT_VERSION}")
  endif()
endif()

# Make the Output directory which is where we will copy all of the build artifacts on a successful build
set(MSCL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Output)
file(MAKE_DIRECTORY ${MSCL_OUTPUT_DIR})

# Setup a phony target that will zip up all the artifacts
set(MSCL_ZIP_TARGET Zip)
add_custom_target(${MSCL_ZIP_TARGET})
set_property(TARGET ${MSCL_ZIP_TARGET} PROPERTY EXCLUDE_FROM_ALL ON)

if(MSVC)
  # Parallel build options for Windows
  add_compile_options(/MP)

  # Ignore warnings from the linker when it can't find a pdb file
  add_link_options(/ignore:4099)
endif()

# On Windows, add a few flags for compatibility with the old solution files
if(WIN32)
  add_compile_definitions(
    WIN32
    _WINDOWS
    _USRDLL
    NOMINMAX
    _WIN32_WINNT=0x0501
  )
endif()

# Don't let boost figure out the libraries to link
add_compile_definitions(BOOST_ALL_NO_LIB)

# Custom variable used in this CMake file, not used by FindBoost.cmake
set(Boost_REQUESTED_COMPONENTS system filesystem)

# Setup the boost root variable
if(NOT DEFINED Boost_ROOT)
  set(Boost_ROOT "${DEFAULT_BOOST_ROOT}")
endif()

# Find the static version of boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost ${Boost_REQUESTED_VERSION} EXACT REQUIRED COMPONENTS ${Boost_REQUESTED_COMPONENTS})
set(Boost_STATIC_LIBRARIES ${Boost_LIBRARIES})
message(STATUS "Boost_STATIC_LIBRARIES: " ${Boost_LIBRARIES})

# Optionally find some boost testing libraries
if(BUILD_TESTS)
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_STATIC_RUNTIME ON)
  find_package(Boost ${Boost_REQUESTED_VERSION} EXACT REQUIRED COMPONENTS unit_test_framework test_exec_monitor)
  set(Boost_TEST_LIBRARIES ${Boost_LIBRARIES})
endif()

# Find the shared version of boost
if(BUILD_SHARED_LIBS OR (UNIX AND BUILD_PYTHON3) OR (UNIX AND BUILD_PYTHON2))
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_STATIC_RUNTIME OFF)
  find_package(Boost ${Boost_REQUESTED_VERSION} EXACT REQUIRED COMPONENTS ${Boost_REQUESTED_COMPONENTS})
  set(Boost_SHARED_LIBRARIES ${Boost_LIBRARIES})  # Save the shared libraries, so they will not be overridden when we find the static libraries
endif()

# Find the threading library
find_package(Threads REQUIRED)

# If we were requested to build with SSL, find OpenSSL
if(WITH_SSL)
  # Ultra mega hack since we are finding the lib path of OpenSSL, we need to manually set the include path...
  if(NOT DEFINED OPENSSL_ROOT_DIR)
    set(OPENSSL_ROOT_DIR "${DEFAULT_OPENSSL_ROOT_DIR}")
    if(MSCL_X64)
      set(OPENSSL_INCLUDE_DIR ${DEFAULT_OPENSSL_ROOT_DIR}/../include64 CACHE INTERNAL "")
    elseif(MSCL_X86)
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
if(BUILD_PYTHON3)
  set(Python3_USE_STATIC_LIBS OFF)
  find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
endif()
if(BUILD_PYTHON2)
  set(Python2_USE_STATIC_LIBS OFF)
  find_package(Python2 REQUIRED COMPONENTS Interpreter Development)
endif()
if(BUILD_CSHARP)
  enable_language(CSharp)
endif()

if(BUILD_PYTHON2 OR BUILD_PYTHON3 OR BUILD_CSHARP)
  # Make sure we can find swig
  cmake_policy(SET CMP0078 NEW)
  cmake_policy(SET CMP0086 NEW)
  if(BUILD_CSHARP AND WIN32)
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
if(BUILD_DOCUMENTATION)
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
if(BUILD_PACKAGE AND UNIX AND NOT APPLE)
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

# Add the underlying CMake files
add_subdirectory(MSCL)
if(BUILD_EXAMPLES)
  add_subdirectory(MSCL_Examples)

  # Also copy the test source and build files to the output directory so it can be compressed
  set(MSCL_EXAMPLES_OUTPUT_DIR "${MSCL_OUTPUT_DIR}/Examples")
  add_custom_target(MSCL_Examples_Copy
    ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${MSCL_EXAMPLES_OUTPUT_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory ${MSCL_EXAMPLES_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindMSCL.cmake ${MSCL_EXAMPLES_OUTPUT_DIR}/cmake/FindMSCL.cmake
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindMSCL_Managed.cmake ${MSCL_EXAMPLES_OUTPUT_DIR}/cmake/FindMSCL_Managed.cmake
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/MSCL_Examples ${MSCL_EXAMPLES_OUTPUT_DIR}/MSCL_Examples
  )

  # Zip up the examples
  add_custom_target(MSCL_Examples_Zip
    WORKING_DIRECTORY ${MSCL_OUTPUT_DIR}
    DEPENDS MSCL_Examples_Copy
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${MSCL_OUTPUT_DIR}/mscl_${MSCL_GIT_VERSION}_Examples.zip" --format=zip "Examples"
  )
  add_dependencies(${MSCL_ZIP_TARGET} MSCL_Examples_Zip)
endif()
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(MSCL_Unit_Tests)
endif()
