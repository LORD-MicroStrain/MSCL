# MSCL - The MicroStrain Communication Library

MSCL is developed by [MicroStrain](https://www.hbkworld.com/en/Campaign/microstrain-by-hbk) in Williston, VT. Its purpose is to
serve as a simple user-friendly API to interact with our [Wireless](https://www.hbkworld.com/en/products/instruments/wireless-daq-systems), and
[Inertial](https://www.hbkworld.com/en/products/transducers/inertial-sensors) sensors.

[![GitHub tag status](https://img.shields.io/github/checks-status/LORD-MicroStrain/MSCL/v68.0.0?label=v68.0.0)](https://github.com/LORD-MicroStrain/MSCL/releases/v68.0.0/) &nbsp;
[![GitHub tag status](https://img.shields.io/github/checks-status/LORD-MicroStrain/MSCL/latest?label=latest)](https://github.com/LORD-MicroStrain/MSCL/releases/latest/)

### Support/Issues

If you have any questions or run into any issues, please let us know!
[MicroStrain Support Portal](https://support.microstrain.com)

Also, have a look at our [FAQs](guides/FAQ.md) for common issues.

### Inertial Successor API

For projects using our inertial product lines check out our new lightweight
C/C++ API, [MIP SDK](https://github.com/LORD-MicroStrain/mip_sdk)

## Downloads

Please see our [releases](../../releases) page for all of our release notes and packages.</br>
Packages for the current release, <b>v68.0.0</b>, can be found [here](../../releases/tag/v68.0.0)</br>
Latest pre-release packages can be found [here](../../releases/tag/latest)</br>

## Supported Pre-Built Binaries/Packages

#### Windows

<table>
  <colgroup/>
  <colgroup/>
  <colgroup/>
  <tr>
    <th> Language </th>
    <th> x64 </th>
    <th> x86 </th>
  </tr>
  <tr align="center">
    <td rowspan="2"> C++ </td>
    <td> C++ Shared (.dll) x64 </td>
    <td> C++ Shared (.dll) x86 </td>
  </tr>
  <tr align="center">
    <td> C++ Static (.lib) x64 </td>
    <td> C++ Static (.lib) x86 </td>
  </tr>
  <tr align="center">
    <td> Python </td>
    <td> Python 3.12 x64 </td>
    <td> Python 3.12 x86 </td>
  </tr>
  <tr align="center">
    <td> .NET </td>
    <td> .NET x64 </td>
    <td> .NET x86 </td>
  </tr>
</table>

#### Debian

<table>
  <colgroup/>
  <colgroup/>
  <colgroup/>
  <colgroup/>
  <tr>
    <th> Language </th>
    <th> x64 </th>
    <th> arm64 </th>
    <th> armhf </th>
  </tr>
  <tr align="center">
    <td rowspan="2"> C++ </td>
    <td> C++ Shared (.so) x64 </td>
    <td> C++ Shared (.so) arm64 </td>
    <td> C++ Shared (.so) armhf </td>
  </tr>
  <tr align="center">
    <td> C++ Static (.a) x64 </td>
    <td> C++ Static (.a) arm64 </td>
    <td> C++ Static (.a) armhf </td>
  </tr>
  <tr align="center">
    <td> Python </td>
    <td> Python 3.12 x64 </td>
    <td> Python 3.12 arm64 </td>
    <td> Python 3.12 armhf </td>
  </tr>
</table>

#### RPM

We are no longer providing pre-built RPM downloads.</br>
If you wish to continue using MSCL on RPM systems, please see
[Building From Source](#building-from-source) below for more information

## Bindings

MSCL provides bindings for both .NET and Python

#### Python

MSCL provides bindings for the latest supported version of Python in vcpkg at
the time of release. If you need a different version of Python, please see the
build [instructions](guides/Build.md) for more information on how to build Python bindings

## Project Integration

The best approach to using MSCL is integrating it into your project with the
pre-built packages following the integration [guide](guides/Integration.md)

## Building From Source

If the pre-built packages aren't available on your platform, or you prefer to
build MSCL from source yourself, you can do so with the build [instructions](guides/Build.md)

## Documentation

MSCL has both [online](https://lord-microstrain.github.io/MSCL_documentation) and [offline](../../releases/download/v68.0.0/MSCL-Documentation-v68.0.0.zip) documentation

## Examples

MSCL has an array of [examples](examples) for all supported languages

* Note: LabVIEW example code is provided in the [LabVIEW-MSCL VI package](https://github.com/LORD-MicroStrain/LabVIEW-MSCL).

## Tests

MSCL has a suite of unit [tests](tests) to ensure the library functions as expected

## License

MSCL is released under the MIT [license](LICENSE)

## Third-Party Notices

MSCL uses additional libraries as part of the project and has separate licensing

- [OpenSSL](License_OpenSSL.txt)
- [Boost](License_Boost.txt)
