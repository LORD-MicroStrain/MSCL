# Python users typically don't need the debug builds
# This also allows for proper packaging when requesting both Debug and Release builds in the same package
# but Python might not be included with Debug files
option(MSCL_PACKAGE_PYTHON_DEBUG "Include the debug package of Python builds" OFF)

# Add all the requested versions of Python2 to a list for project creation
if(MSCL_BUILD_PYTHON2)
    # Allow the user to request a certain version of Python2
    # If using a version not supported by the build system then the user must have the requested version installed already
    set(MSCL_PYTHON2_REQUESTED_VERSION "2.7" CACHE STRING "The requested version of Python2 to use for bindings")

    # List of supported Python2 versions
    set(MSCL_SUPPORTED_PYTHON2_VERSIONS
        "2.7"
    )

    # Add only the requested version or all supported versions of Python2 to be built
    if("${MSCL_PYTHON2_REQUESTED_VERSION}" STREQUAL "")
        list(APPEND MSCL_PYTHON_BUILD_VERSIONS ${MSCL_SUPPORTED_PYTHON2_VERSIONS})
    else()
        list(APPEND MSCL_PYTHON_BUILD_VERSIONS "${MSCL_PYTHON2_REQUESTED_VERSION}")
    endif()
endif()

# Add all the requested versions of Python3 to a list for project creation
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
        list(APPEND MSCL_PYTHON_BUILD_VERSIONS ${MSCL_SUPPORTED_PYTHON3_VERSIONS})
    else()
        list(APPEND MSCL_PYTHON_BUILD_VERSIONS "${MSCL_PYTHON3_REQUESTED_VERSION}")
    endif()
endif()

# Use the requested versions in the examples
set(MSCL_PYTHON_REQUESTED_VERSIONS ${MSCL_PYTHON_BUILD_VERSIONS} CACHE INTERNAL "")

# Include the Swig Python utilities file for easier binding configuration
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(mscl_swig_python_utilities)

# Create all of the requested Python targets
foreach(MSCL_PYTHON_REQUESTED_VERSION IN LISTS MSCL_PYTHON_REQUESTED_VERSIONS)
    # Validate the requested versions of Python are supported for download
    string(REGEX MATCH "^([23]).[0-9][0-9]?" MSCL_PYTHON_VERSION "${MSCL_PYTHON_REQUESTED_VERSION}")
    if(NOT MSCL_PYTHON_VERSION)
        message(FATAL_ERROR "Invalid Python version request '${MSCL_PYTHON_REQUESTED_VERSION}'. Valid syntax is x.x or x.x.x")
    endif()

    # Get the Python major version
    string(REGEX MATCH "^[23]" MSCL_PYTHON_MAJOR_VERSION "${CMAKE_MATCH_1}")

    list(FIND MSCL_SUPPORTED_PYTHON${MSCL_PYTHON_MAJOR_VERSION}_VERSIONS "${MSCL_PYTHON_VERSION}" MSCL_PYTHON_VERSION_SUPPORTED)

    # The requested version is supported and should be downloaded
    if(MSCL_PYTHON_VERSION_SUPPORTED GREATER_EQUAL 0 AND MSCL_DOWNLOAD_PYTHON${MSCL_PYTHON_MAJOR_VERSION})
        if("${MSCL_PYTHON_MAJOR_VERSION}" STREQUAL "2")
            message(WARNING "Python2 is end-of-life and will need to be installed manually")
        else()
            mscl_download_python("${MSCL_PYTHON_VERSION}" "${MSCL_PYTHON_MAJOR_VERSION}")
        endif()
    endif()

    # Create the Python binding library for the requested version of Python
    mscl_add_swig_python_module_library("${MSCL_PYTHON_VERSION}" "${MSCL_PYTHON_MAJOR_VERSION}")
endforeach()

if(MSCL_PYTHON2_ALL_TARGETS)
    # Create the Python2 All target
    set(MSCL_PYTHON2_ALL_TARGET "${PROJECT_NAME}-Python2")
    add_custom_target(${MSCL_PYTHON2_ALL_TARGET})

    # Add all the requested Python2 targets to the All target
    foreach(MSCL_PYTHON2_TARGET IN LISTS MSCL_PYTHON2_ALL_TARGETS)
        add_dependencies(${MSCL_PYTHON2_ALL_TARGET} ${MSCL_PYTHON2_TARGET})
    endforeach()
endif()

if(MSCL_PYTHON3_ALL_TARGETS)
    # Create the Python3 All target
    set(MSCL_PYTHON3_ALL_TARGET "${PROJECT_NAME}-Python3")
    add_custom_target(${MSCL_PYTHON3_ALL_TARGET})

    # Add all the requested Python3 targets to the All target
    foreach(MSCL_PYTHON3_TARGET IN LISTS MSCL_PYTHON3_ALL_TARGETS)
        add_dependencies(${MSCL_PYTHON3_ALL_TARGET} ${MSCL_PYTHON3_TARGET})
    endforeach()
endif()
