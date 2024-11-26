# Get the Git version to use for the version file generation
microstrain_extract_git_version(MSCL_GIT_VERSION_CLEAN MSCL_GIT_VERSION_MAJOR MSCL_GIT_VERSION_MINOR MSCL_GIT_VERSION_PATCH)

# Get the current year to make sure the file copyright is up-to-date
string(TIMESTAMP MSCL_CURRENT_YEAR "%Y")

set(MSCL_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")
set(MSCL_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/source")
set(MSCL_SOURCE_FILES_DIR "${MSCL_SOURCE_DIR}/mscl")

# Generate the version header file
set(VERSION_FILE "LibVersion.h")
set(MSCL_VERSION_IN_FILE "${CMAKE_CURRENT_LIST_DIR}/../cmake/${VERSION_FILE}.in")
set(MSCL_VERSION_OUT_FILE "${MSCL_SOURCE_FILES_DIR}/${VERSION_FILE}")
configure_file(${MSCL_VERSION_IN_FILE} ${MSCL_VERSION_OUT_FILE})

if(BUILD_CSHARP)
    # Generate the assembly info file for CSharp
    set(ASSEMBLY_FILE "AssemblyInfo.cs")
    set(MSCL_ASSEMBLY_CS_IN_FILE "${CMAKE_CURRENT_LIST_DIR}/../cmake/${ASSEMBLY_FILE}.in")
    set(MSCL_ASSEMBLY_CS_OUT_FILE "${MSCL_SOURCE_FILES_DIR}/Wrapper/CSharp/Properties/${ASSEMBLY_FILE}")
    configure_file(${MSCL_ASSEMBLY_CS_IN_FILE} ${MSCL_ASSEMBLY_CS_OUT_FILE})
endif()

# Since we use globs here we won't need to update this file every time.
# NOTE: If building locally and you add a file, you will need to reconfigure CMake to make it appear to the glob
file(GLOB_RECURSE SRC_FILES
    ${MSCL_SOURCE_DIR}/**/*.cpp
    ${MSCL_SOURCE_DIR}/**/*.h
)

# Create VS filters based on file directories
foreach(FILE ${SRC_FILES})
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group and removed the trailing mscl source directory
    string(REPLACE "${MSCL_SOURCE_FILES_DIR}" "" GROUP "${PARENT_DIR}")

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
    ${MSCL_SOURCE_FILES_DIR}/Communication/WsdaFinder.h
    ${MSCL_SOURCE_FILES_DIR}/Communication/WsdaFinder.cpp
    ${MSCL_SOURCE_FILES_DIR}/Communication/UpnpService.h
    ${MSCL_SOURCE_FILES_DIR}/Communication/UpnpService.cpp
    ${MSCL_SOURCE_FILES_DIR}/Communication/UpnpDeviceFinderCallback.h
    ${MSCL_SOURCE_FILES_DIR}/Communication/UpnpDeviceFinderCallback.cpp
)

# Files that should only be compiled on linux
set(LINUX_ONLY_FILES
    ${MSCL_SOURCE_FILES_DIR}/Communication/UnixSocketConnection.cpp
)

# Excluded file on all OSes
set(LIB_EXCLUDED_FILES
    ${MSCL_SOURCE_FILES_DIR}/Wrapper/MSCL_Wrap.cpp
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

if(NOT WITH_SSL)
    list(APPEND LIB_DEFINES MSCL_DISABLE_SSL)
endif()

if(NOT WITH_WEBSOCKETS)
    list(APPEND LIB_DEFINES MSCL_DISABLE_WEBSOCKETS)
endif()

if(UNIX)
    list(APPEND LIB_DEFINES UNIX_BUILD)
endif()

# Add some include directories
set(LIB_INCLUDE_DIRS
    ${Boost_INCLUDE_DIRS}
    ${MSCL_SOURCE_DIR}
)

if(WITH_SSL)
    list(APPEND LIB_INCLUDE_DIRS ${OPENSSL_INCLUDE_DIR})
endif()

# Collect the list of shared libraries to link against if building shared
if(BUILD_SHARED_LIBS)
    set(LIB_SHARED_LIBRARIES
        ${Boost_SHARED_LIBRARIES}
    )

    if(WITH_SSL)
        list(APPEND LIB_SHARED_LIBRARIES ${OPENSSL_SHARED_LIBRARIES})
    endif()
endif()

# Collect the list of static libraries to link against if building static
set(LIB_STATIC_LIBRARIES
    ${Boost_STATIC_LIBRARIES}
)

if(WITH_SSL)
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
    ${MSCL_SOURCE_DIR}/stdafx.h
    ${MSCL_SOURCE_DIR}/stdafx.cpp
)

# In order to copy the headers, create a cmake script that will do the copying
set(MSCL_STATIC_HEADER_CP_SCRIPT ${CMAKE_BINARY_DIR}/${LIB_NAME_STATIC}_$<CONFIG>_header_cp.cmake)
set(MSCL_STATIC_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/C++/Static/${LIB_NAME})
set(MSCL_STATIC_OUTPUT_INCLUDE_DIR ${MSCL_STATIC_OUTPUT_DIR}/include)
set(MSCL_STATIC_OUTPUT_LIB_DIR ${MSCL_STATIC_OUTPUT_DIR}/lib/${MSCL_ARCH_NAME}/$<CONFIG>)
file(GENERATE
    OUTPUT ${MSCL_STATIC_HEADER_CP_SCRIPT}
    CONTENT "file(COPY ${MSCL_SOURCE_FILES_DIR} DESTINATION ${MSCL_STATIC_OUTPUT_INCLUDE_DIR} FILES_MATCHING PATTERN *.h PATTERN Wrapper EXCLUDE)\n"
)

# Copy the artifacts to an Output directory to make it easier for users to navigate the artifacts
add_custom_command(TARGET ${LIB_NAME_STATIC} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_STATIC_OUTPUT_INCLUDE_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_STATIC_OUTPUT_LIB_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:${LIB_NAME_STATIC}> ${MSCL_STATIC_OUTPUT_LIB_DIR}
    COMMAND ${CMAKE_COMMAND} -P ${MSCL_STATIC_HEADER_CP_SCRIPT}
)

include(GNUInstallDirs)

if(MSVC)
    set(MSCL_STATIC_INSTALL_LIBDIR "MSCL/${CMAKE_INSTALL_LIBDIR}/${MSCL_ARCH_NAME}/$<CONFIG>")
    set(MSCL_STATIC_INSTALL_INCLUDEDIR "MSCL/${CMAKE_INSTALL_INCLUDEDIR}")
else()
    set(MSCL_STATIC_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}")
    set(MSCL_STATIC_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}")
endif()

set(MSCL_STATIC_INSTALL_COMPONENT ${PROJECT_NAME}_STATIC)
install(
    TARGETS ${LIB_NAME_STATIC}
    DESTINATION "${MSCL_STATIC_INSTALL_LIBDIR}"
    COMPONENT ${MSCL_STATIC_INSTALL_COMPONENT}
)
install(
    DIRECTORY "${MSCL_SOURCE_FILES_DIR}"
    DESTINATION "${MSCL_STATIC_INSTALL_INCLUDEDIR}"
    COMPONENT ${MSCL_STATIC_INSTALL_COMPONENT}
    FILES_MATCHING PATTERN "*.h"
    PATTERN "Wrapper" EXCLUDE
)

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
        ${MSCL_SOURCE_DIR}/stdafx.h
        ${MSCL_SOURCE_DIR}/stdafx.cpp
    )

    # In order to copy the headers, create a cmake script that will do the copying
    set(MSCL_SHARED_HEADER_CP_SCRIPT ${CMAKE_BINARY_DIR}/${LIB_NAME_SHARED}_$<CONFIG>_header_cp.cmake)
    set(MSCL_SHARED_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/C++/Shared/${LIB_NAME})
    set(MSCL_SHARED_OUTPUT_INCLUDE_DIR ${MSCL_SHARED_OUTPUT_DIR}/include)
    set(MSCL_SHARED_OUTPUT_LIB_DIR ${MSCL_SHARED_OUTPUT_DIR}/lib/${MSCL_ARCH_NAME}/$<CONFIG>)
    file(GENERATE
        OUTPUT ${MSCL_SHARED_HEADER_CP_SCRIPT}
        CONTENT "file(COPY ${MSCL_SOURCE_FILES_DIR} DESTINATION ${MSCL_SHARED_OUTPUT_INCLUDE_DIR} FILES_MATCHING PATTERN *.h PATTERN Wrapper EXCLUDE)\n"
    )

    # Copy the artifacts to an Output directory to make it easier for users to navigate the artifacts
    add_custom_command(TARGET ${LIB_NAME_SHARED} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_SHARED_OUTPUT_INCLUDE_DIR}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_SHARED_OUTPUT_LIB_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:${LIB_NAME_SHARED}> ${MSCL_SHARED_OUTPUT_LIB_DIR}
        COMMAND ${CMAKE_COMMAND} -P ${MSCL_SHARED_HEADER_CP_SCRIPT}
    )

    include(GNUInstallDirs)

    if(MSVC)
        set(MSCL_SHARED_INSTALL_LIBDIR "MSCL/${CMAKE_INSTALL_LIBDIR}/${MSCL_ARCH_NAME}/$<CONFIG>")
        set(MSCL_SHARED_INSTALL_INCLUDEDIR "MSCL/${CMAKE_INSTALL_INCLUDEDIR}")
    else()
        set(MSCL_SHARED_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}")
        set(MSCL_SHARED_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}")
    endif()

    set(MSCL_SHARED_INSTALL_COMPONENT ${PROJECT_NAME}_SHARED)
    install(
        TARGETS ${LIB_NAME_SHARED}
        DESTINATION "${MSCL_SHARED_INSTALL_LIBDIR}"
        COMPONENT ${MSCL_SHARED_INSTALL_COMPONENT}
    )

    install(
        DIRECTORY "${MSCL_SOURCE_FILES_DIR}"
        DESTINATION "${MSCL_SHARED_INSTALL_INCLUDEDIR}"
        COMPONENT ${MSCL_SHARED_INSTALL_COMPONENT}
        FILES_MATCHING PATTERN "*.h"
        PATTERN "Wrapper" EXCLUDE
    )
