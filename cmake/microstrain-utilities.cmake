#
# Utility macros to write to output variables
# Do not call these in the conventional way I.E. macro_name(${VARIABLE_NAME})
# Instead, do macro_name(VARIABLE_NAME) which will do `set(${PARAM_OUT} value)` and is equivalent to set(VARIABLE_NAME value)
#

macro(microstrain_get_git_version GIT_VERSION_OUT GIT_VERSION_CLEAN_OUT)
    # Use Git to find the version
    find_package(Git)

    set(MICROSTRAIN_DEFAULT_GIT_VERSION "v${PROJECT_VERSION}")

    if(NOT GIT_FOUND)
        message(WARNING "Unable to find Git, defaulting to version ${MICROSTRAIN_DEFAULT_GIT_VERSION}")
        set(${GIT_VERSION_OUT} ${MICROSTRAIN_DEFAULT_GIT_VERSION})
    else()
        # Find the latest semantic version tag I.E. 'v1.0.0' not 'latest'
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E env ${GIT_EXECUTABLE} describe --tags --match "v*"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            OUTPUT_VARIABLE MICROSTRAIN_GIT_VERSION_OUT
            ERROR_VARIABLE MICROSTRAIN_GIT_VERSION_ERR
            RESULT_VARIABLE MICROSTRAIN_GIT_VERSION_RET
        )
        if(NOT ${MICROSTRAIN_GIT_VERSION_RET} EQUAL 0)
            message(STATUS "Unable to determine version from Git, defaulting to version ${MICROSTRAIN_DEFAULT_GIT_VERSION}")
            set(${GIT_VERSION_OUT} ${MICROSTRAIN_DEFAULT_GIT_VERSION})
        else()
            if("${MICROSTRAIN_GIT_VERSION_OUT}" MATCHES "^v.+")
                set(${GIT_VERSION_OUT} ${MICROSTRAIN_GIT_VERSION_OUT})
            else()
                message(STATUS "Unable to determine semantic version from Git, defaulting to version ${MICROSTRAIN_DEFAULT_GIT_VERSION}")
                set(${GIT_VERSION_OUT} ${MICROSTRAIN_DEFAULT_GIT_VERSION})
            endif()
            string(REGEX REPLACE "\n" "" ${GIT_VERSION_OUT} "${${GIT_VERSION_OUT}}")
            message(STATUS "Determined version from Git: ${${GIT_VERSION_OUT}}")
        endif()
    endif()


    # Massage the version number a little so we can use it in a couple places
    string(REGEX REPLACE "^v?([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\1.\\2.\\3" ${GIT_VERSION_CLEAN_OUT} ${${GIT_VERSION_OUT}})
endmacro()

# Use the variable name not value for GIT_VERSION_CLEAN to lookup the version and also set it
# This is a followup macro for microstrain_get_git_version
# I.E. microstrain_extract_git_version(MICROSTRAIN_GIT_VERSION_CLEAN MICROSTRAIN_GIT_VERSION_MAJOR ...)
macro(microstrain_extract_git_version GIT_VERSION_CLEAN GIT_VERSION_MAJOR_OUT GIT_VERSION_MINOR_OUT GIT_VERSION_PATCH_OUT)
    if(NOT DEFINED ${GIT_VERSION_CLEAN})
        message(WARNING "Use the name to use for the variable GIT_VERSION_CLEAN instead of passing the value")
    endif()

    string(REPLACE "." ";" MICROSTRAIN_GIT_VERSION_LIST ${${GIT_VERSION_CLEAN}})
    list(LENGTH MICROSTRAIN_GIT_VERSION_LIST MICROSTRAIN_GIT_VERSION_LIST_LENGTH)

    if(MICROSTRAIN_GIT_VERSION_LIST_LENGTH GREATER_EQUAL 3)
        list(GET MICROSTRAIN_GIT_VERSION_LIST 0 ${GIT_VERSION_MAJOR_OUT})
        list(GET MICROSTRAIN_GIT_VERSION_LIST 1 ${GIT_VERSION_MINOR_OUT})
        list(GET MICROSTRAIN_GIT_VERSION_LIST 2 ${GIT_VERSION_PATCH_OUT})
    else()
        message(WARNING "Version cannot be parsed into a semantic version string.\nPlease run 'git fetch --tags' to get a properly tagged build")
        set(${GIT_VERSION_CLEAN} "0.0.0")
        set(${GIT_VERSION_MAJOR_OUT} 0)
        set(${GIT_VERSION_MINOR_OUT} 0)
        set(${GIT_VERSION_PATCH_OUT} 0)
    endif()
