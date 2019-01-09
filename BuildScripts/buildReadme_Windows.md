# **Building MSCL for Windows**

## Hold up!
Most users will not need to build MSCL themselves!

A pre-built version is available for download. To get it, head over to the [MSCL Releases Page](https://github.com/LORD-MicroStrain/MSCL/releases), for the latest release. Under the `Downloads` section of that release, you will find the C++, Python, and .NET versions of MSCL, as well as Example Code and Documentation.

## I really want to build it myself
Ok, if you are making changes to MSCL's source code, or need to build MSCL from scratch for any other reason, here are the steps to build for Windows:

#### Dependencies

- \>= Visual Studio 2015 (msvc-14.0) or MSBuild equivalent
- \>= [Boost 1.68](http://www.boost.org/)
- \>= [OpenSSL 1.1.0](https://www.npcglib.org/~stathis/blog/precompiled-openssl/) (optional, see below)
- = [SWIG 3.0.6](http://swig.org/download.html) (for .NET and Python builds)
- \>= [Python 2.7 or 3.6](https://www.python.org/downloads/) (for Python build)
- [Boost.Build](http://www.boost.org/build/) (for Python build)

Create an environment variable, `LIB_PATH`, that points to a folder containing the following dependencies like so:
  - `%LIB_PATH%\boost\boost_1_68_0`
  - `%LIB_PATH%\openssl`
  - `%LIB_PATH%\swig\swigwin-3.0.6` (for .NET and Python builds)

OpenSSL and Beast are optional and are used for creating secure WebSocket connections to an ethernet connected WSDA from anywhere in the world. If this is a feature you do not want, you can avoid adding these extra dependencies by defining the following before compiling:
```cpp
#define MSCL_DISABLE_SSL            //removes OpenSSL dependency

#define MSCL_DISABLE_WEBSOCKETS     //removes Beast dependency
```

#### Installing Boost and Boost.Build

SourceForge hosts some [Pre-Built Boost binaries for Windows](https://sourceforge.net/projects/boost/files/boost-binaries/1.68.0/). Simply installing these for your specific compiler will make it so you do not need to build Boost yourself, which can be time consuming. 

If you want to install Boost yourself, you can follow the instructions on [Boost's Getting Started page](http://www.boost.org/doc/libs/1_68_0/more/getting_started/windows.html). 

Boost.Build is required for building MSCL for Python. Instructions on how to install it can be found [here](http://www.boost.org/build/doc/html/bbv2/installation.html). 

**Note**: Unfortunately, it seems there might be an issue in newer versions of bjam that come with Boost 1.61+ when using msvc ([see this Stack Overflow](http://stackoverflow.com/questions/29450634/compile-boost-python-tutorial-with-vs-2015-ctp-5-and-python-3-5a-on-windows-10-t)). From our internal build, it seems this fixes the issue:

1. Edit the file `D:\boost\boost_1_61_0\tools\build\src\tools\msvc.jam`
2. Change this (lines 1358-1363) from: 
``` 
     generators.register [ new msvc-linking-generator msvc.link.dll :
         OBJ SEARCHED_LIB STATIC_LIB IMPORT_LIB : SHARED_LIB IMPORT_LIB :
         <toolset>msvc <suppress-import-lib>false ] ;
     generators.register [ new msvc-linking-generator msvc.link.dll :
         OBJ SEARCHED_LIB STATIC_LIB IMPORT_LIB : SHARED_LIB :
         <toolset>msvc <suppress-import-lib>true ] ;
```
to this:
```
     generators.register [ new msvc-linking-generator msvc.link.dll :
        OBJ SEARCHED_LIB STATIC_LIB IMPORT_LIB : SHARED_LIB IMPORT_LIB :
        <toolset>msvc ] ;
```
3. Remove this (line 1479):
```
toolset.flags msvc.link.dll LINKFLAGS <suppress-import-lib>true : /NOENTRY ;
```


## Building MSCL for C++

Run the following from the top level MSCL source directory:

```
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" "BuildScripts/msbuildConfig_CPP_NoTests.xml" /p:VisualStudioVersion=14.0
```

Output: 
```
x64
  Debug
    MSCL.lib
    MSCL.pdb
  Release
    MSCL.lib
    MSCL.pdb
x86
  Debug
    MSCL.lib
    MSCL.pdb
  Release
    MSCL.lib
    MSCL.pdb
```

Note: The default C++ build does not link in dependencies (such as Boost) directly. You will need to link the dependencies in when using MSCL.lib in your project.

## Building MSCL for .NET

Building the .NET library involves 3 steps:

1. use SWIG to generate/update the `MSCL_Wrap.cpp` file and create the C# source files
2. build the `MSCL` C++ project to generate a DLL
3. build the `MSCL_Managed` C# project to generate the managed DLL

These are all handled for you by running the following from the top level MSCL source directory:

```
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild" "BuildScripts/msbuildConfig_DotNet.xml" /p:VisualStudioVersion=14.0
```

Output: 
```
x64
  Release
    MSCL.dll
    MSCL_Managed.dll
x86
  Release
    MSCL.dll
    MSCL_Managed.dll
```

Note: The default .NET build statically links in all dependencies. In your project that uses MSCL, you can simply link in MSCL, and it's dependencies (such as Boost) will already be included.

## Building MSCL for Python

Building the Python library involves using Boost.Build framework, using the `bjam` or `b2` command, and utilizing the provided Jamfiles.

Configure bjam by creating a [site-config.jam or user-config.jam file](https://boostorg.github.io/build/manual/develop/index.html#bbv2.overview.configuration) in your Home path or Boost Build Path. The contents of the file should look similar to this:
```
using msvc
:
:
: <cxxflags>/D"WIN32"
  <cxxflags>/D"_WINDOWS"
  <cxxflags>/D"_USRDLL"
  <cxxflags>/D"NOMINMAX"
  <cxxflags>/D"_WIN32_WINNT=0x0501"
  <cxxflags>/D"_USING_V110_SDK71_"
  <cxxflags>/D"_UNICODE"
  <cxxflags>/D"UNICODE"
;
```

Edit the include (/I) and library (/LIBPATH) paths in the following command, and then run from the top level MSCL source directory.

For 32-bit Python:
```
"BuildScripts\build_Python_x86.cmd" "/bigobj /I"E:/Python27/include" /I"E:/Lib/boost/boost_1_68_0" /I"E:/Lib/openssl/include"" "/LIBPATH:"E:/Python27/libs" /LIBPATH:"E:/Lib/boost/boost_1_68_0/lib32-msvc-14.0" /LIBPATH:"E:/Lib/openssl/lib" libboost_system-vc140-mt-s-x32-1_68.lib libsslMT.lib libcryptoMT.lib crypt32.lib ws2_32.lib gdi32.lib advapi32.lib user32.lib"
```

For 64-bit Python:
```
"BuildScripts\build_Python_x64.cmd" "/bigobj /I"E:/Python27_64/include" /I"E:/Lib/boost/boost_1_68_0" /I"E:/Lib/openssl/include64"" "/LIBPATH:"E:/Python27_64/libs" /LIBPATH:"E:/Lib/boost/boost_1_68_0/lib64-msvc-14.0" /LIBPATH:"E:/Lib/openssl/lib64" libboost_system-vc140-mt-s-x64-1_68.lib libsslMT.lib libcryptoMT.lib crypt32.lib ws2_32.lib gdi32.lib advapi32.lib user32.lib"
```

Output: 
```
x64
  mscl.py
  _mscl.pyd
x86
  mscl.py
  _mscl.pyd
```

Note: The default Python build statically links in all dependencies. In your project that uses MSCL, you can simply link in MSCL, and it's dependencies (such as Boost) will already be included.