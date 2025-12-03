# Custom triplet needed when building for arm32 on an arm64 computer using docker
set(VCPKG_TARGET_ARCHITECTURE arm)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

set(VCPKG_C_FLAGS "-march=armv7-a+fp -mfpu=neon -mfloat-abi=hard")
set(VCPKG_CXX_FLAGS "-march=armv7-a+fp -mfpu=neon -mfloat-abi=hard")
