if(NOT WIN32)
    message(WARNING "Building documentation is only supported on Windows")
    return()
endif()

set(NaturalDocs_ROOT "" CACHE PATH "Location of Natural Docs used to generate the documentation")

set(NaturalDocs_NAME "NaturalDocs")

# Attempt to find Natural Docs before manually downloading it (this assumes NaturalDocs_ROOT was set by the user)
find_program(NaturalDocs_EXECUTABLE
    NAMES "${NaturalDocs_NAME}"
    PATHS "${NaturalDocs_ROOT}"
    DOC "Natural Docs command line client"
)

# Manually download and install Natural Docs
if(NOT NaturalDocs_EXECUTABLE)
    set(NaturalDocs_REQUESTED_VERSION "2.3.1" CACHE STRING "Requested version of Natural Docs")
    set(NaturalDocs_ARCHIVE_DIR "Natural Docs")

    set(NaturalDocs_ARCHIVE_URL "https://naturaldocs.org/download/natural_docs/${NaturalDocs_REQUESTED_VERSION}/Natural_Docs_${NaturalDocs_REQUESTED_VERSION}.zip")

    microstrain_download_and_extract_archive(
        NAME "${NaturalDocs_NAME}"
        URL "${NaturalDocs_ARCHIVE_URL}"
        DEPS_BASE_DIR "${DEPS_BASE_DIR}"
        EXTRACTED_DIR "${NaturalDocs_ARCHIVE_DIR}"
    )

    # NaturalDocs_ROOT is required to find the Natural Docs program
    set(NaturalDocs_ROOT "${DEPS_BASE_DIR}/${NaturalDocs_ARCHIVE_DIR}" CACHE PATH "Location of Natural Docs used to generate the documentation" FORCE)

    # Attempt to find the downloaded Natural Docs dependency
    find_program(NaturalDocs_EXECUTABLE
        NAMES "${NaturalDocs_NAME}"
        PATHS "${NaturalDocs_ROOT}"
        DOC "Natural Docs command line client"
    )
endif()

if(NOT NaturalDocs_EXECUTABLE)
    message(FATAL_ERROR "Could not find Natural Docs in '${NaturalDocs_ROOT}' to build documentation")
else()
    message(STATUS "Found Natural Docs: ${NaturalDocs_EXECUTABLE}")
endif()

# Get the NaturalDocs version for the Project.txt and Comments.txt file generation
execute_process(
    COMMAND "${NaturalDocs_EXECUTABLE}" "--version"
    OUTPUT_VARIABLE NaturalDocs_VERSION
)

# Create a target to build all the documentation targets
set(MSCL_ALL_DOCS_TARGET "${PROJECT_NAME}-All-Docs")
add_custom_target("${MSCL_ALL_DOCS_TARGET}")

set(MSCL_DOCS_COMPONENT_NAME "Documentation")

# Helper function to configure each documentation target
function(mscl_configure_docs_target)
    set(OPTIONS API_DOCS)
    set(SINGLE_VALUES)
    set(MULTI_VALUES)

    set(CONFIGURE_DOCS_ARG_PREFIX "CONFIGURE_DOCS_ARG")
    cmake_parse_arguments(${CONFIGURE_DOCS_ARG_PREFIX}
        "${OPTIONS}"
        "${SINGLE_VALUES}"
        "${MULTI_VALUES}"
        "${ARGN}"
    )

    # Remove the prefix from the arguments
    foreach(ARG IN LISTS OPTIONS SINGLE_VALUES MULTI_VALUES)
        set(${ARG} ${${CONFIGURE_DOCS_ARG_PREFIX}_${ARG}})
    endforeach()

    set(MSCL_DOCS_TARGET ${PROJECT_NAME})
    set(DOCS_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")

    if(API_DOCS)
        string(APPEND MSCL_DOCS_TARGET "-API")
        string(APPEND DOCS_OUTPUT_DIR "_API")
    endif()

    string(APPEND MSCL_DOCS_TARGET "-Docs")
    string(APPEND DOCS_OUTPUT_DIR "_Docs")

    # Set the natural docs generated files directories
    set(DOCS_PROJECT_DIR "${CMAKE_CURRENT_BINARY_DIR}/natural_docs_project")
    set(DOCS_WORKING_DATA_DIR "${CMAKE_CURRENT_BINARY_DIR}/working_data")

    # Set the docs title for the Project.txt configure_file call
    set(MSCL_DOCS_TITLE "${PROJECT_NAME}")
    if(NOT API_DOCS)
        string(APPEND MSCL_DOCS_TITLE " Full")
    endif()
    string(APPEND MSCL_DOCS_TITLE " ${MSCL_DOCS_COMPONENT_NAME}")

    # Generate the project file in the generated project directory
    # This requires 'NaturalDocs_VERSION', 'MSCL_DOCS_TITLE', and 'MSCL_CURRENT_YEAR' to be set
    set(DOCS_PROJECT_FILE "Project.txt")
    configure_file(
        "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/${DOCS_PROJECT_FILE}.in"
        "${DOCS_PROJECT_DIR}/${DOCS_PROJECT_FILE}"
        @ONLY
    )

    # Generate the comment file in the generated project directory
    # This requires 'NaturalDocs_VERSION' to be set
    set(DOCS_COMMENT_FILE "Comments.txt")
    configure_file(
        "${CMAKE_CURRENT_LIST_DIR}/${DOCS_COMMENT_FILE}.in"
        "${DOCS_PROJECT_DIR}/${DOCS_COMMENT_FILE}"
        @ONLY
    )

    # Copy the custom stylesheet into the generated project directory
    set(DOCS_CUSTOM_STYLESHEET_FILENAME "msclDocsStyle")
    file(
        COPY "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/${DOCS_CUSTOM_STYLESHEET_FILENAME}.css"
        DESTINATION "${DOCS_PROJECT_DIR}"
    )

    add_custom_target(${MSCL_DOCS_TARGET} ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${DOCS_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${DOCS_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${DOCS_WORKING_DATA_DIR}"
        COMMAND "${NaturalDocs_EXECUTABLE}"
        --project-config "${DOCS_PROJECT_DIR}"
        --source "${MSCL_INCLUDE_DIR}"
        --output "FramedHTML" "${DOCS_OUTPUT_DIR}"
        --style "${DOCS_CUSTOM_STYLESHEET_FILENAME}"
        --working-data "${DOCS_WORKING_DATA_DIR}"
    )

    # Add the docs target as a dependency to the all docs target
    add_dependencies("${MSCL_ALL_DOCS_TARGET}" "${MSCL_DOCS_TARGET}")

    install(
        DIRECTORY "${DOCS_OUTPUT_DIR}"
        DESTINATION "${MSCL_DOCS_COMPONENT_NAME}" # Use the component name as the install prefix
        COMPONENT "${MSCL_DOCS_COMPONENT_NAME}"
    )
endfunction()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/api_docs")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/docs")

if(MSCL_BUILD_PACKAGE)
    microstrain_set_cpack_component_file_name(
        COMPONENT_NAME "${MSCL_DOCS_COMPONENT_NAME}"
        COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
    )
endif()
