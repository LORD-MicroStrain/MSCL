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

# Include the Swig module after finding Swig
include(UseSWIG)

# The exceptions interface is included in the main interface like a C++ header
# It is not needed to be included in this list
set(SWIG_SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/MSCL_Main_Interface.i"
)

# Tell Swig to generate files in module specific directories in the current binary directory
set(UseSWIG_MODULE_VERSION 2)

set(MSCL_SWIG_INTERFACE_LIB ${PROJECT_NAME}_Swig_Interface)
add_library("${MSCL_SWIG_INTERFACE_LIB}" INTERFACE EXCLUDE_FROM_ALL)

target_link_libraries("${MSCL_SWIG_INTERFACE_LIB}" INTERFACE
    "${MSCL_LIBRARY}"
)

if(MSVC)
    target_compile_options("${MSCL_SWIG_INTERFACE_LIB}" INTERFACE
        "/MP"
        "/bigobj"
    )
else()
    # Make sure Linux compiles static libraries with -fPIC
    set_target_properties("${MSCL_SWIG_INTERFACE_LIB}" PROPERTIES
        POSITION_INDEPENDENT_CODE TRUE
    )
endif()

# Build the C# bindings
if(MSCL_BUILD_CSHARP)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/csharp")
endif()

# Build the Python 2 bindings
if(MSCL_BUILD_PYTHON2)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/python2")
endif()

# Build the Python 3 bindings
if(MSCL_BUILD_PYTHON3)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/python3")
endif()