endmacro()

macro(microstrain_get_git_commit GIT_COMMIT_OUT)
    # Use Git to find the commit
    find_package(Git)

    set(MICROSTRAIN_DEFAULT_GIT_COMMIT "000000000")

    if(NOT GIT_FOUND)
        message(WARNING "Unable to find Git, defaulting to commit ${MICROSTRAIN_DEFAULT_GIT_COMMIT}")
        set(${GIT_COMMIT_OUT} ${MICROSTRAIN_DEFAULT_GIT_COMMIT})
    else()
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E env ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            OUTPUT_VARIABLE MICROSTRAIN_GIT_COMMIT_OUT
            ERROR_VARIABLE MICROSTRAIN_GIT_COMMIT_ERR
            RESULT_VARIABLE MICROSTRAIN_GIT_COMMIT_RET
        )

        if(NOT ${MICROSTRAIN_GIT_COMMIT_RET} EQUAL 0)
            message(STATUS "Unable to determine commit from Git, defaulting to commit ${MICROSTRAIN_DEFAULT_GIT_COMMIT}")
            set(${GIT_COMMIT_OUT} ${MICROSTRAIN_DEFAULT_GIT_COMMIT})
        else()
            # Remove newline from the commit hash
            string(REGEX REPLACE "\n" "" MICROSTRAIN_GIT_COMMIT_OUT "${MICROSTRAIN_GIT_COMMIT_OUT}")

            # Check if there are any uncommitted changes
            execute_process(
                    COMMAND ${CMAKE_COMMAND} -E env ${GIT_EXECUTABLE} diff-index --quiet HEAD --
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE MICROSTRAIN_GIT_DIRTY_RET
            )

            set(${GIT_COMMIT_OUT} "${MICROSTRAIN_GIT_COMMIT_OUT}")

            # If the diff-index command returns non-zero, there are uncommitted changes
            if(NOT ${MICROSTRAIN_GIT_DIRTY_RET} EQUAL 0)
                string(APPEND ${GIT_COMMIT_OUT} "-dirty")
            endif()

            message(STATUS "Determined commit from Git: ${${GIT_COMMIT_OUT}}")
        endif()
    endif()
endmacro()

# Try to determine what architecture we are building for based on the compiler output
# Specify the variable to set as the parameter
macro(microstrain_get_architecture SYS_ARCH_OUT)
    # Detect if this is a x64 or x86 build
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(${SYS_ARCH_OUT} "x64")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(${SYS_ARCH_OUT} "x86")
    endif()

    if(NOT DEFINED ${SYS_ARCH_OUT})
        message(STATUS "Defaulting ${SYS_ARCH_OUT} to ${CMAKE_SYSTEM_PROCESSOR}")
        set(${SYS_ARCH_OUT} ${CMAKE_SYSTEM_PROCESSOR})
    else()
        message(STATUS "Detected system architecture ${${SYS_ARCH_OUT}}")
    endif()
endmacro()

