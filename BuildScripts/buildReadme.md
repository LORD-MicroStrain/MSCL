# **MSCL build info**

The following information describes how to build MSCL for various platforms and programming languages.



## **Windows**

### Dependencies

- Visual Studio 2015 (msvc-14.0)
- [Boost 1.61](http://www.boost.org/users/history/version_1_61_0.html) (prebuilt can be downloaded [here](https://sourceforge.net/projects/boost/files/boost-binaries/1.61.0/))
- [SWIG 3.0.6](http://swig.org/) (.NET, Python only)
- [Turtle 1.2.6](http://turtle.sourceforge.net/) (Unit Tests only)
- [Boost.Build](http://www.boost.org/build/) (Python only)
- [Python 2.7](https://www.python.org/download/releases/2.7.6/) (Python only)
- Create an environment variable, `LIB_PATH`, that points to a folder containing the above libraries.

Use the master build script to build everything (C++, .NET, Python, Unit Tests, and Documentation):
```
BuildScripts/buildAll.cmd
```

### C++

**Static Lib (.lib) - (x86, Debug/Release):** 

```bat
msbuild "BuildScripts/msbuildConfig_CPP.xml" /p:VisualStudioVersion=14.0
```

or

- open the Visual Studio `MSCL_Dev.sln` solution
- build the `MSCL` project using the `Debug (C++)` and `Release (C++)` configurations

### .NET

Building the .NET library involves 3 steps:

1. use SWIG to generate/update the `MSCL_Wrap.cpp` file and create the C# source files
2. build the `MSCL` C++ project to generate a DLL
3. build the `MSCL_Managed` C# project to generate the managed DLL

**Dynamic Library (.dll) - (x86/x64, Debug/Release):**

```
msbuild "BuildScripts/msbuildConfig_DotNet.xml" /p:VisualStudioVersion=14.0
```

or

- open the Visual Studio `MSCL_Dev.sln` solution
- build the `MSCL` project using the `Debug (.NET)` and `Release (.NET)` configurations
- the previous step has a pre-build command to automatically run the SWIG command
- take the generated C# files (located in `MSCL_Managed/mscl`) and add them to the `MSCL_Managed` project in Visual Studio
- build the `MSCL_Managed` project using the `Debug (.NET)` and `Release (.NET)` configurations

### Python

Building the Python library involves using Boost.Build framework, using the `bjam` or `b2` command, and utilizing the provided Jamfiles.

**Python File (.py)**

```
mkdir build\swig-python

bjam MSCL//stage_python runtime-link=static link=static release linkflags=/SUBSYSTEM:WINDOWS",5.01"

bjam MSCL//stage_python runtime-link=static link=static release linkflags=/SUBSYSTEM:WINDOWS",5.01"

move /y Output\Python\_mscl.dll Output\Python\_mscl.pyd

del Output\Python\_mscl.lib
```
