#
# DO NOT MODIFY THIS FILE WITHOUT UPDATING THE MAIN CONFIGURATION FILE
# This file is used as a post-build step for generating the C# bindings with Swig
# It only works after the main configuration file has gone through the generation step
#

cmake_minimum_required(VERSION 3.18)
project("${MSCL_CSHARP_MANAGED_TARGET}"
    LANGUAGES "CSharp"
)

set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Supported configuration types" FORCE)

# Export compile commands by default (helpful for clang-tidy and autocomplete for certain IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If a build type was not specified, default to debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# This will make windows create a .lib file with all the symbols of the .dll files exported
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Get all the Swig generated files
file(GLOB MSCL_GENERATED_CSHARP_SOURCE "${MSCL_GENERATED_CSHARP_SOURCE_DIR}/*.cs")

# Optional: Validate generated files
foreach(CSHARP_FILE IN LISTS MSCL_GENERATED_CSHARP_SOURCE)
    get_filename_component(CSHARP_FILENAME "${CSHARP_FILE}" NAME)
    if("${CSHARP_FILENAME}" MATCHES "^SWIGTYPE_p")
        string(APPEND CSHARP_INCORRECT_FILENAMES "\n${CSHARP_FILENAME}")
    endif()
endforeach()

if(CSHARP_INCORRECT_FILENAMES)
    message(FATAL_ERROR "Incorrect CSharp filename generation(s) found ${CSHARP_INCORRECT_FILENAMES}")
endif()

add_library(${PROJECT_NAME} SHARED
    ${MSCL_CSHARP_MANAGED_SOURCE_FILES}
    ${MSCL_GENERATED_CSHARP_SOURCE}
)

# Add the pre-built native library as a dependency
# Use add_library with IMPORTED to reference the pre-built DLL
add_library(${MSCL_CSHARP_TARGET} SHARED IMPORTED GLOBAL)
set_target_properties(${MSCL_CSHARP_TARGET} PROPERTIES
    IMPORTED_LOCATION "${NATIVE_DLL}"
    IMPORTED_IMPLIB "${NATIVE_DLL_IMPLIB}"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${MSCL_CSHARP_TARGET}
)
