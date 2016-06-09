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

REM build the C++ version of MSCL
echo ********************************
echo Building MSCL for C++
echo ********************************
echo.
echo Running msbuild with msbuildConfig_CPP.xml
msbuild "msbuildConfig_CPP.xml" /p:VisualStudioVersion=12.0 | find /v "warning MSB4098:" | find /v "warning D9025:"


REM ==========================================================================
REM Zip the Output
REM ==========================================================================
echo ********************************
echo Zipping the MSCL Output...
echo ********************************
echo.

REM zip all the output files for MSCL
call zipOutput_CPP.cmd

echo DONE BUILDING MSCL (end build_CPP.cmd)

:end