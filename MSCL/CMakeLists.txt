set(MSCL_LIBRARY "${PROJECT_NAME}" CACHE INTERNAL "Name of the MSCL library")
set(MSCL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/source" CACHE INTERNAL "MSCL include directory")

# Create the MSCL main target library
set(MSCL_CPP_TARGET "${MSCL_LIBRARY}-Cpp")
add_library("${MSCL_CPP_TARGET}" ${MSCL_SOURCES})

# Set the correct library output name
set_target_properties("${MSCL_CPP_TARGET}" PROPERTIES
    OUTPUT_NAME "${MSCL_LIBRARY}"
)

# Create an alias for proper linking
# This is the actual name of the packaged library
add_library("${MSCL_LIBRARY}" ALIAS "${MSCL_CPP_TARGET}")

if(MSVC)
    target_compile_definitions("${MSCL_CPP_TARGET}" PRIVATE
        "_CRT_SECURE_NO_WARNINGS" # Turn off MSVC specific CRT warnings as they're not cross platform compatible
    )
    target_compile_options("${MSCL_CPP_TARGET}" PRIVATE
        "/MP" # Enable parallel builds
        "/W4" # Turn on warnings
        "/WX" # Set warnings as errors
    )
elseif(UNIX AND NOT BUILD_SHARED_LIBS)
    # Make sure Linux compiles static libraries with -fPIC
    set_target_properties("${MSCL_CPP_TARGET}" PROPERTIES
        POSITION_INDEPENDENT_CODE TRUE
    )
endif()

# Setup the HEADERS file set
# This is required to be done here so any subdirectories can use it properly
set(MSCL_HEADER_FILE_SET "HEADERS")
target_sources("${MSCL_CPP_TARGET}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    BASE_DIRS "${MSCL_INCLUDE_DIR}"
)

# Add all the sources
add_subdirectory("${MSCL_INCLUDE_DIR}/mscl")

# Setup IDE filters for the IDEs that support it
get_target_property(MSCL_SOURCES ${MSCL_CPP_TARGET} SOURCES)
get_target_property(MSCL_HEADERS ${MSCL_CPP_TARGET} HEADER_SET)
source_group(
    TREE ${MSCL_INCLUDE_DIR}
    FILES ${MSCL_SOURCES} ${MSCL_HEADERS}
)

target_include_directories("${MSCL_CPP_TARGET}" PUBLIC
    "${MSCL_INCLUDE_DIR}"
)

# Find/configure some dependencies

# Find the threading library (included by default by MSVC)
if(NOT MSVC)
    find_package("Threads" REQUIRED)
endif()

# Find Boost
set(Boost_REQUESTED_COMPONENTS
    "asio"
    "beast"
    "circular_buffer"
    "crc"
    "filesystem"
    "lambda"
    "math"
)

# Find the proper linking version of Boost
set(Boost_USE_STATIC_LIBS ${MSCL_LINK_STATIC_DEPS})
set(Boost_USE_STATIC_RUNTIME ${MSCL_LINK_STATIC_DEPS})

find_package("Boost" REQUIRED COMPONENTS ${Boost_REQUESTED_COMPONENTS} CONFIG)

target_link_libraries("${MSCL_CPP_TARGET}" PUBLIC
    ${Boost_LIBRARIES}
)

#target_include_directories("${MSCL_CPP_TARGET}" PUBLIC
#    "${Boost_INCLUDE_DIRS}"
#)

# Disable deprecated Boost components
# Forces updates on deprecated components sooner rather than later
# These are not required by users and are defined privately in MSCL
target_compile_definitions("${MSCL_CPP_TARGET}" PRIVATE
    "BOOST_ASIO_NO_DEPRECATED"
    "BOOST_FILESYSTEM_NO_DEPRECATED"
    "BOOST_PROCESS_NO_DEPRECATED"
    "BOOST_SYSTEM_NO_DEPRECATED"
)

# Find OpenSSL if requested
if(MSCL_WITH_SSL)
    # Find the proper linking version of OpenSSL
    set(OPENSSL_USE_STATIC_LIBS ${MSCL_LINK_STATIC_DEPS})
    set(OPENSSL_MSVC_STATIC_RT ${MSCL_LINK_STATIC_DEPS})

    find_package("OpenSSL" REQUIRED)

    target_link_libraries("${MSCL_CPP_TARGET}" PUBLIC
        ${OPENSSL_LIBRARIES}
    )

#    target_include_directories("${MSCL_CPP_TARGET}" PUBLIC
#        "${OPENSSL_INCLUDE_DIR}"
#    )
else()
    # TODO: Don't assume the user linked proper libraries for this support!!
    target_compile_definitions("${MSCL_CPP_TARGET}" PUBLIC
        "MSCL_DISABLE_SSL"
    )
endif()

if(NOT MSCL_WITH_WEBSOCKETS)
    # TODO: Don't assume the user linked proper libraries for this support!!
    target_compile_definitions("${MSCL_CPP_TARGET}" PUBLIC
        "MSCL_DISABLE_WEBSOCKETS"
    )
endif()

# For completeness and compatibility with find_package(MSCL), add the LIBRARIES and INCLUDE_DIRS variables as well
set(MSCL_LIBRARIES "${MSCL_LIBRARY}" CACHE STRING "List of MSCL libraries" FORCE)
get_target_property(MSCL_INTERFACE_INCLUDE_DIRS "${MSCL_CPP_TARGET}" INTERFACE_INCLUDE_DIRECTORIES)
set(MSCL_INCLUDE_DIRS ${MSCL_INTERFACE_INCLUDE_DIRS} CACHE STRING "List of MSCL include directories" FORCE)

#
# Installation setup
#

set(MSCL_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}")
set(MSCL_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}")

if(MSVC)
    string(PREPEND MSCL_INSTALL_LIBDIR "MSCL/")
    string(PREPEND MSCL_INSTALL_INCLUDEDIR "MSCL/")

    string(APPEND MSCL_INSTALL_LIBDIR "/${MSCL_ARCH_NAME}/$<CONFIG>")
endif()

set(MSCL_CPP_COMPONENT_NAME "Cpp")
if(BUILD_SHARED_LIBS)
    string(APPEND MSCL_CPP_COMPONENT_NAME "-Shared")
else()
    string(APPEND MSCL_CPP_COMPONENT_NAME "-Static")
endif()

install(
    TARGETS "${MSCL_CPP_TARGET}"
    LIBRARY
        COMPONENT "${MSCL_CPP_COMPONENT_NAME}"
        DESTINATION "${MSCL_INSTALL_LIBDIR}"
    ARCHIVE
        COMPONENT "${MSCL_CPP_COMPONENT_NAME}"
        DESTINATION "${MSCL_INSTALL_LIBDIR}"
    FILE_SET "${MSCL_HEADER_FILE_SET}"
        COMPONENT "${MSCL_CPP_COMPONENT_NAME}"
        DESTINATION "${MSCL_INSTALL_INCLUDEDIR}"
)

if(MSCL_BUILD_PACKAGE)
    microstrain_set_cpack_component_file_name(
        COMPONENT_NAME "${MSCL_CPP_COMPONENT_NAME}"
        COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
        PACKAGE_ARCH "${CPACK_SYSTEM_NAME}"
    )
endif()











# Optionally generate the language bindings using swig
#if(MSCL_BUILD_PYTHON2 OR MSCL_BUILD_PYTHON3 OR MSCL_BUILD_CSHARP)
#    include(UseSWIG)
#    include(mscl_python_swig)
#
#    if(MSVC)
#        # Linking through the MSCL cmake interface causes linker error 4197. This is related to swig and can be ignored
#        #TODO: Figure out how to fix this linker error
##        list(APPEND CMAKE_SHARED_LINKER_FLAGS "/ignore:4197")
#
#        set(SWIG_COMPILE_OPTIONS
#            "${COMMON_COMPILE_OPTIONS}"
#            "/bigobj"
#        )
#    endif()
#
#    # Set up our source
#    set(SWIG_SOURCE_FILES
#        ${MSCL_SOURCE_FILES_DIR}/Wrapper/MSCL_Main_Interface.i
#    )
#    set_property(SOURCE ${SWIG_SOURCE_FILES} PROPERTY CPLUSPLUS ON)
#
#    # Different compile flags depending on the platform
#    set(PYTHON_COMPILE_OPTIONS "${SWIG_COMPILE_OPTIONS}")
#    set(PYTHON_LINK_OPTIONS $<$<CXX_COMPILER_ID:GNU>:-Wl,--no-as-needed>)
#    set(PYTHON_LINK_LIBRARIES
#        ${MSCL_LIBRARY}
#        ${Boost_LIBRARIES}
#    )
#
#    if(MSCL_WITH_SSL)
#        list(APPEND PYTHON_LINK_LIBRARIES ${OPENSSL_LIBRARIES})
#    endif()
#
#    # Fix the include paths on Windows to remove backslashes
#    if(WIN32)
#        list(TRANSFORM LIB_INCLUDE_DIRS REPLACE "\\\\" "/")
#    endif()
#
#    # Build for python3
#    if(MSCL_BUILD_PYTHON3)
#        set(PYTHON3_MODULE_NAME MSCL_Python3)
#        set(MSCL_PYTHON3_VERSION ${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR})
#        mscl_python_swig(
#            MODULE_NAME ${PYTHON3_MODULE_NAME}
#            MODULE_VERSION ${MSCL_GIT_VERSION}
#            OUTPUT_NAME mscl
#            OUTPUT_DIR ${MSCL_OUTPUT_DIR}
#            PYTHON_VERSION ${MSCL_PYTHON3_VERSION}
#            ARCH ${MSCL_ARCH_NAME}
#            SOURCES ${SWIG_SOURCE_FILES}
#            COMPILE_OPTIONS ${PYTHON_COMPILE_OPTIONS}
#            COMPILE_DEFINITIONS ${LIB_DEFINES} SWIG_PYTHON_INTERPRETER_NO_DEBUG
#            INCLUDE_DIRECTORIES ${LIB_INCLUDE_DIRS} ${Python3_INCLUDE_DIRS} ${MSCL_SOURCE_FILES_DIR}/Wrapper # Temp fix for bad include paths
#            LINK_DIRECTORIES ${Python3_LIBRARY_DIRS}
#            LINK_OPTIONS ${PYTHON_LINK_OPTIONS}
#            LINK_LIBRARIES ${PYTHON_LINK_LIBRARIES} ${Python3_LIBRARIES}
#        )
#    endif()
#
#    # Build for python2
#    if(MSCL_BUILD_PYTHON2)
#        set(PYTHON2_MODULE_NAME MSCL_Python2)
#        set(MSCL_PYTHON2_VERSION ${Python2_VERSION_MAJOR}.${Python2_VERSION_MINOR})
#        mscl_python_swig(
#            MODULE_NAME ${PYTHON2_MODULE_NAME}
#            MODULE_VERSION ${MSCL_GIT_VERSION}
#            OUTPUT_NAME mscl
#            OUTPUT_DIR ${MSCL_OUTPUT_DIR}
#            PYTHON_VERSION ${MSCL_PYTHON2_VERSION}
#            ARCH ${MSCL_ARCH_NAME}
#            SOURCES ${SWIG_SOURCE_FILES}
#            COMPILE_OPTIONS ${PYTHON_COMPILE_OPTIONS}
#            COMPILE_DEFINITIONS ${LIB_DEFINES} SWIG_PYTHON_INTERPRETER_NO_DEBUG
#            INCLUDE_DIRECTORIES ${LIB_INCLUDE_DIRS} ${Python2_INCLUDE_DIRS} ${MSCL_SOURCE_FILES_DIR}/Wrapper # Temp fix for bad include paths
#            LINK_DIRECTORIES ${Python2_LIBRARY_DIRS}
#            LINK_OPTIONS ${PYTHON_LINK_OPTIONS}
#            LINK_LIBRARIES ${PYTHON_LINK_LIBRARIES} ${Python2_LIBRARIES}
#        )
#    endif()
#
#    # Build C# on Windows
#    # Wish we could generate it the same as python, but we need to get the list of CSharp files
#    if(MSCL_BUILD_CSHARP)
#        set(CSHARP_MODULE_NAME MSCL_CSharp)
#
#        # Hack of all hacks, but we need to generate the source separately so we can determine the source files at configure time
#        set(CSHARP_MODULE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CSHARP_MODULE_NAME})
#        set(CSHARP_MODULE_CPP_FILE ${CSHARP_MODULE_DIR}/MSCL_Main_InterfaceCSHARP_wrap.cxx)
#
#        # Always clean old generated files
#        if(EXISTS ${CSHARP_MODULE_DIR})
#            file(REMOVE_RECURSE ${CSHARP_MODULE_DIR})
#        endif()
#        file(MAKE_DIRECTORY ${CSHARP_MODULE_DIR})
#
#        message(STATUS "Generating CSharp binding source")
#        execute_process(
#            COMMAND ${CMAKE_COMMAND} -E env SWIG_LIB=${SWIG_DIR} "${SWIG_EXECUTABLE}" -csharp -namespace mscl -outdir "${CSHARP_MODULE_DIR}" -c++ -dllimport MSCL -o "${CSHARP_MODULE_CPP_FILE}" "${SWIG_SOURCE_FILES}"
#            COMMAND_ERROR_IS_FATAL ANY
#        )
#
#        file(GLOB MSCL_GENERATED_CSHARP_SOURCE
#            ${CSHARP_MODULE_DIR}/*.cs
#        )
#
#        # Filter out incorrect file generation to make it simple to spot issues
#        foreach(MSCL_GENERATED_CSHARP_FILE IN LISTS MSCL_GENERATED_CSHARP_SOURCE)
#            get_filename_component(CSHARP_FILENAME "${MSCL_GENERATED_CSHARP_FILE}" NAME)
#            if("${CSHARP_FILENAME}" MATCHES "^SWIGTYPE_p*")
#                string(APPEND CSHARP_INCORRECT_FILENAMES "\n${CSHARP_FILENAME}")
#            endif()
#        endforeach()
#
#        if(CSHARP_INCORRECT_FILENAMES)
#            message(FATAL_ERROR "Incorrect CSharp filename generation(s) found ${CSHARP_INCORRECT_FILENAMES}")
#        endif()
#
#        # Build the C++ wrapper
#        add_library(${CSHARP_MODULE_NAME} SHARED
#            ${CSHARP_MODULE_CPP_FILE}
#        )
#
#        target_compile_options(${CSHARP_MODULE_NAME} PRIVATE
#            "${SWIG_COMPILE_OPTIONS}"
#        )
#
#        target_compile_definitions(${CSHARP_MODULE_NAME} PUBLIC
#            ${LIB_DEFINES}
#        )
#
#        target_include_directories(${CSHARP_MODULE_NAME} PUBLIC
#            ${LIB_INCLUDE_DIRS}
#            ${MSCL_SOURCE_FILES_DIR}/Wrapper # Temp fix for bad include path
#        )
#
#        target_link_libraries(${CSHARP_MODULE_NAME} PRIVATE
#            ${MSCL_LIBRARY}
#            ${Boost_LIBRARIES}
#        )
#
#        if(MSCL_WITH_SSL)
#            target_link_libraries(${CSHARP_MODULE_NAME} PRIVATE
#                ${OPENSSL_LIBRARIES}
#            )
#        endif()
#
#        set_target_properties(${CSHARP_MODULE_NAME}
#            PROPERTIES
#            OUTPUT_NAME ${MSCL_LIBRARY}
#            ARCHIVE_OUTPUT_DIRECTORY "${CSHARP_MODULE_DIR}"
#            LIBRARY_OUTPUT_DIRECTORY "${CSHARP_MODULE_DIR}"
#            RUNTIME_OUTPUT_DIRECTORY "${CSHARP_MODULE_DIR}"
#        )
#
#        # Add the CSharp library
#        set(MSCL_CSHARP_SOURCE
#            ${MSCL_ASSEMBLY_CS_OUT_FILE}
#            ${MSCL_SOURCE_FILES_DIR}/Wrapper/CSharp/mscl/Exceptions.cs
#            ${MSCL_GENERATED_CSHARP_SOURCE}
#        )
#        set(MSCL_Managed_NAME MSCL_Managed)
#        add_library(${MSCL_Managed_NAME} SHARED ${MSCL_CSHARP_SOURCE})
#        target_link_libraries(${MSCL_Managed_NAME} PUBLIC ${CSHARP_MODULE_NAME})
#
#        # Copy the library to an Output directory
#        set(MSCL_Managed_OUTPUT_DIR ${MSCL_OUTPUT_DIR}/DotNet/${MSCL_ARCH_NAME}/$<CONFIG>)
#        add_custom_command(TARGET ${MSCL_Managed_NAME} POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E remove_directory ${MSCL_Managed_OUTPUT_DIR}
#            COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:${MSCL_Managed_NAME}> ${MSCL_Managed_OUTPUT_DIR}
#            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${CSHARP_MODULE_NAME}> ${MSCL_Managed_OUTPUT_DIR}
#        )
#
#        set(MSCL_CSHARP_INSTALL_COMPONENT ${MSCL_LIBRARY}_CSHARP)
#        install(
#            TARGETS ${MSCL_Managed_NAME}
#            DESTINATION "DotNet/${MSCL_ARCH_NAME}/$<CONFIG>"
#            COMPONENT ${MSCL_CSHARP_INSTALL_COMPONENT}
#        )
#
#        # Install the shared libraries
#        install(
#            FILES $<TARGET_RUNTIME_DLLS:${MSCL_Managed_NAME}>
#            DESTINATION "DotNet/${MSCL_ARCH_NAME}/$<CONFIG>"
#            COMPONENT ${MSCL_CSHARP_INSTALL_COMPONENT}
#        )
#    endif()
#endif()

# If we were asked to build packages, include CPack and set up packaging
#if(MSCL_BUILD_PACKAGE)
#    # Try to determine what architecture we are building for based on the compiler output
#    if(MSVC)
#        set(MSCL_ARCH ${MSCL_ARCH_NAME})
#
#        # Make a zip of the package
#        list(APPEND FOUND_CPACK_GENERATORS "ZIP")
#    elseif(UNIX)
#        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#            # The dumpmachine command from gcc should contain information on the architecture
#            execute_process(
#                COMMAND ${CMAKE_COMMAND} -E env /bin/bash -c "${CMAKE_CXX_COMPILER} -dumpmachine"
#                OUTPUT_VARIABLE GCC_ARCHITECTURE_OUT
#                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                ERROR_VARIABLE GCC_ARCHITECTURE_ERR
#                RESULT_VARIABLE GCC_ARCHITECTURE_RET
#            )
#
#            # Convert the GCC architecture to the format that we use
#            if("${GCC_ARCHITECTURE_OUT}" MATCHES ".*x86_64.*")
#                set(MSCL_ARCH "amd64")
#            elseif("${GCC_ARCHITECTURE_OUT}" MATCHES ".*aarch64.*")
#                set(MSCL_ARCH "arm64")
#            elseif("${GCC_ARCHITECTURE_OUT}" MATCHES ".*arm.*")
#                set(MSCL_ARCH "armhf")
#            else()
#                message(STATUS "Unrecognized GCC architecture ${GCC_ARCHITECTURE_OUT}. Using CMAKE_SYSTEM_PROCESSOR for architecture")
#            endif()
#        endif()
#    endif()
#
#    if(NOT DEFINED MSCL_ARCH)
#        message(STATUS "Defaulting MSCL_ARCH to ${CMAKE_SYSTEM_PROCESSOR}")
#        set(MSCL_ARCH ${CMAKE_SYSTEM_PROCESSOR})
#    endif()
#
#    # NOTE: CPack requires all these variables to be set before importing the module. Do not move them after the include(CPack) line
#    set(CPACK_GENERATOR "${FOUND_CPACK_GENERATORS}")
#    set(CPACK_PACKAGE_VENDOR "MicroStrain by HBK")
#    set(CPACK_PACKAGE_CONTACT "MicroStrain Support <microstrainsupport@hbkworld.com>")
#
#    set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
#
#    if(WIN32)
#        set(MSCL_FILE_NAME_PREFIX "${MSCL_LIBRARY}_Windows_${MSCL_ARCH}")
#    else()
#        set(MSCL_FILE_NAME_PREFIX "${MSCL_LIBRARY}_${MSCL_ARCH}")
#    endif()
#
#    # Archive specific configuration
#    set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
#
#    # Deb specific configuration
#    set(CPACK_DEB_COMPONENT_INSTALL ON)
#
#    # Most packages share these dependencies
#    set(CPACK_DEBIAN_COMMON_DEPS libboost-system-dev libboost-filesystem-dev)
#
#    if(MSCL_WITH_SSL)
#        list(APPEND CPACK_DEBIAN_COMMON_DEPS libssl-dev)
#    endif()
#
#    string(REPLACE ";" ", " CPACK_DEBIAN_COMMON_DEPS "${CPACK_DEBIAN_COMMON_DEPS}")
#
#    # RPM specific configuration
#    set(CPACK_RPM_COMPONENT_INSTALL ON)
#    set(CPACK_RPM_PACKAGE_AUTOREQ OFF)
#
#    # Most packages share these dependencies
#    set(CPACK_RPM_COMMON_DEPS boost-filesystem boost-system boost-devel)
#
#    if(MSCL_WITH_SSL)
#        list(APPEND CPACK_RPM_COMMON_DEPS openssl-devel)
#    endif()
#
#    string(REPLACE ";" ", " CPACK_RPM_COMMON_DEPS "${CPACK_RPM_COMMON_DEPS}")
#
#
#    microstrain_set_cpack_component_file_name(
#        PACKAGE_NAME "${PROJECT_NAME}"
#        COMPONENT_NAME "${MSCL_CPP_COMPONENT_NAME}"
#        COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
#        PACKAGE_ARCH "${CPACK_SYSTEM_NAME}"
#    )
#    set(CPACK_DEBIAN_${MSCL_LIBRARY}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
#    set(CPACK_RPM_${MSCL_LIBRARY}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
#
#    if(MSCL_BUILD_PYTHON3)
#        microstrain_set_cpack_component_file_name(
#            COMPONENT_NAME ${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}
#            FILE_NAME_PREFIX ${MSCL_FILE_NAME_PREFIX}
#            FILE_NAME "Python${MSCL_PYTHON3_VERSION}"
#            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#        )
#        set(CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "python${MSCL_PYTHON3_VERSION}")
#        set(CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "python3")
#
#        if(NOT MSCL_LINK_STATIC_DEPS)
#            list(APPEND CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
#            string(REPLACE ";" ", " CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS}")
#
#            list(APPEND CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
#            string(REPLACE ";" ", " CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES}")
#        endif()
#    endif()
#
#    if(MSCL_BUILD_PYTHON2)
#        microstrain_set_cpack_component_file_name(
#            COMPONENT_NAME ${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}
#            FILE_NAME_PREFIX ${MSCL_FILE_NAME_PREFIX}
#            FILE_NAME "Python${MSCL_PYTHON2_VERSION}"
#            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#        )
#        set(CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "python${MSCL_PYTHON2_VERSION}")
#        set(CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "python2")
#
#        if(NOT MSCL_LINK_STATIC_DEPS)
#            list(APPEND CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_COMMON_DEPS}")
#            string(REPLACE ";" ", " CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS "${CPACK_DEBIAN_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_DEPENDS}")
#
#            list(APPEND CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_COMMON_DEPS}")
#            string(REPLACE ";" ", " CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES "${CPACK_RPM_${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}_PACKAGE_REQUIRES}")
#        endif()
#    endif()
#
#    if(MSCL_BUILD_CSHARP)
#        microstrain_set_cpack_component_file_name(
#            COMPONENT_NAME ${MSCL_CSHARP_INSTALL_COMPONENT}
#            FILE_NAME_PREFIX ${MSCL_FILE_NAME_PREFIX}
#            FILE_NAME "DotNet"
#            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#        )
#    endif()
#
##    if(MSCL_BUILD_DOCUMENTATION)
##        microstrain_set_cpack_component_file_name(
##            COMPONENT_NAME ${MSCL_DOCS_INSTALL_COMPONENT}
##            FILE_NAME_PREFIX ${MSCL_LIBRARY}
##            FILE_NAME "Documentation"
##            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
##        )
##    endif()
#
#    if(MSCL_ZIP_EXAMPLES)
#        microstrain_set_cpack_component_file_name(
#            COMPONENT_NAME ${MSCL_EXAMPLES_INSTALL_COMPONENT}
#            FILE_NAME_PREFIX ${MSCL_LIBRARY}
#            FILE_NAME "Examples"
#            FILE_NAME_SUFFIX ${MSCL_PACKAGE_VERSION_SUFFIX}
#        )
#    endif()
#
#    # Finally include cpack which should have taken all of the previous variables into consideration
#    include(CPack)
#
##    cpack_add_component(${MSCL_LIBRARY}
##        DESCRIPTION "MSCL library and header files"
##    )
##
##    if(MSCL_BUILD_PYTHON3)
##        cpack_add_component(${MSCL_PYTHON${MSCL_PYTHON3_VERSION}_INSTALL_COMPONENT}
##            DESCRIPTION "MSCL python bindings for ${MSCL_PYTHON3_VERSION}"
##        )
##    endif()
##
##    if(MSCL_BUILD_PYTHON2)
##        cpack_add_component(${MSCL_PYTHON${MSCL_PYTHON2_VERSION}_INSTALL_COMPONENT}
##            DESCRIPTION "MSCL python bindings for ${MSCL_PYTHON2_VERSION}"
##        )
##    endif()
##
##    if(MSCL_BUILD_CSHARP)
##        cpack_add_component(${MSCL_CSHARP_INSTALL_COMPONENT}
##            DESCRIPTION "MSCL CSharp bindings"
##        )
##    endif()
##
##    if(MSCL_BUILD_DOCUMENTATION)
##        cpack_add_component(${MSCL_DOCS_INSTALL_COMPONENT}
##            DESCRIPTION "MSCL documentation"
##        )
##    endif()
##
##    if(MSCL_ZIP_EXAMPLES)
##        cpack_add_component(${MSCL_EXAMPLES_INSTALL_COMPONENT}
##            DESCRIPTION "MSCL examples"
##        )
##    endif()
#endif()
