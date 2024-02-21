# MSCL Examples Readme

Example projects are provided for some MSCL use cases. This does not encompass all features of MSCL.
Please refer to the [MSCL documentation](https://lord-microstrain.github.io/MSCL/Documentation/MSCL%20API%20Documentation/index.html) for more details.

Open the **Wireless** directory to view example code for LORD's Wireless product line.
Open the **Inertial** directory to view example code for LORD's Inertial product line.
Open the **Displacement** directory to view example code for LORD's Inertial product line.

To compile and run the example code, you will need to copy the **C++**, **DotNet**, or **Python** libraries for MSCL to a **dependencies** directory (preferably within the project directory).\
If not building for multiple configurations, the architecture and build type can be omitted from the folder structure.\
The structure for how the libraries should be placed inside the **dependencies** directory is as follows:

## C++
```
/dependencies/MSCL/include/mscl/*.h
/dependencies/MSCL/lib/[arch]/[buildType]/MSCL.lib
```

Note: The C++ MSCL library depends on the following libraries:
- Boost 1.68
- OpenSSL

You will need to perform the following steps:
1. Download and build [Boost 1.68](https://www.boost.org/) ([precompiled versions available](https://sourceforge.net/projects/boost/files/boost-binaries/))
2. Download and build [OpenSSL](https://www.openssl.org/) ([precompiled versions available](https://www.npcglib.org/~stathis/blog/precompiled-openssl/)).
3. In the project properties, update the paths/names of the following to point to the files on your machine:
    - Additional Include Directories
        - ```[boostInstallDir]```
    - Additional Library Directories
        - **64-bit:**
            - ```[boostInstallDir]/lib64_msvc-14.0```
            - ```[opensslInstallDir]/lib64```
        - **32-bit:**
            - ```[boostInstallDir]/lib32_msvc-14.0```
            - ```[opensslInstallDir]/lib```
    - Additional Dependencies
        - **64-bit:**
            - **Release:** 
             - ```libboost_system-vc140-mt-s-x64-1_68.lib```
                - ```libsslMTd.lib```
                - ```libcryptoMTd.lib```
                - ```crypt32.lib```
            - **Debug:** 
             - ```libboost_system-vc140-mt-sgd-x64-1_68.lib```
                - ```libsslMT.lib```
                - ```libcryptoMT.lib```
                - ```crypt32.lib```
        - **32-bit:**
            - **Release:** 
             - ```libboost_system-vc140-mt-s-x32-1_68.lib```
                - ```libsslMTd.lib```
                - ```libcryptoMTd.lib```
                - ```crypt32.lib```
            - **Debug:** 
             - ```libboost_system-vc140-mt-sgd-x32-1_68.lib```
                - ```libsslMT.lib```
                - ```libcryptoMT.lib```
                - ```crypt32.lib```

## .NET

```
/dependencies/DotNet/[arch]/[buildType]/MSCL.dll
/dependencies/DotNet/[arch]/[buildType]/MSCL_Managed.dll
```

## Python
```
/dependencies/Python/[pythonVersion]/[arch]/[buildType]/mscl.py
/dependencies/Python/[pythonVersion]/[arch]/[buildType]/_mscl.pyd
```
