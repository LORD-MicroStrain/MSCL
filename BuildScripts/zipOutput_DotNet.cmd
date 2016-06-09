@echo off

REM Paths to copy all of the output files to
SET DOTNET_OUTPUT_DIR="..\Output\MSCL\DotNet\x86"
SET DOTNET64_OUTPUT_DIR="..\Output\MSCL\DotNet\x64"

REM Paths to the folders that need to be zipped up
SET DOTNET_TO_ZIP="..\Output\MSCL\DotNet"
SET DIR_TO_ZIP="..\Output\MSCL"

REM Paths/FileNames of the resulting zip files
SET DOTNET_ZIP_OUT="..\Output\DotNet.zip"
SET OUTPUT_ZIP="..\Output\MSCL.zip"

REM set the current directory to this file's directory
cd /d %~dp0

echo ========================================================
echo (zipOutput_DotNet.cmd) START - ZIP THE MSCL DOTNET OUTPUT
echo.

REM copy the output/result files into a single directory structure 
echo (zipOutput_DotNet.cmd) Copying files
xcopy "..\Output\DotNet\x86\*.dll" %DOTNET_OUTPUT_DIR% /i /s
xcopy "..\Output\DotNet\x64\*.dll" %DOTNET64_OUTPUT_DIR% /i /s

REM remove old .zip files if they already exist
echo (zipOutput_DotNet.cmd) Deleting zip files if they already exist
del %DOTNET_ZIP_OUT%
del %OUTPUT_ZIP%

REM zip the output that we just created
echo (zipOutput_DotNet.cmd) Zipping Output files
7z a %OUTPUT_ZIP% %DIR_TO_ZIP% 
7z a %DOTNET_ZIP_OUT% %DOTNET_TO_ZIP% 

REM remove the temporary directory that we created, since it is now zipped
echo (zipOutput_DotNet.cmd) Removing temp directory that was zipped
rmdir %DIR_TO_ZIP% /S /Q

echo.
echo (zipOutput_DotNet.cmd) DONE
echo ========================================================