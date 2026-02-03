# MSCL C# Examples

This directory contains C# / .NET example projects for MSCL.

## Prerequisites

- **MSCL_Managed Library**: You must have `MSCL_Managed.dll` and `MSCL.dll`
  (the C++ wrapper).
- **.NET Runtime**: A compatible .NET runtime installed on your system.

See the bindings [instructions](../bindings/README.md) for more information on
how to build the MSCL C# bindings.

## Building with CMake (Recommended)

The examples are set up to be built using CMake. You can build them as part of
the main MSCL project or as standalone projects. The main difference is the
options used to configure the project.

### Configuration as a standalone project

Set the MSCL dotnet installation root directory using `MSCL_MANAGED_ROOT_DIR`:

```powershell
cmake -S . -B build -DMSCL_MANAGED_ROOT_DIR="C:/path/to/mscl/install/dotnet"
```

### Configuration through the MSCL project

Enable C# using `MSCL_BUILD_CSHARP` and the examples using `MSCL_BUILD_CSHARP_EXAMPLES`:

```powershell
cmake -S . -B build -DMSCL_BUILD_CSHARP:BOOL=ON -DMSCL_BUILD_CSHARP_EXAMPLES:BOOL=ON
```

### Building the example

Build the C# example targets:
- `MSCL-CSharp-Displacement-Example`: The displacement example.
- `MSCL-CSharp-Inertial-Example`: The inertial example.
- `MSCL-CSharp-Wireless-Example`: The wireless example.

```powershell
cmake --build build --config Release --target MSCL-CSharp-Wireless-Example --parallel $env:NUMBER_OF_PROCESSORS
```

## Building without CMake (Manual)

To use MSCL in your own C# project manually:

1. **Add Reference**: In your IDE, add a reference to `MSCL_Managed.dll`.
2. **Copy Native Library**: Ensure that the native `MSCL.dll` (unmanaged) is
   present in the same directory as your executable at runtime.
   - You can add `MSCL.dll` to your project and set "Copy to Output Directory"
     to "Copy if newer."
3. **Platform**: Ensure your project's target architecture (x64 or x86) matches
   the architecture of the MSCL DLLs you are using.
