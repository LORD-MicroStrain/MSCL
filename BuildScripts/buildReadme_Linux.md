# **Building MSCL for Linux**

## Hold up!

Most users will not need to build MSCL themselves!

Pre-built versions are available for download. To get it, head over to the [MSCL Releases Page](https://github.com/LORD-MicroStrain/MSCL/releases), for
the latest release. Under the `Downloads` section of that release, you will find the C++, and Python versions of MSCL, as well as Example Code and
Documentation.

## I really want to build it myself

Ok, if you are making changes to MSCL's source code, or need to build MSCL from scratch for any other reason, here are the steps to build for Linux:

#### Dependencies

For more information on how to configure the build to use, or not use the optional dependencies see [this section](#configuring-the-build)

##### Required

- \>= gcc 4.9.1-5
- \>= [cmake 3.16](https://cmake.org/download/)
- &nbsp;&nbsp;\= [Boost 1.68](https://www.boost.org/users/download/)

##### Optional

- \>= libssl1.0.0
- \>= libssl-dev
- \>= libcrypto
- \>= [SWIG 4.0.0](https://swig.org/download.html) (for Python2 or Python3)
- \>= python2.7
- \>= python2.7-dev
- \>= python3
- \>= python3-dev
- \>= [turtle 1.3.1](https://turtle.sourceforge.net/)

#### Note

On some systems, you may get a virtual memory error when compiling MSCL (ex. `Virtual memory exhausted: Cannot allocate memory`). It may be necessary
to temporarily increase your Swapfile size. For an example, see
[this post](https://www.bitpi.co/2015/02/11/how-to-change-raspberry-pis-swapfile-size-on-rasbian/) explaining this for the Raspberry Pi. Keep in mind
that you may want to change back to the original swapfile size when you are done compiling MSCL (especially if using an SD card), as it can cause a lot
of unnecessary writes to your disk.

## Building MSCL for C++

1. Clone or download the [MSCL repo](https://github.com/LORD-MicroStrain/MSCL). The location of MSCL will be referred to as `<Project Root>` for the
   rest of this guide.
2. Create a build directory. We will refer to this directory as `build` for the rest of the documentation, and it will be located at
   `<Project Root>/build` but it can be named anything and put anywhere as long as you update the following steps accordingly.
3. Open a new terminal in `<Project Root>/build` and run the following command to configure the project. If you want to add options to build language
   bindings, or change configuration, see [this section](#configuring-the-build) and add the desired options as `-D` flags to the end of this command:
    ```bash
    # Please note that you should change ".." to wherever the project is located if you did not put the "build" directory directly in <Project Root>
    cmake ..
    ```
4. In the same terminal, run the following command to build all the requested targets:
    ```bash
    cmake --build . -j$(nproc)
    ```
5. All build artifacts will be located in the `<Project Root>/build` directory in a somewhat disorderly directory structure, but the important
   artifacts such as the libraries, header files, etc. will be copied to `<Project Root>/Output` in a more orderly directory structure
6. If you want to build the packages (`.deb` for debian/Ubuntu, `.rpm` for RedHat/CentOS) run the following command after building:
    ```bash
    cmake --build . --target package
    ```

## Configuring the build

The [`CMakeLists.txt`](../CMakeLists.txt) file exposes several parameters to the user to allow you to enable or disable different parts of the build.
These options can be set in the configuration step documented above by prepending them with `-D` and setting them to the desired value. For example, to
build python3, I would run the command:

```bash
cmake .. -DMSCL_BUILD_PYTHON3=ON
```

##### Boolean Parameters

The following table lists some parameters that can be set to `ON` or `OFF` to enable, or disable certain pieces of the build

| Parameter             | Description                                                                                                                     | Default |
|-----------------------|---------------------------------------------------------------------------------------------------------------------------------| ------- |
| BUILD_SHARED_LIBS     | Build MSCL as a shared library as well as a static library                                                                      | OFF     |
| MSCL_BUILD_PYTHON2    | Build the Python2 bindings for MSCL. Note that this requires swig and python2 to be installed                                   | OFF     |
| MSCL_BUILD_PYTHON3    | Build the Python3 bindings for MSCL. Note that this requires swig and python3 to be installed                                   | OFF     |
| MSCL_BUILD_TESTS      | Build the unit tests for MSCL. This also enables the `test` CMake target. Note that this also requires that turtle be installed | OFF     |
| MSCL_BUILD_EXAMPLES   | Build the examples in [`MSCL_Examples`](../MSCL_Examples/)                                                                      | OFF     |
| MSCL_ZIP_EXAMPLES     | Zip the examples in [`MSCL_Examples`](../MSCL_Examples/)                                                                        | OFF     |
| MSCL_BUILD_PACKAGE    | Build the resulting artifacts into `.deb`, or `.rpm` files                                                                      | OFF     |
| MSCL_WITH_SSL         | Whether to build with SSL support. Note that this requires openssl to be installed                                              | ON      |
| MSCL_WITH_WEBSOCKETS  | Whether to build with Websocket support                                                                                         | ON      |
| MSCL_LINK_STATIC_DEPS | Whether to link boost and OpenSSL statically. Note that this requires both libraries to have been compiled with `-fPIC`         | OFF     |

##### String Parameters

| Parameter          | Description                                                                                                                                    | Default                 |
| ------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------- |
| TURTLE_INCLUDE_DIR | Directory where the turtle include files are installed. Only required if include files are in a nonstandard place.                             | `C:/lib/turtle/include` |
| DPKG_ROOT          | Directory to search for the `dpkg` executable. Only required if `MSCL_BUILD_PACKAGE` is true, and `dpkg` is installed somewhere nonstandard         | `""`                    |
| RPMBUILD_ROOT      | Directory to search for the `rpmbuild` executable. Only required if `MSCL_BUILD_PACKAGE` is true, and `rpmbuild` is installed somewhere nonstandard | `""`                    |

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