endif()

# Compiler definitions
target_compile_definitions(${LIB_NAME_STATIC} PRIVATE ${LIB_DEFINES})
target_include_directories(${LIB_NAME_STATIC} PUBLIC ${LIB_INCLUDE_DIRS})
target_compile_options(${LIB_NAME_STATIC} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fPIC> # Normally static libraries aren't compiled with this flag, but we need it to compile our bindings properly
    $<$<CXX_COMPILER_ID:MSVC>:/MT$<$<CONFIG:Debug>:d>>
    $<$<CXX_COMPILER_ID:MSVC>:/MP>
)

if(BUILD_SHARED_LIBS)
    if(MSVC)
        target_compile_options(${LIB_NAME_SHARED} PRIVATE
            /MD$<$<CONFIG:Debug>:d>
            /MP
        )
    endif()

    target_compile_definitions(${LIB_NAME_SHARED} PRIVATE ${LIB_DEFINES})
    target_include_directories(${LIB_NAME_SHARED} PUBLIC ${LIB_INCLUDE_DIRS})
endif()

# Shared linker options
if(BUILD_SHARED_LIBS)
    if(UNIX AND LINK_STATIC_DEPS)
        target_link_libraries(${LIB_NAME_SHARED} PUBLIC ${LIB_STATIC_LIBRARIES})
    else()
        target_link_libraries(${LIB_NAME_SHARED} PUBLIC ${LIB_SHARED_LIBRARIES})
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
        ${MSCL_SOURCE_FILES_DIR}/Wrapper/MSCL_Main_Interface.i
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
            INCLUDE_DIRECTORIES ${LIB_INCLUDE_DIRS} ${Python3_INCLUDE_DIRS} ${MSCL_SOURCE_FILES_DIR}/Wrapper # Temp fix for bad include paths
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
            INCLUDE_DIRECTORIES ${LIB_INCLUDE_DIRS} ${Python2_INCLUDE_DIRS} ${MSCL_SOURCE_FILES_DIR}/Wrapper # Temp fix for bad include paths
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
            /MP
        )
        target_compile_definitions(${CSHARP_MODULE_NAME} PRIVATE
            ${LIB_DEFINES}
        )
        target_include_directories(${CSHARP_MODULE_NAME} PUBLIC
            ${LIB_INCLUDE_DIRS}
            ${MSCL_SOURCE_FILES_DIR}/Wrapper # Temp fix for bad include path
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
            ${MSCL_SOURCE_FILES_DIR}/Wrapper/CSharp/Properties/${ASSEMBLY_FILE}
            ${MSCL_SOURCE_FILES_DIR}/Wrapper/CSharp/mscl/Exceptions.cs
            ${MSCL_GENERATED_CSHARP_SOURCE}
        )
        set(MSCL_Managed_NAME MSCL_Managed)
        add_library(${MSCL_Managed_NAME} SHARED ${MSCL_CSHARP_SOURCE})
        target_link_libraries(${MSCL_Managed_NAME} PUBLIC ${CSHARP_MODULE_NAME})

        # Copy the library to an Output directory
        set(MSCL_Managed_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/DotNet/${MSCL_ARCH_NAME}/$<CONFIG>)
        add_custom_command(TARGET ${MSCL_Managed_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_Managed_OUTPUT_DIR}
            COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:${MSCL_Managed_NAME}> ${MSCL_Managed_OUTPUT_DIR}
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${CSHARP_MODULE_NAME}> ${MSCL_Managed_OUTPUT_DIR}
        )

        set(MSCL_CSHARP_INSTALL_COMPONENT ${PROJECT_NAME}_CSHARP)
        install(
            TARGETS ${MSCL_Managed_NAME}
            DESTINATION "DotNet/${MSCL_ARCH_NAME}/$<CONFIG>"
            COMPONENT ${MSCL_CSHARP_INSTALL_COMPONENT}
        )
    endif()
