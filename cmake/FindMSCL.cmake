# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindMSCL
-------

Finds the MSCL library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``MSCL::MSCL``
  The MSCL library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``MSCL_FOUND``
  True if the system has the MSCL library.
``MSCL_INCLUDE_DIRS``
  Include directories needed to use MSCL.
``MSCL_LIBRARIES``
  Libraries needed to link to MSCL.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``MSCL_ROOT_DIR``
  The directory containing the ``include`` directory and ``lib`` directory
``MSCL_INCLUDE_DIR``
  The directory containing ``mscl.h``.
``MSCL_LIBRARY``
  The path to the MSCL library.

#]=======================================================================]

# This variable can be overridden to point to a different location where MSCL is installed
if(NOT MSCL_ROOT_DIR)
  set(MSCL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/MSCL" CACHE STRING "Directory to search for MSCL")
endif()

# The following directories are the common additional places to search for MSCL
set(_MSCL_ROOT_DIRS 
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${MSCL_ROOT_DIR}
)
foreach(_MSCL_ROOT_DIR IN LISTS _MSCL_ROOT_DIRS)
  list(APPEND _MSCL_INCLUDE_DIRS "${_MSCL_ROOT_DIR}/include")
  list(APPEND _MSCL_LIBRARY_DIRS "${_MSCL_ROOT_DIR}/lib")
endforeach()

# Find the MSCL library and include directory
find_path(MSCL_INCLUDE_DIR
  NAMES mscl/mscl.h
  PATHS ${_MSCL_INCLUDE_DIRS}
)
find_library(MSCL_LIBRARY
  NAMES MSCL mscl
  PATHS ${_MSCL_LIBRARY_DIRS}
)

# Also find the dependencies for MSCL
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.68.0 REQUIRED COMPONENTS system filesystem)

# We also need to find OpenSSL
set(OPENSSL_USE_STATIC_LIBS TRUE)
set(OPENSSL_MSVC_STATIC_RT TRUE)
find_package(OpenSSL REQUIRED)
set(MSCL_OPENSSL_LIBRARIES ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})

# If linking on Windows, we will also need the windows crypto library
if(WIN32)
  list(APPEND MSCL_OPENSSL_LIBRARIES CRYPT32.lib)
endif()

# Find the threading library
find_package(Threads REQUIRED)

# Hand the rest off to find_package
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MSCL
  FOUND_VAR MSCL_FOUND
  REQUIRED_VARS
    MSCL_LIBRARY
    MSCL_INCLUDE_DIR
  VERSION_VAR MSCL_VERSION
)

# Append the dependencies to the list of MSCL libraries
set(MSCL_INCLUDE_DIRS "" CACHE STRING "Collection of directories needed to include")
set(MSCL_LIBRARIES "" CACHE STRING "Collection of libraries required to link MSCL")
list(APPEND MSCL_INCLUDE_DIRS ${MSCL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
list(APPEND MSCL_LIBRARIES ${MSCL_LIBRARY} ${Boost_LIBRARIES} ${MSCL_OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# If on linux, we also need to link against libdl
if(UNIX)
  list(APPEND MSCL_LIBRARIES dl)

  # Determine the flavor of linux we are running on, as different flavors require different libraries
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E env bash -c "awk -F= '/^ID=/{print $2}' /etc/os-release |tr -d '\n' | tr -d '\"'"
    COMMAND_ERROR_IS_FATAL ANY
    OUTPUT_VARIABLE _MSCL_LINUX_FLAVOR
  )
  if("${_MSCL_LINUX_FLAVOR}" STREQUAL "centos")
    list(APPEND MSCL_LIBRARIES z krb5 k5crypto)
  endif()
endif()
