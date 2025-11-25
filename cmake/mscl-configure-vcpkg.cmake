#
# Setup and use vcpkg
#

if(MSCL_LINK_STATIC_DEPS)
    # Link dependencies statically on Windows. Windows links dynamically by default in vcpkg
    if(WIN32)
        if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
            set(VCPKG_TARGET_TRIPLET "x86-windows-static-md" CACHE STRING "Vcpkg target triplet")
        else()
            set(VCPKG_TARGET_TRIPLET "x64-windows-static-md" CACHE STRING "Vcpkg target triplet")
        endif()
    endif()
elseif(UNIX AND NOT APPLE)
    # Link dependencies dynamically on Linux. Linux links statically by default in vcpkg
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
        set(VCPKG_TARGET_TRIPLET "x64-linux-dynamic" CACHE STRING "Vcpkg target triplet")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
        set(VCPKG_TARGET_TRIPLET "arm64-linux-dynamic" CACHE STRING "Vcpkg target triplet")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "armv7|armv7l|armv7-a")
        message(FATAL_ERROR "Dynamic linking of dependencies is not supported by vcpkg on Linux ARM32")
    endif()
endif()

# Include any Boost dependencies with vcpkg
if(MSCL_DOWNLOAD_BOOST)
    list(APPEND VCPKG_MANIFEST_FEATURES "boost")

    # Include any testing dependencies with vcpkg
    if(MSCL_BUILD_TESTS)
        list(APPEND VCPKG_MANIFEST_FEATURES "testing")
    endif()
endif()

# Include any OpenSSL dependencies with vcpkg
if(MSCL_DOWNLOAD_OPENSSL)
    list(APPEND VCPKG_MANIFEST_FEATURES "openssl")
endif()

# Force vcpkg to output our dependencies to the install directory. This should handle sub dependencies too
option(X_VCPKG_APPLOCAL_DEPS_INSTALL
    "(experimental) Automatically copy dependencies into the install target directory for executables. Requires CMake 3.14."
    ON
)

# Make sure vcpkg uses the correct generator options
if(CMAKE_GENERATOR)
    set(Z_VCPKG_CMAKE_GENERATOR "${CMAKE_GENERATOR}")
endif()

if(CMAKE_GENERATOR_TOOLSET)
    set(VCPKG_PLATFORM_TOOLSET "${CMAKE_GENERATOR_TOOLSET}")
    set(Z_VCPKG_PLATFORM_TOOLSET "${CMAKE_GENERATOR_TOOLSET}")
endif()

set(MSCL_VCPKG_DIR "${CMAKE_SOURCE_DIR}/deps/vcpkg")

# Prefer vcpkg if we can find it. Fallback if CMake presets aren't used
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    # Different vcpkg roots depending on OS
    if(WIN32)
        set(MSCL_VCPKG_ROOTS
            "${MSCL_VCPKG_DIR}"
            "C:/Program Files/vcpkg"
            "C:/Program Files (x86)/vcpkg"
        )
    elseif(UNIX OR OSX)
        set(MSCL_VCPKG_ROOTS
            "${MSCL_VCPKG_DIR}"
            "/opt/vcpkg"
        )
    endif()

    # See if we can find the vcpkg toolchain file
    find_file(MSCL_VCPKG_TOOLCHAIN
        NAMES "scripts/buildsystems/vcpkg.cmake"
        PATHS ${MSCL_VCPKG_ROOTS}
        NO_DEFAULT_PATH
        REQUIRED
    )
    if(MSCL_VCPKG_TOOLCHAIN)
        message(STATUS "Using vcpkg toolchain file ${MSCL_VCPKG_TOOLCHAIN}")
    endif()

    # Tell cmake about the toolchain file
    set(CMAKE_TOOLCHAIN_FILE ${MSCL_VCPKG_TOOLCHAIN})
endif()
