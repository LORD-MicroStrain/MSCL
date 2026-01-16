#
# Setup and use vcpkg
#

if(NOT MSCL_USE_VCPKG)
    message(STATUS "MSCL_USE_VCPKG is OFF. Turn it ON to use vcpkg configurations in MSCL")
    return()
endif()

# Make sure the overlay triplets can be found
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_CURRENT_LIST_DIR}/triplets")

if(VCPKG_CHAINLOAD_TOOLCHAIN_FILE AND NOT EXISTS "${VCPKG_CHAINLOAD_TOOLCHAIN_FILE}")
    set(MSCL_TOOLCHAINS_DIR "${CMAKE_CURRENT_LIST_DIR}/toolchains")

    # Get the toolchain file name
    get_filename_component(TOOLCHAIN_FILENAME ${VCPKG_CHAINLOAD_TOOLCHAIN_FILE} NAME)

    # Get all the available toolchains in the project
    file(GLOB MSCL_TOOLCHAINS "${MSCL_TOOLCHAINS_DIR}/*.cmake")

    # Loop through the available toolchains to fix the root path
    foreach(MSCL_TOOLCHAIN IN LISTS MSCL_TOOLCHAINS)
        get_filename_component(MSCL_TOOLCHAIN_FILENAME ${MSCL_TOOLCHAIN} NAME)
        if("${MSCL_TOOLCHAIN_FILENAME}" MATCHES "${TOOLCHAIN_FILENAME}")
            # Update the path of the toolchain so it's loaded correctly
            set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE "${MSCL_TOOLCHAINS_DIR}/${MSCL_TOOLCHAIN_FILENAME}")
            unset(MSCL_TOOLCHAIN_FILENAME)

            # Done searching
            break()
        endif()
    endforeach()

    unset(MSCL_TOOLCHAINS_DIR)
    unset(TOOLCHAIN_FILENAME)
    unset(MSCL_TOOLCHAINS)
endif()

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

set(MSCL_VCPKG_DIR "${CMAKE_CURRENT_LIST_DIR}/../deps/vcpkg")

find_package(Git QUIET)

# Name of a common file to check if it exists to know the submodule was checked out
# gitignore is a good option since it will always exist
set(VCPKG_CHECK_FILENAME "${MSCL_VCPKG_DIR}/.gitignore")

if(GIT_FOUND)
    # Make a lock file
    set(VCPKG_LOCK_FILE "${MSCL_VCPKG_DIR}/downloads/.lock")

    # Check if the submodule directory exists and is populated
    if(NOT EXISTS "${VCPKG_CHECK_FILENAME}")
        # Attempt to lock the file so we can print a status message on the lock
        file(LOCK "${VCPKG_LOCK_FILE}" GUARD FILE RESULT_VARIABLE VCPKG_IS_LOCKED TIMEOUT 1)

        # The try-lock will timeout (not 0) if another config is already updating the submodule
        if(NOT "${VCPKG_IS_LOCKED}" STREQUAL "0")
            message(STATUS "vcpkg submodule is already being updated. Waiting for the lock to release...")
        endif()
        unset(VCPKG_IS_LOCKED)

        # Release the try-lock to proceed to update the submodule
        file(LOCK "${VCPKG_LOCK_FILE}" RELEASE)

        # Acquire lock to serialize updates across parallel configurations
        file(LOCK "${VCPKG_LOCK_FILE}" GUARD FILE TIMEOUT 600)

        # Double-check after acquiring lock
        if(NOT EXISTS "${VCPKG_CHECK_FILENAME}")
            message(STATUS "vcpkg submodule not found, updating submodules...")

            execute_process(
                COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/.."
                RESULT_VARIABLE SUBMODULE_UPDATE_RESULT
            )

            file(LOCK "${VCPKG_LOCK_FILE}" RELEASE)

            if(NOT SUBMODULE_UPDATE_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init --recursive failed with ${SUBMODULE_UPDATE_RESULT}")
            endif()
        endif()

        unset(VCPKG_LOCK_FILE)
    endif()
endif()

# Check if the submodule directory exists and is populated
if(NOT EXISTS "${VCPKG_CHECK_FILENAME}")
    message(FATAL_ERROR "The vcpkg submodule was not checked out! Please update submodules and try again")
endif()

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
