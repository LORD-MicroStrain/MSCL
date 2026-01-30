# MSCL C++ Examples

This directory contains C++ example projects for MSCL.

## Prerequisites

- **MSCL Library**: You must have MSCL built or installed on your system.
- **Boost**: MSCL depends on Boost (recommended 1.70.0 or newer).
- **OpenSSL**: MSCL depends on OpenSSL. (Required if `MSCL_WITH_SSL` is enabled)

## Building with CMake (Recommended)

The examples are set up to be built using CMake. You can build them as part of
the main MSCL project or as standalone projects. The main difference is the
options used to configure the project

### Configuration as a standalone project

Set the MSCL installation root directory using `MSCL_ROOT_DIR`:

#### Windows
```powershell
cmake -S . -B build -DMSCL_ROOT_DIR="C:/path/to/mscl/install"
```

#### Linux
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING=Release -DMSCL_ROOT_DIR="/path/to/mscl/install"
```

### Configuration through the MSCL project

Enable the examples using `MSCL_BUILD_EXAMPLES`:

#### Windows
```powershell
cmake -S . -B build -DMSCL_BUILD_EXAMPLES:BOOL=ON
```

#### Linux
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING=Release -DMSCL_BUILD_EXAMPLES:BOOL=ON
```

### Building the example

Build the C++ example targets:
- `MSCL-Cpp-Displacement-Example`: The displacement example.
- `MSCL-Cpp-Inertial-Example`: The inertial example.
- `MSCL-Cpp-Wireless-Example`: The wireless example.

#### Windows
```powershell
cmake --build build --config Release --target MSCL-Cpp-Wireless-Example --parallel $env:NUMBER_OF_PROCESSORS 
```

#### Linux
```shell
cmake --build build --target MSCL-Cpp-Wireless-Example --parallel $(nproc)
```

## Building without CMake (Manual)

If you prefer not to use CMake, you can manually configure your project

1. **Include Directories**:
   - Add the path to MSCL headers (e.g., `MSCL/include`).
   - Add the path to Boost headers.
   - Add the path to OpenSSL headers. (if `MSCL_WITH_SSL` is defined)
2. **Linker Dependencies**:
   - Link against `MSCL`.
   - Link against required Boost libraries (e.g., `libboost_system`).
   - Link against OpenSSL libraries (`libssl`, `libcrypto`).
3. **Compiler Options**:
   - Define `MSCL_WITH_SSL` to enable SSL support
   - Define `MSCL_WITH_WEBSOCKETS` to enable websocket support
4. **Precompiled Headers**:
   - MSCL headers often require `mscl/stdafx.h` to be included first, or use it
     as a precompiled header.