# Try to determine what system architecture we are building for based on the compiler output
# Specify the variable to set as the parameter
macro(microstrain_get_package_architecture PACKAGE_ARCH_OUT)
    unset(${PACKAGE_ARCH_OUT})

    # Detect if this is a x64 or x86 build
    if(WIN32)
        set(${PACKAGE_ARCH_OUT} "Windows")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            string(APPEND ${PACKAGE_ARCH_OUT} "-x64")
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            string(APPEND ${PACKAGE_ARCH_OUT} "-x86")
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # Convert the GCC architecture to the format that we use
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
            set(${PACKAGE_ARCH_OUT} "x86_64")
        elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
            set(${PACKAGE_ARCH_OUT} "aarch64")
        elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "armv7l|armv7")
            set(${PACKAGE_ARCH_OUT} "armhf")
        endif()
    endif()

    if(NOT DEFINED ${PACKAGE_ARCH_OUT})
        message(STATUS "Defaulting ${PACKAGE_ARCH_OUT} to ${CMAKE_SYSTEM_PROCESSOR}")
        set(${PACKAGE_ARCH_OUT} ${CMAKE_SYSTEM_PROCESSOR})
    else()
        message(STATUS "Detected package architecture ${${PACKAGE_ARCH_OUT}}")
    endif()
endmacro()

function(microstrain_detect_deb IS_DEB_OUT)
    set(${IS_DEB_OUT} OFF PARENT_SCOPE)

    if(EXISTS "/etc/debian_version")
        set(${IS_DEB_OUT} ON PARENT_SCOPE)
    endif()
endfunction()

function(microstrain_detect_rpm IS_RPM_OUT)
    set(${IS_RPM_OUT} OFF PARENT_SCOPE)

    if(EXISTS "/etc/redhat-release" OR
       EXISTS "/etc/fedora-release"
    )
        set(${IS_RPM_OUT} ON PARENT_SCOPE)
    # Both Ubuntu and RedHat may use this file
    elseif(EXISTS "/etc/os-release")
        # Check that the system isn't Debian to know that it's RedHat
        microstrain_detect_deb(IS_DEBIAN)
        if(NOT IS_DEBIAN)
            set(${IS_RPM_OUT} ON PARENT_SCOPE)
        endif()
    endif()
endfunction()

# Modify the default values of the available CMake generators only, based on the detected system
# This is typically only for library projects that just needs to make archive packages
macro(microstrain_set_cpack_archive_generators)
    # Configure the generators to use
    if(UNIX)
        if(CYGWIN)
            set(CPACK_BINARY_CYGWIN OFF)

            set(CPACK_SOURCE_CYGWIN OFF)
        else()
            if(NOT APPLE)
                set(CPACK_BINARY_TZ OFF)
            endif()

            # Set CPACK_BINARY_DEB to ON if the system is deb based
            microstrain_detect_deb(CPACK_BINARY_DEB)

            # Set CPACK_BINARY_RPM to ON if the system is rpm based
            microstrain_detect_rpm(CPACK_BINARY_RPM)

            set(CPACK_BINARY_STGZ OFF)
            set(CPACK_BINARY_TGZ OFF)

            set(CPACK_SOURCE_TBZ2 OFF)
            set(CPACK_SOURCE_TGZ OFF)
            set(CPACK_SOURCE_TXZ OFF)
            set(CPACK_SOURCE_TZ OFF)
        endif()
    else()
        set(CPACK_BINARY_ZIP ON)
        set(CPACK_BINARY_NSIS OFF)

        set(CPACK_SOURCE_7Z OFF)
        set(CPACK_SOURCE_ZIP OFF)
    endif()
endmacro()

