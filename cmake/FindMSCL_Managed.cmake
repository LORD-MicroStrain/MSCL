# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindMSCL_Managed
-------

Finds the MSCL managed C# library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``MSCL_Managed::MSCL_Managed``
  The MSCL_Managed library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``MSCL_Managed_FOUND``
  True if the system has the MSCL library.
``MSCL_Managed_LIBRARIES``
  Libraries needed to link to MSCL.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``MSCL_Managed_ROOT_DIR``
  The directory containing the ``MSCL_Managed.dll`` and ``MSCL.dll`` files

#]=======================================================================]

# This variable can be overridden to point to a different location where MSCL is installed
if(NOT DEFINED MSCL_Managed_ROOT_DIR)
  set(MSCL_Managed_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/MSCL_Managed" CACHE STRING "Directory to search for MSCL Managed")
endif()

# Default to x64 if no platform is set
if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
  set(_MSCL_Managed_MSVC_ARCH_SUFFIX "x86")
else()
  set(_MSCL_Managed_MSVC_ARCH_SUFFIX "x64")
endif()

# The following directories are the common additional places to search for MSCL Managed
set(_MSCL_DEBUG_ROOT_DIRS
  "${CMAKE_CURRENT_LIST_DIR}/.."
  "${CMAKE_CURRENT_LIST_DIR}/../Output/DotNet/${_MSCL_Managed_MSVC_ARCH_SUFFIX}/Debug/MSCL_Managed"
  "${MSCL_Managed_ROOT_DIR}"
)

set(_MSCL_RELEASE_ROOT_DIRS
  "${CMAKE_CURRENT_LIST_DIR}/.."
  "${CMAKE_CURRENT_LIST_DIR}/../Output/DotNet/${_MSCL_Managed_MSVC_ARCH_SUFFIX}/Release/MSCL_Managed"
  "${MSCL_Managed_ROOT_DIR}"
)

# Find the MSCL Managed library and include directory
find_file(MSCL_Managed_RELEASE_LIBRARY_PATH
  NAMES MSCL_Managed.dll
  PATHS ${_MSCL_RELEASE_ROOT_DIRS}
)
find_file(MSCL_Managed_DEBUG_LIBRARY_PATH
  NAMES MSCL_Managed.dll
  PATHS ${_MSCL_DEBUG_ROOT_DIRS}
)

# Find the MSCL library and include directory
find_file(MSCL_Managed_RELEASE_INTERFACE_LIBRARY_PATH
  NAMES MSCL.dll
  PATHS ${_MSCL_RELEASE_ROOT_DIRS}
)
find_file(MSCL_Managed_DEBUG_INTERFACE_LIBRARY_PATH
  NAMES MSCL.dll
  PATHS ${_MSCL_DEBUG_ROOT_DIRS}
)

# Default to release versions of MSCL Managed
if(EXISTS ${MSCL_Managed_RELEASE_LIBRARY_PATH})
  set(MSCL_Managed_LIBRARY_PATH ${MSCL_Managed_RELEASE_LIBRARY_PATH})
elseif(EXISTS ${MSCL_Managed_DEBUG_LIBRARY_PATH})
  set(MSCL_Managed_LIBRARY_PATH ${MSCL_Managed_DEBUG_LIBRARY_PATH})
endif()

# Default to release versions of MSCL
if(EXISTS ${MSCL_Managed_RELEASE_INTERFACE_LIBRARY_PATH})
  set(MSCL_Managed_INTERFACE_LIBRARY_PATH ${MSCL_Managed_RELEASE_INTERFACE_LIBRARY_PATH})
elseif(EXISTS ${MSCL_Managed_DEBUG_INTERFACE_LIBRARY_PATH})
  set(MSCL_Managed_INTERFACE_LIBRARY_PATH ${MSCL_Managed_DEBUG_INTERFACE_LIBRARY_PATH})
endif()

set(MSCL_Managed_LIBRARY MSCL_Managed)

# Hand the rest off to find_package
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MSCL_Managed
  FOUND_VAR MSCL_Managed_FOUND
  REQUIRED_VARS
    MSCL_Managed_LIBRARY
    MSCL_Managed_LIBRARY_PATH
    MSCL_Managed_INTERFACE_LIBRARY_PATH
  VERSION_VAR MSCL_Managed_VERSION
)

# Append the dependencies to the list of MSCL libraries
set(MSCL_Managed_LIBRARIES "MSCL_Managed" CACHE STRING "Collection of libraries required to link MSCL Managed")
