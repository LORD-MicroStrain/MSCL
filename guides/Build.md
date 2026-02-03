# Building MSCL From Source

This guide provides instructions on how to build MSCL from source. Building
using CMake is the recommended approach as it automatically handles dependency
management and platform-specific configurations.

## Building with CMake (Recommended)

MSCL uses modern CMake (3.23+) and [vcpkg](https://vcpkg.io/) for dependency
management.

### Prerequisites

*   **CMake**: Version 3.23 or higher.
*   **Git**: Required to download dependencies via submodules and vcpkg.
*   **C++ Compiler**: A compiler supporting C++14.

### Submodules

MSCL uses submodules to manage certain dependencies.

#### Initialization

After cloning the project, make sure the submodules are initialized

```shell
git submodule update --init --recursive
```

#### Updates

If the project already exists, the submodules may need to be updated
periodically, but should already happen on `git pull`

```shell
git submodule update --recursive
```

### Build Steps

1.  **Configure the project**:

   #### Windows

   ```powershell
   cmake -S . -B build -DMSCL_BUILD_CPP_EXAMPLES:BOOL=ON
   ```

   #### Linux

   ```shell
   cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING=Release -DMSCL_BUILD_CPP_EXAMPLES:BOOL=ON
   ```

2.  **Build the project**:

   #### Windows

   ```powershell
   cmake --build build --config Release --parallel $env:NUMBER_OF_PROCESSORS
   ```

   #### Linux

   ```shell
   cmake --build build --parallel $(nproc)
   ```

### CMake Options

The following primary options can be passed to CMake during the configuration
step (using `-D<OPTION>=<VALUE>`).

#### Core Options

| Option                  | Description                                            | Default |
|:------------------------|:-------------------------------------------------------|:--------|
| `MSCL_USE_VCPKG`        | Use vcpkg to download/install dependencies.            | `ON`    |
| `MSCL_WITH_SSL`         | Compile with SSL support (requires OpenSSL).           | `ON`    |
| `MSCL_WITH_WEBSOCKETS`  | Compile with WebSocket support (requires Boost.Beast). | `ON`    |
| `MSCL_LINK_STATIC_DEPS` | Link dependencies (Boost, OpenSSL) statically.         | `ON`    |
| `BUILD_SHARED_LIBS`     | Build MSCL as a shared library (.dll/.so).             | `OFF`   |

#### Dependency Management

MSCL is now self-contained and can manage its own dependencies. All dependencies
are included within the MSCL repository, simplifying the build process and
reducing external dependencies. There are options to turn off all or some
dependency management in favor of using system-installed libraries. In some
cases, MSCL will try to find system-installed libraries first before fetching
them.

##### Using vcpkg (Default)

vcpkg is the default method of dependency management for MSCL. It simplifies the
process of obtaining and configuring dependencies, ensuring that the correct
versions are used across different platforms. These include Boost, OpenSSL, and
Python3

If `MSCL_USE_VCPKG` is `ON`, CMake will automatically:
1.  Initialize the vcpkg submodule in `deps/vcpkg`.
2.  Install the required dependencies based on your configuration (e.g., Boost,
    OpenSSL, Boost.Test, Python3).
3.  Configure the build to use these libraries.

| Variable                | Description                                               | Default |
|:------------------------|:----------------------------------------------------------|:--------|
| `MSCL_DOWNLOAD_BOOST`   | Download Boost using vcpkg                                | `ON`    |
| `MSCL_DOWNLOAD_OPENSSL` | Automatically copy dependencies to the install directory. | `ON`    |
| `MSCL_DOWNLOAD_PYTHON3` | Path to a toolchain file to use in addition to vcpkg.     | `ON`    |

If any of these options are `OFF`, vcpkg will not download the dependency and
instead, MSCL will expect it to be installed on the system already

The following dependencies can be managed via vcpkg features if any of the
previous `MSCL_DOWNLOAD_*` options are `ON`:
*   **Boost**: Required.
*   **OpenSSL**: Required if `MSCL_WITH_SSL` is enabled.
*   **Boost.Test**: Required if `MSCL_BUILD_TESTS` is enabled.
*   **Python3**: Required if `MSCL_BUILD_PYTHON3` is enabled.

##### Using Pre-installed Libraries

If you prefer to use libraries already installed on your system, set
`MSCL_USE_VCPKG` to `OFF`. In this case, you may need to provide the paths to
the dependencies manually:

*   **Boost**: Set `Boost_ROOT` or `Boost_DIR` to your Boost installation path.
*   **OpenSSL**: Set `OPENSSL_ROOT_DIR` to your OpenSSL installation path.

Note: When `MSCL_USE_VCPKG` is `OFF`, the automatic download options
(`MSCL_DOWNLOAD_*`) are also disabled.

For any dependency not managed by vcpkg, MSCL will attempt to find it on the
system first before downloading it. This includes:

*   **Swig**: Set `SWIG_ROOT` to your Swig executable path. (Required for
    generating all bindings)
*   **Natural Docs**: Set `NaturalDocs_ROOT` to your Natural Docs executable
    path. (Required for generating documentation - Windows only)
*   **Turtle**: Set `Turtle_ROOT` to your Turtle header include directory.
    (Required for building unit tests)

#### Feature Options

MSCL features such as examples, language bindings, tests, and documentation have
their own sets of configuration variables. See the relevant directory READMEs
for more information.

| Option                       | Description                                                                     | Default |
|:-----------------------------|:--------------------------------------------------------------------------------|:--------|
| `MSCL_BUILD_CPP_EXAMPLES`    | Enables C++ examples.                                                           | `OFF`   |
| `MSCL_BUILD_PYTHON3`         | Enables Python 3 bindings.                                                      | `OFF`   |
| `MSCL_BUILD_PYTHON2`         | Enables Python 2 bindings (legacy).                                             | `OFF`   |
| `MSCL_BUILD_PYTHON_EXAMPLES` | Enables Python examples. (Requires `MSCL_BUILD_PYTHON3` or `MSCL_BUILD_PYTHON2` | `OFF`   |
| `MSCL_BUILD_CSHARP`          | ENables C# bindings (Windows only).                                             | `OFF`   |
| `MSCL_BUILD_CSHARP_EXAMPLES` | Enables C# examples. (Requires `MSCL_BUILD_CSHARP`)                             | `OFF`   |
| `MSCL_BUILD_TESTS`           | Enables the unit test suite.                                                    | `OFF`   |
| `MSCL_BUILD_DOCUMENTATION`   | Enables documentation (Windows only).                                           | `OFF`   |
| `MSCL_BUILD_PACKAGE`         | Enables packaging support (CPack).                                              | `OFF`   |

- For detailed **Binding** information, see the bindings
  [instructions](../bindings/README.md).
- For detailed **Testing** information, see tests
  [instructions](../tests/README.md).
- For detailed **Documentation** information, see the docs
  [instructions](../docs/README.md).
- For detailed **Examples** information, see the examples
  [instructions](../examples/README.md).

---

## Building Without CMake (Manual)

If you prefer to build MSCL without CMake, follow these guidelines.

### Prerequisites

*   **C++14 Compiler**.
*   **Boost Libraries** (v1.70.0 or higher): Required for Asio, Filesystem,
    System, and more.
*   **OpenSSL**: Required if `MSCL_WITH_SSL` is defined.

### Include Paths

Add the following directories to your compiler's include paths:
*   `<MSCL_ROOT>/src`
*   Your Boost include directory.
*   Your OpenSSL include directory (if using SSL).

### Required Compiler Definitions

Define these macros as needed for your configuration:

| Definition                 | Purpose                                     |
|:---------------------------|:--------------------------------------------|
| `MSCL_WITH_SSL`            | Enables SSL support for communication.      |
| `MSCL_WITH_WEBSOCKETS`     | Enables WebSocket support.                  |
| `_CRT_SECURE_NO_WARNINGS`  | (MSVC only) Suppresses CRT warnings.        |

### Dependencies to Link

*   **Boost**: `system`, `filesystem`, `date_time`, `regex`.
*   **OpenSSL**: `ssl`, `crypto` (if `MSCL_WITH_SSL` is defined).
