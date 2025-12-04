# Force vcpkg to use the system tools instead of downloading/using its own
# This is a development option and may not work in the future
set(ENV{VCPKG_FORCE_SYSTEM_BINARIES} ON)

# Specify the cross-compilers and tell CMake we are cross-compiling
set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
set(CMAKE_CROSSCOMPILING ON)

# Set some cross-compiling flags needed to tell CMake to compile properly
set(VCPKG_C_FLAGS "-march=armv7-a+fp -mfpu=neon -mfloat-abi=hard")
set(VCPKG_CXX_FLAGS "-march=armv7-a+fp -mfpu=neon -mfloat-abi=hard")

# Set the target triplet to use (custom overlay triplet)
set(VCPKG_TARGET_TRIPLET "arm-linux-crosscompile")
