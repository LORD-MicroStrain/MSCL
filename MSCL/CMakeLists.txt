project(MSCL)

# Since we use globs here we won't need to update this file every time.
# NOTE: If building locally and you add a file, you will need to reconfigure CMake to make it appear to the glob
file(GLOB_RECURSE SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/source/**/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/**/*.h
)

# Create VS filters based on file directories
foreach(FILE ${SRC_FILES})
  # Get the directory of the source file
  get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

  # Remove common directory prefix to make the group and removed the trailing mscl source directory
  string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/source/mscl" "" GROUP "${PARENT_DIR}")

  # Make sure we are using windows slashes
  string(REPLACE "/" "\\" GROUP "${GROUP}")

  # Group into "Source Files" and "Header Files"
  if("${FILE}" MATCHES ".*\\.cpp")
    set(GROUP "Source Files${GROUP}")
  elseif("${FILE}" MATCHES ".*\\.h")
    set(GROUP "Header Files${GROUP}")
  endif()

  source_group("${GROUP}" FILES "${FILE}")
endforeach()


# Files that should only be compiled on windows
set(WINDOWS_ONLY_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Communication/WsdaFinder.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Communication/WsdaFinder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Communication/UpnpService.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Communication/UpnpService.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Communication/UpnpDeviceFinderCallback.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Communication/UpnpDeviceFinderCallback.cpp
)

# Files that should only be compiled on linux
set(LINUX_ONLY_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Communication/UnixSocketConnection.cpp
)

# Excluded file on all OSes
set(LIB_EXCLUDED_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Wrapper/MSCL_Wrap.cpp
)

# Remove files from the list based on the OS
if(WIN32)
  foreach(item_to_remove IN LISTS LINUX_ONLY_FILES)
    list(REMOVE_ITEM SRC_FILES "${item_to_remove}")
  endforeach()
endif()
if(UNIX)
  foreach(item_to_remove IN LISTS WINDOWS_ONLY_FILES)
    list(REMOVE_ITEM SRC_FILES "${item_to_remove}")
  endforeach()
endif()
foreach(item_to_remove IN LISTS LIB_EXCLUDED_FILES)
  list(REMOVE_ITEM SRC_FILES "${item_to_remove}")
endforeach()

# Configure some compiler flags
set(LIB_DEFINES "")
if(NOT ${WITH_SSL})
  list(APPEND LIB_DEFINES MSCL_DISABLE_SSL)
endif()
if(NOT ${WITH_WEBSOCKETS})
  list(APPEND LIB_DEFINES MSCL_DISABLE_WEBSOCKETS)
endif()
if(UNIX)
  list(APPEND LIB_DEFINES UNIX_BUILD)
endif()

# Add some include directories
set(LIB_INCLUDE_DIRS
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/source
)
if(${WITH_SSL})
  list(APPEND LIB_INCLUDE_DIRS ${OPENSSL_INCLUDE_DIR})
endif()

# Collect the list of shared libraries to link against if building shared
if(BUILD_SHARED_LIBS)
  set(LIB_SHARED_LIBRARIES
    ${Boost_SHARED_LIBRARIES}
  )
  if(${WITH_SSL})
    list(APPEND LIB_SHARED_LIBRARIES ${OPENSSL_SHARED_LIBRARIES})
  endif()
endif()

# Collect the list of static libraries to link against if building static
set(LIB_STATIC_LIBRARIES
  ${Boost_STATIC_LIBRARIES}
)
if(${WITH_SSL})
  list(APPEND LIB_STATIC_LIBRARIES ${OPENSSL_STATIC_LIBRARIES})
endif()

# Build both the C++ shared and static libraries if configured to do so
set(LIB_NAME ${PROJECT_NAME})
set(LIB_NAME_STATIC ${LIB_NAME}_Static)
set(LIB_NAME_SHARED ${LIB_NAME}_Shared)

