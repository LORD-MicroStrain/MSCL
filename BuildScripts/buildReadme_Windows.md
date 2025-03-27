# **Building MSCL for Windows**

## Hold up!

Most users will not need to build MSCL themselves!

Pre-built versions are available for download. To get it, head over to the
[MSCL Releases Page](https://github.com/LORD-MicroStrain/MSCL/releases), for the latest release.
Under the `Downloads` section of that release, you will find the C++, Python, and C# versions of MSCL,
as well as Example Code and Documentation.

## I really want to build it myself

Ok, if you are making changes to MSCL's source code, or need to build MSCL from scratch for any other reason,
here are the steps to build for Windows:

#### Dependencies

For more information on how to configure the build to use, or not use the optional dependencies see [this section](#configuring-the-build)

##### Required

- \>= [Visual Studio 2015](https://visualstudio.microsoft.com/downloads/) (msvc-14.0) or MSBuild equivalent
- \>= [cmake 3.16](https://cmake.org/download/)
- \>= [Boost 1.68](https://www.boost.org/users/download/)

##### Optional

- \>= [OpenSSL 1.1.0](https://www.npcglib.org/~stathis/blog/precompiled-openssl/)
- \>= [SWIG 4.0.0](https://swig.org/download.html) (for Python2, Python3, or .NET builds)
- \>= [Python 2.7](https://www.python.org/downloads/)
- \>= [Python 3.9](https://www.python.org/downloads/)
- \>= [NaturalDocs 2.0](https://www.naturaldocs.org/)

Since Windows has no standard path for libraries to be installed in,
we will refer to `LIB_PATH` as the location that you will install dependencies.
Each of these paths can be configured at build time, but for reference,
this is what a common `LIB_PATH` directory will look like:

- `LIB_PATH/boost/boost_1_68_0`
- `LIB_PATH/openssl`
- `LIB_PATH/swig/swigwin-4.0.0` (for .NET and Python builds)
- `LIB_PATH/NaturalDocs`

#### Installing Boost

SourceForge hosts some [Pre-Built Boost binaries for Windows](https://sourceforge.net/projects/boost/files/boost-binaries/).
Simply installing these for your specific compiler will make it so you do not need to build Boost yourself, which can be time-consuming.

If you want to install Boost yourself, you can follow the instructions on
[Boost's Getting Started page](https://www.boost.org/doc/libs/1_79_0/more/getting_started/windows.html).

## Building MSCL for C++

1. Clone or download the [MSCL repo](https://github.com/LORD-MicroStrain/MSCL). The location of MSCL will be referred to as `<Project Root>` for the
   rest of this guide.
2. Create a build directory. We will refer to this directory as `build` for the rest of the documentation, and it will be located at
   `<Project Root>/build` but it can be named anything and put anywhere as long as you update the following steps accordingly.
3. Open a new powershell terminal in `<Project Root>/build` and run the following command to configure the project. If you want to add options to build
   language bindings, or change configuration, see [this section](#configuring-the-build) and add the desired options as `-D` flags to the end of this
   command:
    ```powershell
    # Please note that you should change ".." to wherever the project is located if you did not put the "build" directory directly in <Project Root>
    cmake ..
    ```
4. In the same terminal, run the following command to build all the requested targets:
    ```powershell
    cmake --build .
    ```
5. All build artifacts will be located in the `<Project Root>/build` directory in a somewhat disorderly directory structure, but the important
   artifacts such as the libraries, header files, etc. will be copied to `<Project Root>/Output` in a more orderly directory structure
6. If you want to build the zip files run the following command after building:
    ```powershell
    cmake --build . --target zip
    ```

## Configuring the build

The [`CMakeLists.txt`](../CMakeLists.txt) file exposes several parameters to the user to allow you to enable or disable different parts of the build.
These options can be set in the configuration step documented above by prepending them with `-D` and setting them to the desired value.
For example, to build python3, I would run the command:

```powershell
cmake .. -DMSCL_BUILD_PYTHON3=ON
```

##### Boolean Parameters

The following table lists some parameters that can be set to `ON` or `OFF` to enable, or disable certain pieces of the build

| Parameter                | Description                                                                                                                     | Default |
|--------------------------|---------------------------------------------------------------------------------------------------------------------------------| ------- |
| BUILD_SHARED_LIBS        | Build MSCL as a shared library as well as a static library                                                                      | OFF     |
| MSCL_BUILD_PYTHON2       | Build the Python2 bindings for MSCL. Note that this requires swig and python2 to be installed                                   | OFF     |
| MSCL_BUILD_PYTHON3       | Build the Python3 bindings for MSCL. Note that this requires swig and python3 to be installed                                   | OFF     |
| MSCL_BUILD_CSHARP        | Build the C# bindings for MSCL. Note that this requires swig and a csharp compiler to be installed                              | OFF     |
| MSCL_BUILD_TESTS         | Build the unit tests for MSCL. This also enables the `test` CMake target. Note that this also requires that turtle be installed | OFF     |
| MSCL_BUILD_EXAMPLES      | Build the examples in [`MSCL_Examples`](../MSCL_Examples/)                                                                      | OFF     |
| MSCL_ZIP_EXAMPLES        | Zip the examples in [`MSCL_Examples`](../MSCL_Examples/)                                                                        | OFF     |
| MSCL_BUILD_DOCUMENTATION | Builds the documentation using NaturalDocs.                                                                                     | OFF     |
| MSCL_WITH_SSL            | Whether to build with SSL support. Note that this requires openssl to be installed                                              | ON      |
| MSCL_WITH_WEBSOCKETS     | Whether to build with Websocket support                                                                                         | ON      |

##### String Parameters

| Parameter          | Description                                                                                                                                                        | Default                 |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ----------------------- |
| TURTLE_INCLUDE_DIR | Directory where the turtle include files are installed. Only required if include files are in a nonstandard place.                                                 | `C:/lib/turtle/include` |
| NATURAL_DOCS_ROOT  | Directory to search for the `NaturalDocs` executable. Only required if `MSCL_BUILD_DOCUMENTATION` is true, and `NaturalDocs` is installed somewhere nonstandard         | `C:/lib/NaturalDocs`    |

##### Other parameters

MSCL uses existing `find_package` calls to find other packages such as boost, OpenSSL, etc.
which all expose their own variables that can be overridden in the same way as the above parameters.
See the following documentation for more information on how to configure the `find_package` call for those modules:

* [FindGit](https://cmake.org/cmake/help/latest/module/FindGit.html)
* [FindBoost](https://cmake.org/cmake/help/latest/module/FindBoost.html)
* [FindThreads](https://cmake.org/cmake/help/latest/module/FindThreads.html)
* [FindOpenSSL](https://cmake.org/cmake/help/latest/module/FindOpenSSL.html)
* [FindSWIG](https://cmake.org/cmake/help/latest/module/FindSWIG.html)
* [FindPython2](https://cmake.org/cmake/help/latest/module/FindPython2.html)
* [FindPython3](https://cmake.org/cmake/help/latest/module/FindPython3.html)
