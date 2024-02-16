cmake_minimum_required(VERSION 3.16.0)
project(MSCL_Example_Inertial_CPP LANGUAGES CXX)

#set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Supported configuration types" FORCE)

# Set up the example, and link it against MSCL.
add_executable(${PROJECT_NAME} main.cpp)

# Append to the module path so we can use the FindMSCL.cmake and MSCLExampleConfigCPP.cmake scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../cmake")

include(MSCLExampleConfigCPP)

mscl_configure_example_cpp()
