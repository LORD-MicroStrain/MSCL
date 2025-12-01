cmake_minimum_required(VERSION 3.16)

project("MSCL-CSharp-Displacement-Example"
    VERSION "1.0.0"
    DESCRIPTION "Simple displacement example using C#"
    LANGUAGES CSharp
)

# TODO: Set MSCL_MANAGED_ROOT_DIR if building as a standalone project
if(DEFINED MSCL_MANAGED_ROOT_DIR OR DEFINED CACHE{MSCL_MANAGED_ROOT_DIR})
    set(_MSCL_MANAGED_ROOT_DIR "${MSCL_MANAGED_ROOT_DIR}")
elseif(DEFINED ENV{MSCL_MANAGED_ROOT_DIR})
    set(_MSCL_MANAGED_ROOT_DIR "$ENV{MSCL_MANAGED_ROOT_DIR}")
else()
    set(_MSCL_MANAGED_ROOT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
endif()

# We need to find MSCL_Managed in a standalone project
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}")
    list(APPEND CMAKE_PREFIX_PATH "${_MSCL_MANAGED_ROOT_DIR}")

    find_package("MSCL_Managed" REQUIRED CONFIG)
endif()

# Create the example
add_executable("${PROJECT_NAME}"
    "${CMAKE_CURRENT_LIST_DIR}/Program.cs"
)

# Configure the project in an examples sub-folder for IDEs that support it
if(NOT "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}")
    file(RELATIVE_PATH PROJECT_RELATIVE_PATH "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}/..")
    set_target_properties("${PROJECT_NAME}" PROPERTIES
        FOLDER "${PROJECT_RELATIVE_PATH}"
    )
endif()

# This function exists as part of the find_package module for MSCL_Managed
# The parameter needs to be the target to add the MSCL references to
# If this is not used, MSCL_Managed.dll and MSCL.dll need to be in the output
# directory of the application at runtime
mscl_managed_add_references("${PROJECT_NAME}")
