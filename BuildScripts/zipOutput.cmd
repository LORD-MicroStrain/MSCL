@echo off

REM Paths to copy all of the output files to
SET CPP_HEADERS_OUTPUT_DIR="..\Output\MSCL\C++\include"
SET CPP_LIBS_OUTPUT_DIR="..\Output\MSCL\C++\lib"
SET DOTNET_OUTPUT_DIR="..\Output\MSCL\DotNet\x86"
SET DOTNET64_OUTPUT_DIR="..\Output\MSCL\DotNet\x64"
SET PYTHON_OUTPUT_DIR="..\Output\MSCL\Python"
SET DOCS_OUTPUT_DIR="..\Output\MSCL\Documentation\MSCL Documentation"
SET API_DOCS_OUTPUT_DIR="..\Output\MSCL\Documentation\MSCL API Documentation"
SET GS_OUTPUT_DIR="..\Output\MSCL\Documentation\Getting Started"
SET EX_OUTPUT_DIR="..\Output\MSCL\Examples\"

REM Paths to the folders that need to be zipped up
SET CPP_TO_ZIP="..\Output\MSCL\C++"
SET DOTNET_TO_ZIP="..\Output\MSCL\DotNet"
SET PYTHON_TO_ZIP="..\Output\MSCL\Python"
SET DOCS_TO_ZIP="..\Output\MSCL\Documentation"
SET EX_TO_ZIP="..\Output\MSCL\Examples"
SET DIR_TO_ZIP="..\Output\MSCL"

REM Paths/FileNames of the resulting zip files
SET CPP_ZIP_OUT="..\Output\C++.zip"
SET DOTNET_ZIP_OUT="..\Output\DotNet.zip"
SET PYTHON_ZIP_OUT="..\Output\Python.zip"
SET DOCS_ZIP_OUT="..\Output\Documentation.zip"
SET EX_ZIP_OUT="..\Output\Examples.zip"
SET OUTPUT_ZIP="..\Output\MSCL.zip"

REM set the current directory to this file's directory
cd /d %~dp0

echo ========================================================
echo (zipOutput.cmd) START - ZIP ALL OF THE MSCL OUTPUT
echo.

REM copy all the Public C++ header files
echo (zipOutput.cmd) Copying public header files
python copyPublicHeaders.py "..\MSCL\source" %CPP_HEADERS_OUTPUT_DIR%

REM copy the output/result files into a single directory structure 
echo (zipOutput.cmd) Copying files
xcopy "..\Output\C++\*.lib" %CPP_LIBS_OUTPUT_DIR% /i /s
xcopy "..\Output\C++\*.pdb" %CPP_LIBS_OUTPUT_DIR% /i /s
xcopy "..\Output\DotNet\x86\*.dll" %DOTNET_OUTPUT_DIR% /i /s
xcopy "..\Output\DotNet\x64\*.dll" %DOTNET64_OUTPUT_DIR% /i /s
xcopy "..\Output\Python\*.*" %PYTHON_OUTPUT_DIR% /i /s
xcopy "..\Output\Documentation\MSCL_Docs\*.*" %DOCS_OUTPUT_DIR% /i /s
xcopy "..\Output\Documentation\MSCL_API_Docs\*.*" %API_DOCS_OUTPUT_DIR% /i /s
xcopy "..\GettingStartedGuide\build\*.*" %GS_OUTPUT_DIR% /i /s
xcopy "..\MSCL_Examples\readme.txt" %EX_OUTPUT_DIR% /i /s
xcopy "..\MSCL_Examples\*.sln" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s
xcopy "..\MSCL_Examples\*.props" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s
xcopy "..\MSCL_Examples\*.cpp" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s
xcopy "..\MSCL_Examples\*.h" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s
xcopy "..\MSCL_Examples\*.vcxproj" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s
xcopy "..\MSCL_Examples\*.cs" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s
xcopy "..\MSCL_Examples\*.csproj" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s
xcopy "..\MSCL_Examples\*.py" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s
xcopy "..\MSCL_Examples\*.vi" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s

REM copy the MSCL_Examples dependencies folder
echo (zipOutput.cmd) Copying example dependencies folder
xcopy "..\MSCL_Examples\dependencies" %EX_OUTPUT_DIR%\dependencies /i /T /E

REM remove old .zip files if they already exist
echo (zipOutput.cmd) Deleting zip files if they already exist
del %CPP_ZIP_OUT%
del %DOTNET_ZIP_OUT%
del %PYTHON_ZIP_OUT%
del %DOCS_ZIP_OUT%
del %EX_ZIP_OUT%
del %OUTPUT_ZIP%

REM zip the output that we just created
echo (zipOutput.cmd) Zipping Output files
7z a %OUTPUT_ZIP% %DIR_TO_ZIP% 
7z a %CPP_ZIP_OUT% %CPP_TO_ZIP%
7z a %DOTNET_ZIP_OUT% %DOTNET_TO_ZIP% 
7z a %PYTHON_ZIP_OUT% %PYTHON_TO_ZIP% 
7z a %DOCS_ZIP_OUT% %DOCS_TO_ZIP% 
7z a %EX_ZIP_OUT% %EX_TO_ZIP%

REM remove the temporary directory that we created, since it is now zipped
echo (zipOutput.cmd) Removing temp directory that was zipped
rmdir %DIR_TO_ZIP% /S /Q

echo.
echo (zipOutput.cmd) DONE
echo ========================================================