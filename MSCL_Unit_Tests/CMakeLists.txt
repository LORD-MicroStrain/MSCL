cmake_minimum_required(VERSION 3.18)
project(MSCL_Unit_Tests)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_ROOT "" CACHE PATH "Location to search for the Boost libraries")
set(Turtle_ROOT "" CACHE PATH "Location to search for the Boost Turtle headers")

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

# Include some utilities used for MicroStrain projects
include(microstrain_utilities)

# Create the common dependencies directory in the project root (if not already created from the MSCL root project)
if(NOT DEPS_BASE_DIR)
    set(DEPS_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/_deps")
endif()

find_package(MSCL REQUIRED)

# Custom variable used in this CMake file, not used by FindBoost.cmake
set(Boost_REQUESTED_VERSION "1.89.0" CACHE STRING "Requested version of Boost")
set(Boost_TEST_REQUESTED_COMPONENTS unit_test_framework test_exec_monitor)

# Find the static version of boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

# Make sure both Boost root variables are set if only 1 of them has been set by the user
# Different versions of CMake uses one implementation over the other, this guarantees both ways are supported
if(NOT Boost_ROOT AND BOOST_ROOT)
    set(Boost_ROOT "${BOOST_ROOT}" CACHE PATH "Location to search for the Boost libraries" FORCE)
endif()

if(NOT BOOST_ROOT AND Boost_ROOT)
    set(BOOST_ROOT "${Boost_ROOT}")
endif()

# Attempt to find Boost before manually downloading it (this assumes Boost_ROOT was set by the user)
find_package(Boost ${Boost_REQUESTED_VERSION} COMPONENTS ${Boost_TEST_REQUESTED_COMPONENTS} CONFIG QUIET)

# Manually download and install Boost
if(NOT Boost_FOUND)
    # Replace the periods in the version with underscores for the URL
    string(REGEX REPLACE "([0-9])\\.([0-9])" "\\1_\\2" Boost_PACKAGE_VERSION "${Boost_REQUESTED_VERSION}")
    set(Boost_ARCHIVE_DIR "boost_${Boost_PACKAGE_VERSION}")

    set(Boost_ARCHIVE_URL "https://archives.boost.io/release/${Boost_REQUESTED_VERSION}")
    if(MSVC)
        string(APPEND Boost_ARCHIVE_URL "/binaries/${Boost_ARCHIVE_DIR}-bin-msvc-all-32-64.7z")
    else()
        string(APPEND Boost_ARCHIVE_URL "/source/${Boost_ARCHIVE_DIR}.tar.bz2")
    endif()

    microstrain_download_and_extract_archive(
        NAME "Boost"
        URL "${Boost_ARCHIVE_URL}"
        DEPS_BASE_DIR "${DEPS_BASE_DIR}"
        EXTRACTED_DIR "${Boost_ARCHIVE_DIR}"
    )

    if(UNIX)
        # TODO: Install Boost on Linux
    endif()

    # Boost_ROOT is required to include/find the Boost binaries
    set(Boost_ROOT "${DEPS_BASE_DIR}/${BOOST_ARCHIVE_DIR}" CACHE PATH "Location to search for the Boost libraries" FORCE)
    set(BOOST_ROOT "${Boost_ROOT}")
endif()

find_package(Boost ${Boost_REQUESTED_VERSION} REQUIRED COMPONENTS ${Boost_TEST_REQUESTED_COMPONENTS} CONFIG)

# Common header in the Turtle library used to find the include directory
set(Turtle_MOCK_HEADER "mock.hpp")
set(Turtle_PATH_SUFFIXES
    "include/turtle"
    "turtle"
)

# Attempt to find Turtle include directory before manually downloading it (this assumes Turtle_ROOT was set by the user)
find_path(Turtle_INCLUDE_DIR
    NAMES "${Turtle_MOCK_HEADER}"
    PATHS "${Turtle_ROOT}"
    PATH_SUFFIXES ${Turtle_PATH_SUFFIXES}
    DOC "Location to search for the turtle include files"
)

# Manually download and install Turtle
if(NOT Turtle_INCLUDE_DIR)
    set(Turtle_REQUESTED_VERSION "1.3.0" CACHE STRING "Requested version of Turtle")
    set(Turtle_ARCHIVE_DIR "Turtle")

    set(Turtle_ARCHIVE_URL "https://sourceforge.net/projects/turtle/files/turtle/${Turtle_REQUESTED_VERSION}/turtle-${Turtle_REQUESTED_VERSION}.zip")

    microstrain_download_and_extract_archive(
        NAME "Turtle"
        URL "${Turtle_ARCHIVE_URL}"
        DEPS_BASE_DIR "${DEPS_BASE_DIR}"
        EXTRACTED_DIR "${Turtle_ARCHIVE_DIR}"
        CREATE_EXTRACTED_DIR
    )

    set(Turtle_ROOT "${DEPS_BASE_DIR}/${Turtle_ARCHIVE_DIR}" CACHE PATH "Location to search for the Boost Turtle headers" FORCE)
endif()

find_path(Turtle_INCLUDE_DIR
    NAMES "${Turtle_MOCK_HEADER}"
    PATHS "${Turtle_ROOT}"
    PATH_SUFFIXES ${Turtle_PATH_SUFFIXES}
    DOC "Location to search for the turtle include files"
    REQUIRED
)

if(NOT Turtle_INCLUDE_DIR)
    message(FATAL_ERROR "Unable to find the Boost Turtle mock library")
else()
    get_filename_component(Turtle_INCLUDE_DIR "${Turtle_INCLUDE_DIR}" DIRECTORY)
    message(STATUS "Found Boost Turtle: ${Turtle_INCLUDE_DIR}")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MSCL_INCLUDE_DIRS}
    ${Turtle_INCLUDE_DIR}
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
