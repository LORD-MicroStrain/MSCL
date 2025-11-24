# To use this file properly with vcpkg, set VCPKG_CHAINLOAD_TOOLCHAIN_FILE to
# this file instead of using this directly as the toolchain file.
# vcpkg will extend its toolchain file with this one

# Cross-compile Linux ARM32 on ARM64
# Requires the following packages to be installed:
#   gcc-arm-linux-gnueabihf
#   g++-arm-linux-gnueabihf
#   binutils-arm-linux-gnueabihf
#   libc6-armhf-cross
#   libstdc++6-armhf-cross
#   qemu-user
#   qemu-user-static

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR armv7l)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_AR arm-linux-gnueabihf-ar)
set(CMAKE_RANLIB arm-linux-gnueabihf-ranlib)

set(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS "-march=armv7-a -mfpu=neon -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS "-march=armv7-a -mfpu=neon -mfloat-abi=hard")

set(CMAKE_CROSSCOMPILING_EMULATOR qemu-arm-static)
