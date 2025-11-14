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
    RUNTIME
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

    # Configure manual Debian dependencies
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

        foreach(MSCL_LINUX_PACKAGE_DEPEND IN LISTS MSCL_LINUX_PACKAGE_DEPENDS)
            if("${MSCL_LINUX_PACKAGE_DEPEND}" MATCHES "^boost")
                list(APPEND MSCL_DEBIAN_PACKAGE_DEPEND "lib${MSCL_LINUX_PACKAGE_DEPEND}-dev (>= ${Boost_VERSION})")

                if("${MSCL_LINUX_PACKAGE_DEPEND}" MATCHES "^boost$")
                    list(APPEND MSCL_RPM_PACKAGE_REQUIRES "${MSCL_LINUX_PACKAGE_DEPEND}-devel >= ${Boost_VERSION}")
                else()
                    list(APPEND MSCL_RPM_PACKAGE_REQUIRES "${MSCL_LINUX_PACKAGE_DEPEND} >= ${Boost_VERSION}")
                endif()
            elseif("${MSCL_LINUX_PACKAGE_DEPEND}" MATCHES "^ssl")
                list(APPEND MSCL_DEBIAN_PACKAGE_DEPEND "lib${MSCL_LINUX_PACKAGE_DEPEND}-dev (>= ${OPENSSL_VERSION})")
                list(APPEND MSCL_RPM_PACKAGE_REQUIRES "open${MSCL_LINUX_PACKAGE_DEPEND}-devel >= ${OPENSSL_VERSION}")
            endif()
        endforeach()

        string(REPLACE ";" ", " MSCL_DEBIAN_PACKAGE_DEPEND "${MSCL_DEBIAN_PACKAGE_DEPEND}")
        string(REPLACE ";" ", " MSCL_RPM_PACKAGE_REQUIRES "${MSCL_RPM_PACKAGE_REQUIRES}")

        # Make sure the parent scope has this set for packaging
        set(CPACK_DEBIAN_${MSCL_CPP_COMPONENT_NAME_UPPER}_PACKAGE_DEPENDS "${MSCL_DEBIAN_PACKAGE_DEPEND}" PARENT_SCOPE)
        set(CPACK_RPM_${MSCL_CPP_COMPONENT_NAME_UPPER}_PACKAGE_REQUIRES "${MSCL_RPM_PACKAGE_REQUIRES}" PARENT_SCOPE)
    endif()
endif()
