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

REM ==========================================================================
REM PYTHON BUILD
REM ==========================================================================
echo ********************************
echo Building MSCL for Python... (bjam)
echo ********************************
echo.

SET msclCxxFlags="/I"C:/Python27/include" /I"C:/Dev/Lib/boost/boost_1_61_0""
IF NOT [%1]==[] SET msclCxxFlags=%1
IF [%1]==["none"] SET msclCxxFlags=" "

SET msclLinkFlags="/LIBPATH:"C:/Python27/libs" /LIBPATH:"C:/Dev/Lib/boost/boost_1_61_0/lib32-msvc-14.0" libboost_system-vc140-mt-s-1_61.lib"
IF NOT [%2]==[] SET msclLinkFlags=%2
IF [%2]==["none"] SET msclLinkFlags=" "

echo msclCxxFlags: %msclCxxFlags%
echo msclLinkFlags: %msclLinkFlags%

REM change to the directory of Jamroot
cd ..\

REM for now, bjam needs this folder to exist
echo Creating the build\swig-python directory
mkdir build\swig-python

REM build the python version of MSCL (have to do this twice to copy the .py output file (BUG))
echo Running BJAM (1)
REM linkflags=/SUBSYSTEM:WINDOWS",5.01"
bjam MSCL//stage_python runtime-link=static link=static release cxxflags=%msclCxxFlags% linkflags=%msclLinkFlags% address-model=32 -j4
echo Running BJAM (2)
bjam MSCL//stage_python runtime-link=static link=static release cxxflags=%msclCxxFlags% linkflags=%msclLinkFlags% address-model=32 -j4

REM rename _mscl.dll to _mscl.pyd 
echo Renaming _mscl.dll to _mscl.pyd
move /y Output\Python\_mscl.dll Output\Python\_mscl.pyd

REM delete the unnecessary _mscl.lib that is leftover in the Python output folder
echo Deleting extra _mscl.lib 
del Output\Python\_mscl.lib

cd /d %~dp0


REM ==========================================================================
REM Zip the Output
REM ==========================================================================
echo ********************************
echo Zipping the MSCL Output...
echo ********************************
echo.

REM zip all the output files for MSCL
call zipOutput_Python.cmd

echo DONE BUILDING MSCL (end build_Python.cmd)

:end