if(NOT WIN32)
    message(WARNING "Building .NET is only supported on Windows")
    return()
endif()

enable_language(CSharp)

# Generate the assembly info file for CSharp (This uses the MSCL_CURRENT_YEAR variable)
set(ASSEMBLY_FILE "AssemblyInfo.cs")
set(MSCL_ASSEMBLY_CS_IN_FILE "${MSCL_MODULE_DIR}/${ASSEMBLY_FILE}.in")
set(MSCL_ASSEMBLY_CS_OUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${ASSEMBLY_FILE}")
set(MSCL_ASSEMBLY_CS_GEN_FILE "${CMAKE_CURRENT_BINARY_DIR}/${ASSEMBLY_FILE}.out")

# Generate a file to generate the AssemblyInfo.cs files per configuration
configure_file("${MSCL_ASSEMBLY_CS_IN_FILE}" "${MSCL_ASSEMBLY_CS_GEN_FILE}")

# Generate the actual assembly file for the project with config info
file(GENERATE
    OUTPUT "${MSCL_ASSEMBLY_CS_OUT_FILE}"
    INPUT "${MSCL_ASSEMBLY_CS_GEN_FILE}"
)
