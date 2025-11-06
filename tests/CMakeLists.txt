set(MSCL_UNIT_TESTS "MSCL_Unit_Tests")

set(Turtle_ROOT "" CACHE PATH "Location to search for the Turtle headers")

# Create the test project
add_executable(${MSCL_UNIT_TESTS})

# The unit tests cannot be built without the MSCL library
add_dependencies("${MSCL_UNIT_TESTS}" "${MSCL_LIBRARY}")

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
        "/MP"
        "/bigobj"
    )
endif()

# TODO: Add CI/CD plugin support for JUNIT results
# Reporting as JUNIT isn't compatible for direct CI/CD logging, but it can be easily parsed with a plugin
add_test(
    NAME "${MSCL_UNIT_TESTS}"
    COMMAND ${MSCL_UNIT_TESTS} --log_level=test_suite --log_format=JUNIT  --log_sink=mscl_test_results.xml --report_level=no
)
