set(SWIG_ROOT "" CACHE PATH "Location to search for the Swig executable")
set(SWIG_REQUESTED_VERSION "4.0.0" CACHE STRING "Requested version of Swig")

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

# Set some CMake policies for Swig
if(POLICY CMP0078)
    cmake_policy(SET CMP0078 NEW)
endif()

if(POLICY CMP0086)
    cmake_policy(SET CMP0086 NEW)
endif()

# Build the C# bindings
if(MSCL_BUILD_CSHARP)
    if(POLICY CMP0122)
        cmake_policy(SET CMP0122 NEW)
    endif()

    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/CSharp")
endif()

# Build the Python 2 bindings
if(MSCL_BUILD_PYTHON2)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Python2")
endif()

# Build the Python 3 bindings
if(MSCL_BUILD_PYTHON3)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Python3")
endif()
