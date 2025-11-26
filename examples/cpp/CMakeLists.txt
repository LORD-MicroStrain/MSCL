set(MSCL_EXAMPLES_CPP_COMPONENT_NAME "Cpp-Examples")

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/displacement")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/inertial")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/wireless")

microstrain_set_cpack_component_file_name(
    COMPONENT_NAME "${MSCL_EXAMPLES_CPP_COMPONENT_NAME}"
    COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
)
