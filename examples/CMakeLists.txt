# Handle examples installation for packaging
function(mscl_install_examples)
    set(OPTIONS)
    set(SINGLE_VALUES COMPONENT_NAME)
    set(MULTI_VALUES SUBDIRECTORIES)

    set(EXAMPLES_PARSE_PREFIX "EXAMPLES")
    cmake_parse_arguments(${EXAMPLES_PARSE_PREFIX}
        "${OPTIONS}"
        "${SINGLE_VALUES}"
        "${MULTI_VALUES}"
        "${ARGN}"
    )

    # Remove the prefix from the arguments
    foreach(ARG IN LISTS OPTIONS SINGLE_VALUES MULTI_VALUES)
        set(${ARG} ${${EXAMPLES_PARSE_PREFIX}_${ARG}})
    endforeach()

    # Make sure all the required arguments are used
    foreach(ARG IN LISTS SINGLE_VALUES MULTI_VALUES)
        if(NOT ${ARG})
            message(FATAL_ERROR "Setting up the examples installation requires the ${ARG} argument to be set")
        endif()
    endforeach()

    foreach(SUBDIRECTORY IN LISTS SUBDIRECTORIES)
        # Keep the same directory structure for installation
        # The directory itself is also installed, so get the relative path to the parent
        file(RELATIVE_PATH EXAMPLE_INSTALL_DIR "${CMAKE_SOURCE_DIR}" "${SUBDIRECTORY}/..")

        # Install the source files for packaging
        install(
            DIRECTORY "${SUBDIRECTORY}"
            DESTINATION "${EXAMPLE_INSTALL_DIR}"
            # No need to package examples for multiple configurations since it's a file installation
            CONFIGURATIONS "Release"
            COMPONENT "${COMPONENT_NAME}"
        )
    endforeach()

    if(MSCL_BUILD_PACKAGE)
        microstrain_set_cpack_component_file_name(
            COMPONENT_NAME "${COMPONENT_NAME}"
            COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
        )
    endif()
endfunction()

microstrain_append_cmake_folder()

# Create a target to allow building all the example targets
set(MSCL_EXAMPLES_ALL_TARGET "${PROJECT_NAME}-Examples")
add_custom_target("${MSCL_EXAMPLES_ALL_TARGET}")

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/cpp")

if(MSCL_BUILD_CSHARP)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/csharp")
endif()

if(MSCL_BUILD_PYTHON)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/python")
endif()
