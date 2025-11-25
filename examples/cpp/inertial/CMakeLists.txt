cmake_minimum_required(VERSION 3.18)

project("MSCL_Example_Inertial_CPP"
    VERSION ""
    DESCRIPTION ""
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

    find_package(MSCL REQUIRED CONFIG)
endif()

# Make sure the MIP libraries are found
if(NOT DEFINED CACHE{MSCL_LIBRARIES} AND NOT DEFINED MSCL_LIBRARIES)
    message(FATAL_ERROR "Could not find the required MSCL libraries.")
endif()

# Create the example
add_executable(${PROJECT_NAME}
    "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)

# Configure the project in an examples sub-folder for IDEs that support it
if(NOT ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_LIST_DIR})
    file(RELATIVE_PATH PROJECT_RELATIVE_PATH "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}/..")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        FOLDER "${PROJECT_RELATIVE_PATH}"
    )
endif()

# Append to the module path so we can use the FindMSCL.cmake script
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../cmake")

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MSCL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${MSCL_LIBRARIES}
)

if(MSVC)
    # On windows, we need to set the runtime library to the same as MSCL
    target_compile_options(${PROJECT_NAME} PRIVATE
        /MT$<$<CONFIG:Debug>:d>
        /MP
    )
endif()
