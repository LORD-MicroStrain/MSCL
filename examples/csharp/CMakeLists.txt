microstrain_append_cmake_folder()

set(MSCL_CSHARP_EXAMPLES_SUBDIRECTORIES
    "${CMAKE_CURRENT_LIST_DIR}/displacement"
    "${CMAKE_CURRENT_LIST_DIR}/inertial"
    "${CMAKE_CURRENT_LIST_DIR}/wireless"
)

# Include the C# utilities script which is exported alongside the libraries
# This is defined in the C# bindings directory and is needed to use the
# mscl_managed_add_references function within the examples
include("${MSCL_CSHARP_MANAGED_REF_UTILS}")

# Add all of the example projects
foreach(MSCL_CSHARP_EXAMPLES_SUBDIRECTORY IN LISTS MSCL_CSHARP_EXAMPLES_SUBDIRECTORIES)
    add_subdirectory("${MSCL_CSHARP_EXAMPLES_SUBDIRECTORY}")

    # Get the name of the target that was just generated
    get_property(MSCL_CSHARP_EXAMPLES_TARGET_NAME DIRECTORY "${MSCL_CSHARP_EXAMPLES_SUBDIRECTORY}"
        PROPERTY BUILDSYSTEM_TARGETS
    )

    if (NOT MSCL_CSHARP_EXAMPLES_TARGET_NAME)
        message(FATAL_ERROR "Could not find the C# example target")
    endif()

    # Add the example target to the all examples target
    add_dependencies("${MSCL_EXAMPLES_ALL_TARGET}" "${MSCL_CSHARP_EXAMPLES_TARGET_NAME}")
endforeach()

mscl_install_examples(
    SUBDIRECTORIES ${MSCL_CSHARP_EXAMPLES_SUBDIRECTORIES}
    COMPONENT_NAME "CSharp-Examples"
)
