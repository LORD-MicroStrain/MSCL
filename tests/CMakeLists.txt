microstrain_append_cmake_folder()

set(MSCL_TEST_TARGET "${PROJECT_NAME}-Tests")

# Create the test project
add_executable(${MSCL_TEST_TARGET})

# The unit tests cannot be built without the MSCL library
add_dependencies("${MSCL_TEST_TARGET}" "${MSCL_LIBRARY}")

# Add the test sources
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src")

set(Turtle_ROOT "" CACHE PATH "Location to search for the Turtle headers")

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
        DEPS_BASE_DIR "${MSCL_DEPS_BASE_DIR}"
        EXTRACTED_DIR "${Turtle_ARCHIVE_DIR}"
        CREATE_EXTRACTED_DIR
    )

    set(Turtle_ROOT "${MSCL_DEPS_BASE_DIR}/${Turtle_ARCHIVE_DIR}" CACHE PATH "Location to search for the Turtle headers" FORCE)
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

target_include_directories("${MSCL_TEST_TARGET}" PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${Turtle_INCLUDE_DIR}"
)

target_link_libraries("${MSCL_TEST_TARGET}" PRIVATE
    ${MSCL_LIBRARY}
    ${Boost_LIBRARIES}
)

target_precompile_headers("${MSCL_TEST_TARGET}" PRIVATE
    "${MSCL_INCLUDE_DIR}/mscl/stdafx.h"
)

# On windows, we need to set the runtime library to the same as MSCL
if(MSVC)
    target_compile_options("${MSCL_TEST_TARGET}" PRIVATE
        "/MP"
        "/bigobj"
    )
endif()

# TODO: Add CI/CD plugin support for JUNIT results
# Reporting as JUNIT isn't compatible for direct CI/CD logging, but it can be easily parsed with a plugin
add_test(
    NAME "${MSCL_TEST_TARGET}"
    COMMAND ${MSCL_TEST_TARGET} --log_level=test_suite --log_format=JUNIT  --log_sink=mscl_test_results.xml --report_level=no
)
