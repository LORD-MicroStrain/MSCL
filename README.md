# MSCL - The MicroStrain Communication Library

MSCL is developed by [LORD Sensing - Microstrain](http://microstrain.com) in Williston, VT. It was created to make it simple to interact with our [Wireless](http://www.microstrain.com/wireless), [Inertial](http://www.microstrain.com/inertial), and digital [Displacement](https://www.microstrain.com/displacement/nodes) sensors.

[![Latest](https://img.shields.io/github/v/release/LORD-MicroStrain/MSCL?color=bright&label=Latest%20Release)](https://github.com/LORD-MicroStrain/MSCL/releases/latest/)

#### Downloads

[Offline Documentation](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/mscl_65.0.0_Documentation.zip) | 
[Offline Example Code](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/mscl_65.0.0_Examples.zip)

##### Pre-built MSCL Binaries/Packages

Windows:
[C++](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/mscl_65.0.0_Windows_C++.zip) | 
[Python 2.7](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/mscl_65.0.0_Windows_Python2.7.zip) |
[Python 3.6](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/mscl_65.0.0_Windows_Python3.6.zip) |
[Python 3.11](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/mscl_65.0.0_Windows_Python3.11.zip) |
[.NET](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/mscl_65.0.0_Windows_DotNet.zip)

Debian:
  * x64:
  [C++](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/c++-mscl_65.0.0_amd64.deb) |
  [Python 2](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python2-mscl_65.0.0_amd64.deb) |
  [Python 3](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python3-mscl_65.0.0_amd64.deb)
  * arm64:
  [C++](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/c++-mscl_65.0.0_arm64.deb) |
  [Python 2](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python2-mscl_65.0.0_arm64.deb) |
  [Python 3](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python3-mscl_65.0.0_arm64.deb)
  * armhf (Raspbian):
  [C++](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/c++-mscl_65.0.0_armhf.deb) |
  [Python 2](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python2-mscl_65.0.0_armhf.deb) |
  [Python 3](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python3-mscl_65.0.0_armhf.deb)

RPM:
  * x64:
  [C++](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/c++-mscl-65.0.0_x86_64.rpm) |
  [Python 2](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python2-mscl-65.0.0_x86_64.rpm) |
  [Python 3](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python3-mscl-65.0.0_x86_64.rpm)
  * arm64:
  [C++](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/c++-mscl-65.0.0_aarch64.rpm) |
  [Python 2](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python2-mscl-65.0.0_aarch64.rpm) |
  [Python 3](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python3-mscl-65.0.0_aarch64.rpm)
  * CentOS:
  [C++](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/c++-mscl-65.0.0_x86_64_centos7.6.1810.rpm) |
  [Python 2](https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/python2-mscl-65.0.0_x86_64_centos7.6.1810.rpm)

---

If the pre-built packages aren't available on your platform, you can build MSCL from source.

Instructions can be found here:
[Building MSCL on Windows](https://github.com/LORD-MicroStrain/MSCL/blob/master/BuildScripts/buildReadme_Windows.md) | 
[Building MSCL on Linux](https://github.com/LORD-MicroStrain/MSCL/blob/master/BuildScripts/buildReadme_Linux.md)

---

### Documentation

[How to use MSCL](https://github.com/LORD-MicroStrain/MSCL/blob/master/HowToUseMSCL.md)

[Quick Start Guide](http://lord-microstrain.github.io/MSCL/Documentation/Getting%20Started/index.html)

[Public Documentation](http://lord-microstrain.github.io/MSCL/Documentation/MSCL%20API%20Documentation/index.html) - Documentation for all the public functionality of MSCL.

[Full Documentation](http://lord-microstrain.github.io/MSCL/Documentation/MSCL%20Documentation/index.html) - Full Documentation of everything in MSCL (useful when editing the source).

[Example Code](https://github.com/LORD-MicroStrain/MSCL/tree/master/MSCL_Examples)
  * Note: LabVIEW example code is provided in the [LabVIEW-MSCL VI package](https://github.com/LORD-MicroStrain/LabVIEW-MSCL).
  
[FAQs](https://github.com/LORD-MicroStrain/MSCL/blob/master/FAQs.md)

#### Included Libraries

OpenSSL - This product includes software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org/) - see the `License_OpenSSL.txt` file in the source distribution.

Boost - see the `License_Boost.txt` file in the source distribution.

#### License
MSCL is released under the MIT License - see the `LICENSE` file in the source distribution.

Copyright (C) 2015-2022 Parker Hannifin Corp. All Rights Reserved.