# MSCL Python Examples

This directory contains Python example projects for MSCL.

## Prerequisites

- **MSCL Python Library**: You must have `MSCL.py` and the native module 
  `_MSCL.pyd` (Windows) or `_MSCL.so` (Linux).
- **Python**: A compatible Python version.

See the bindings [instructions](../bindings/README.md) for more information on
how to build the MSCL Python bindings.

**Note:** The version of Python used must match the version used to build the
MSCL Python bindings.

## Running the example

To run the Python examples:

1. **Locate MSCL**: Find the `MSCL.py` and `_MSCL.pyd`/`_MSCL.so` files.
2. **Set PYTHONPATH**: Add the directory containing these files to your
   `PYTHONPATH` environment variable.

   #### Windows
   ```powershell
   $env:PYTHONPATH += ";C:/path/to/mscl/python/binding"
   ```

   #### Linux
   ```shell
   export PYTHONPATH=$PYTHONPATH:/path/to/mscl/python/binding
   ```

3. **Run the Script**:
   ```shell
   python examples/python/wireless/main.py
   ```

Alternatively, you can copy `MSCL.py` and the native module into the same
directory as the example script or into your site-packages/dist-packages.

## Running with CMake

CMake can be used to set up a wrapper that automatically configures the 
`PYTHONPATH` to run the examples against the built MSCL library. This only works
as part of the main MSCL project.

### Configuring the example

The following options need to be set:

- `MSCL_BUILD_PYTHON3`: Required to build Python3 bindings (`ON`).
- `MSCL_PYTHON3_REQUESTED_VERSION`: Optional to override the Python3 version
  (`"3.12"`).
- `MSCL_BUILD_PYTHON2`: Required to build Python2 bindings (`ON`).
- `MSCL_PYTHON2_REQUESTED_VERSION`: Optional to override the Python2 version
  (`"2.7"`).
- `MSCL_BUILD_EXAMPLES`: Enable building the examples (`ON`).

#### Windows

```powershell
cmake -S . -B build -DMSCL_BUILD_PYTHON3:BOOL=ON -DMSCL_BUILD_EXAMPLES:BOOL=ON
```

#### Linux

```shell
cmake -S . -B build  -DCMAKE_BUILD_TYPE:STRING=Release -DMSCL_BUILD_PYTHON3:BOOL=ON -DMSCL_BUILD_EXAMPLES:BOOL=ON
```

### Building the example

Build the Python example targets:
- `MSCL-Python3.12-Displacement-Example`: The displacement example.
- `MSCL-Python3.12-Inertial-Example`: The inertial example.
- `MSCL-Python3.12-Wireless-Example`: The wireless example.

*Note: Replace 3.12 with your Python version as needed*

#### Windows
```powershell
cmake --build build --config Release --target MSCL-Python3.12-Wireless-Example --parallel $env:NUMBER_OF_PROCESSORS 
```

#### Linux
```shell
cmake --build build --target MSCL-Python3.12-Wireless-Example --parallel $(nproc)
```
