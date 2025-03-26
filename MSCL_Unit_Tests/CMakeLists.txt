cmake_minimum_required(VERSION 3.16.0)
project(MSCL_Unit_Tests)

enable_testing()

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

target_precompile_headers(${PROJECT_NAME} PRIVATE "${MSCL_INCLUDE_DIR}/mscl/stdafx.h")

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
        "/ignore:4099"
    )
endif()

# Generate the list of test suites so each test result is output to the console
# Not elegant but it's easier to do this programmatically

set(TEST_SUITE_START_REGEX "BOOST_AUTO_TEST_SUITE\\(([^)]+)\\)")
set(TEST_FIXTURE_START_REGEX "BOOST_FIXTURE_TEST_SUITE\\(([^,]+), [^)]+\\)")
set(TEST_SUITE_CASE_REGEX "BOOST_AUTO_TEST_CASE\\(([^)]+)\\)*")
set(TEST_SUITE_END_REGEX "BOOST_AUTO_TEST_SUITE_END\\(\\)")

foreach(SOURCE IN LISTS SRC_FILES)
    file(STRINGS "${SOURCE}" FILE_CONTENT REGEX "^BOOST_*")

    unset(SUITE_NAMES)
    unset(SUITE_TREE_LIST)
    unset(SUITE_TREE_NAME)
    unset(RUN_TEST_PREFIX)

    foreach(LINE IN LISTS FILE_CONTENT)
        if("${LINE}" MATCHES "${TEST_SUITE_START_REGEX}" OR "${LINE}" MATCHES "${TEST_FIXTURE_START_REGEX}")
            if("${LINE}" MATCHES "${TEST_SUITE_START_REGEX}")
                string(REGEX REPLACE "${TEST_SUITE_START_REGEX}" "\\1" SUITE_NAME "${LINE}")
            else()
                string(REGEX REPLACE "${TEST_FIXTURE_START_REGEX}" "\\1" SUITE_NAME "${LINE}")
            endif()

            list(APPEND SUITE_TREE_LIST ${SUITE_NAME})

            if(NOT "${SUITE_TREE_NAME}" STREQUAL "")
                string(APPEND SUITE_TREE_NAME "-")
                string(APPEND RUN_TEST_PREFIX "/")
            endif()

            string(APPEND SUITE_TREE_NAME ${SUITE_NAME})
            string(APPEND RUN_TEST_PREFIX ${SUITE_NAME})
        elseif("${LINE}" MATCHES "${TEST_SUITE_CASE_REGEX}")
            string(REGEX REPLACE "${TEST_SUITE_CASE_REGEX}" "\\1" CASE_NAME "${LINE}")

            unset(TEST_NAME)
            unset(RUN_NAME)

            if(NOT "${SUITE_TREE_NAME}" STREQUAL "")
                set(TEST_NAME "${SUITE_TREE_NAME}-")
            endif()

            string(APPEND TEST_NAME ${CASE_NAME})

            if(NOT "${RUN_TEST_PREFIX}" STREQUAL "")
                set(RUN_NAME "${RUN_TEST_PREFIX}/")
            endif()

            string(APPEND RUN_NAME ${CASE_NAME})

            add_test(NAME "${TEST_NAME}" COMMAND ${PROJECT_NAME} --log_level=test_suite --report_level=no --run_test=${RUN_NAME})
        elseif("${LINE}" MATCHES "${TEST_SUITE_END_REGEX}")
            list(POP_BACK SUITE_TREE_LIST)

            unset(SUITE_TREE_NAME)
            unset(RUN_TEST_PREFIX)

            # Generate the new tree name
            foreach(TREE_NAME IN LISTS SUITE_TREE_LIST)
                if(NOT "${SUITE_TREE_NAME}" STREQUAL "")
                    string(APPEND SUITE_TREE_NAME "-")
                    string(APPEND RUN_TEST_PREFIX "/")
                endif()

                string(APPEND SUITE_TREE_NAME ${TREE_NAME})
                string(APPEND RUN_TEST_PREFIX ${TREE_NAME})
            endforeach()
        else()
            message(FATAL_ERROR "${LINE}")
        endif()
    endforeach()
endforeach()
