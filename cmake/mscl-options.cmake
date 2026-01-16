# Catch-all option to use vcpkg for dependency management
# Any dependency not installed using vcpkg will attempt to find the dependency
# first and ONLY download/install it if it's not found
option(MSCL_USE_VCPKG "Option to use vcpkg to download/install some dependencies" ON)

option(BUILD_SHARED_LIBS "Whether or not to build the shared version of the library." OFF)
option(MSCL_BUILD_PYTHON2 "Whether to build the python 2 bindings." OFF)
option(MSCL_BUILD_PYTHON3 "Whether to build the python 3 bindings." OFF)
option(MSCL_LINK_STATIC_DEPS "Whether to link the dependencies statically. Please note that this means that OpenSSL and Boost must be built with -fPIC on Linux" ON)
option(MSCL_BUILD_TESTS "Whether to build the unit tests." OFF)
option(MSCL_WITH_SSL "Whether or not to compile the library with SSL support" ON)

# Allow the user to use a pre-installed version of Boost
option(MSCL_DOWNLOAD_BOOST "MSCL can download Boost if not already installed. Set Boost_ROOT to the Boost directory if this is turned off" ON)

if(NOT MSCL_USE_VCPKG)
    set(MSCL_DOWNLOAD_BOOST OFF)
endif()

if(MSCL_WITH_SSL)
    # Allow the user to use a pre-installed version of OpenSSL
    option(MSCL_DOWNLOAD_OPENSSL "MSCL can download OpenSSL if not already installed. Set OPENSSL_ROOT_DIR to the OpenSSL directory if this is turned off" ON)

    if(NOT MSCL_USE_VCPKG)
        set(MSCL_DOWNLOAD_OPENSSL OFF)
    endif()
endif()

# Helper to check if Python is requested
set(MSCL_BUILD_PYTHON OFF)
if(MSCL_BUILD_PYTHON3 OR MSCL_BUILD_PYTHON2)
    set(MSCL_BUILD_PYTHON ON)
endif()

# Dependencies should be linked statically if MSCL is built statically
if(NOT BUILD_SHARED_LIBS AND NOT MSCL_LINK_STATIC_DEPS)
    set(MSCL_LINK_STATIC_DEPS ON)
endif()
