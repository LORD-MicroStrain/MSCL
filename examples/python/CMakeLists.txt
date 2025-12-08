set(MSCL_PYTHON_EXAMPLES_SUBDIRECTORIES
    "displacement"
    "inertial"
    "wireless"
)

#
set(MSCL_PYTHON_EXAMPLE_CMAKE_CONFIG_IN "${CMAKE_CURRENT_LIST_DIR}/cmake/CMakeLists.txt.in")

# Add all of the example projects
# This generates one example per Python version per example-type
# These are wrapper targets to run a Python script through CMake
foreach(MSCL_PYTHON_EXAMPLES_SUBDIRECTORY IN LISTS MSCL_PYTHON_EXAMPLES_SUBDIRECTORIES)
    # Add an example for each requested version of Python
    foreach(MSCL_PYTHON_VERSION IN LISTS MSCL_PYTHON_REQUESTED_VERSIONS)
        set(MSCL_PYTHON_EXAMPLE_DIR "${CMAKE_CURRENT_LIST_DIR}/generated/python${MSCL_PYTHON_VERSION}-${MSCL_PYTHON_EXAMPLES_SUBDIRECTORY}")
        set(MSCL_PYTHON_EXAMPLE_CMAKE_CONFIG_OUT "${MSCL_PYTHON_EXAMPLE_DIR}/CMakeLists.txt")

        string(SUBSTRING "${MSCL_PYTHON_EXAMPLES_SUBDIRECTORY}" 0 1 FIRST_CHAR_UPPER)
        string(TOUPPER "${FIRST_CHAR_UPPER}" FIRST_CHAR_UPPER)
        string(REGEX REPLACE "^.(.+)" "${FIRST_CHAR_UPPER}\\1" MSCL_PYTHON_EXAMPLE_TYPE "${MSCL_PYTHON_EXAMPLES_SUBDIRECTORY}")

        # Create the project file
        configure_file(
            "${MSCL_PYTHON_EXAMPLE_CMAKE_CONFIG_IN}"
            "${MSCL_PYTHON_EXAMPLE_CMAKE_CONFIG_OUT}"
            @ONLY
        )

        add_subdirectory("${MSCL_PYTHON_EXAMPLE_DIR}")
    endforeach()
endforeach()

list(TRANSFORM MSCL_PYTHON_EXAMPLES_SUBDIRECTORIES PREPEND "${CMAKE_CURRENT_LIST_DIR}/")

mscl_install_examples(
    SUBDIRECTORIES ${MSCL_PYTHON_EXAMPLES_SUBDIRECTORIES}
    COMPONENT_NAME "Python-Examples"
)
