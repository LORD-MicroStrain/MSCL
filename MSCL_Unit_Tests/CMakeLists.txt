project(MSCL_Unit_Tests)

# Tests should just consist of compiling all source in this directory and linking against MSCL
file(GLOB SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)
add_executable(${PROJECT_NAME} ${SRC_FILES})

if(CMAKE_PROJECT_NAME STREQUAL "MSCL")
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

target_include_directories(${PROJECT_NAME} PRIVATE
  ${TURTLE_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${MSCL_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
  ${MSCL_LIBRARIES}
  ${Boost_TEST_LIBRARIES}
)

# Don't let MSCL find it's own libraries
target_compile_definitions(${PROJECT_NAME} PRIVATE BOOST_ALL_NO_LIB)

# On windows, we need to set the runtime library to the same as MSCL
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Debug>:/MTd> $<$<CONFIG:Release>:/MT>>)

# Ignore some annoying linker warnings
target_link_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/ignore:4099>)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif(MSVC)

add_custom_command(
  TARGET MSCL_Unit_Tests
  COMMENT "*****RUNNING MSCL UNIT TESTS*****"
  POST_BUILD
  COMMAND "$(TargetPath)" --log_level=test_suite --report_level=no
)

# Mark the tests to run when the test target is run
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})