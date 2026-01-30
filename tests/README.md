# MSCL Unit Testing

MSCL uses a suite of unit tests to ensure library stability and correctness. The
tests are built using the **Boost Test Framework** and the **Turtle** mock
library.

## Prerequisites

- **Boost**: Specifically the `unit_test_framework` component.
- **Turtle**: A C++ mock object library based on Boost.

## CMake Options

To enable building the tests, use the following CMake option:

| Option             | Description                           | Default |
|:-------------------|:--------------------------------------|:--------|
| `MSCL_BUILD_TESTS` | Whether to build the unit test suite. | `OFF`   |

### Test Specific Options

| Option                     | Description                                 | Default |
|:---------------------------|:--------------------------------------------|:--------|
| `Turtle_ROOT`              | Manual path to search for Turtle headers.   | (Empty) |
| `Turtle_REQUESTED_VERSION` | Version of Turtle to download if not found. | `2.0.0` |

## Dependencies

Building documentation requires the Boost testing framework and **Turtle**. MSCL
is capable of downloading Turtle if it does not already exist on the system. The
options listed above are optional to allow MSCL to find Turtle before
downloading it. The Boost testing framework will be downloaded using vcpkg if
`MSCL_USE_VCPKG` and `MSCL_DOWNLOAD_BOOST` are `ON` otherwise, it needs to
already exist on the system.

## Building and Running Tests

1. Enable tests in your CMake configuration:

   #### Windows

   ```powershell
   cmake -S . -B build -DMSCL_BUILD_TESTS:BOOL=ON
   ```

   #### Linux

   ```shell
   cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING=Debug -DMSCL_BUILD_TESTS:BOOL=ON
   ```

2. Build the tests:

   #### Windows

   ```powershell
   cmake --build build --config Debug --target MSCL-Tests --parallel $env:NUMBER_OF_PROCESSORS
   ```

   #### Linux

   ```shell
   cmake --build build --target MSCL-Tests --parallel $(nproc)
   ```

3. Run the tests:

   ```shell
   cd build
   ctest -C Debug
   ```

   Alternatively, you can run the test executable directly:

   #### Windows

   ```powershell
   ./build/tests/Debug/MSCL-Tests.exe
   ```

   #### Linux

   ```shell
   ./build/Debug/tests/MSCL-Tests
   ```

## Test Results
The tests are configured to output results in JUNIT format to
`mscl_test_results.xml` by default when run via the build system, which is
useful for CI/CD integration.
