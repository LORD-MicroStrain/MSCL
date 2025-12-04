set(VCPKG_TARGET_ARCHITECTURE arm)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)

set(VCPKG_CMAKE_SYSTEM_NAME Linux)

# Include the toolchain file for cross-compiling
include("${CMAKE_CURRENT_LIST_DIR}/../toolchains/arm-linux-crosscompile-toolchain.cmake")
