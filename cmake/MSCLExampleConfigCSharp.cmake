function(mscl_configure_example_csharp)
  if(CMAKE_PROJECT_NAME STREQUAL "MSCL")
    # NOTE: This section will only be called if this CMakeLists.txt is imported during the MSCL build.
    #       If not building in the MSCL repo, this can be safely ignored or removed
    set(MSCL_Managed_LIBRARIES MSCL_Managed)
    set(MSCL_Managed_LIBRARY_PATH $<TARGET_FILE:MSCL_Managed>)
    set(MSCL_Managed_INTERFACE_LIBRARY_PATH $<TARGET_FILE:MSCL_CSharp>)
  else()
    find_package(MSCL_Managed REQUIRED)
  endif()

  target_link_libraries(${PROJECT_NAME} ${MSCL_Managed_LIBRARIES})

  # This seems like the only way to properly link the CSharp file to the project, wish we could do this in the Find script
  if(NOT CMAKE_PROJECT_NAME STREQUAL "MSCL")
    set_target_properties(${PROJECT_NAME} PROPERTIES
      VS_DOTNET_REFERENCE_MSCL_Managed "${MSCL_Managed_LIBRARY_PATH}")
  endif()

  # Copy the MSCL.dll file to the build directory for this binary
  add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${MSCL_Managed_INTERFACE_LIBRARY_PATH} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM
  )

  # Copy the MSCL_Managed.dll file to the build directory for this binary
  add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${MSCL_Managed_LIBRARY_PATH} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM
  )
endfunction()
