@echo off

:BUILD

echo.
echo ********************************
echo Starting MSCL Build...
echo ********************************
echo.

REM change the directory to this file's directory
cd /d %~dp0

set ISHUDSONBUILD=True

REM build the C++ and .NET versions of MSCL
echo ********************************
echo Building MSCL for C++ and .NET...
echo ********************************
echo.
echo Running msbuild with msbuildConfig.xml
"%MSBUILD_14%\msbuild" "msbuildConfig.xml" /p:VisualStudioVersion=14.0 | find /v "warning MSB4098:" | find /v "warning D9025:"



REM ==========================================================================
REM PYTHON BUILD
REM ==========================================================================
echo ********************************
echo Building MSCL for Python... (bjam)
echo ********************************
echo.

REM change to the directory of Jamroot
cd ..\

REM for now, bjam needs this folder to exist
echo Creating the build\swig-python directory
mkdir build\swig-python

REM build the python version of MSCL (have to do this twice to copy the .py output file (BUG))
echo Running BJAM (1)
bjam MSCL//stage_python runtime-link=static link=static release linkflags=/SUBSYSTEM:WINDOWS",5.01"
echo Running BJAM (2)
bjam MSCL//stage_python runtime-link=static link=static release linkflags=/SUBSYSTEM:WINDOWS",5.01"

REM rename _mscl.dll to _mscl.pyd 
echo Renaming _mscl.dll to _mscl.pyd
move /y Output\Python\_mscl.dll Output\Python\_mscl.pyd

REM delete the unnecessary _mscl.lib that is leftover in the Python output folder
echo Deleting extra _mscl.lib 
del Output\Python\_mscl.lib


REM ==========================================================================
REM BUILD DOCUMENTATION
REM ==========================================================================
echo ********************************
echo Building MSCL Documentation...
echo ********************************
echo.

REM change the directory to this file's directory
cd /d %~dp0

REM create the MSCL documentation
call buildDocs.cmd


REM ==========================================================================
REM Zip the Output
REM ==========================================================================
echo ********************************
echo Zipping the MSCL Output...
echo ********************************
echo.

REM zip all the output files for MSCL
call zipOutput.cmd

echo DONE BUILDING MSCL (end buildAll.cmd)

:end