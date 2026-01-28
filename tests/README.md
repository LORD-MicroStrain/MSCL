# MSCL Unit Testing

MSCL uses a suite of unit tests to ensure library stability and correctness. The tests are built using the **Boost Test Framework** and the **Turtle** mock library.

## CMake Options

To enable building the tests, use the following CMake option:

| Option | Description | Default |
| :--- | :--- | :--- |
| `MSCL_BUILD_TESTS` | Whether to build the unit test suite. | `OFF` |

### Test Specific Options

| Option | Description | Default |
| :--- | :--- | :--- |
| `Turtle_ROOT` | Manual path to search for Turtle headers. | (Empty) |
| `Turtle_REQUESTED_VERSION` | Version of Turtle to download if not found. | `2.0.0` |

## Prerequisites

- **Boost**: Specifically the `unit_test_framework` component.
- **Turtle**: A C++ mock object library based on Boost. CMake will attempt to download it automatically if not found.

## Building and Running Tests

1. Enable tests in your CMake configuration:
   ```powershell
   cmake -S . -B build -DMSCL_BUILD_TESTS=ON
   ```

2. Build the tests:
   ```powershell
   cmake --build build --config Debug --target MSCL-Tests
   ```

3. Run the tests:
   ```powershell
   cd build
   ctest -C Debug
   ```
   Alternatively, you can run the test executable directly:
   ```powershell
   ./tests/Debug/MSCL-Tests.exe
   ```

## Test Results
The tests are configured to output results in JUNIT format to `mscl_test_results.xml` by default when run via the build system, which is useful for CI/CD integration.
