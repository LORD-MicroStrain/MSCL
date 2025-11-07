if(NOT WIN32)
    message(WARNING "Building .NET is only supported on Windows")
    return()
endif()

enable_language(CSharp)

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

# The generated Swig module to link the C# bindings to (C++ module)
set(MSCL_CSHARP_MODULE_NAME "${PROJECT_NAME}_CSharp")

# Set up the Swig interface file properties
set_source_files_properties(${SWIG_SOURCE_FILES} PROPERTIES
    CPLUSPLUS ON
    SWIG_MODULE_NAME "${MSCL_CSHARP_MODULE_NAME}"
    INCLUDE_DIRECTORIES "${MSCL_INCLUDE_DIR}"
    # Add the namespace option for the Swig executable which converts to '-namespace mscl'
    COMPILE_OPTIONS "-namespace;mscl"
)

# Generate C++ wrapper and .cs files at BUILD time (not configure time)
swig_add_library("${MSCL_CSHARP_MODULE_NAME}"
    TYPE SHARED
    LANGUAGE "csharp"
    SOURCES ${SWIG_SOURCE_FILES}
)

target_link_libraries("${MSCL_CSHARP_MODULE_NAME}" PRIVATE
    "${MSCL_SWIG_INTERFACE_LIB}"
)

set_target_properties("${MSCL_CSHARP_MODULE_NAME}" PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF # Exporting all symbols causes issues in Swig with the precompiled header
    OUTPUT_NAME "${MSCL_LIBRARY}"
)

# Get the generated .cs files output directory
get_target_property(MSCL_GENERATED_CSHARP_SOURCE_DIR "${MSCL_CSHARP_MODULE_NAME}" SWIG_SUPPORT_FILES_DIRECTORY)

set(MSCL_CSHARP_MANAGED_NAME "${PROJECT_NAME}_Managed")
set(MSCL_CSHARP_MANAGED_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${MSCL_CSHARP_MANAGED_NAME}")

add_custom_command(TARGET "${MSCL_CSHARP_MODULE_NAME}" POST_BUILD
    # Clear the Managed library build directory every time
    COMMAND "${CMAKE_COMMAND}"
        -E remove_directory "${MSCL_CSHARP_MANAGED_BUILD_DIR}"
    # Generate the Manged library project using the same CMake configuration
    COMMAND "${CMAKE_COMMAND}"
        -G "${CMAKE_GENERATOR}"
        -A "${CMAKE_GENERATOR_PLATFORM}"
        -S "${CMAKE_CURRENT_LIST_DIR}/managed"
        -B "${MSCL_CSHARP_MANAGED_BUILD_DIR}"
        -DMSCL_CSHARP_MANAGED_NAME="${MSCL_CSHARP_MANAGED_NAME}"
        -DMSCL_GENERATED_CSHARP_SOURCE_DIR="${MSCL_GENERATED_CSHARP_SOURCE_DIR}"
        -DMSCL_CSHARP_ASSEMBLY_FILE="${MSCL_ASSEMBLY_CS_OUT_FILE}"
        -DMSCL_CSHARP_EXCEPTIONS_FILE="${CMAKE_CURRENT_LIST_DIR}/Exceptions.cs"
        -DNATIVE_DLL="$<TARGET_FILE:${MSCL_CSHARP_MODULE_NAME}>"
        -DNATIVE_DLL_IMPLIB="$<TARGET_LINKER_FILE:${MSCL_CSHARP_MODULE_NAME}>"
        -DMSCL_CSHARP_MODULE_NAME="${MSCL_CSHARP_MODULE_NAME}"
    # Build the Manged library project
    COMMAND "${CMAKE_COMMAND}"
        --build "${MSCL_CSHARP_MANAGED_BUILD_DIR}"
        --config "$<CONFIG>"
        --target "${MSCL_CSHARP_MANAGED_NAME}"
    COMMENT "Building the managed C# library"
)

# Installation
set(MSCL_CSHARP_INSTALL_DIR "DotNet/${MSCL_ARCH_NAME}/$<CONFIG>")
install(
    TARGETS "${MSCL_CSHARP_MODULE_NAME}"
    DESTINATION "${MSCL_CSHARP_INSTALL_DIR}"
    COMPONENT "${MSCL_CSHARP_MODULE_NAME}"
)

install(
    FILES "${MSCL_CSHARP_MANAGED_BUILD_DIR}/$<CONFIG>/${MSCL_CSHARP_MANAGED_NAME}.dll"
    DESTINATION "${MSCL_CSHARP_INSTALL_DIR}"
    COMPONENT "${MSCL_CSHARP_MODULE_NAME}"
)

if(MSCL_BUILD_PACKAGE)
    microstrain_set_cpack_component_file_name(
        PACKAGE_NAME "${PROJECT_NAME}"
        COMPONENT_NAME "${MSCL_CSHARP_MODULE_NAME}"
        COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
    )
endif()