function(microstrain_set_cpack_component_file_name)
    set(OPTIONS)
    set(SINGLE_VALUES COMPONENT_NAME COMPONENT_VERSION)
    set(OPTIONAL_SINGLE_VALUES PACKAGE_ARCH)
    set(MULTI_VALUES)

    set(ADD_ARCHIVE_ARG_PREFIX "ADD_ARCHIVE_ARG")
    cmake_parse_arguments(${ADD_ARCHIVE_ARG_PREFIX}
        "${OPTIONS}"
        "${SINGLE_VALUES};${OPTIONAL_SINGLE_VALUES}"
        "${MULTI_VALUES}"
        "${ARGN}"
    )

    # Remove the prefix from the arguments
    foreach(ARG IN LISTS OPTIONS SINGLE_VALUES OPTIONAL_SINGLE_VALUES MULTI_VALUES)
        set(${ARG} ${${ADD_ARCHIVE_ARG_PREFIX}_${ARG}})
    endforeach()

    # Make sure all the required arguments are used
    foreach(ARG IN LISTS SINGLE_VALUES)
        if(NOT ${ARG})
            message(FATAL_ERROR "Adding package components requires the ${ARG} argument to be set")
        endif()
    endforeach()

    set(FILE_NAME "${PROJECT_NAME}-${COMPONENT_NAME}")

    if(PACKAGE_ARCH)
        string(APPEND FILE_NAME "-${PACKAGE_ARCH}")
    endif()

    string(APPEND FILE_NAME "-${COMPONENT_VERSION}")

    # The component name needs to be all uppercase when creating the component variables
    string(TOUPPER "${COMPONENT_NAME}" COMPONENT_NAME_UPPER)

    set(CPACK_ARCHIVE_${COMPONENT_NAME_UPPER}_FILE_NAME "${FILE_NAME}" CACHE INTERNAL "${COMPONENT_NAME} archive file name")
    set(CPACK_DEBIAN_${COMPONENT_NAME_UPPER}_FILE_NAME "${FILE_NAME}.deb" CACHE INTERNAL "${COMPONENT_NAME} Debian package file name")
    set(CPACK_RPM_${COMPONENT_NAME_UPPER}_FILE_NAME "${FILE_NAME}.rpm" CACHE INTERNAL "${COMPONENT_NAME} RPM package file name")
endfunction()

macro(microstrain_get_git_branch GIT_BRANCH_OUT USER_CACHE_BRANCH)
    set(MICROSTRAIN_DEFAULT_GIT_BRANCH "unknown")
    set(${USER_CACHE_BRANCH} "${MICROSTRAIN_DEFAULT_GIT_BRANCH}" CACHE STRING "Branch that this build is happening on")

    if("${${USER_CACHE_BRANCH}}" STREQUAL "${MICROSTRAIN_DEFAULT_GIT_BRANCH}")
        # Use Git to find the version
        if(NOT GIT_FOUND)
            find_package(Git)
        endif()

        if(NOT GIT_FOUND)
            message(STATUS "Unable to determine branch from Git, defaulting to ${MICROSTRAIN_DEFAULT_GIT_BRANCH}")
            set(${GIT_BRANCH_OUT} ${MICROSTRAIN_DEFAULT_GIT_BRANCH})
        else()
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E env ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_VARIABLE MICROSTRAIN_GIT_BRANCH_OUT
                ERROR_VARIABLE MICROSTRAIN_GIT_BRANCH_ERR
                RESULT_VARIABLE MICROSTRAIN_GIT_BRANCH_RET
            )

            if(NOT ${MICROSTRAIN_GIT_BRANCH_RET} EQUAL 0)
                message(STATUS "Unable to determine branch from Git, defaulting to ${MICROSTRAIN_DEFAULT_GIT_BRANCH}")
                set(${GIT_BRANCH_OUT} ${MICROSTRAIN_DEFAULT_GIT_BRANCH})
            else()
                set(${GIT_BRANCH_OUT} ${MICROSTRAIN_GIT_BRANCH_OUT})
                string(REGEX REPLACE "\n" "" ${GIT_BRANCH_OUT} "${MICROSTRAIN_GIT_BRANCH_OUT}")
                message(STATUS "Determined branch from Git: ${${GIT_BRANCH_OUT}}")
            endif()
        endif()
    else()
        set(${GIT_BRANCH_OUT} "${${USER_CACHE_BRANCH}}")
        message(STATUS "Using user defined Git branch: ${${GIT_BRANCH_OUT}}")
    endif()
endmacro()

