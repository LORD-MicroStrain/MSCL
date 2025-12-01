set(MSCL_PYTHON_EXAMPLES_SUBDIRECTORIES
    "${CMAKE_CURRENT_LIST_DIR}/displacement"
    "${CMAKE_CURRENT_LIST_DIR}/inertial"
    "${CMAKE_CURRENT_LIST_DIR}/wireless"
)

# Add all of the example projects
foreach(MSCL_PYTHON_EXAMPLES_SUBDIRECTORY IN LISTS MSCL_PYTHON_EXAMPLES_SUBDIRECTORIES)
    add_subdirectory("${MSCL_PYTHON_EXAMPLES_SUBDIRECTORY}")

    # Get the name of the target that was just generated
    get_property(MSCL_PYTHON_EXAMPLES_TARGET_NAME DIRECTORY "${MSCL_PYTHON_EXAMPLES_SUBDIRECTORY}"
        PROPERTY BUILDSYSTEM_TARGETS
    )

    if (NOT MSCL_PYTHON_EXAMPLES_TARGET_NAME)
        message(FATAL_ERROR "Could not find the Python example target")
    endif()

    # Add the example target to the all examples target
    add_dependencies("${MSCL_EXAMPLES_ALL_TARGET}" "${MSCL_PYTHON_EXAMPLES_TARGET_NAME}")
endforeach()

mscl_install_examples(
    SUBDIRECTORIES ${MSCL_PYTHON_EXAMPLES_SUBDIRECTORIES}
    COMPONENT_NAME "Python-Examples"
)