add_library(${LIB_NAME_STATIC} STATIC ${SRC_FILES})
set(LIB_NAME_STATIC_DIR ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME_STATIC})
set_target_properties(${LIB_NAME_STATIC}
  PROPERTIES
  OUTPUT_NAME ${LIB_NAME}
  COMPILE_PDB_NAME ${LIB_NAME}
  COMPILE_PDB_OUTPUT_DIRECTORY ${LIB_NAME_STATIC_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${LIB_NAME_STATIC_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${LIB_NAME_STATIC_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${LIB_NAME_STATIC_DIR}
)

# Configure some precompiled headers
target_precompile_headers(${LIB_NAME_STATIC} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/source/stdafx.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/stdafx.cpp
)

# In order to copy the headers, create a cmake script that will do the copying
set(MSCL_STATIC_HEADER_CP_SCRIPT ${CMAKE_BINARY_DIR}/${LIB_NAME_STATIC}_$<CONFIG>_header_cp.cmake)
set(MSCL_STATIC_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/C++/Static/${LIB_NAME})
set(MSCL_STATIC_OUTPUT_INCLUDE_DIR ${MSCL_STATIC_OUTPUT_DIR}/include)
set(MSCL_STATIC_OUTPUT_LIB_DIR ${MSCL_STATIC_OUTPUT_DIR}/lib/${MSCL_ARCH_NAME}/$<CONFIG>)
file(GENERATE
  OUTPUT ${MSCL_STATIC_HEADER_CP_SCRIPT}
  CONTENT "file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl DESTINATION ${MSCL_STATIC_OUTPUT_INCLUDE_DIR} FILES_MATCHING PATTERN *.h PATTERN Wrapper EXCLUDE)\n"
)

# Copy the artifacts to an Output directory to make it easier for users to navigate the artifacts
add_custom_command(TARGET ${LIB_NAME_STATIC} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_STATIC_OUTPUT_INCLUDE_DIR}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_STATIC_OUTPUT_LIB_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:${LIB_NAME_STATIC}> ${MSCL_STATIC_OUTPUT_LIB_DIR}
  COMMAND ${CMAKE_COMMAND} -P ${MSCL_STATIC_HEADER_CP_SCRIPT}
)

if(UNIX)
  # If running on linux, mark the target for installation
  install(
    TARGETS ${LIB_NAME_STATIC}
    DESTINATION "lib"
    COMPONENT static
  )
  install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source/mscl"
    DESTINATION "include"
    COMPONENT static
    FILES_MATCHING PATTERN "*.h"
  )
endif()
if(BUILD_SHARED_LIBS)
  add_library(${LIB_NAME_SHARED} SHARED ${SRC_FILES})
  set(LIB_NAME_SHARED_DIR ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME_SHARED})
  set_target_properties(${LIB_NAME_SHARED}
    PROPERTIES
    OUTPUT_NAME ${LIB_NAME}
    PDB_NAME ${LIB_NAME}
    PDB_OUTPUT_DIRECTORY ${LIB_NAME_SHARED_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_NAME_SHARED_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_NAME_SHARED_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${LIB_NAME_SHARED_DIR}
  )

  # Configure some precompiled headers
  target_precompile_headers(${LIB_NAME_SHARED} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/stdafx.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/stdafx.cpp
  )

  # In order to copy the headers, create a cmake script that will do the copying
  set(MSCL_SHARED_HEADER_CP_SCRIPT ${CMAKE_BINARY_DIR}/${LIB_NAME_SHARED}_$<CONFIG>_header_cp.cmake)
  set(MSCL_SHARED_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/C++/Shared/${LIB_NAME})
  set(MSCL_SHARED_OUTPUT_INCLUDE_DIR ${MSCL_SHARED_OUTPUT_DIR}/include)
  set(MSCL_SHARED_OUTPUT_LIB_DIR ${MSCL_SHARED_OUTPUT_DIR}/lib/${MSCL_ARCH_NAME}/$<CONFIG>)
  file(GENERATE
    OUTPUT ${MSCL_SHARED_HEADER_CP_SCRIPT}
    CONTENT "file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl DESTINATION ${MSCL_SHARED_OUTPUT_INCLUDE_DIR} FILES_MATCHING PATTERN *.h PATTERN Wrapper EXCLUDE)\n"
  )

  # Copy the artifacts to an Output directory to make it easier for users to navigate the artifacts
  add_custom_command(TARGET ${LIB_NAME_SHARED} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_SHARED_OUTPUT_INCLUDE_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_SHARED_OUTPUT_LIB_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:${LIB_NAME_SHARED}> ${MSCL_SHARED_OUTPUT_LIB_DIR}
    COMMAND ${CMAKE_COMMAND} -P ${MSCL_SHARED_HEADER_CP_SCRIPT}
  )

  if(UNIX)
    # If running on linux, mark the target for installation
    install(
      TARGETS ${LIB_NAME_SHARED}
      DESTINATION "lib"
      COMPONENT shared
    )
    install(
      DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source/mscl"
      DESTINATION "include"
      COMPONENT shared
      FILES_MATCHING PATTERN "*.h"
    )
  endif()
endif()

# Compiler definitions
target_compile_definitions(${LIB_NAME_STATIC} PRIVATE ${LIB_DEFINES})
target_include_directories(${LIB_NAME_STATIC} PRIVATE ${LIB_INCLUDE_DIRS})
target_compile_options(${LIB_NAME_STATIC} PRIVATE
  $<$<CXX_COMPILER_ID:GNU>:-fPIC>  # Normally static libraries aren't compiled with this flag, but we need it to compile our bindings properly
  $<$<CXX_COMPILER_ID:MSVC>:/MT$<$<CONFIG:Debug>:d>>
)
if(BUILD_SHARED_LIBS)
  target_compile_options(${LIB_NAME_SHARED} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/MD$<$<CONFIG:Debug>:d>>
  )
  target_compile_definitions(${LIB_NAME_SHARED} PRIVATE ${LIB_DEFINES})
  target_include_directories(${LIB_NAME_SHARED} PRIVATE ${LIB_INCLUDE_DIRS})
endif()

# Shared linker options
if(BUILD_SHARED_LIBS)
  if(UNIX AND LINK_STATIC_DEPS)
    target_link_libraries(${LIB_NAME_SHARED} ${LIB_STATIC_LIBRARIES})
  else()
    target_link_libraries(${LIB_NAME_SHARED} ${LIB_SHARED_LIBRARIES})
  endif()
endif()

# Optionally generate the language bindings using swig
if(BUILD_PYTHON2 OR BUILD_PYTHON3 OR BUILD_CSHARP)
  include(UseSWIG)
  include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/mscl_python_swig.cmake)

  if(MSVC)
    # Linking through the MSCL cmake interface causes linker error 4197. This is related to swig and can be ignored
    #TODO: Figure out how to fix this linker error
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /ignore:4197")
  endif()

  # Set up our source
  set(SWIG_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Wrapper/MSCL_Main_Interface.i
  )
  set_property(SOURCE ${SWIG_SOURCE_FILES} PROPERTY CPLUSPLUS ON)

  # Different compile flags depending on the platform
  set(PYTHON_COMPILE_OPTIONS $<$<CXX_COMPILER_ID:MSVC>:/bigobj /MT$<$<CONFIG:Debug>:d>>)
  set(PYTHON_LINK_OPTIONS $<$<CXX_COMPILER_ID:GNU>:-Wl,--no-as-needed>)
  set(PYTHON_LINK_LIBRARIES ${LIB_NAME_STATIC})
  if((UNIX AND LINK_STATIC_DEPS) OR WIN32)
    list(APPEND PYTHON_LINK_LIBRARIES ${Boost_STATIC_LIBRARIES})
  else()
    list(APPEND PYTHON_LINK_LIBRARIES ${Boost_SHARED_LIBRARIES})
  endif()
  if(WITH_SSL)
    if((UNIX AND PYTHON_STATIC_DEPS) OR WIN32)
      list(APPEND PYTHON_LINK_LIBRARIES ${OPENSSL_STATIC_LIBRARIES})
    else()
      list(APPEND PYTHON_LINK_LIBRARIES ${OPENSSL_SHARED_LIBRARIES})
    endif()
  endif()

  # Build for python3
  if(BUILD_PYTHON3)
    set(PYTHON3_MODULE_NAME MSCL_Python3)
    set(MSCL_PYTHON3_VERSION ${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR})
    mscl_python_swig(
      MODULE_NAME ${PYTHON3_MODULE_NAME}
      MODULE_VERSION ${MSCL_GIT_VERSION}
      OUTPUT_NAME mscl
      OUTPUT_DIR ${MSCL_OUTPUT_DIR}
      PYTHON_VERSION ${MSCL_PYTHON3_VERSION}
      ARCH ${MSCL_ARCH_NAME}
      SOURCES ${SWIG_SOURCE_FILES}
      COMPILE_OPTIONS ${PYTHON_COMPILE_OPTIONS}
      COMPILE_DEFINITIONS ${LIB_DEFINES} SWIG_PYTHON_INTERPRETER_NO_DEBUG
      INCLUDE_DIRECTORIES ${LIB_INCLUDE_DIRS} ${Python3_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Wrapper  # Temp fix for bad include paths
      LINK_DIRECTORIES ${Python3_LIBRARY_DIRS}
      LINK_OPTIONS ${PYTHON_LINK_OPTIONS}
      LINK_LIBRARIES ${PYTHON_LINK_LIBRARIES} ${Python3_LIBRARIES}
    )
  endif()

  # Build for python2
  if(BUILD_PYTHON2)
    set(PYTHON2_MODULE_NAME MSCL_Python2)
    set(MSCL_PYTHON2_VERSION ${Python2_VERSION_MAJOR}.${Python2_VERSION_MINOR})
    mscl_python_swig(
      MODULE_NAME ${PYTHON2_MODULE_NAME}
      MODULE_VERSION ${MSCL_GIT_VERSION}
      OUTPUT_NAME mscl
      OUTPUT_DIR ${MSCL_OUTPUT_DIR}
      PYTHON_VERSION ${MSCL_PYTHON2_VERSION}
      ARCH ${MSCL_ARCH_NAME}
      SOURCES ${SWIG_SOURCE_FILES}
      COMPILE_OPTIONS ${PYTHON_COMPILE_OPTIONS}
      COMPILE_DEFINITIONS ${LIB_DEFINES} SWIG_PYTHON_INTERPRETER_NO_DEBUG
      INCLUDE_DIRECTORIES ${LIB_INCLUDE_DIRS} ${Python2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Wrapper  # Temp fix for bad include paths
      LINK_DIRECTORIES ${Python2_LIBRARY_DIRS}
      LINK_OPTIONS ${PYTHON_LINK_OPTIONS}
      LINK_LIBRARIES ${PYTHON_LINK_LIBRARIES} ${Python2_LIBRARIES}
    )
  endif()

  # Build C# on Windows
  # Wish we could generate it the same as python, but we need to get the list of CSharp files
  if(BUILD_CSHARP)
    set(CSHARP_MODULE_NAME MSCL_CSharp)

    # Hack of all hacks, but we need to generate the source separately so we can determine the source files at configure time
    set(CSHARP_MODULE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CSHARP_MODULE_NAME})
    set(CSHARP_MODULE_CPP_FILE ${CSHARP_MODULE_DIR}/MSCL_Main_InterfaceCSHARP_wrap.cxx)
    file(MAKE_DIRECTORY ${CSHARP_MODULE_DIR})
    message(STATUS "Generating CSharp binding source")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E env SWIG_LIB=${SWIG_DIR} "${SWIG_EXECUTABLE}" -csharp -namespace mscl -outdir "${CSHARP_MODULE_DIR}" -c++ -dllimport MSCL -o "${CSHARP_MODULE_CPP_FILE}" "${SWIG_SOURCE_FILES}"
      COMMAND_ERROR_IS_FATAL ANY
    )
    file(GLOB MSCL_GENERATED_CSHARP_SOURCE
      ${CSHARP_MODULE_DIR}/*.cs
    )

    # Build the C++ wrapper
    add_library(${CSHARP_MODULE_NAME} SHARED ${CSHARP_MODULE_CPP_FILE})
    target_compile_options(${CSHARP_MODULE_NAME} PRIVATE
      /bigobj
      /MT$<$<CONFIG:Debug>:d>
    )
    target_compile_definitions(${CSHARP_MODULE_NAME} PRIVATE
      ${LIB_DEFINES}
    )
    target_include_directories(${CSHARP_MODULE_NAME} PRIVATE
      ${LIB_INCLUDE_DIRS}
      ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Wrapper  # Temp fix for bad include path
    )
    target_link_libraries(${CSHARP_MODULE_NAME} PRIVATE
      ${LIB_NAME_STATIC} ${Boost_STATIC_LIBRARIES}
    )
    if(WITH_SSL)
      target_link_libraries(${CSHARP_MODULE_NAME} PRIVATE
        ${OPENSSL_STATIC_LIBRARIES}
      )
    endif()
    set_target_properties(${CSHARP_MODULE_NAME}
      PROPERTIES
      OUTPUT_NAME ${LIB_NAME}
      ARCHIVE_OUTPUT_DIRECTORY "${CSHARP_MODULE_DIR}"
      LIBRARY_OUTPUT_DIRECTORY "${CSHARP_MODULE_DIR}"
      RUNTIME_OUTPUT_DIRECTORY "${CSHARP_MODULE_DIR}"
    )

    # Add the CSharp library
    set(MSCL_CSHARP_SOURCE
      ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Wrapper/CSharp/Properties/AssemblyInfo.cs
      ${CMAKE_CURRENT_SOURCE_DIR}/source/mscl/Wrapper/CSharp/mscl/Exceptions.cs
      ${MSCL_GENERATED_CSHARP_SOURCE}
    )
    set(MSCL_Managed_NAME MSCL_Managed)
    add_library(${MSCL_Managed_NAME} SHARED ${MSCL_CSHARP_SOURCE})
    target_link_libraries(${MSCL_Managed_NAME} ${CSHARP_MODULE_NAME})

    # Copy the library to an Output directory
    set(MSCL_Managed_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/DotNet/${MSCL_ARCH_NAME}/$<CONFIG>)
    add_custom_command(TARGET ${MSCL_Managed_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_Managed_OUTPUT_DIR}
      COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:${MSCL_Managed_NAME}> ${MSCL_Managed_OUTPUT_DIR}
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${CSHARP_MODULE_NAME}> ${MSCL_Managed_OUTPUT_DIR}
    )
  endif()

  # Build the documentation
  if(BUILD_DOCUMENTATION)
    set(MSCL_DOCS_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/Documentation/MSCL_Docs)
    set(MSCL_API_DOCS_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/Documentation/MSCL_API_Docs)
    add_custom_target(MSCL_Docs
      ALL
      DEPENDS ${SRC_FILES}
      COMMAND ${CMAKE_COMMAND} -E remove_directory "${MSCL_OUTPUT_DIR}/Documentation"
      COMMAND ${CMAKE_COMMAND} -E make_directory "${MSCL_DOCS_OUTPUT_DIR}"
      COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_SOURCE_DIR}/../BuildScripts/NaturalDocsProjects/MSCL_Docs_Project/Working Data"
      COMMAND ${CMAKE_COMMAND} -E env ${NaturalDocs_EXECUTABLE} -i "${CMAKE_CURRENT_SOURCE_DIR}/source/mscl" -o FramedHTML "${MSCL_DOCS_OUTPUT_DIR}" -p "${CMAKE_CURRENT_SOURCE_DIR}/../BuildScripts/NaturalDocsProjects/MSCL_Docs_Project" -s msclDocsStyle
      COMMAND ${CMAKE_COMMAND} -E make_directory "${MSCL_API_DOCS_OUTPUT_DIR}"
      COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_SOURCE_DIR}/../BuildScripts/NaturalDocsProjects/MSCL_API_Docs_Project/Working Data"
      COMMAND ${CMAKE_COMMAND} -E env ${NaturalDocs_EXECUTABLE} -i "${CMAKE_CURRENT_SOURCE_DIR}/source/mscl" -o FramedHTML "${MSCL_API_DOCS_OUTPUT_DIR}" -p "${CMAKE_CURRENT_SOURCE_DIR}/../BuildScripts/NaturalDocsProjects/MSCL_API_Docs_Project" -s msclDocsStyle
    )
  endif()
endif()


# If we were asked to build packages, include CPack and set up packaging
if(BUILD_PACKAGE)
  # NOTE: CPack requires all these variables to be set before importing the module. Do not move them after the include(CPack) line
  set(CPACK_GENERATOR "${FOUND_CPACK_GENERATORS}")
  set(CPACK_PACKAGE_VENDOR "MicroStrain by HBK")
  set(CPACK_PACKAGE_CONTACT "Rob Fisher <rob.fisher@hbkworld.com>")
  set(CPACK_COMPONENTS_ALL "static")
  if(BUILD_SHARED_LIBS)
    list(APPEND CPACK_COMPONENTS_ALL shared)
  endif()
  if(BUILD_PYTHON3)
    list(APPEND CPACK_COMPONENTS_ALL python${MSCL_PYTHON3_VERSION})
  endif()
  if(BUILD_PYTHON2)
    list(APPEND CPACK_COMPONENTS_ALL python${MSCL_PYTHON2_VERSION})
  endif()

  # Massage the version number a little so we can set the proper version
  string(REGEX REPLACE "^v([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\1.\\2.\\3" MSCL_GIT_VERSION_CPACK ${MSCL_GIT_VERSION})
  set(CPACK_PACKAGE_VERSION ${MSCL_GIT_VERSION_CPACK})

  set(MSCL_FILE_NAME_PREFIX "MSCL_${MSCL_GIT_VERSION}_${CMAKE_SYSTEM_PROCESSOR}_${CMAKE_SYSTEM_NAME}")
  set(MSCL_FILE_NAME_SHARED "${MSCL_FILE_NAME_PREFIX}_Shared_C++")
  set(MSCL_FILE_NAME_STATIC "${MSCL_FILE_NAME_PREFIX}_Static_C++")
  set(MSCL_FILE_NAME_PYTHON2 "${MSCL_FILE_NAME_PREFIX}_Python${MSCL_PYTHON2_VERSION}")
  set(MSCL_FILE_NAME_PYTHON3 "${MSCL_FILE_NAME_PREFIX}_Python${MSCL_PYTHON3_VERSION}")

  # DEB specific configuration
  # Build different deb packages for each target
  set(CPACK_DEBIAN_SHARED_FILE_NAME "${MSCL_FILE_NAME_SHARED}.deb")
  set(CPACK_DEBIAN_STATIC_FILE_NAME "${MSCL_FILE_NAME_STATIC}.deb")
  set(CPACK_DEBIAN_PYTHON${MSCL_PYTHON2_VERSION}_FILE_NAME "${MSCL_FILE_NAME_PYTHON2}.deb")
  set(CPACK_DEBIAN_PYTHON${MSCL_PYTHON3_VERSION}_FILE_NAME "${MSCL_FILE_NAME_PYTHON3}.deb")
  set(CPACK_DEB_COMPONENT_INSTALL ON)

  # Most packages share these dependencies
  set(CPACK_DEBIAN_COMMON_DEPS libboost-system-dev libboost-filesystem-dev)
  if(WITH_SSL)
    list(APPEND CPACK_DEBIAN_COMMON_DEPS libssl-dev)
  endif()
  string(REPLACE ";" ", " CPACK_DEBIAN_COMMON_DEPS "${CPACK_DEBIAN_COMMON_DEPS}")

  # Package specific configuration for debian packages
  set(CPACK_DEBIAN_STATIC_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
  set(CPACK_DEBIAN_SHARED_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
  set(CPACK_DEBIAN_PYTHON${MSCL_PYTHON3_VERSION}_PACKAGE_DEPENDS "python${MSCL_PYTHON3_VERSION}")
  if(NOT LINK_STATIC_DEPS)
    list(APPEND CPACK_DEBIAN_PYTHON${MSCL_PYTHON3_VERSION}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
    string(REPLACE ";" ", " CPACK_DEBIAN_PYTHON${MSCL_PYTHON3_VERSION}_PACKAGE_DEPENDS "${CPACK_DEBIAN_PYTHON${MSCL_PYTHON3_VERSION}_PACKAGE_DEPENDS}")
  endif()
  set(CPACK_DEBIAN_PYTHON${MSCL_PYTHON2_VERSION}_PACKAGE_DEPENDS "python${MSCL_PYTHON2_VERSION}")
  if(NOT LINK_STATIC_DEPS)
    list(APPEND CPACK_DEBIAN_PYTHON${MSCL_PYTHON2_VERSION}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
    string(REPLACE ";" ", " CPACK_DEBIAN_PYTHON${MSCL_PYTHON2_VERSION}_PACKAGE_DEPENDS "${CPACK_DEBIAN_PYTHON${MSCL_PYTHON2_VERSION}_PACKAGE_DEPENDS}")
  endif()

  # RPM specific configuration
  # Build different RPM packages for each target
  set(CPACK_RPM_SHARED_FILE_NAME "${MSCL_FILE_NAME_SHARED}.rpm")
  set(CPACK_RPM_STATIC_FILE_NAME "${MSCL_FILE_NAME_STATIC}.rpm")
  set(CPACK_RPM_PYTHON${MSCL_PYTHON2_VERSION}_FILE_NAME "${MSCL_FILE_NAME_PYTHON2}.rpm")
  set(CPACK_RPM_PYTHON${MSCL_PYTHON3_VERSION}_FILE_NAME "${MSCL_FILE_NAME_PYTHON3}.rpm")
  set(CPACK_RPM_COMPONENT_INSTALL ON)
  set(CPACK_RPM_PACKAGE_AUTOREQ OFF)

  # Most packages share these dependencies
  set(CPACK_RPM_COMMON_DEPS boost-filesystem boost-system boost-devel)
  if(WITH_SSL)
    list(APPEND CPACK_RPM_COMMON_DEPS openssl-devel)
  endif()
  string(REPLACE ";" ", " CPACK_RPM_COMMON_DEPS "${CPACK_RPM_COMMON_DEPS}")

  # Package specific configuration for RPM packages
  set(CPACK_RPM_STATIC_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
  set(CPACK_RPM_SHARED_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
  set(CPACK_RPM_PYTHON${MSCL_PYTHON3_VERSION}_PACKAGE_REQUIRES "python3")
  if(NOT LINK_STATIC_DEPS)
    list(APPEND CPACK_RPM_PYTHON${MSCL_PYTHON3_VERSION}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
    string(REPLACE ";" ", " CPACK_RPM_PYTHON${MSCL_PYTHON3_VERSION}_PACKAGE_REQUIRES "${CPACK_RPM_PYTHON${MSCL_PYTHON3_VERSION}_PACKAGE_REQUIRES}")
  endif()
  set(CPACK_RPM_PYTHON${MSCL_PYTHON2_VERSION}_PACKAGE_REQUIRES "python2")
  if(NOT LINK_STATIC_DEPS)
    list(APPEND CPACK_RPM_PYTHON${MSCL_PYTHON2_VERSION}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
    string(REPLACE ";" ", " CPACK_RPM_PYTHON${MSCL_PYTHON2_VERSION}_PACKAGE_REQUIRES "${CPACK_RPM_PYTHON${MSCL_PYTHON2_VERSION}_PACKAGE_REQUIRES}")
  endif()

  if(MSVC)
    set(CPACK_ARCHIVE_FILE_NAME "${MSCL_FILE_NAME_PREFIX}_MSVC_v${MSVC_TOOLSET_VERSION}")
  elseif(UNIX AND NOT APPLE)
    set(CPACK_ARCHIVE_FILE_NAME "${MSCL_FILE_NAME_PREFIX}_Linux")
  else()
    set(CPACK_ARCHIVE_FILE_NAME "${MSCL_FILE_NAME_PREFIX}")
  endif()
  set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

  # Finally include cpack which should have taken all of the previous variables into consideration
  include(CPack)

  cpack_add_component(static
    DESCRIPTION "MSCL static library and header files"
    GROUP static
  )
  if(BUILD_SHARED_LIBS)
    cpack_add_component(shared
      DESCRIPTION "MSCL shared library and header files"
      GROUP shared
    )
  endif()
  if(BUILD_PYTHON3)
    cpack_add_component(python${MSCL_PYTHON3_VERSION}
      DESCRIPTION "MSCL python bindings for ${MSCL_PYTHON3_VERSION}"
      GROUP python${MSCL_PYTHON3_VERSION}
    )
  endif()
  if(BUILD_PYTHON2)
    cpack_add_component(python${MSCL_PYTHON2_VERSION}
      DESCRIPTION "MSCL python bindings for ${MSCL_PYTHON2_VERSION}"
      GROUP python${MSCL_PYTHON2_VERSION}
    )
  endif()
endif()
