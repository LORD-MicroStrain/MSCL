macro(mscl_add_swig_python_module_library MSCL_PYTHON_VERSION MSCL_PYTHON_MAJOR_VERSION)
    set(MSCL_PYTHON_COMPONENT_NAME "Python${MSCL_PYTHON_VERSION}")
    set(MSCL_PYTHON_TARGET_NAME "${PROJECT_NAME}-${MSCL_PYTHON_COMPONENT_NAME}")

    # Set some linker options
    if(MSVC)
        set(MSCL_PYTHON_LINK_OPTIONS
            "$<$<CONFIG:Release>:/LTCG>"
        )
    else()
        set(MSCL_PYTHON_LINK_OPTIONS
            "-Wl,--no-as-needed"
        )
    endif()

    mscl_add_swig_module_library(
        LIB_NAME "${MSCL_PYTHON_TARGET_NAME}"
        MODULE_LANGUAGE "python"
        LINK_OPTIONS ${MSCL_PYTHON_LINK_OPTIONS}
    )

    # Set the output directory similar to how actual libraries/projects output artifacts
    # This allows multiple versions of Python to be build without overwriting the previous artifacts
    set(MSCL_PYTHON_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${MSCL_PYTHON_TARGET_NAME}")
    if(MSVC)
        string(APPEND MSCL_PYTHON_OUTPUT_DIRECTORY "/$<CONFIG>")
    endif()

    # Make sure all the artifacts are output in their own build directories
    set_target_properties("${MSCL_PYTHON_TARGET_NAME}" PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${MSCL_PYTHON_OUTPUT_DIRECTORY}"
        RUNTIME_OUTPUT_DIRECTORY "${MSCL_PYTHON_OUTPUT_DIRECTORY}"
        LIBRARY_OUTPUT_DIRECTORY "${MSCL_PYTHON_OUTPUT_DIRECTORY}"
    )

    # Add the target to a list to build all targets
    list(APPEND MSCL_PYTHON${MSCL_PYTHON_MAJOR_VERSION}_ALL_TARGETS "${MSCL_PYTHON_TARGET_NAME}")

    set(PYTHON_PACKAGE_NAME "Python${MSCL_PYTHON_MAJOR_VERSION}")
    set(${PYTHON_PACKAGE_NAME}_USE_STATIC_LIBS ${MSCL_LINK_STATIC_DEPS})

    # Find the required Python package
    find_package("${PYTHON_PACKAGE_NAME}"
        "${MSCL_PYTHON_VERSION}" EXACT
        REQUIRED
        COMPONENTS "Development"
    )

    # Link/include the required Python package
    target_link_libraries("${MSCL_PYTHON_TARGET_NAME}" PRIVATE
        ${${PYTHON_PACKAGE_NAME}_LIBRARIES}
    )
    target_include_directories("${MSCL_PYTHON_TARGET_NAME}" PRIVATE
        "${${PYTHON_PACKAGE_NAME}_INCLUDE_DIRS}"
    )

    # vcpkg doesn't provide pdb files for debug builds of Python
    if(MSVC)
        target_link_options("${MSCL_PYTHON_TARGET_NAME}" PRIVATE
            "/ignore:4099"
        )
    endif()

    # Python 3.10 doesn't seem to link ZLIB properly through vcpkg
    # Make sure it's actually linked
    if(WIN32 AND MSCL_PYTHON_VERSION MATCHES "^3\.10")
        find_package("ZLIB" REQUIRED)
        target_link_libraries("${MSCL_PYTHON_TARGET_NAME}" PRIVATE
            ${ZLIB_LIBRARIES}
        )
    endif()

    # Get the generated .py files
    get_target_property(MSCL_GENERATED_PYTHON_SOURCES "${MSCL_PYTHON_TARGET_NAME}" SWIG_SUPPORT_FILES)

    # Installation
    if(MSVC)
        string(REPLACE "\." "" MSCL_PYTHON_INSTALL_DIR_VERSION "${MSCL_PYTHON_VERSION}")
        set(MSCL_PYTHON_SITE_PACKAGES_DIR "Python${MSCL_PYTHON_INSTALL_DIR_VERSION}/Lib/site-packages")
    else()
        set(MSCL_PYTHON_SITE_PACKAGES_DIR ${CMAKE_INSTALL_LIBDIR}/python${MSCL_PYTHON_VERSION}/)
#        if(DEBIAN)
            # TODO: This is Debian specific
            string(APPEND MSCL_PYTHON_SITE_PACKAGES_DIR "dist-packages")
#        else()
#            string(APPEND MSCL_PYTHON_SITE_PACKAGES_DIR "site-packages")
#        endif()
    endif()

    set(MSCL_PYTHON_INSTALL_CONFIGURATIONS "Release")
    if(MSCL_PACKAGE_PYTHON_DEBUG)
        list(APPEND MSCL_PYTHON_INSTALL_CONFIGURATIONS "Debug")
    endif()

    install(
        TARGETS "${MSCL_PYTHON_TARGET_NAME}"
        CONFIGURATIONS ${MSCL_PYTHON_INSTALL_CONFIGURATIONS}
        RUNTIME
            COMPONENT "${MSCL_PYTHON_COMPONENT_NAME}"
            DESTINATION "${MSCL_PYTHON_SITE_PACKAGES_DIR}"
        LIBRARY
            COMPONENT "${MSCL_PYTHON_COMPONENT_NAME}"
            DESTINATION "${MSCL_PYTHON_SITE_PACKAGES_DIR}"
    )

    install(
        FILES "${MSCL_GENERATED_PYTHON_SOURCES}"
        DESTINATION "${MSCL_PYTHON_SITE_PACKAGES_DIR}"
        CONFIGURATIONS ${MSCL_PYTHON_INSTALL_CONFIGURATIONS}
        COMPONENT "${MSCL_PYTHON_COMPONENT_NAME}"
    )

    if(MSCL_BUILD_PACKAGE)
        microstrain_set_cpack_component_file_name(
            COMPONENT_NAME "${MSCL_PYTHON_COMPONENT_NAME}"
            COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
            PACKAGE_ARCH "${CPACK_SYSTEM_NAME}"
        )
    endif()
endmacro()

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