# Utility to download and extract archives (usually used for dependencies)
function(microstrain_download_and_extract_archive)
    set(OPTIONS CREATE_EXTRACTED_DIR)
    set(SINGLE_VALUES NAME URL DEPS_BASE_DIR EXTRACTED_DIR)
    set(MULTI_VALUES)

    set(DOWNLOAD_EXTRACT_ARG_PREFIX "DOWNLOAD_EXTRACT_ARG")
    cmake_parse_arguments(${DOWNLOAD_EXTRACT_ARG_PREFIX}
        "${OPTIONS}"
        "${SINGLE_VALUES}"
        "${MULTI_VALUES}"
        "${ARGN}"
    )

    # Remove the prefix from the arguments
    foreach(ARG IN LISTS OPTIONS SINGLE_VALUES MULTI_VALUES)
        set(${ARG} ${${DOWNLOAD_EXTRACT_ARG_PREFIX}_${ARG}})
    endforeach()

    # Make sure all the required arguments are used
    foreach(ARG IN LISTS SINGLE_VALUES)
        if(NOT ${ARG})
            message(FATAL_ERROR "Download and extracting files requires the ${ARG} argument to be set")
        endif()
    endforeach()

    # Make a lock file
    set(LOCK_FILE "${DEPS_BASE_DIR}/${NAME}.extract.lock")

    # If already extracted, skip
    if(EXISTS "${DEPS_BASE_DIR}/${EXTRACTED_DIR}")
        message(STATUS "${NAME} has already been downloaded and extracted")
        return()
    endif()

    # Attempt to lock the file so we can print a status message on the lock
    file(LOCK "${LOCK_FILE}" GUARD FUNCTION RESULT_VARIABLE IS_LOCKED TIMEOUT 1)

    # The try-lock will timeout (not 0) if another config is already downloading the archive
    if(NOT "${IS_LOCKED}" STREQUAL "0")
        message(STATUS "${NAME} is already being downloaded. Waiting for the lock to release...")
    endif()

    # Release the try-lock to proceed to the download
    file(LOCK "${LOCK_FILE}" RELEASE)

    # Acquire lock to serialize extraction across parallel configurations
    file(LOCK "${LOCK_FILE}" GUARD FUNCTION TIMEOUT 600)

    # Double-check after acquiring lock
    if(EXISTS "${DEPS_BASE_DIR}/${EXTRACTED_DIR}")
        message(STATUS "${NAME} has already been downloaded and extracted")
        return()
    endif()

    # Get the archive filename (including the extension)
    get_filename_component(FILENAME "${URL}" NAME)
    set(ARCHIVE_PATH "${DEPS_BASE_DIR}/${FILENAME}")

    if(NOT EXISTS "${ARCHIVE_PATH}")
        message(STATUS "Downloading ${NAME}...")
        file(DOWNLOAD "${URL}" "${ARCHIVE_PATH}" STATUS DOWNLOAD_STATUS)

        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        if(NOT ${STATUS_CODE} EQUAL 0)
            # Remove the corrupt archive
            file(REMOVE "${ARCHIVE_PATH}")

            # Certificate issues
            if(${STATUS_CODE} EQUAL 60)
                message(WARNING "The download encountered a certificate authority issue. Set CMAKE_TLS_CAINFO to the certificate authority file needed to fix the download issue")
            endif()

            list(GET DOWNLOAD_STATUS 1 STATUS_MESSAGE)
            message(FATAL_ERROR "Error downloading ${NAME}: ${STATUS_MESSAGE}")
        endif()
    endif()

    message(STATUS "Extracting ${NAME}...")

    # Set the extraction destination
    set(EXTRACT_DESTINATION "${DEPS_BASE_DIR}")

    # Optionally "create" the directory for archives that are not already in a directory upon extraction
    if(CREATE_EXTRACTED_DIR)
        string(APPEND EXTRACT_DESTINATION "/${EXTRACTED_DIR}")
    endif()

    file(ARCHIVE_EXTRACT
        INPUT "${ARCHIVE_PATH}"
        DESTINATION "${EXTRACT_DESTINATION}"
    )

    message(STATUS "Successfully extracted ${NAME}")
endfunction()

