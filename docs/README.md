# MSCL Documentation

MSCL documentation can be built from source using **Doxygen** and **Natural Docs**.

## CMake Options

To enable building the documentation, use the following CMake option (Windows only):

| Option | Description | Default |
| :--- | :--- | :--- |
| `MSCL_BUILD_DOCUMENTATION` | Whether to build the documentation. | `OFF` |

## Prerequisites

- **Doxygen**: Required for generating API documentation from source comments.
- **Natural Docs**: Used for generating more user-friendly documentation.
- **Windows**: Documentation building is currently only supported on Windows.

## Building Documentation

1. Enable documentation in your CMake configuration:
   ```powershell
   cmake -S . -B build -DMSCL_BUILD_DOCUMENTATION=ON
   ```

2. Build the documentation targets:
   - `MSCL-API-Docs`: Generates the API reference.
   - `MSCL-Full-Docs`: Generates the full documentation set.
   - `MSCL-Docs`: A master target that builds all documentation.

   ```powershell
   cmake --build build --target MSCL-Docs
   ```

## Output

Once built, the documentation will be available in the `docs` directory within your build folder.
