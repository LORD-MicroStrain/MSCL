if(NOT WIN32)
    message(WARNING "Building .NET is only supported on Windows")
    return()
endif()

# The generated Swig module to link the C# bindings to (C++ module)
set(MSCL_CSHARP_COMPONENT_NAME "CSharp")
set(MSCL_CSHARP_TARGET "${PROJECT_NAME}-${MSCL_CSHARP_COMPONENT_NAME}")
string(TOLOWER "${MSCL_CSHARP_TARGET}" MSCL_CSHARP_TARGET_LOWER)
mscl_add_swig_module_library(
    LIB_NAME "${MSCL_CSHARP_TARGET}"
    MODULE_LANGUAGE "csharp"
    ADDITIONAL_SWIG_OPTIONS "-namespace;mscl"
)

# Get the generated .cs files output directory
get_target_property(MSCL_GENERATED_CSHARP_SOURCE_DIR "${MSCL_CSHARP_TARGET}" SWIG_SUPPORT_FILES_DIRECTORY)

set(MSCL_CSHARP_MANAGED_TARGET "${MSCL_LIBRARY}_Managed")
string(TOLOWER "${MSCL_CSHARP_MANAGED_TARGET}" MSCL_CSHARP_MANAGED_TARGET_LOWER)
set(MSCL_CSHARP_MANAGED_EXPORT_TARGET_NAME "${MSCL_CSHARP_MANAGED_TARGET_LOWER}-targets")
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
        "-DMSCL_CSHARP_MANAGED_EXPORT_TARGET_NAME=${MSCL_CSHARP_MANAGED_EXPORT_TARGET_NAME}"
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

# Create imported target MSCL_Managed (for use within the project)
add_library(${MSCL_CSHARP_MANAGED_TARGET} SHARED IMPORTED GLOBAL)

# Set up the properties for each configuration type
foreach(CMAKE_CONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER "${CMAKE_CONFIG}" CMAKE_CONFIG_UPPER)

    set_target_properties(${MSCL_CSHARP_MANAGED_TARGET} PROPERTIES
        IMPORTED_COMMON_LANGUAGE_RUNTIME_${CMAKE_CONFIG_UPPER} "CSharp"
        IMPORTED_LOCATION_${CMAKE_CONFIG_UPPER} ${MSCL_CSHARP_MANAGED_BUILD_DIR}/${CMAKE_CONFIG}/${MSCL_CSHARP_MANAGED_TARGET}.dll
    )

    set_target_properties(${MSCL_CSHARP_TARGET} PROPERTIES
        IMPORTED_COMMON_LANGUAGE_RUNTIME_${CMAKE_CONFIG_UPPER} "CSharp"
        IMPORTED_LOCATION_${CMAKE_CONFIG_UPPER} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIG}/${MSCL_CSHARP_TARGET}.dll
    )

    unset(CMAKE_CONFIG_UPPER)
endforeach()

target_link_libraries(${MSCL_CSHARP_MANAGED_TARGET} INTERFACE
    "${MSCL_CSHARP_TARGET}"
)

# Set the library names for consistency with the find_package config
set(MSCL_MANAGED_LIBRARY "${MSCL_CSHARP_MANAGED_TARGET}" CACHE INTERNAL "The name of the MSCL Managed library")
set(MSCL_CSHARP_LIBRARY "${MSCL_CSHARP_TARGET}" CACHE INTERNAL "The name of the MSCL CSharp library")

# CMake utilities for consumption of the managed target
# This is exported/installed with the C# library
set(MSCL_CSHARP_MANAGED_REF_UTILS_FILENAME "mscl-managed-ref-utils.cmake")

# This is included in the root examples directory so all C# examples can use it
# exactly the same as the MSCL_Managed find module
set(MSCL_CSHARP_MANAGED_REF_UTILS "${CMAKE_CURRENT_LIST_DIR}/cmake/${MSCL_CSHARP_MANAGED_REF_UTILS_FILENAME}" CACHE INTERNAL "The location of the MSCL Managed reference utilities file")

# Installation

set(MSCL_CSHARP_EXPORT_TARGET_NAME "${MSCL_CSHARP_TARGET_LOWER}-targets")
string(APPEND MSCL_CSHARP_INSTALL_LIBDIR "$<$<CONFIG:Debug>:/debug>")
install(
    TARGETS "${MSCL_CSHARP_TARGET}"
    EXPORT "${MSCL_CSHARP_EXPORT_TARGET_NAME}"
    RUNTIME
        COMPONENT "${MSCL_CSHARP_COMPONENT_NAME}"
        DESTINATION "${MSCL_CSHARP_INSTALL_LIBDIR}"
)

# Install the reference utilities file alongside the find package module
install(
    FILES "${MSCL_CSHARP_MANAGED_REF_UTILS}"
    DESTINATION "${MSCL_CSHARP_CONFIG_INSTALL_DIR}"
    COMPONENT "${MSCL_CSHARP_COMPONENT_NAME}"
)

# Create export files for the library for all configurations
install(
    EXPORT "${MSCL_CSHARP_EXPORT_TARGET_NAME}"
    DESTINATION "${MSCL_CSHARP_CONFIG_INSTALL_DIR}/${MSCL_ARCH_NAME}"
    COMPONENT "${MSCL_CSHARP_COMPONENT_NAME}"
)

# Run the installation script for the managed target as part of the CSharp installation
install(
    SCRIPT "${MSCL_CSHARP_MANAGED_BUILD_DIR}/cmake_install.cmake"
    COMPONENT "${MSCL_CSHARP_COMPONENT_NAME}"
)

# Create the find_package config and version files for MSCL_Managed
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include("mscl-managed-create-config-file")

if(MSCL_BUILD_PACKAGE)
    microstrain_set_cpack_component_file_name(
        COMPONENT_NAME "${MSCL_CSHARP_COMPONENT_NAME}"
        COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
        PACKAGE_ARCH "${CPACK_SYSTEM_NAME}"
    )
endif()
