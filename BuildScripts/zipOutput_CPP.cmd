@echo off

REM Paths to copy all of the output files to
SET CPP_HEADERS_OUTPUT_DIR="..\Output\MSCL\C++\include"
SET CPP_LIBS_OUTPUT_DIR="..\Output\MSCL\C++\lib"

REM Paths to the folders that need to be zipped up
SET CPP_TO_ZIP="..\Output\MSCL\C++"
SET DIR_TO_ZIP="..\Output\MSCL"

REM Paths/FileNames of the resulting zip files
SET CPP_ZIP_OUT="..\Output\C++.zip"
SET OUTPUT_ZIP="..\Output\MSCL.zip"

REM set the current directory to this file's directory
cd /d %~dp0

echo ========================================================
echo (zipOutput_CPP.cmd) START - ZIP THE C++ MSCL OUTPUT
echo.

REM copy the output/result files into a single directory structure 
echo (zipOutput.cmd) Copying files
xcopy "..\MSCL\source\*.h" %CPP_HEADERS_OUTPUT_DIR% /i /s
xcopy "..\Output\C++\*.lib" %CPP_LIBS_OUTPUT_DIR% /i /s
xcopy "..\Output\C++\*.pdb" %CPP_LIBS_OUTPUT_DIR% /i /s

REM remove old .zip files if they already exist
echo (zipOutput_CPP.cmd) Deleting zip files if they already exist
del %CPP_ZIP_OUT%
del %OUTPUT_ZIP%

REM zip the output that we just created
echo (zipOutput_CPP.cmd) Zipping Output files
7z a %OUTPUT_ZIP% %DIR_TO_ZIP% 
7z a %CPP_ZIP_OUT% %CPP_TO_ZIP%

REM remove the temporary directory that we created, since it is now zipped
echo (zipOutput_CPP.cmd) Removing temp directory that was zipped
rmdir %DIR_TO_ZIP% /S /Q

echo.
echo (zipOutput_CPP.cmd) DONE
echo ========================================================