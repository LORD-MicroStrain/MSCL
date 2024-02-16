cmake_minimum_required(VERSION 3.16.0)
project(MSCL_Example_Displacement_CSharp LANGUAGES CSharp)

#set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Supported configuration types" FORCE)

# Append to the module path so we can use the FindMSCL_Managed.cmake and MSCLExampleConfigCSharp.cmake scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../cmake")

include(MSCLExampleConfigCSharp)

add_executable(${PROJECT_NAME}
  Properties/AssemblyInfo.cs
  getCurrentConfig.cs
  parseData.cs
  Program.cs
  setCurrentConfig.cs
  setToIdle.cs
  startSampling.cs
)

mscl_configure_example_csharp()
