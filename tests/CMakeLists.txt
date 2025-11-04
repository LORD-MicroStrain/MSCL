set(MSCL_UNIT_TESTS "MSCL_Unit_Tests")

set(Turtle_ROOT "" CACHE PATH "Location to search for the Turtle headers")

# Create the test project
add_executable(${MSCL_UNIT_TESTS})

# Add the test sources
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src")

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
    set(Turtle_REQUESTED_VERSION "2.0.0" CACHE STRING "Requested version of Turtle")
    set(Turtle_ARCHIVE_DIR "Turtle")

    set(Turtle_ARCHIVE_URL "https://github.com/mat007/turtle/releases/download/v${Turtle_REQUESTED_VERSION}/turtle-${Turtle_REQUESTED_VERSION}.zip")

    microstrain_download_and_extract_archive(
        NAME "Turtle"
        URL "${Turtle_ARCHIVE_URL}"
        DEPS_BASE_DIR "${DEPS_BASE_DIR}"
        EXTRACTED_DIR "${Turtle_ARCHIVE_DIR}"
        CREATE_EXTRACTED_DIR
    )

    set(Turtle_ROOT "${DEPS_BASE_DIR}/${Turtle_ARCHIVE_DIR}" CACHE PATH "Location to search for the Turtle headers" FORCE)
endif()

find_path(Turtle_INCLUDE_DIR
    NAMES "${Turtle_MOCK_HEADER}"
    PATHS "${Turtle_ROOT}"
    PATH_SUFFIXES ${Turtle_PATH_SUFFIXES}
    DOC "Location to search for the turtle include files"
    REQUIRED
)

if(NOT Turtle_INCLUDE_DIR)
    message(FATAL_ERROR "Unable to find the Turtle mock library")
else()
    get_filename_component(Turtle_INCLUDE_DIR "${Turtle_INCLUDE_DIR}" DIRECTORY)
    message(STATUS "Found Boost Turtle: ${Turtle_INCLUDE_DIR}")
endif()

# Turtle depends on the Boost testing framework
find_package("Boost" COMPONENTS "unit_test_framework" CONFIG)

target_include_directories(${MSCL_UNIT_TESTS} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Turtle_INCLUDE_DIR}
)

target_link_libraries(${MSCL_UNIT_TESTS} PRIVATE
    ${MSCL_LIBRARY}
    ${Boost_LIBRARIES}
)

# On windows, we need to set the runtime library to the same as MSCL
if(MSVC)
    target_compile_options(${MSCL_UNIT_TESTS} PRIVATE
        "/MT$<$<CONFIG:Debug>:d>"
        "/MP"
        "/bigobj"
    )

    # Ignore some annoying linker warnings
#    target_link_options(${MSCL_UNIT_TESTS} PRIVATE
#        "/ignore:4099"
#    )
endif()

# Generate the list of test suites so each test result is output to the console
# Not elegant but it's easier to do this programmatically

set(TEST_SUITE_START_REGEX "BOOST_AUTO_TEST_SUITE\\(([^)]+)\\)")
set(TEST_FIXTURE_START_REGEX "BOOST_FIXTURE_TEST_SUITE\\(([^,]+), [^)]+\\)")
set(TEST_SUITE_CASE_REGEX "BOOST_AUTO_TEST_CASE\\(([^)]+)\\)*")
set(TEST_SUITE_END_REGEX "BOOST_AUTO_TEST_SUITE_END\\(\\)")

get_target_property(SRC_FILES ${MSCL_UNIT_TESTS} SOURCES)

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

            add_test(NAME "${TEST_NAME}" COMMAND ${MSCL_UNIT_TESTS} --log_level=test_suite --report_level=no --run_test=${RUN_NAME})
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
