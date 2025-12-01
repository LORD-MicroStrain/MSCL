function(mscl_managed_add_references TARGET_NAME)
    if(NOT TARGET_NAME)
        message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION} requires the target name as a parameter")
    endif()

    if((NOT DEFINED CACHE{MSCL_MANAGED_LIBRARY} AND NOT DEFINED MSCL_MANAGED_LIBRARY) OR NOT TARGET "${MSCL_MANAGED_LIBRARY}")
        message(FATAL_ERROR "The MSCL Managed library doesn't exist")
    endif()

    if((NOT DEFINED CACHE{MSCL_CSHARP_LIBRARY} AND NOT DEFINED MSCL_CSHARP_LIBRARY) OR NOT TARGET "${MSCL_CSHARP_LIBRARY}")
        message(FATAL_ERROR "The MSCL CSharp library doesn't exist")
    endif()

    # PRIVATE/PUBLIC doesn't seem to make a difference for C# references
    # This automatically marks the reference for copy into the build directory
    target_link_libraries("${TARGET_NAME}" PRIVATE
        "${MSCL_MANAGED_LIBRARY}"
        "${MSCL_CSHARP_LIBRARY}"
    )

    # The managed library needs to unmanaged library in the same build directory
    # for the executable to run.
    # For projects not configured with CMake, make sure MSCL_Managed.dll and
    # MSCL.dll are copied into the output directory.
    # C# project references will do this automatically if set up correctly
    add_custom_command(TARGET "${TARGET_NAME}" POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${MSCL_CSHARP_LIBRARY}>" # Copy the MSCL 'unmanaged' C# library
        "$<TARGET_FILE_DIR:${TARGET_NAME}>"     # into the project output directory
        COMMENT "Copying $<TARGET_FILE_NAME:${MSCL_CSHARP_LIBRARY}> into $<TARGET_FILE_DIR:${TARGET_NAME}>"
    )
endfunction()