function(microstrain_generate_package_config)
    set(OPTIONS)
    set(SINGLE_VALUES PACKAGE_NAME LIBRARY_NAME PACKAGE_NAMESPACE COMPONENT_NAME)
    set(OPTIONAL_SINGLE_VALUES LIBRARY_NAME_ALIAS)
    set(MULTI_VALUES)

    set(GENERATE_PACKAGE_CONFIG_ARG_PREFIX "GENERATE_PACKAGE_CONFIG_ARG")
    cmake_parse_arguments(${GENERATE_PACKAGE_CONFIG_ARG_PREFIX}
        "${OPTIONS}"
        "${SINGLE_VALUES};${OPTIONAL_SINGLE_VALUES}"
        "${MULTI_VALUES}"
        "${ARGN}"
    )

    # Remove the prefix from the arguments
    foreach(ARG IN LISTS OPTIONS SINGLE_VALUES OPTIONAL_SINGLE_VALUES MULTI_VALUES)
        set(${ARG} ${${GENERATE_PACKAGE_CONFIG_ARG_PREFIX}_${ARG}})
    endforeach()

    # Make sure all the required arguments are used
    foreach(ARG IN LISTS SINGLE_VALUES)
        if(NOT ${ARG})
            message(FATAL_ERROR "Download and extracting files requires the ${ARG} argument to be set")
        endif()
    endforeach()

    set(PACKAGE_VERSION ${PROJECT_VERSION})

    string(TOLOWER "${PACKAGE_NAME}" PACKAGE_NAME_LOWER)

    set(MICROSTRAIN_CONFIG_FILE_NAME "${PACKAGE_NAME_LOWER}-config")

    set(MICROSTRAIN_VERSION_FILE_NAME "${MICROSTRAIN_CONFIG_FILE_NAME}-version.cmake")
    set(MICROSTRAIN_VERSION_FILE_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${MICROSTRAIN_VERSION_FILE_NAME}")

    string(APPEND MICROSTRAIN_CONFIG_FILE_NAME ".cmake")
    set(MICROSTRAIN_CONFIG_FILE_IN ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/${MICROSTRAIN_CONFIG_FILE_NAME}.in)
    set(MICROSTRAIN_CONFIG_FILE_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${MICROSTRAIN_CONFIG_FILE_NAME}")

    if(LIBRARY_NAME_ALIAS)
        # Set a proper alias name if the library target name isn't ideal
        set(ADDITIONAL_LIBRARY_ALIAS "add_library(${PACKAGE_NAMESPACE}::${LIBRARY_NAME_ALIAS} ALIAS ${PACKAGE_NAMESPACE}::${LIBRARY_NAME})\n")
    else()
        # Keep the actual library name
        set(LIBRARY_NAME_ALIAS ${LIBRARY_NAME})
    endif()

    # Set the package name uppercase to conform to the CMake variable naming convention
    # This is only used in the configure_package_config_file output file
    string(TOUPPER "${LIBRARY_NAME_ALIAS}" LIBRARY_NAME_UPPER)

    include(GNUInstallDirs)
    set(MICROSTRAIN_CMAKE_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/${PACKAGE_NAME_LOWER}")

    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        "${MICROSTRAIN_CONFIG_FILE_IN}"
        "${MICROSTRAIN_CONFIG_FILE_OUTPUT}"
        INSTALL_DESTINATION
            "${MICROSTRAIN_CMAKE_CONFIG_INSTALL_DIR}"
    )

    # Create the package version file
    write_basic_package_version_file(
        "${MICROSTRAIN_VERSION_FILE_OUTPUT}"
        VERSION "${PACKAGE_VERSION}"
        COMPATIBILITY AnyNewerVersion
        ARCH_INDEPENDENT
    )

    set(MICROSTRAIN_CONFIG_FILES
        "${MICROSTRAIN_CONFIG_FILE_OUTPUT}"
        "${MICROSTRAIN_VERSION_FILE_OUTPUT}"
    )

    # Install all of the configuration files
    install(
        FILES ${MICROSTRAIN_CONFIG_FILES}
        DESTINATION "${MICROSTRAIN_CMAKE_CONFIG_INSTALL_DIR}"
        COMPONENT "${COMPONENT_NAME}"
    )
endfunction()

macro(microstrain_append_cmake_folder)
    get_filename_component(CURRENT_DIR_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)
    string(APPEND CMAKE_FOLDER "/${CURRENT_DIR_NAME}")
endmacro()
