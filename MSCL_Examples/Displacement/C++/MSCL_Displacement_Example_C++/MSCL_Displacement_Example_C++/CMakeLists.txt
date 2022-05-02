cmake_minimum_required(VERSION 3.12.0)
project(MSCL_Example_Displacement_CPP)

# Set up the example, and link it against MSCL.
add_executable(${PROJECT_NAME} main.cpp)

if(CMAKE_PROJECT_NAME STREQUAL "MSCL")
  # NOTE: This section will only be called if this CMakeLists.txt is imported during the MSCL build.
  #       If not building in the MSCL repo, this can be safely ignored or removed
  set(MSCL_LIBRARY MSCL)
  set(MSCL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../MSCL/source")
  target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/MSCL/MSCL_static/${CMAKE_CFG_INTDIR})
  add_dependencies(${PROJECT_NAME} MSCL_static)
endif()

# Append to the module path so we can use the FindMSCL.cmake script
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../cmake")
find_package(MSCL REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${MSCL_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} ${MSCL_LIBRARIES})

# Don't let MSCL find it's own libraries
target_compile_definitions(${PROJECT_NAME} PRIVATE BOOST_ALL_NO_LIB)

# On windows, we need to set the runtime library to the same as MSCL
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Debug>:/MTd> $<$<CONFIG:Release>:/MT>>)

# Ignore some annoying linker warnings
target_link_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/ignore:4099>)