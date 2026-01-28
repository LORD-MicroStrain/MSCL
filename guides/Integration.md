# MSCL Project Integration

Integrating MSCL into your project allows you to communicate with MicroStrain
Wireless, Inertial, and Displacement sensors. The recommended approach is using
**CMake**, but manual integration is also supported.

---

## CMake Integration (Recommended)

MSCL provides a CMake configuration file (`mscl-config.cmake`) that makes it
easy to find and link the library in your own CMake-based projects.

### 1. Prerequisites
Ensure you have MSCL installed or built from source. If you built from source,
the `mscl-config.cmake` file will be located in your build directory.

### 2. C++ Integration

To use MSCL in a C++ project, use `find_package` to locate the library and then
link your target to `${MSCL_LIBRARIES}`.

**Example `CMakeLists.txt`:**

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyMsclProject)

# Set MSCL_ROOT_DIR to the location where MSCL is installed or built
set(MSCL_ROOT_DIR "/path/to/mscl" CACHE PATH "Path to MSCL")
list(APPEND CMAKE_PREFIX_PATH "${MSCL_ROOT_DIR}")

# Find the MSCL package
find_package(MSCL REQUIRED CONFIG)

add_executable(my_app main.cpp)

# Link to MSCL libraries
target_link_libraries(my_app PRIVATE ${MSCL_LIBRARIES})

# Optional MSCL include directories (implied by target_link_libraries)
target_include_directories(my_app PRIVATE ${MSCL_INCLUDE_DIRS})

# MSCL uses precompiled headers or 'mscl.h' for all-in-one inclusion
target_precompile_headers(my_app PRIVATE "${MSCL_INCLUDE_DIR}/mscl/stdafx.h")
```

### 3. C# (.NET) Integration

For C# projects, MSCL provides an `MSCL_Managed` package.

**Example `CMakeLists.txt`:**

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyMsclCSharpProject LANGUAGES CSharp)

# Set MSCL_MANAGED_ROOT_DIR to the location of MSCL_Managed
set(MSCL_MANAGED_ROOT_DIR "/path/to/mscl" CACHE PATH "Path to MSCL Managed")
list(APPEND CMAKE_PREFIX_PATH "${MSCL_MANAGED_ROOT_DIR}")

# Find the MSCL_Managed package
find_package(MSCL_Managed REQUIRED CONFIG)

add_executable(my_csharp_app Program.cs)

# Use the helper function provided by MSCL_Managed to add references
mscl_managed_add_references(my_csharp_app)
```

---

## Manual Integration (Without CMake)

If you are not using CMake, you must manually configure your compiler and linker.

### C++ Integration

1.  **Include Paths**: Add the following to your compiler's include search paths:
    - `<MSCL_ROOT>/src` (if using source) or `<MSCL_INSTALL>/include`
      (if using installed headers).
    - **Boost** include directory (v1.68.0+).
    - **OpenSSL** include directory (if using SSL).

2.  **Compiler Definitions**:
    - `MSCL_WITH_SSL` (to enable SSL support).
    - `MSCL_WITH_WEBSOCKETS` (to enable WebSocket support).

3.  **Linking**:
    - Link against the MSCL library (`MSCL.lib` on Windows, `libmscl.so` on
      Linux).
    - Link against **Boost** libraries: `system`, `filesystem`, `date_time`,
      `regex`.
    - Link against **OpenSSL** libraries: `ssl`, `crypto` (if `MSCL_WITH_SSL` is
      defined).
    - **System Libraries (Windows)**: `ws2_32.lib`, `crypt32.lib`,
      `setupapi.lib`.

### Python Integration

Python integration does not strictly require CMake. You just need the `mscl.py`
and `_mscl` extension module.

1.  **Locate Files**: Find `mscl.py` and the compiled extension (`_mscl.pyd` on
    Windows or `_mscl.so` on Linux).
    * Note: The MSCL Python bindings are packaged using the respective Python
      site-packages or dist-packages directories and can be installed directly
      into those directories
2.  **Add to Path**:
    - **Method A (Recommended)**: Copy these files into your project directory
      or into a standard Python `site-packages` directory.
    - **Method B (Manual Path)**: Add the path to the directory containing these
      files in your Python script:

    ```python
    import sys
    sys.path.append('/path/to/mscl/python/bindings')
    import mscl
    ```

### C# (.NET) Integration

1.  **Add Reference**: In your IDE (like Visual Studio), add a reference to `MSCL_Managed.dll`.
2.  **Runtime Dependency**: Ensure `MSCL.dll` (the native C++ library) is present in the same directory as your application's executable at runtime.
3.  **Platform**: Ensure your project targets the correct architecture (`x64` or `x86`) to match the MSCL binaries.
