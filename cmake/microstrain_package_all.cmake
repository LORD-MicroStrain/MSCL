# This file is meant for single-config generators to package both debug and
# release builds in a single package. It will not work for multi-config
# generators like 'Visual Studio' or 'Ninja Multi-Config'
#
# This requires setting both MICROSTRAIN_BUILD_DIR_DEBUG and
# MICROSTRAIN_BUILD_DIR_RELEASE to find the CPackConfig.cmake files for each
# configuration
#
# Optionally, if the CPackConfig.cmake file has a custom name,
# MICROSTRAIN_CPACK_CONFIG_FILENAME can be defined with the filename
#
# This script will combine the install projects from those 2 files to create a
# combined package
#
# Usage: cpack --config microstrain_package_all.cmake -D MICROSTRAIN_BUILD_DIR_DEBUG:PATH=<DEBUG_DIR> -D MICROSTRAIN_BUILD_DIR_RELEASE:PATH=<RELEASE_DIR>
#

# Allow overriding the CPack config file name
if(NOT MICROSTRAIN_CPACK_CONFIG_FILENAME)
    set(MICROSTRAIN_CPACK_CONFIG_FILENAME "CPackConfig.cmake")
endif()

# Make sure the debug build directory exists
if(NOT EXISTS "${MICROSTRAIN_BUILD_DIR_DEBUG}")
    message(FATAL_ERROR "MICROSTRAIN_BUILD_DIR_DEBUG is required to be set to package both Debug and Release")
endif()

# Make sure the debug package config file exists
set(MICROSTRAIN_CPACK_CONFIG_DEBUG "${MICROSTRAIN_BUILD_DIR_DEBUG}/${MICROSTRAIN_CPACK_CONFIG_FILENAME}")
if(NOT EXISTS "${MICROSTRAIN_CPACK_CONFIG_DEBUG}")
    message(FATAL_ERROR "The debug build config file '${MICROSTRAIN_CPACK_CONFIG_DEBUG}' does not exist in '${MICROSTRAIN_BUILD_DIR_DEBUG}'")
endif()

# Include the debug version of the packaging file
include("${MICROSTRAIN_CPACK_CONFIG_DEBUG}")

# Get the debug install projects
set(MICROSTRAIN_CPACK_INSTALL_PROJECT_DEBUG ${CPACK_INSTALL_CMAKE_PROJECTS})

# Make sure the release build directory exists
if(NOT EXISTS "${MICROSTRAIN_BUILD_DIR_RELEASE}")
    message(FATAL_ERROR "MICROSTRAIN_BUILD_DIR_RELEASE is required to be set to package both Debug and Release")
endif()

# Make sure the release package config file exists
set(MICROSTRAIN_CPACK_CONFIG_RELEASE "${MICROSTRAIN_BUILD_DIR_RELEASE}/${MICROSTRAIN_CPACK_CONFIG_FILENAME}")
if(NOT EXISTS "${MICROSTRAIN_CPACK_CONFIG_RELEASE}")
    message(FATAL_ERROR "The release build config file '${MICROSTRAIN_CPACK_CONFIG_RELEASE}' does not exist in '${MICROSTRAIN_BUILD_DIR_RELEASE}'")
endif()

# Include the release version of the packaging file
# Since release takes precedence for packaging, this will also be the setup for the entire CPack process
include("${MICROSTRAIN_CPACK_CONFIG_RELEASE}")

# Add the debug projects for proper combined packaging of release and debug
list(APPEND CPACK_INSTALL_CMAKE_PROJECTS
    ${MICROSTRAIN_CPACK_INSTALL_PROJECT_DEBUG}
)
