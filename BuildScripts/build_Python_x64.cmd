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
echo Building MSCL for Python x64... (bjam)
echo ********************************
echo.

SET pythonDir=C:/Python27
IF NOT [%1]==[] SET pythonDir=%1
IF [%1]==["none"] SET pythonDir=" "
SET pythonDir=%pythonDir:"=%

SET extraMsclCxxFlags=""
IF NOT [%2]==[] SET extraMsclCxxFlags=%2

SET extraMsclLinkFlags=""
IF NOT [%3]==[] SET extraMsclLinkFlags=%3

SET msclCxxFlags="%extraMsclCxxFlags:"=% /bigobj /I"%pythonDir%/include" /I"%LIB_PATH%/boost/boost_1_68_0" /I"%LIB_PATH%/openssl/include64""
SET msclLinkFlags="%extraMsclLinkFlags:"=% /LIBPATH:"%pythonDir%/libs" /LIBPATH:"%LIB_PATH%/boost/boost_1_68_0/lib64-msvc-14.0" /LIBPATH:"%LIB_PATH%/openssl/lib64" libsslMT.lib libcryptoMT.lib crypt32.lib Advapi32.lib"

echo pythonDir: %pythonDir%
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
bjam MSCL//stage_python_x64 release -j %NUMBER_OF_PROCESSORS% ^
    runtime-link=static ^
    link=shared ^
    toolset=msvc-14.0 ^
    address-model=64 ^
    cxxflags=%msclCxxFlags% ^
    linkflags=%msclLinkFlags%
echo Running BJAM (2)
bjam MSCL//stage_python_x64 release -j %NUMBER_OF_PROCESSORS% ^
    runtime-link=static ^
    link=shared ^
    toolset=msvc-14.0 ^
    address-model=64 ^
    cxxflags=%msclCxxFlags% ^
    linkflags=%msclLinkFlags%

REM rename _mscl.dll to _mscl.pyd 
echo Renaming _mscl.dll to _mscl.pyd
move /y Output\Python\x64\_mscl.dll Output\Python\x64\_mscl.pyd

REM delete the unnecessary _mscl.lib that is leftover in the Python output folder
echo Deleting extra _mscl.lib 
del Output\Python\x64\_mscl.lib

cd /d %~dp0

echo DONE BUILDING MSCL (end build_Python_x64.cmd)

:end