# Building MSCL From Source

This guide provides instructions on how to build MSCL from source. Building using CMake is the recommended approach as it automatically handles dependency management and platform-specific configurations.

## Building with CMake (Recommended)

MSCL uses modern CMake (3.23+) and [vcpkg](https://vcpkg.io/) for dependency management.

### Prerequisites

*   **CMake**: Version 3.23 or higher.
*   **Git**: Required to download dependencies via submodules and vcpkg.
*   **C++ Compiler**: A compiler supporting C++14 (e.g., MSVC 2019+, GCC 7+, or Clang 5+).

### Build Steps

1.  **Clone the repository and submodules**:
    ```powershell
    git clone https://github.com/LORD-MicroStrain/MSCL.git
    cd MSCL
    git submodule update --init --recursive
    ```

2.  **Configure the project**:
    ```powershell
    cmake -S . -B build -DMSCL_BUILD_EXAMPLES=ON
    ```

3.  **Build the project**:
    ```powershell
    cmake --build build --config Release
    ```

### CMake Options

The following primary options can be passed to CMake during the configuration step (using `-D<OPTION>=<VALUE>`).

#### Core Options

| Option | Description | Default |
| :--- | :--- | :--- |
| `MSCL_USE_VCPKG` | Use vcpkg to download/install dependencies. | `ON` |
| `BUILD_SHARED_LIBS` | Build MSCL as a shared library (.dll/.so). | `OFF` |
| `MSCL_WITH_SSL` | Compile with SSL support (requires OpenSSL). | `ON` |
| `MSCL_WITH_WEBSOCKETS` | Compile with WebSocket support (requires Boost.Beast). | `ON` |
| `MSCL_LINK_STATIC_DEPS` | Link dependencies (Boost, OpenSSL) statically. | `ON` |
| `MSCL_BUILD_EXAMPLES` | Build MSCL example projects. | `OFF` |
| `MSCL_BUILD_PACKAGE` | Enable packaging support (CPack). | `OFF` |

#### Dependency Management (vcpkg)

MSCL uses **vcpkg** by default to manage its dependencies (Boost and OpenSSL). This ensures that the correct versions of the libraries are used and simplifies the setup process.

##### Using vcpkg (Default)

If `MSCL_USE_VCPKG` is `ON`, CMake will automatically:
1.  Initialize the vcpkg submodule in `deps/vcpkg`.
2.  Install the required dependencies based on your configuration (e.g., Boost, OpenSSL, Boost.Test).
3.  Configure the build to use these libraries.

| Variable | Description | Default |
| :--- | :--- | :--- |
| `VCPKG_TARGET_TRIPLET` | The triplet used to build dependencies (e.g., `x64-windows-static-md`). | Platform dependent |
| `X_VCPKG_APPLOCAL_DEPS_INSTALL` | Automatically copy dependencies to the install directory. | `ON` |
| `VCPKG_CHAINLOAD_TOOLCHAIN_FILE` | Path to a toolchain file to use in addition to vcpkg. | None |

The following dependencies are managed via vcpkg features:
*   **Boost**: Includes `asio`, `beast`, `circular_buffer`, `crc`, `filesystem`, `lambda`, `math`.
*   **OpenSSL**: Required if `MSCL_WITH_SSL` is enabled.
*   **Boost.Test**: Required if `MSCL_BUILD_TESTS` is enabled.

##### Using Pre-installed Libraries

If you prefer to use libraries already installed on your system, set `MSCL_USE_VCPKG` to `OFF`. In this case, you must provide the paths to the dependencies manually:

*   **Boost**: Set `Boost_ROOT` or `Boost_DIR` to your Boost installation path.
*   **OpenSSL**: Set `OPENSSL_ROOT_DIR` to your OpenSSL installation path.

Note: When `MSCL_USE_VCPKG` is `OFF`, the automatic download options (`MSCL_DOWNLOAD_BOOST`, `MSCL_DOWNLOAD_OPENSSL`) are also disabled.

#### Feature Options

MSCL features such as language bindings, tests, and documentation have their own sets of configuration variables. See the relevant directory READMEs for more information.

| Option | Description | Default |
| :--- | :--- | :--- |
| `MSCL_BUILD_PYTHON3` | Build Python 3 bindings. | `OFF` |
| `MSCL_BUILD_PYTHON2` | Build Python 2 bindings (legacy). | `OFF` |
| `MSCL_BUILD_CSHARP` | Build C# bindings (Windows only). | `OFF` |
| `MSCL_BUILD_TESTS` | Build the unit test suite. | `OFF` |
| `MSCL_BUILD_DOCUMENTATION` | Build documentation (Windows only). | `OFF` |

- For detailed **Binding** options (like Python versions), see [bindings/README.md](../bindings/README.md).
- For detailed **Testing** options, see [tests/README.md](../tests/README.md).
- For detailed **Documentation** options, see [docs/README.md](../docs/README.md).
- For detailed **Example** information, see [examples/README.md](../examples/README.md).

---

## Building Without CMake (Manual)

If you prefer to integrate MSCL source files directly into your own build system, follow these guidelines.

### Prerequisites

*   **C++14 Compiler**.
*   **Boost Libraries** (v1.68.0 or higher): Required for Asio, Filesystem, System, and more.
*   **OpenSSL**: Required if `MSCL_WITH_SSL` is defined.

### Include Paths

Add the following directories to your compiler's include paths:
*   `<MSCL_ROOT>/src`
*   Your Boost include directory.
*   Your OpenSSL include directory (if using SSL).

### Required Compiler Definitions

Define these macros as needed for your configuration:

| Definition | Purpose |
| :--- | :--- |
| `MSCL_WITH_SSL` | Enables SSL support for communication. |
| `MSCL_WITH_WEBSOCKETS` | Enables WebSocket support. |
| `BOOST_ASIO_NO_DEPRECATED` | Recommended for modern Boost compatibility. |
| `_CRT_SECURE_NO_WARNINGS` | (MSVC only) Suppresses CRT warnings. |

### Source Files

You must compile all `.cpp` files within the `<MSCL_ROOT>/src/mscl` directory and its subdirectories:
*   `src/mscl/*.cpp`
*   `src/mscl/Communication/*.cpp`
*   `src/mscl/MicroStrain/*.cpp` (and all nested subdirectories: `Inertial`, `Wireless`, `Displacement`)

### Dependencies to Link

*   **Boost**: `system`, `filesystem` (if not using C++17), `date_time`, `regex`.
*   **OpenSSL**: `ssl`, `crypto` (if `MSCL_WITH_SSL` is defined).
*   **System Libraries**: `ws2_32`, `crypt32`, `setupapi` (on Windows).