endif()

# Build the documentation
if(BUILD_DOCUMENTATION)
    set(MSCL_BASE_DOCS_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/Documentation)
    set(MSCL_DOCS_OUTPUT_DIR ${MSCL_BASE_DOCS_OUTPUT_DIR}/MSCL_Docs)
    set(MSCL_API_DOCS_OUTPUT_DIR ${MSCL_BASE_DOCS_OUTPUT_DIR}/MSCL_API_Docs)
    set(MSCL_DOCS_TARGET MSCL_Documentation)

    add_custom_target(${MSCL_DOCS_TARGET}
        ALL
        DEPENDS ${SRC_FILES}
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${MSCL_BASE_DOCS_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${MSCL_DOCS_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_SOURCE_DIR}/../BuildScripts/NaturalDocsProjects/MSCL_Docs_Project/Working Data"
        COMMAND ${CMAKE_COMMAND} -E env ${NaturalDocs_EXECUTABLE} -i "${MSCL_SOURCE_FILES_DIR}" -o FramedHTML "${MSCL_DOCS_OUTPUT_DIR}" -p "${CMAKE_CURRENT_SOURCE_DIR}/../BuildScripts/NaturalDocsProjects/MSCL_Docs_Project" -s msclDocsStyle
        COMMAND ${CMAKE_COMMAND} -E make_directory "${MSCL_API_DOCS_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_SOURCE_DIR}/../BuildScripts/NaturalDocsProjects/MSCL_API_Docs_Project/Working Data"
        COMMAND ${CMAKE_COMMAND} -E env ${NaturalDocs_EXECUTABLE} -i "${MSCL_SOURCE_FILES_DIR}" -o FramedHTML "${MSCL_API_DOCS_OUTPUT_DIR}" -p "${CMAKE_CURRENT_SOURCE_DIR}/../BuildScripts/NaturalDocsProjects/MSCL_API_Docs_Project" -s msclDocsStyle
    )

    set(MSCL_DOCS_INSTALL_COMPONENT ${PROJECT_NAME}_DOCS)
    install(
        DIRECTORY "${MSCL_BASE_DOCS_OUTPUT_DIR}/"
        DESTINATION .
        COMPONENT ${MSCL_DOCS_INSTALL_COMPONENT}
    )
endif()

# If we were asked to build packages, include CPack and set up packaging
if(BUILD_PACKAGE)
    # Try to determine what architecture we are building for based on the compiler output
    if(MSVC)
        set(MSCL_ARCH ${MSCL_ARCH_NAME})

        # Make a zip of the package
        list(APPEND FOUND_CPACK_GENERATORS "ZIP")
    elseif(UNIX)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            # The dumpmachine command from gcc should contain information on the architecture
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E env /bin/bash -c "${CMAKE_CXX_COMPILER} -dumpmachine"
                OUTPUT_VARIABLE GCC_ARCHITECTURE_OUT
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                ERROR_VARIABLE GCC_ARCHITECTURE_ERR
                RESULT_VARIABLE GCC_ARCHITECTURE_RET
            )

            # Convert the GCC architecture to the format that we use
            if("${GCC_ARCHITECTURE_OUT}" MATCHES ".*x86_64.*")
                set(MSCL_ARCH "amd64")
            elseif("${GCC_ARCHITECTURE_OUT}" MATCHES ".*aarch64.*")
                set(MSCL_ARCH "arm64")
            elseif("${GCC_ARCHITECTURE_OUT}" MATCHES ".*arm.*")
                set(MSCL_ARCH "armhf")
            else()
                message(STATUS "Unrecognized GCC architecture ${GCC_ARCHITECTURE_OUT}. Using CMAKE_SYSTEM_PROCESSOR for architecture")
            endif()
        endif()
    endif()

    if(NOT DEFINED MSCL_ARCH)
        message(STATUS "Defaulting MSCL_ARCH to ${CMAKE_SYSTEM_PROCESSOR}")
        set(MSCL_ARCH ${CMAKE_SYSTEM_PROCESSOR})
    endif()

    # NOTE: CPack requires all these variables to be set before importing the module. Do not move them after the include(CPack) line
    set(CPACK_GENERATOR "${FOUND_CPACK_GENERATORS}")
    set(CPACK_PACKAGE_VENDOR "MicroStrain by HBK")
    set(CPACK_PACKAGE_CONTACT "MicroStrain Support <microstrainsupport@hbkworld.com>")

    # Massage the version number a little so we can set the proper version
    set(CPACK_PACKAGE_VERSION ${MSCL_GIT_VERSION_CLEAN})

    if(WIN32)
        set(MSCL_FILE_NAME_PREFIX "${PROJECT_NAME}_Windows_${MSCL_ARCH}")
    else()
        set(MSCL_FILE_NAME_PREFIX "${PROJECT_NAME}_${MSCL_ARCH}")
    endif()

    # Archive specific configuration
    set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

    # Deb specific configuration
    set(CPACK_DEB_COMPONENT_INSTALL ON)

    # Most packages share these dependencies
    set(CPACK_DEBIAN_COMMON_DEPS libboost-system-dev libboost-filesystem-dev)

    if(WITH_SSL)
        list(APPEND CPACK_DEBIAN_COMMON_DEPS libssl-dev)
    endif()

    string(REPLACE ";" ", " CPACK_DEBIAN_COMMON_DEPS "${CPACK_DEBIAN_COMMON_DEPS}")

    # RPM specific configuration
    set(CPACK_RPM_COMPONENT_INSTALL ON)
    set(CPACK_RPM_PACKAGE_AUTOREQ OFF)

    # Most packages share these dependencies
    set(CPACK_RPM_COMMON_DEPS boost-filesystem boost-system boost-devel)

    if(WITH_SSL)
        list(APPEND CPACK_RPM_COMMON_DEPS openssl-devel)
    endif()

    string(REPLACE ";" ", " CPACK_RPM_COMMON_DEPS "${CPACK_RPM_COMMON_DEPS}")

    # Static package
    microstrain_add_archive_component(${MSCL_STATIC_INSTALL_COMPONENT} ${MSCL_FILE_NAME_PREFIX} "Static_C++" ${MSCL_GIT_VERSION})
    set(CPACK_DEBIAN_${MSCL_STATIC_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
    set(CPACK_RPM_${MSCL_STATIC_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")

    if(BUILD_SHARED_LIBS)
        microstrain_add_archive_component(${MSCL_SHARED_INSTALL_COMPONENT} ${MSCL_FILE_NAME_PREFIX} "Shared_C++" ${MSCL_GIT_VERSION})
        set(CPACK_DEBIAN_${MSCL_SHARED_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
        set(CPACK_RPM_${MSCL_SHARED_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
    endif()

    if(BUILD_PYTHON3)
        microstrain_add_archive_component(${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT} ${MSCL_FILE_NAME_PREFIX} "Python${MSCL_PYTHON3_VERSION}" ${MSCL_GIT_VERSION})
        set(CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "python${MSCL_PYTHON3_VERSION}")
        set(CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "python3")

        if(NOT LINK_STATIC_DEPS)
            list(APPEND CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
            string(REPLACE ";" ", " CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS}")

            list(APPEND CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
            string(REPLACE ";" ", " CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES}")
        endif()
    endif()

    if(BUILD_PYTHON2)
        microstrain_add_archive_component(${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT} ${MSCL_FILE_NAME_PREFIX} "Python${MSCL_PYTHON2_VERSION}" ${MSCL_GIT_VERSION})
        set(CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "python${MSCL_PYTHON2_VERSION}")
        set(CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "python2")

        if(NOT LINK_STATIC_DEPS)
            list(APPEND CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
            string(REPLACE ";" ", " CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS}")

            list(APPEND CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
            string(REPLACE ";" ", " CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES}")
        endif()
    endif()

    if(BUILD_CSHARP)
        microstrain_add_archive_component(${MSCL_CSHARP_INSTALL_COMPONENT} ${MSCL_FILE_NAME_PREFIX} "DotNet" ${MSCL_GIT_VERSION})
    endif()

    if(BUILD_DOCUMENTATION)
        microstrain_add_archive_component(${MSCL_DOCS_INSTALL_COMPONENT} ${PROJECT_NAME} "Documentation" ${MSCL_GIT_VERSION})
    endif()

    if(BUILD_EXAMPLES)
        microstrain_add_archive_component(${MSCL_EXAMPLES_INSTALL_COMPONENT} ${PROJECT_NAME} "Examples" ${MSCL_GIT_VERSION})
    endif()

    # Finally include cpack which should have taken all of the previous variables into consideration
    include(CPack)

    cpack_add_component(${MSCL_STATIC_INSTALL_COMPONENT}
        DESCRIPTION "MSCL static library and header files"
        GROUP ${MSCL_STATIC_INSTALL_COMPONENT}
    )

    if(BUILD_SHARED_LIBS)
        cpack_add_component(${MSCL_SHARED_INSTALL_COMPONENT}
            DESCRIPTION "MSCL shared library and header files"
            GROUP ${MSCL_SHARED_INSTALL_COMPONENT}
        )
    endif()

    if(BUILD_PYTHON3)
        cpack_add_component(${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}
            DESCRIPTION "MSCL python bindings for ${MSCL_PYTHON3_VERSION}"
            GROUP ${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}
        )
    endif()

    if(BUILD_PYTHON2)
        cpack_add_component(${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}
            DESCRIPTION "MSCL python bindings for ${MSCL_PYTHON2_VERSION}"
            GROUP ${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}
        )
    endif()

    if(BUILD_CSHARP)
        cpack_add_component(${MSCL_CSHARP_INSTALL_COMPONENT}
            DESCRIPTION "MSCL CSharp bindings"
            GROUP ${MSCL_CSHARP_INSTALL_COMPONENT}
        )
    endif()

    if(BUILD_DOCUMENTATION)
        cpack_add_component(${MSCL_DOCS_INSTALL_COMPONENT}
            DESCRIPTION "MSCL documentation"
            GROUP ${MSCL_DOCS_INSTALL_COMPONENT}
        )
    endif()

    if(BUILD_EXAMPLES)
        cpack_add_component(${MSCL_EXAMPLES_INSTALL_COMPONENT}
            DESCRIPTION "MSCL examples"
            GROUP ${MSCL_EXAMPLES_INSTALL_COMPONENT}
        )
    endif()
endif()
