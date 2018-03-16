----------------------------------------------------------------
                     MSCL Examples Readme
                Copyright 2017 LORD Corporation
----------------------------------------------------------------

Example projects are provided for some use cases for MSCL. This does not encompass all features of MSCL.
Please refer to the MSCL documentation for more details.

Open the "Inertial" directory to view example code for LORD's Inertial product line.
Open the "Wireless" directory to view example code for LORD's Wireless product line.

To compile and run the example code, you will need to copy the "C++", "DotNet", and "Python" directories, containing the actual MSCL libraries to the "dependencies" directory.
The directory structure for how the libraries should be placed is given inside the "dependencies" directory and is as follows:

----------------------------------------------------------------
                            C++
----------------------------------------------------------------
/dependencies/C++/include/mscl/*.h
/dependencies/C++/lib/x86/Debug/MSCL.lib 
/dependencies/C++/lib/x86/Release/MSCL.lib
/dependencies/C++/lib/x64/Debug/MSCL.lib 
/dependencies/C++/lib/x64/Release/MSCL.lib

Note: The C++ MSCL library depends on boost 1.64. You will need to perform the following steps:
      1. Download boost 1.64 from boost.org
      2. Install the Prebuilt windows binaries, or build boost from source
      3. Edit the MSCL_PropertySheet_Debug.props and MSCL_PropertySheet_Release.props files, or the property pages of each project
      4. Update the "Additional Include Directories" to include the path to: 
            [boostInstallDir]/boost
      5. Update the "Additional Library Directories" to include the path to:
            [boostInstallDir]/lib32_msvc-14.0
      6. Update the "Additional Dependencies" to include the following:
         Release:
            libboost_system-vc140-mt-s-1_64.lib
         Debug:
            libboost_system-vc140-mt-sgd-1_64.lib


----------------------------------------------------------------
                           .NET
----------------------------------------------------------------
/dependencies/DotNet/x64/MSCL.dll
/dependencies/DotNet/x64/MSCL_Managed.dll
/dependencies/DotNet/x86/MSCL.dll
/dependencies/DotNet/x86/MSCL_Managed.dll


----------------------------------------------------------------
                           Python
----------------------------------------------------------------
/dependencies/Python/mscl.py
/dependencies/Python/_mscl.pyd