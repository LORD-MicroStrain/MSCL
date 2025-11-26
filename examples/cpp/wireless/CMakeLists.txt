cmake_minimum_required(VERSION 3.16)

project("MSCL-Cpp-Wireless-Example"
    VERSION "1.0.0"
    DESCRIPTION "Simple wireless example using C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: Set MSCL_ROOT_DIR if building as a standalone project
if(DEFINED MSCL_ROOT_DIR OR DEFINED CACHE{MSCL_ROOT_DIR})
    set(_MSCL_ROOT_DIR "${MSCL_ROOT_DIR}")
elseif(DEFINED ENV{MSCL_ROOT_DIR})
    set(_MSCL_ROOT_DIR "$ENV{MSCL_ROOT_DIR}")
else()
    set(_MSCL_ROOT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
endif()

# We need to find MSCL in a standalone project
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_LIST_DIR})
    list(APPEND CMAKE_PREFIX_PATH "${_MSCL_ROOT_DIR}")

    find_package("MSCL" REQUIRED CONFIG)
endif()

# Make sure the MSCL libraries are found
if(NOT DEFINED CACHE{MSCL_LIBRARIES} AND NOT DEFINED MSCL_LIBRARIES)
    message(FATAL_ERROR "Could not find the required MSCL libraries.")
endif()

set(EXAMPLE_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)

# Create the example
add_executable(${PROJECT_NAME}
    ${EXAMPLE_SOURCES}
)

# Configure the project in an examples sub-folder for IDEs that support it
if(NOT ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_LIST_DIR})
    file(RELATIVE_PATH PROJECT_RELATIVE_PATH "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}/..")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        FOLDER "${PROJECT_RELATIVE_PATH}"
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${MSCL_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${MSCL_INCLUDE_DIRS}
)

# Precompiled headers are needed for the MSCL source code
# Alternatively, the 'mscl.h' header can be included instead of individual MSCL headers
target_precompile_headers(${PROJECT_NAME} PRIVATE
    "${MSCL_INCLUDE_DIR}/mscl/stdafx.h"
)

if(MSVC)
    set(COMPILE_OPTIONS
        "/W4" # Enable warnings
        "/WX" # Warnings as errors
        "/MP" # Multi-process compilation
    )
else()
    set(COMPILE_OPTIONS
        "-Wall"   # Enable warnings
        "-Wextra" # Enable extra warnings
        "-Werror" # Warnings as errors
    )
endif()

target_compile_options(${PROJECT_NAME} PRIVATE
    ${COMPILE_OPTIONS}
)

# Package the example (this can be removed for a standalone example)
# This is for the entire MSCL source project to package the example for distribution
if(CMAKE_PROJECT_NAME STREQUAL "MSCL" AND MSCL_BUILD_PACKAGE)
    # Keep the same directory structure for installation
    file(RELATIVE_PATH EXAMPLES_INSTALL_DIR ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
    install(
        FILES
            "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt"
            ${EXAMPLE_SOURCES}
        DESTINATION "${EXAMPLES_INSTALL_DIR}"
        # No need to package this for multiple configurations since it's a file installation
        CONFIGURATIONS "Release"
        COMPONENT "${MSCL_EXAMPLES_CPP_COMPONENT_NAME}"
    )
endif()
