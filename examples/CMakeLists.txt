add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/cpp")

if(MSCL_BUILD_CSHARP)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/csharp")
endif()

if(MSCL_BUILD_PYTHON)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/python")
endif()
