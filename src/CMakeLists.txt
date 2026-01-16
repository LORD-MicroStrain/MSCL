set(MSCL_LIBRARY "${PROJECT_NAME}" CACHE INTERNAL "Name of the MSCL library")
set(MSCL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "MSCL include directory")

# Create the MSCL main target library
set(MSCL_CPP_TARGET "${MSCL_LIBRARY}-Cpp")
add_library("${MSCL_CPP_TARGET}")

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

    set(MSCL_COMPILE_OPTIONS
        "/MP" # Enable parallel builds
        "/W4" # Turn on warnings
        "/WX" # Set warnings as errors
    )

    # Turn off warnings on external libraries/headers if supported
    if(MSVC_VERSION GREATER_EQUAL 1913)
        if(MSVC_VERSION LESS 1929)
            # Experimental support for /external (VS 2017 15.6 to VS 2019 16.9)
            list(APPEND MSCL_COMPILE_OPTIONS
                "/experimental:external"
            )
        endif()

        list(APPEND MSCL_COMPILE_OPTIONS
            "/external:W0"            # Turn off warnings on external headers
            "/external:anglebrackets" # Treat angle bracket includes as external headers
        )
    endif()


    target_compile_options("${MSCL_CPP_TARGET}" PRIVATE
        ${MSCL_COMPILE_OPTIONS}
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
    "$<BUILD_INTERFACE:${MSCL_INCLUDE_DIR}>"           # Include directory for building
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>" # Include directory for installations
)

# Find/configure some dependencies

# Find the threading library (included by default by MSVC)
if(NOT MSVC)
    find_package("Threads" REQUIRED)
endif()

# Find Boost
# Boost compiled components
set(Boost_COMPILED_COMPONENTS
    "filesystem"
    "headers" # Interface library encompassing all header-only libraries
)

# Header-only components available only when Boost is included from source
# All of these are typically linked to boost_header/Boost::headers
# These don't need to be used, but tells Boost exactly which libraries we want
set(Boost_HEADER_COMPONENTS
    "asio"
    "beast"
    "circular_buffer"
    "crc"
    "lambda"
    "math"
)

# Find the proper linking version of Boost
set(Boost_USE_STATIC_LIBS ${MSCL_LINK_STATIC_DEPS})

find_package("Boost" REQUIRED
    COMPONENTS ${Boost_COMPILED_COMPONENTS}
    OPTIONAL_COMPONENTS ${Boost_HEADER_COMPONENTS}
    CONFIG
)

target_link_libraries("${MSCL_CPP_TARGET}" PUBLIC
    # Prevent Boost from being exported when MSCL is a dependency of another project
    $<BUILD_INTERFACE:${Boost_LIBRARIES}>
)

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
    # This conflicts with vcpkg, so don't set it if OpenSSL was installed with it
    if(NOT MSCL_DOWNLOAD_OPENSSL)
        set(OPENSSL_USE_STATIC_LIBS ${MSCL_LINK_STATIC_DEPS})
    endif()

    # OpenSSL doesn't clear its variables properly for recurring find_package calls
    # This variable needs to be cleared so OPENSSL_ROOT_DIR can then be used properly
    unset(OPENSSL_INCLUDE_DIR CACHE)

    find_package("OpenSSL" REQUIRED)

    target_link_libraries("${MSCL_CPP_TARGET}" PUBLIC
        "$<BUILD_INTERFACE:OpenSSL::SSL>"
        "$<BUILD_INTERFACE:OpenSSL::Crypto>"
    )

    target_compile_definitions("${MSCL_CPP_TARGET}" PUBLIC
        "MSCL_WITH_SSL"
    )
endif()

if(MSCL_WITH_WEBSOCKETS)
    target_compile_definitions("${MSCL_CPP_TARGET}" PUBLIC
        "MSCL_WITH_WEBSOCKETS"
    )
endif()

# For completeness and compatibility with find_package(MSCL), add the LIBRARIES and INCLUDE_DIRS variables as well
set(MSCL_LIBRARIES "${MSCL_LIBRARY}" CACHE STRING "List of MSCL libraries" FORCE)
get_target_property(MSCL_INTERFACE_INCLUDE_DIRS "${MSCL_CPP_TARGET}" INTERFACE_INCLUDE_DIRECTORIES)
set(MSCL_INCLUDE_DIRS ${MSCL_INTERFACE_INCLUDE_DIRS} CACHE STRING "List of MSCL include directories" FORCE)

#
# Installation setup
#

set(MSCL_CPP_COMPONENT_NAME "Cpp")
if(BUILD_SHARED_LIBS)
    string(APPEND MSCL_CPP_COMPONENT_NAME "-Shared")
else()
    string(APPEND MSCL_CPP_COMPONENT_NAME "-Static")
endif()

set(MSCL_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}")
set(MSCL_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}")

set(MSCL_EXPORT_TARGET_NAME "${PROJECT_NAME_LOWER}-targets")

# Handle 32-bit installations
if(MSVC AND MSCL_ARCH_NAME STREQUAL "x86")
    string(APPEND MSCL_INSTALL_LIBDIR "32")
endif()

string(APPEND MSCL_INSTALL_LIBDIR "$<$<CONFIG:Debug>:/debug>")

