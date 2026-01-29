# MSCL Documentation

MSCL documentation can be built from source using **Natural Docs** only for
Windows.

## Prerequisites

- **Natural Docs**: Used for generating more user-friendly documentation.
- **Windows**: Documentation building is currently only supported on Windows.

## CMake Options

To enable building the documentation, use the following CMake option:

| Option                      | Description                         | Default |
|:----------------------------|:------------------------------------|:--------|
| `MSCL_BUILD_DOCUMENTATION`  | Whether to build the documentation. | `OFF`   |

### Docs Specific Options

| Option                          | Description                                        | Default |
|:--------------------------------|:---------------------------------------------------|:--------|
| `NaturalDocs_ROOT`              | Specifies the path to the Natural Docs executable. | (Empty) |
| `NaturalDocs_REQUESTED_VERSION` | Version of Natural Docs to download if not found.  | `2.3.1` |

## Dependencies

Building documentation requires **Natural Docs**. MSCL is capable of downloading
Natural Docs if it does not already exist on the system. The options listed
above are optional to allow MSCL to find Natural Docs before downloading it.

## Building Documentation

1. Enable documentation in your CMake configuration:
   ```powershell
   cmake -S . -B build -DMSCL_BUILD_DOCUMENTATION:BOOL=ON
   ```

2. Build the documentation targets:
   - `MSCL-API-Docs`: Generates the API reference.
   - `MSCL-Full-Docs`: Generates the full documentation set.
   - `MSCL-Docs`: A master target that builds all documentation.

   ```powershell
   cmake --build build --config Release --target MSCL-Docs
   ```

## Output

Once built, the documentation will be available in the `docs` directory within
your build folder.
