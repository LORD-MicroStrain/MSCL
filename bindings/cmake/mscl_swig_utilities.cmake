set(SWIG_ROOT "" CACHE PATH "Location to search for the Swig executable")
set(SWIG_REQUESTED_VERSION "4.0.0" CACHE STRING "Requested version of Swig")

# Attempt to find Swig before manually downloading it (this assumes SWIG_ROOT was set by the user)
find_package("SWIG" "${SWIG_REQUESTED_VERSION}" QUIET)

# Set a default swig executable location and try again
if(NOT SWIG_FOUND)
    set(SWIG_PACKAGE_NAME "swig")
    if(MSVC)
        string(APPEND SWIG_PACKAGE_NAME "win")
    endif()

    set(SWIG_ARCHIVE_DIR "${SWIG_PACKAGE_NAME}-${SWIG_REQUESTED_VERSION}")
    set(SWIG_ARCHIVE_URL "https://sourceforge.net/projects/swig/files/${SWIG_PACKAGE_NAME}/${SWIG_ARCHIVE_DIR}/${SWIG_ARCHIVE_DIR}")

    if(MSVC)
        string(APPEND SWIG_ARCHIVE_URL ".zip")
    else()
        string(APPEND SWIG_ARCHIVE_URL ".tar.gz")
    endif()

    microstrain_download_and_extract_archive(
        NAME "Swig"
        URL "${SWIG_ARCHIVE_URL}"
        DEPS_BASE_DIR "${MSCL_DEPS_BASE_DIR}"
        EXTRACTED_DIR "${SWIG_ARCHIVE_DIR}"
    )

    set(SWIG_ROOT "${MSCL_DEPS_BASE_DIR}/${SWIG_ARCHIVE_DIR}" CACHE PATH "Location to search for the Swig executable" FORCE)

    # On Linux, build and install Swig locally using the source
    if(UNIX)
        set(SWIG_PROJECT_DIR "${SWIG_ROOT}")

        # Update the cache variable with the local install directory of Swig
        set(SWIG_ROOT "${SWIG_ROOT}/install" CACHE PATH "Location to search for the Swig executable" FORCE)

        # Attempt to find swig again before installing
        find_package("SWIG" "${SWIG_REQUESTED_VERSION}" QUIET)

        # Swig hasn't been installed yet. Install it
        if(NOT SWIG_FOUND)
            # Make sure to build Swig natively on the system, even for cross-compilation
            set(SWIG_NATIVE_COMPILE_OPTIONS
                "CC=/usr/bin/gcc"
                "CXX=/usr/bin/g++"
                "LD=/usr/bin/ld"
                "AR=/usr/bin/ar"
                "AS=/usr/bin/as"
                "RANLIB=/usr/bin/ranlib"
                "STRIP=/usr/bin/strip"
                "--unset=CFLAGS"
                "--unset=CXXFLAGS"
                "--unset=LDFLAGS"
                "--unset=CPPFLAGS"
            )

            # Configure Swig with a local install directory
            # All the '--without-*' options are to disable tests and examples from being compiled
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E
                    env ${SWIG_NATIVE_COMPILE_OPTIONS}
                    ./configure --prefix ${SWIG_ROOT} --without-pcre --without-perl5 --without-python --without-python3
                WORKING_DIRECTORY "${SWIG_PROJECT_DIR}"
                RESULT_VARIABLE SWIG_CONFIGURE_RESULT
            )
            if(NOT SWIG_CONFIGURE_RESULT EQUAL 0)
                message(FATAL_ERROR "Swig configuration failed with code ${SWIG_CONFIGURE_RESULT}")
            endif()

            # Build
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E
                    env ${SWIG_NATIVE_COMPILE_OPTIONS}
                    make
                WORKING_DIRECTORY "${SWIG_PROJECT_DIR}"
                RESULT_VARIABLE SWIG_MAKE_RESULT
            )
            if(NOT SWIG_MAKE_RESULT EQUAL 0)
                message(FATAL_ERROR "Swig make failed with code ${SWIG_MAKE_RESULT}")
            endif()

            # Install
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E
                    env ${SWIG_NATIVE_COMPILE_OPTIONS}
                    make install
                WORKING_DIRECTORY "${SWIG_PROJECT_DIR}"
                RESULT_VARIABLE SWIG_INSTALL_RESULT
            )
            if(NOT SWIG_INSTALL_RESULT EQUAL 0)
                message(FATAL_ERROR "Swig installation failed with code ${SWIG_INSTALL_RESULT}")
            endif()
        endif()
    endif()
