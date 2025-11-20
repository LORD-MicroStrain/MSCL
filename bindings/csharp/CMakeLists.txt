if(NOT WIN32)
    message(WARNING "Building .NET is only supported on Windows")
    return()
endif()

# The generated Swig module to link the C# bindings to (C++ module)
set(MSCL_CSHARP_COMPONENT_NAME "CSharp")
set(MSCL_CSHARP_TARGET "${PROJECT_NAME}-${MSCL_CSHARP_COMPONENT_NAME}")
mscl_add_swig_module_library(
    LIB_NAME "${MSCL_CSHARP_TARGET}"
    MODULE_LANGUAGE "csharp"
    ADDITIONAL_SWIG_OPTIONS "-namespace;mscl"
)

# Get the generated .cs files output directory
get_target_property(MSCL_GENERATED_CSHARP_SOURCE_DIR "${MSCL_CSHARP_TARGET}" SWIG_SUPPORT_FILES_DIRECTORY)

set(MSCL_CSHARP_MANAGED_TARGET "${MSCL_LIBRARY}_Managed")
set(MSCL_CSHARP_MANAGED_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${MSCL_CSHARP_MANAGED_TARGET}")

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    # Allow clearing the cache before reconfiguring the project
    set(MSCL_CSHARP_MANAGED_FRESH_CONFIG_OPTION "--fresh")
endif()

add_custom_command(TARGET "${MSCL_CSHARP_TARGET}" POST_BUILD
    # Generate the Manged library project using the same CMake configuration
    COMMAND "${CMAKE_COMMAND}"
        -G "${CMAKE_GENERATOR}"
        -A "${CMAKE_GENERATOR_PLATFORM}"
        -S "${CMAKE_CURRENT_LIST_DIR}/managed"
        -B "${MSCL_CSHARP_MANAGED_BUILD_DIR}"
        -D "CMAKE_MINIMUM_REQUIRED_VERSION=${CMAKE_MINIMUM_REQUIRED_VERSION}"
        -D "MSCL_CSHARP_MANAGED_TARGET=${MSCL_CSHARP_MANAGED_TARGET}"
        -D "MSCL_GENERATED_CSHARP_SOURCE_DIR=${MSCL_GENERATED_CSHARP_SOURCE_DIR}"

        # Assembly file generation values
        -D "PROJECT_VERSION=${PROJECT_VERSION}"
        -D "MSCL_CURRENT_YEAR=${MSCL_CURRENT_YEAR}"
        -D "MSCL_GIT_COMMIT=${MSCL_GIT_COMMIT}"
        "${MSCL_CSHARP_MANAGED_FRESH_CONFIG_OPTION}" # Clear the cache before configuring
    # Build the Manged library project
    COMMAND ${CMAKE_COMMAND}
        --build "${MSCL_CSHARP_MANAGED_BUILD_DIR}"
        --config "$<CONFIG>"
        --target "${MSCL_CSHARP_MANAGED_TARGET}"
    COMMENT "Building the managed C# library for MSCL"
)

# Installation
set(MSCL_CSHARP_INSTALL_DIR "DotNet/${MSCL_ARCH_NAME}/$<CONFIG>")
install(
    TARGETS "${MSCL_CSHARP_TARGET}"
    RUNTIME
        COMPONENT "${MSCL_CSHARP_COMPONENT_NAME}"
        DESTINATION "${MSCL_CSHARP_INSTALL_DIR}"
)

install(
    FILES "${MSCL_CSHARP_MANAGED_BUILD_DIR}/$<CONFIG>/${MSCL_CSHARP_MANAGED_TARGET}.dll"
    DESTINATION "${MSCL_CSHARP_INSTALL_DIR}"
    COMPONENT "${MSCL_CSHARP_COMPONENT_NAME}"
)

if(MSCL_BUILD_PACKAGE)
    microstrain_set_cpack_component_file_name(
        COMPONENT_NAME "${MSCL_CSHARP_COMPONENT_NAME}"
        COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
    )
endif()