# Setup the installation
install(
    TARGETS "${MSCL_CPP_TARGET}"
    EXPORT "${MSCL_EXPORT_TARGET_NAME}"
    LIBRARY
        COMPONENT "${MSCL_CPP_COMPONENT_NAME}"
        DESTINATION "${MSCL_INSTALL_LIBDIR}"
    ARCHIVE
        COMPONENT "${MSCL_CPP_COMPONENT_NAME}"
        DESTINATION "${MSCL_INSTALL_LIBDIR}"
    RUNTIME
        COMPONENT "${MSCL_CPP_COMPONENT_NAME}"
        DESTINATION "${MSCL_INSTALL_LIBDIR}"
    FILE_SET "${MSCL_HEADER_FILE_SET}"
        COMPONENT "${MSCL_CPP_COMPONENT_NAME}"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Create export files for the library for all configurations
install(
    EXPORT "${MSCL_EXPORT_TARGET_NAME}"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME_LOWER}/${MSCL_ARCH_NAME}"
    NAMESPACE "${PROJECT_NAME}::"
    COMPONENT "${MSCL_CPP_COMPONENT_NAME}"
)

microstrain_generate_package_config(
    PACKAGE_NAME "${PROJECT_NAME_LOWER}"
    LIBRARY_NAME "${MSCL_CPP_TARGET}"
    PACKAGE_NAMESPACE "${MSCL_LIBRARY}"
    COMPONENT_NAME "${MSCL_CPP_COMPONENT_NAME}"
    LIBRARY_NAME_ALIAS "${MSCL_LIBRARY}"
)

if(MSCL_BUILD_PACKAGE)
    microstrain_set_cpack_component_file_name(
        COMPONENT_NAME "${MSCL_CPP_COMPONENT_NAME}"
        COMPONENT_VERSION "${CPACK_PACKAGE_VERSION}"
        PACKAGE_ARCH "${CPACK_SYSTEM_NAME}"
    )

    # Configure manual Linux dependencies
    if(UNIX AND NOT APPLE)
        string(TOUPPER "${MSCL_CPP_COMPONENT_NAME}" MSCL_CPP_COMPONENT_NAME_UPPER)

        # Configure manual package dependencies for Linux packages
        set(MSCL_LINUX_PACKAGE_DEPENDS
            "boost"
            "boost-asio"
            "boost-filesystem"
            "boost-system"
        )

        if(MSCL_WITH_SSL)
            # Include OpenSSL in the manual package dependencies
            list(APPEND MSCL_LINUX_PACKAGE_DEPENDS  "ssl")
        endif()

        microstrain_detect_deb(MSCL_IS_DEB)

        if(MSCL_IS_DEB)
            # Enable per component dependencies
            set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON PARENT_SCOPE)
        endif()

        microstrain_detect_rpm(MSCL_IS_RPM)
        if(MSCL_IS_RPM)
            set(CPACK ON PARENT_SCOPE)
        endif()

        # Due to how Boost and SSL interact with MSCL, dependencies should be exact versions
        foreach(MSCL_LINUX_PACKAGE_DEPEND IN LISTS MSCL_LINUX_PACKAGE_DEPENDS)
            if("${MSCL_LINUX_PACKAGE_DEPEND}" MATCHES "^boost")
                if(MSCL_IS_DEB)
                    list(APPEND MSCL_DEBIAN_PACKAGE_DEPEND "lib${MSCL_LINUX_PACKAGE_DEPEND}-dev (= ${Boost_VERSION})")
                endif()

                if(MSCL_IS_RPM)
                    if("${MSCL_LINUX_PACKAGE_DEPEND}" MATCHES "^boost$")
                        list(APPEND MSCL_RPM_PACKAGE_REQUIRES "${MSCL_LINUX_PACKAGE_DEPEND}-devel = ${Boost_VERSION}")
                    else()
                        list(APPEND MSCL_RPM_PACKAGE_REQUIRES "${MSCL_LINUX_PACKAGE_DEPEND} = ${Boost_VERSION}")
                    endif()
                endif()
            elseif("${MSCL_LINUX_PACKAGE_DEPEND}" MATCHES "^ssl")
                if(MSCL_IS_DEB)
                    list(APPEND MSCL_DEBIAN_PACKAGE_DEPEND "lib${MSCL_LINUX_PACKAGE_DEPEND}-dev (= ${OPENSSL_VERSION})")
                endif()

                if(MSCL_IS_RPM)
                    list(APPEND MSCL_RPM_PACKAGE_REQUIRES "open${MSCL_LINUX_PACKAGE_DEPEND}-devel = ${OPENSSL_VERSION}")
                endif()
            endif()
        endforeach()

        if(MSCL_IS_DEB)
            string(REPLACE ";" ", " MSCL_DEBIAN_PACKAGE_DEPEND "${MSCL_DEBIAN_PACKAGE_DEPEND}")

            # Make sure the parent scope has this set for packaging
            set(CPACK_DEBIAN_${MSCL_CPP_COMPONENT_NAME_UPPER}_PACKAGE_DEPENDS "${MSCL_DEBIAN_PACKAGE_DEPEND}" PARENT_SCOPE)
        endif()

        if(MSCL_IS_RPM)
            string(REPLACE ";" ", " MSCL_RPM_PACKAGE_REQUIRES "${MSCL_RPM_PACKAGE_REQUIRES}")

            # Make sure the parent scope has this set for packaging
            set(CPACK_RPM_${MSCL_CPP_COMPONENT_NAME_UPPER}_PACKAGE_REQUIRES "${MSCL_RPM_PACKAGE_REQUIRES}" PARENT_SCOPE)
        endif()
    endif()
endif()
