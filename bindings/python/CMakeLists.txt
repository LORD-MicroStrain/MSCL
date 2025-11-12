# Get the baseline version for the vcpkg manifest file
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    WORKING_DIRECTORY ${MSCL_VCPKG_DIR}
    OUTPUT_VARIABLE MSCL_VCPKG_BASELINE_VERSION
)
string(STRIP "${MSCL_VCPKG_BASELINE_VERSION}" MSCL_VCPKG_BASELINE_VERSION)

# Use vcpkg to download Python libraries for linking
function(mscl_download_python MSCL_PYTHON_VERSION MSCL_PYTHON_MAJOR_VERSION)
    set(MSCL_PYTHON_PROJECT_DIR "python${MSCL_PYTHON_VERSION}")
    set(MSCL_PYTHON_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${MSCL_PYTHON_PROJECT_DIR}")

    message(STATUS "Installing Python ${MSCL_PYTHON_VERSION}...")
    string(REPLACE "." "" MSCL_PYTHON_VERSION_COMBINED "${MSCL_PYTHON_VERSION}")

    # Get the name of the directory where vcpkg installs packages
    # This has and could change in different versions of vcpkg
    get_filename_component(VCPKG_INSALL_DIR_NAME ${VCPKG_INSTALLED_DIR} NAME)
    set(VCPKG_INSTALLED_DIR ${MSCL_PYTHON_BUILD_DIR}/${VCPKG_INSALL_DIR_NAME})

    # Generate the CMake project file
    set(MSCL_PYTHON_CMAKE_FILENAME "CMakeLists.txt")
    configure_file(
        "${CMAKE_CURRENT_LIST_DIR}/${MSCL_PYTHON_CMAKE_FILENAME}.in"
        "${CMAKE_CURRENT_LIST_DIR}/${MSCL_PYTHON_PROJECT_DIR}/${MSCL_PYTHON_CMAKE_FILENAME}"
        @ONLY
    )

    file(READ "${MSCL_VCPKG_DIR}/versions/p-/python${MSCL_PYTHON_MAJOR_VERSION}.json" VCPKG_PYTHON_VERSIONS_CONTENT)

    # Get the number of available version entries
    string(JSON MSCL_PYTHON_VERSION_COUNT LENGTH "${VCPKG_PYTHON_VERSIONS_CONTENT}" "versions")

    foreach(INDEX RANGE 0 ${MSCL_PYTHON_VERSION_COUNT})
        # Get the version number at the given index
        string(JSON MSCL_PYTHON_LATEST_VERSION GET "${VCPKG_PYTHON_VERSIONS_CONTENT}" "versions" ${INDEX} "version")

        # The first match of the requested version should be the latest supported version
        if(MSCL_PYTHON_LATEST_VERSION MATCHES "^${MSCL_PYTHON_VERSION}")
            # Also get the port version for proper installation
            string(JSON MSCL_PYTHON_LATEST_PORT GET "${VCPKG_PYTHON_VERSIONS_CONTENT}" "versions" ${INDEX} "port-version")
            break()
        endif()
    endforeach()

    if(NOT MSCL_PYTHON_LATEST_PORT AND NOT MSCL_PYTHON_LATEST_PORT STREQUAL "0")
        message(FATAL_ERROR "Could not find a supported version for Python ${MSCL_PYTHON_VERSION} in the vcpkg versions file")
    endif()

    # Generate the vcpkg manifest file
    set(MSCL_PYTHON_VCPKG_FILENAME "vcpkg.json")
    configure_file(
        "${CMAKE_CURRENT_LIST_DIR}/${MSCL_PYTHON_VCPKG_FILENAME}.in"
        "${CMAKE_CURRENT_LIST_DIR}/${MSCL_PYTHON_PROJECT_DIR}/${MSCL_PYTHON_VCPKG_FILENAME}"
    )

    # Generate the Python installation project
    execute_process(
        # Generate the Python project using the same CMake configuration
        COMMAND "${CMAKE_COMMAND}"
        -G "${CMAKE_GENERATOR}"
        -A "${CMAKE_GENERATOR_PLATFORM}"
        -S "${CMAKE_CURRENT_LIST_DIR}/${MSCL_PYTHON_PROJECT_DIR}"
        -B "${CMAKE_CURRENT_BINARY_DIR}/${MSCL_PYTHON_PROJECT_DIR}"
    )

    set(PYTHON_VCPKG_INSTALL_DIR "${MSCL_PYTHON_BUILD_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}")
    list(PREPEND CMAKE_PREFIX_PATH
        "${PYTHON_VCPKG_INSTALL_DIR}/debug"
        "${PYTHON_VCPKG_INSTALL_DIR}"
    )

    # Allow the calling scope to find python properly
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} PARENT_SCOPE)
endfunction()

# Create all of the requested Python targets
foreach(MSCL_PYTHON_REQUESTED_VERSION IN LISTS MSCL_PYTHON_REQUESTED_VERSIONS)
    # Validate the requested versions of Python are supported for download
    string(REGEX MATCH "^([23]).[0-9][0-9]?" MSCL_PYTHON_VERSION "${MSCL_PYTHON_REQUESTED_VERSION}")
    if(NOT MSCL_PYTHON_VERSION)
        message(FATAL_ERROR "Invalid Python version request '${MSCL_PYTHON_REQUESTED_VERSION}'. Valid syntax is x.x or x.x.x")
    endif()

    # Get the Python major version
    string(REGEX MATCH "^[23]" MSCL_PYTHON_MAJOR_VERSION "${CMAKE_MATCH_1}")

    list(FIND MSCL_SUPPORTED_PYTHON${MSCL_PYTHON_MAJOR_VERSION}_VERSIONS "${MSCL_PYTHON_VERSION}" MSCL_PYTHON_VERSION_SUPPORTED)

    # The requested version is supported and should be downloaded
    if(MSCL_PYTHON_VERSION_SUPPORTED GREATER_EQUAL 0 AND MSCL_DOWNLOAD_PYTHON${MSCL_PYTHON_MAJOR_VERSION})
        mscl_download_python("${MSCL_PYTHON_VERSION}" "${MSCL_PYTHON_MAJOR_VERSION}")
    endif()

    # Create the Python binding library for the requested version of Python
    mscl_add_swig_python_module_library("${MSCL_PYTHON_VERSION}" "${MSCL_PYTHON_MAJOR_VERSION}")
endforeach()