endif()

find_package("SWIG" "${SWIG_REQUESTED_VERSION}" REQUIRED)

# Include the Swig module after finding Swig
include(UseSWIG)

# Tell Swig to generate files in module specific directories in the current binary directory
set(UseSWIG_MODULE_VERSION 2)

macro(mscl_add_swig_module_library)
    set(OPTIONS)
    set(SINGLE_VALUES LIB_NAME MODULE_LANGUAGE)
    set(OPTIONAL_SINGLE_VALUES OUTFILE_DIR)
    set(MULTI_VALUES ADDITIONAL_SWIG_OPTIONS LINK_OPTIONS)

    set(SWIG_MODULE_LIB_PREFIX "SWIG_MODULE_LIB_ARG")
    cmake_parse_arguments(${SWIG_MODULE_LIB_PREFIX}
        "${OPTIONS}"
        "${SINGLE_VALUES};${OPTIONAL_SINGLE_VALUES}"
        "${MULTI_VALUES}"
        "${ARGN}"
    )

    # Remove the prefix from the arguments
    foreach(ARG IN LISTS OPTIONS SINGLE_VALUES MULTI_VALUES OPTIONAL_SINGLE_VALUES)
        set(${ARG} ${${SWIG_MODULE_LIB_PREFIX}_${ARG}})
    endforeach()

    # Make sure all the required arguments are used
    foreach(ARG IN LISTS SINGLE_VALUES)
        if(NOT ${ARG})
            message(FATAL_ERROR "Creating a Swig binding library requires the ${ARG} argument to be set")
        endif()
    endforeach()

    # Set up the Swig interface file properties
    set_source_files_properties(${SWIG_SOURCE_FILES} PROPERTIES
        CPLUSPLUS ON
        SWIG_MODULE_NAME "${MSCL_LIBRARY}" # The module name should always match the MSCL library name
        INCLUDE_DIRECTORIES "${MSCL_INCLUDE_DIRS}"
        COMPILE_OPTIONS "${ADDITIONAL_SWIG_OPTIONS}"
    )

    # Generate C++ wrapper and binding files at BUILD time (not configure time)
    swig_add_library("${LIB_NAME}"
        TYPE SHARED
        LANGUAGE "${MODULE_LANGUAGE}"
        OUTPUT_DIR "${OUTFILE_DIR}"
        SOURCES ${SWIG_SOURCE_FILES}
    )

    # The Swig modules cannot be built without the MSCL library
    add_dependencies("${LIB_NAME}" "${MSCL_LIBRARY}")

    # All the bindings require linking to MSCL
    target_link_libraries("${LIB_NAME}" PRIVATE
        "${MSCL_LIBRARY}"
    )

    target_include_directories("${LIB_NAME}" PRIVATE
        ${MSCL_INCLUDE_DIRS}
    )

    set_target_properties("${LIB_NAME}" PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS OFF # Exporting all symbols causes issues in Swig with the precompiled header
        OUTPUT_NAME "${MSCL_LIBRARY}"
        POSITION_INDEPENDENT_CODE TRUE # Make sure Linux compiles static libraries with -fPIC
    )

    # Set some compiler options
    if(MSVC)
        target_compile_options("${LIB_NAME}" PRIVATE
            "/MP"
            "/bigobj"
        )
    endif()

    if(LINK_OPTIONS)
        target_link_options("${LIB_NAME}" PRIVATE
            ${LINK_OPTIONS}
        )
    endif()
endmacro()
