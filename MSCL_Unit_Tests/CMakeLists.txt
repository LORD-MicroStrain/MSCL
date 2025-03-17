cmake_minimum_required(VERSION 3.16.0)
project(MSCL_Unit_Tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tests should just consist of compiling all source in this directory and linking against MSCL
file(GLOB SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)
add_executable(${PROJECT_NAME} ${SRC_FILES})

if(NOT "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    # NOTE: This section will only be called if this CMakeLists.txt is imported during the MSCL build.
    #       If not building in the MSCL repo, this can be safely ignored or removed
    set(MSCL_LIBRARY MSCL)
    set(MSCL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../MSCL/source")
    target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/MSCL/MSCL_Static/${CMAKE_CFG_INTDIR})
    add_dependencies(${PROJECT_NAME} MSCL_Static)
endif()

# Append to the module path so we can use the FindMSCL.cmake script
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
find_package(MSCL REQUIRED)

# Custom variable used in this CMake file, not used by FindBoost.cmake
set(Boost_REQUESTED_VERSION "1.68.0")
set(Boost_TEST_REQUESTED_COMPONENTS unit_test_framework test_exec_monitor)

# Find the static version of boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

# Disable CMake policy for Boost config find_package
# CMake 3.30+ uses Boost Config for Boost 1.70+
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

# Use the old FindBoost module to find the Boost directory
find_package(Boost ${Boost_REQUESTED_VERSION} REQUIRED COMPONENTS ${Boost_TEST_REQUESTED_COMPONENTS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MSCL_INCLUDE_DIRS}
    ${TURTLE_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${MSCL_LIBRARIES}
    ${Boost_LIBRARIES}
)

target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/stdafx.h")

# Don't let MSCL find it's own libraries
target_compile_definitions(${PROJECT_NAME} PRIVATE BOOST_ALL_NO_LIB)

# On windows, we need to set the runtime library to the same as MSCL
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        "/MT$<$<CONFIG:Debug>:d>"
        "/MP"
        "/bigobj"
    )

    # Ignore some annoying linker warnings
    target_link_options(${PROJECT_NAME} PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/ignore:4099>"
    )
endif()

# Mark the tests to run when the test target is run
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} --log_level=test_suite --report_level=no)
