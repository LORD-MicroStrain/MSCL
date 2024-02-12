# MSCL Examples Readme

Example projects are provided for some MSCL use cases. This does not encompass all features of MSCL.
Please refer to the MSCL documentation for more details.

Open the **Wireless** directory to view example code for MicroStrain's Wireless product line.
Open the **Inertial** directory to view example code for MicroStrain's Inertial product line.
Open the **Displacement** directory to view example code for MicroStrain's Inertial product line.

To compile and run the example code, you will need to copy the **C++**, **DotNet**, and **Python** directories, containing the actual MSCL libraries to the **dependencies** directory. The directory structure for how the libraries should be placed is given inside the **dependencies** directory and is as follows:

## C++
```
/dependencies/C++/include/mscl/*.h
/dependencies/C++/lib/x86/Debug/MSCL.lib 
/dependencies/C++/lib/x86/Release/MSCL.lib
/dependencies/C++/lib/x64/Debug/MSCL.lib 
/dependencies/C++/lib/x64/Release/MSCL.lib
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
/dependencies/DotNet/x64/MSCL.dll
/dependencies/DotNet/x64/MSCL_Managed.dll
/dependencies/DotNet/x86/MSCL.dll
/dependencies/DotNet/x86/MSCL_Managed.dll
```

## Python
```
/dependencies/Python/mscl.py
/dependencies/Python/_mscl.pyd
```
