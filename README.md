# MSCL - The MicroStrain Communication Library

MSCL is developed by
[MicroStrain](https://www.hbkworld.com/en/Campaign/microstrain-by-hbk) in
Williston, VT. Its purpose is to serve as a simple user-friendly API to interact
with our [Wireless](https://www.hbkworld.com/en/products/instruments/wireless-daq-systems),
and [Inertial](https://www.hbkworld.com/en/products/transducers/inertial-sensors)
sensors.

[![GitHub tag status](https://img.shields.io/github/checks-status/LORD-MicroStrain/MSCL/v68.0.0?label=v68.0.0)](https://github.com/LORD-MicroStrain/MSCL/releases/v68.0.0/) &nbsp;
[![GitHub tag status](https://img.shields.io/github/checks-status/LORD-MicroStrain/MSCL/latest?label=latest)](https://github.com/LORD-MicroStrain/MSCL/releases/latest/)

### Support

If you have any questions or run into any issues, please let us know!
[MicroStrain Support Portal](https://support.microstrain.com)

Also, have a look at our [FAQs](guides/FAQ.md) for common issues.

### Inertial Successor API

For projects using our latest inertial product lines, check out our new
lightweight C/C++ API, [MIP SDK](https://github.com/LORD-MicroStrain/mip_sdk)

## Releases

Please see our [releases](../../releases) page for all of our release notes and
packages</br>
Packages for the current release, <b>v68.0.0</b>, can be found
[here](../../releases/tag/v68.0.0)</br>
Latest pre-release packages can be found [here](../../releases/tag/latest)</br>

## Supported Packages

MSCL is built and tested for the following list of systems and architectures.
Refer to the build [instructions](guides/Build.md) for more information on
building MSCL from source if your system configuration isn't listed.

### Windows (MSVC)

MSCL is supported on Windows for both x64 and x86 architectures, including all
supported [bindings](bindings/README.md)

### Linux

#### Debian

MSCL is supported on Debian for x64 (x86_64), ARM64 (aarch64) and ARM32 (armv8l)
architectures, including Python [bindings](bindings/README.md)

#### RPM

We are no longer providing RPM packages.</br>
If you wish to continue using MSCL on RPM systems, please see
build [instructions](guides/Build.md) for more information on how to build an
RPM package

## Project Integration

The best approach to using MSCL is integrating it into your project with the
pre-built packages following the integration [guide](guides/Integration.md)

## Building From Source

If the pre-built packages aren't available on your platform, or you prefer to
build MSCL from source yourself, you can do so with the build
[instructions](guides/Build.md)

## Documentation

MSCL has both [online](https://lord-microstrain.github.io/MSCL_documentation)
and [offline](../../releases/download/v68.0.0/MSCL-Documentation-v68.0.0.zip)
documentation.</br>
See the documentation build [instructions](docs/README.md) for information on
building the documentation from source.

## Examples

MSCL has an array of [examples](examples/README.md) for all supported languages

* Note: LabVIEW example code is provided in the
[LabVIEW-MSCL VI package](https://github.com/LORD-MicroStrain/LabVIEW-MSCL).

## Tests

MSCL has a suite of unit tests to ensure the library functions as expected.</br>
See the testing [instructions](tests/README.md) for more information on building
and running tests.

## License

MSCL is released under the MIT [license](LICENSE)

## Third-Party Notices

MSCL uses additional libraries as part of the project and has separate licensing

- [OpenSSL](License_OpenSSL.txt)
- [Boost](License_Boost.txt)
