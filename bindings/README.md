# MSCL Language Bindings

MSCL provides language bindings for **Python** and **C# (.NET)** using
[SWIG](https://www.swig.org/).

## CMake Options

To enable building the bindings, use the following CMake options:

| Option               | Description                       | Default |
|:---------------------|:----------------------------------|:--------|
| `MSCL_BUILD_PYTHON3` | Build Python 3 bindings.          | `OFF`   |
| `MSCL_BUILD_PYTHON2` | Build Python 2 bindings (legacy). | `OFF`   |
| `MSCL_BUILD_CSHARP`  | Build C# bindings (Windows only). | `OFF`   |

### Python Specific Options

| Option                           | Description                                                               | Default |
|:---------------------------------|:--------------------------------------------------------------------------|:--------|
| `MSCL_PYTHON3_REQUESTED_VERSION` | The requested version of Python 3 to use (e.g., "3.12").                  | `3.12`  |
| `MSCL_PYTHON2_REQUESTED_VERSION` | The requested version of Python 2 to use (e.g., "2.7").                   | `2.7`   |
| `MSCL_DOWNLOAD_PYTHON3`          | Automatically download Python 3 if not found (requires `MSCL_USE_VCPKG`). | `ON`    |
| `MSCL_PACKAGE_PYTHON_DEBUG`      | Create a debug version of the Python packages.                            | `OFF`   |

Setting `MSCL_PYTHON3_REQUESTED_VERSION` or `MSCL_PYTHON2_REQUESTED_VERSION` to
an empty value will default to all supported versions of Python for each
respective major version.

MSCL provides bindings for the latest supported version of Python in vcpkg at
the time of release. If you need a different version of Python, set the
respective `MSCL_PYTHON3_REQUESTED_VERSION` or `MSCL_PYTHON2_REQUESTED_VERSION`
to the desired version. The requested version must already be installed on
your system.

## Prerequisites

- **SWIG**: Required to generate the binding source code. If not already
  installed, CMake will attempt to download it automatically.
- **Python**: Required for Python bindings. If `MSCL_USE_VCPKG`
  is enabled, CMake will attempt to download it automatically.
- **.NET SDK / MSVC**: Required for C# bindings.

## Building Bindings

1. Enable the desired binding in your CMake configuration:

    #### Linux
    ```shell
       cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING=Release -DMSCL_BUILD_PYTHON3:BOOL=ON -DMSCL_BUILD_CSHARP:BOOL=ON
    ```

    #### Windows
   ```powershell
      cmake -S . -B build -DMSCL_BUILD_PYTHON3:BOOL=ON -DMSCL_BUILD_CSHARP:BOOL=ON
   ```

2. Build the project:

   #### Linux
      ```shell
      cmake --build build
      ```

    #### Windows
      ```powershell
      cmake --build build --config Release
      ```

## Using the Bindings

### Python
After building, you will find `MSCL.py` and `_MSCL.pyd` (Windows) or `_MSCL.so`
(Linux) in the build output directory.

### C# (.NET)
Building the C# bindings produces:
- `MSCL.dll`: The C++ bridge library.
- `MSCL_Managed.dll`: The .NET managed library.

Add `MSCL_Managed.dll` as a reference in your .NET project and ensure `MSCL.dll`
is available in your executable's path.

### Integration
Refer to the integration [guide](../guides/Integration.md) for details on how to
use these files in your project.
