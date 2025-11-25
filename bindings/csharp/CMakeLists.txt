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
string(TOLOWER "${MSCL_CSHARP_MANAGED_TARGET}" MSCL_CSHARP_MANAGED_TARGET_LOWER)
set(MSCL_CSHARP_MANAGED_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${MSCL_CSHARP_MANAGED_TARGET}")

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    # Allow clearing the cache before reconfiguring the project
    set(MSCL_CSHARP_MANAGED_FRESH_CONFIG_OPTION "--fresh")
endif()

set(MSCL_CSHARP_INSTALL_PREFIX "dotnet")
set(MSCL_CSHARP_INSTALL_LIBDIR "${MSCL_CSHARP_INSTALL_PREFIX}/${MSCL_ARCH_NAME}")
set(MSCL_CSHARP_CONFIG_INSTALL_DIR "${MSCL_CSHARP_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/${MSCL_CSHARP_MANAGED_TARGET_LOWER}")

add_custom_command(TARGET "${MSCL_CSHARP_TARGET}" POST_BUILD
    # Generate the Manged library project using the same CMake configuration
    COMMAND "${CMAKE_COMMAND}"
        -G "${CMAKE_GENERATOR}"
        -A "${CMAKE_GENERATOR_PLATFORM}"
        -S "${CMAKE_CURRENT_LIST_DIR}/managed"
        -B "${MSCL_CSHARP_MANAGED_BUILD_DIR}"
        "-DCMAKE_MINIMUM_REQUIRED_VERSION=${CMAKE_MINIMUM_REQUIRED_VERSION}"
        "-DMSCL_CSHARP_MANAGED_TARGET=${MSCL_CSHARP_MANAGED_TARGET}"
        "-DMSCL_GENERATED_CSHARP_SOURCE_DIR=${MSCL_GENERATED_CSHARP_SOURCE_DIR}"

        # Installation values
        "-DMSCL_CSHARP_INSTALL_LIBDIR=${MSCL_CSHARP_INSTALL_LIBDIR}"
        "-DMSCL_CSHARP_CONFIG_INSTALL_DIR=${MSCL_CSHARP_CONFIG_INSTALL_DIR}"
        "-DMSCL_CSHARP_COMPONENT_NAME=${MSCL_CSHARP_COMPONENT_NAME}"
        "-DMSCL_ARCH_NAME=${MSCL_ARCH_NAME}"

        # Assembly file generation values
        "-DPROJECT_VERSION=${PROJECT_VERSION}"
        "-DMSCL_CURRENT_YEAR=${MSCL_CURRENT_YEAR}"
        "-DMSCL_GIT_COMMIT=${MSCL_GIT_COMMIT}"
        "${MSCL_CSHARP_MANAGED_FRESH_CONFIG_OPTION}" # Clear the cache before configuring
    # Build the Manged library project
    COMMAND ${CMAKE_COMMAND}
        --build "${MSCL_CSHARP_MANAGED_BUILD_DIR}"
        --config "$<CONFIG>"
        --target "${MSCL_CSHARP_MANAGED_TARGET}"
    COMMENT "Building the managed C# library for MSCL"
)

# Installation
install(
    TARGETS "${MSCL_CSHARP_TARGET}"
    RUNTIME
        COMPONENT "${MSCL_CSHARP_COMPONENT_NAME}"
        DESTINATION "${MSCL_CSHARP_INSTALL_LIBDIR}$<$<CONFIG:Debug>:/debug>"
)

# Run the installation script for the managed target as part of the CSharp installation
install(
    SCRIPT "${MSCL_CSHARP_MANAGED_BUILD_DIR}/cmake_install.cmake"
    COMPONENT "${MSCL_CSHARP_COMPONENT_NAME}"
)

# Create the find_package config and version files for MSCL_Managed
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(mscl-managed-create-config-file)

if(MSCL_BUILD_PACKAGE)
    microstrain_set_cpack_component_file_name(
        COMPONENT_NAME "${MSCL_CSHARP_COMPONENT_NAME}"
        COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
        PACKAGE_ARCH "${CPACK_SYSTEM_NAME}"
    )
endif()
