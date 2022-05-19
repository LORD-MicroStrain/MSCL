include(CMakeParseArguments)

function(mscl_python_swig)
  set(single_value_args MODULE_NAME MODULE_VERSION OUTPUT_NAME OUTPUT_DIR PYTHON_VERSION ARCH)
  set(multi_value_args SOURCES SWIG_FLAGS COMPILE_OPTIONS COMPILE_DEFINITIONS INCLUDE_DIRECTORIES LINK_DIRECTORIES LINK_OPTIONS LINK_LIBRARIES)
  cmake_parse_arguments(
    mscl_python_swig
    ""
    "${single_value_args}"
    "${multi_value_args}"
    ${ARGN}
  )

  # Set up the swig target
  set(OUTFILE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${mscl_python_swig_MODULE_NAME})
  set(OUTPUT_DIR ${OUTFILE_DIR}/${OUTPUT_NAME})
  swig_add_library(${mscl_python_swig_MODULE_NAME}
    LANGUAGE python
    TYPE SHARED
    SOURCES ${mscl_python_swig_SOURCES}
    OUTPUT_DIR ${OUTPUT_DIR}
    OUTFILE_DIR ${OUTFILE_DIR}
  )

  # Some extra flags to pass directly to swig
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY SWIG_COMPILE_OPTIONS ${mscl_python_swig_SWIG_FLAGS})

  # Compiler flags for the target that will be passed directly to the compiler
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY COMPILE_OPTIONS ${mscl_python_swig_COMPILE_OPTIONS})
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY GENERATED_COMPILE_OPTIONS ${mscl_python_swig_COMPILE_OPTIONS})

  # Compiler definitons for both the compiler and swig
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY COMPILE_DEFINITIONS ${mscl_python_swig_COMPILE_DEFINITIONS})
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY SWIG_COMPILE_DEFINITIONS ${mscl_python_swig_COMPILE_DEFINITIONS})
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY GENERATED_COMPILE_DEFINITIONS ${mscl_python_swig_COMPILE_DEFINITIONS})

  # Include directories
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY INCLUDE_DIRECTORIES ${mscl_python_swig_INCLUDE_DIRECTORIES})
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY GENERATED_INCLUDE_DIRECTORIES ${mscl_python_swig_INCLUDE_DIRECTORIES})

  # Link directories
  target_link_directories(${mscl_python_swig_MODULE_NAME} PRIVATE ${mscl_python_swig_LINK_DIRECTORIES})

  # Raw linker flags
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY STATIC_LINK_OPTIONS ${mscl_python_swig_LINK_OPTIONS} $<$<CXX_COMPILER_ID:MSVC>:/ignore:4099>)
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY LINK_OPTIONS ${mscl_python_swig_LINK_OPTIONS} $<$<CXX_COMPILER_ID:MSVC>:/ignore:4099>)

  # Link libraries
  target_link_libraries(${mscl_python_swig_MODULE_NAME} ${mscl_python_swig_LINK_LIBRARIES})

  # Change the output directory and name of the resulting library
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
  set_property(TARGET ${mscl_python_swig_MODULE_NAME} PROPERTY OUTPUT_NAME ${mscl_python_swig_OUTPUT_NAME})

  # Copy the python file to the same directory as the library
  set(PYTHON_INTERFACE_FILE ${OUTFILE_DIR}/${mscl_python_swig_OUTPUT_NAME}.py)
  add_custom_command(TARGET ${mscl_python_swig_MODULE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${OUTPUT_DIR}$<$<BOOL:${WIN32}>:/$<CONFIG>> ${mscl_python_swig_OUTPUT_DIR}/Python/${mscl_python_swig_PYTHON_VERSION}/${mscl_python_swig_ARCH}/$<CONFIG>
    COMMAND ${CMAKE_COMMAND} -E copy ${PYTHON_INTERFACE_FILE} ${mscl_python_swig_OUTPUT_DIR}/Python/${mscl_python_swig_PYTHON_VERSION}/${mscl_python_swig_ARCH}/$<CONFIG>/${mscl_python_swig_OUTPUT_NAME}.py
  )

  if(UNIX)
    # If running on linux, install the artifacts
    set(PYTHON_SITE_PACKAGES_DIR lib/python${mscl_python_swig_PYTHON_VERSION}/site-packages)
    install(
      TARGETS ${mscl_python_swig_MODULE_NAME}
      DESTINATION "${PYTHON_SITE_PACKAGES_DIR}"
      COMPONENT python${mscl_python_swig_PYTHON_VERSION}
    )
    install(
      FILES "${PYTHON_INTERFACE_FILE}"
      DESTINATION "${PYTHON_SITE_PACKAGES_DIR}"
      COMPONENT python${mscl_python_swig_PYTHON_VERSION}
    )
  endif()
endfunction()