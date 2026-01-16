if(NOT WIN32)
    message(WARNING "Building documentation is only supported on Windows")
    return()
endif()

microstrain_append_cmake_folder()

# Include the docs utilities file for easier configuration
# This will initialize everything needed to use Natural Docs as well as include helper functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(mscl_docs_utilities)

set(MSCL_DOCS_ROOT_CONFIGURE_FILES_DIR "${CMAKE_CURRENT_LIST_DIR}")

set(MSCL_DOCS_TARGET_ALL "${PROJECT_NAME}-Docs")
add_custom_target(${MSCL_DOCS_TARGET_ALL})

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/api_docs")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/full_docs")

if(MSCL_BUILD_PACKAGE)
    microstrain_set_cpack_component_file_name(
        COMPONENT_NAME "${MSCL_DOCS_COMPONENT_NAME}"
        COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
    )
endif()
