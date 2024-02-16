function(mscl_configure_example_cpp)
  if(CMAKE_PROJECT_NAME STREQUAL "MSCL")
    # NOTE: This section will only be called if this CMakeLists.txt is imported during the MSCL build.
    #       If not building in the MSCL repo, this can be safely ignored or removed
    set(MSCL_LIBRARY MSCL)
    set(MSCL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../MSCL/source")
    target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/MSCL/MSCL_Static/${CMAKE_CFG_INTDIR})
    add_dependencies(${PROJECT_NAME} MSCL_Static)
  endif()

  find_package(MSCL REQUIRED)

  target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MSCL_INCLUDE_DIRS}
  )
  target_link_libraries(${PROJECT_NAME} ${MSCL_LIBRARIES})

  # Don't let MSCL find it's own libraries
  target_compile_definitions(${PROJECT_NAME} PRIVATE BOOST_ALL_NO_LIB)

  if(MSVC)
    # On windows, we need to set the runtime library to the same as MSCL
    target_compile_options(${PROJECT_NAME} PRIVATE /MT$<$<CONFIG:Debug>:d>)

    # Ignore some annoying linker warnings
    target_link_options(${PROJECT_NAME} PRIVATE /ignore:4099)
  endif()
endfunction()
