# MSCL - The MicroStrain Communication Library

MSCL is developed by [MicroStrain](https://www.hbkworld.com/en/Campaign/microstrain-by-hbk) in Williston, VT. It was created to make it simple to interact with our
[Wireless](https://www.hbkworld.com/en/products/instruments/wireless-daq-systems), and [Inertial](https://www.hbkworld.com/en/products/transducers/inertial-sensors) sensors.

[![GitHub tag status](https://img.shields.io/github/checks-status/LORD-MicroStrain/MSCL/v68.0.0?label=v68.0.0)](https://github.com/LORD-MicroStrain/MSCL/releases/v68.0.0/) &nbsp;
[![GitHub tag status](https://img.shields.io/github/checks-status/LORD-MicroStrain/MSCL/latest?label=latest)](https://github.com/LORD-MicroStrain/MSCL/releases/latest/)

### Support/Issues

If you have any questions or run into any issues, please let us know! [MicroStrain Support Portal](https://support.microstrain.com)

Also have a look at our [FAQs](FAQs.md) for common issues.

### Inertial Successor API

For projects using our inertial product lines check out our new lightweight C/C++ API, [MIP SDK](https://github.com/LORD-MicroStrain/mip_sdk)

---

## Downloads
Release notes and all downloadable assets can be found on our [releases page](https://github.com/LORD-MicroStrain/MSCL/releases) or from the
links below.

[Offline Documentation](https://github.com/LORD-MicroStrain/MSCL/releases/download/v68.0.0/MSCL-Documentation-v68.0.0.zip)</br>
[Offline Example Code](https://github.com/LORD-MicroStrain/MSCL/releases/download/v68.0.0/MSCL-Examples-v68.0.0.zip)

Please see our [releases](https://github.com/LORD-MicroStrain/MSCL/releases) page for all of our release notes and packages.</br>
Packages for the current release, <b>v68.0.0</b>, can be found [here](https://github.com/LORD-MicroStrain/MSCL/releases/tag/v68.0.0)</br>
Latest pre-release packages can be found [here](https://github.com/LORD-MicroStrain/MSCL/releases/tag/latest)</br>

## Supported Pre-Built Binaries/Packages

### Windows:

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
    <td rowspan="3"> Python </td>
    <td> Python 3.10 x64 </td>
    <td> Python 3.10 x86 </td>
  </tr>
  <tr align="center">
    <td> Python 3.11 x64 </td>
    <td> Python 3.11 x86 </td>
  </tr>
  <tr align="center">
    <td> Python 3.12 x64 </td>
    <td> Python 3.12 x86 </td>
  </tr>
  <tr align="center">
    <td> .NET </td>
    <td> .NET x64 </td>
    <td> .NET x86 </td>
  </tr>
</table>

### Debian:

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
    <td rowspan="3"> Python </td>
    <td> Python 3.10 x64 </td>
    <td> Python 3.10 arm64 </td>
    <td> Python 3.10 armhf </td>
  </tr>
  <tr align="center">
    <td> Python 3.11 x64 </td>
    <td> Python 3.11 arm64 </td>
    <td> Python 3.11 armhf </td>
  </tr>
  <tr align="center">
    <td> Python 3.12 x64 </td>
    <td> Python 3.12 arm64 </td>
    <td> Python 3.12 armhf </td>
  </tr>
</table>

### RPM:

We are no longer providing pre-built RPM downloads. If you wish to continue using MSCL on RPM systems please see the instructions listed below to build
from source.

### Building From Source:

If the pre-built packages aren't available on your platform, you can build MSCL from source.

Instructions can be found here:</br>
[Building MSCL on Windows](scripts/buildReadme_Windows.md)</br>
[Building MSCL on Linux](scripts/buildReadme_Linux.md)

---

### Documentation

MSCL documentation can now be found [here](https://github.com/LORD-MicroStrain/MSCL_documentation)

[Example Code](examples)

* Note: LabVIEW example code is provided in the [LabVIEW-MSCL VI package](https://github.com/LORD-MicroStrain/LabVIEW-MSCL).

#### Included Libraries

OpenSSL - This product includes software developed by the [OpenSSL Project](https://www.openssl.org/) for use in the OpenSSL Toolkit - see the
[License_OpenSSL.txt](License_OpenSSL.txt) file in the source distribution.

Boost - see the [License_Boost.txt](License_Boost.txt) file in the source distribution.

#### License

MSCL is released under the MIT License - see the [LICENSE](LICENSE) file in the source distribution.

Copyright (c) 2015-2026 MicroStrain by HBK. All Rights Reserved.
