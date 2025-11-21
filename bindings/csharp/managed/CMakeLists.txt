#
# DO NOT MODIFY THIS FILE WITHOUT UPDATING THE MAIN CONFIGURATION FILE
# This file is used as a post-build step for generating the C# bindings with Swig
# It only works after the main configuration file has gone through the generation step
#

message(WARNING "
    CMAKE_MINIMUM_REQUIRED_VERSION: ${CMAKE_MINIMUM_REQUIRED_VERSION}
    MSCL_CSHARP_MANAGED_TARGET: ${MSCL_CSHARP_MANAGED_TARGET}
    MSCL_GENERATED_CSHARP_SOURCE_DIR: ${MSCL_GENERATED_CSHARP_SOURCE_DIR}
    PROJECT_VERSION: ${PROJECT_VERSION}
    MSCL_CURRENT_YEAR: ${MSCL_CURRENT_YEAR}
    MSCL_GIT_COMMIT: ${MSCL_GIT_COMMIT}
")

cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})
project("${MSCL_CSHARP_MANAGED_TARGET}"
    LANGUAGES "CSharp"
    VERSION "${PROJECT_VERSION}"
)

set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Supported configuration types" FORCE)

# Export compile commands by default (helpful for clang-tidy and autocomplete for certain IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# This will make windows create a .lib file with all the symbols of the .dll files exported
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Generate the assembly info file for CSharp (This uses the MSCL_CURRENT_YEAR variable)
set(ASSEMBLY_FILE "AssemblyInfo.cs")
set(MSCL_ASSEMBLY_CS_IN_FILE "${CMAKE_CURRENT_LIST_DIR}/${ASSEMBLY_FILE}.in")
set(MSCL_ASSEMBLY_CS_OUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${ASSEMBLY_FILE}")
set(MSCL_ASSEMBLY_CS_GEN_FILE "${CMAKE_CURRENT_BINARY_DIR}/${ASSEMBLY_FILE}.out")

# Generate a file to generate the AssemblyInfo.cs files per configuration
configure_file("${MSCL_ASSEMBLY_CS_IN_FILE}" "${MSCL_ASSEMBLY_CS_GEN_FILE}")

# Generate the actual assembly file for the project with config info
file(GENERATE
    OUTPUT "${MSCL_ASSEMBLY_CS_OUT_FILE}"
    INPUT "${MSCL_ASSEMBLY_CS_GEN_FILE}"
)

# Get all the Swig generated files
file(GLOB MSCL_GENERATED_CSHARP_SOURCES "${MSCL_GENERATED_CSHARP_SOURCE_DIR}/*.cs")

# Optional: Validate generated files
foreach(CSHARP_FILE IN LISTS MSCL_GENERATED_CSHARP_SOURCES)
    get_filename_component(CSHARP_FILENAME "${CSHARP_FILE}" NAME)
    if("${CSHARP_FILENAME}" MATCHES "^SWIGTYPE_p")
        string(APPEND CSHARP_INCORRECT_FILENAMES "\n${CSHARP_FILENAME}")
    endif()
endforeach()

if(CSHARP_INCORRECT_FILENAMES)
    message(FATAL_ERROR "Incorrect CSharp filename generation(s) found ${CSHARP_INCORRECT_FILENAMES}")
endif()

add_library("${MSCL_CSHARP_MANAGED_TARGET}" SHARED
    "${MSCL_ASSEMBLY_CS_OUT_FILE}"
    "${CMAKE_CURRENT_LIST_DIR}/Exceptions.cs"
    ${MSCL_GENERATED_CSHARP_SOURCES}
)
