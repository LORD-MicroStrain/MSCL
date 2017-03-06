@echo off

REM Paths to copy all of the output files to
SET PYTHON_OUTPUT_DIR="..\Output\MSCL\Python"

REM Paths to the folders that need to be zipped up
SET PYTHON_TO_ZIP="..\Output\MSCL\Python"

REM Paths/FileNames of the resulting zip files
SET PYTHON_ZIP_OUT="..\Output\Python.zip"

REM set the current directory to this file's directory
cd /d %~dp0

echo ========================================================
echo (zipOutput_Python.cmd) START - ZIP ALL OF THE MSCL OUTPUT
echo.

REM copy the output/result files into a single directory structure 
echo (zipOutput_Python.cmd) Copying files
xcopy "..\Output\Python\*.*" %PYTHON_OUTPUT_DIR% /i /s

REM remove old .zip files if they already exist
echo (zipOutput_Python.cmd) Deleting zip files if they already exist
del %PYTHON_ZIP_OUT%

REM zip the output that we just created
echo (zipOutput_Python.cmd) Zipping Output files
7z a %PYTHON_ZIP_OUT% %PYTHON_TO_ZIP% 

REM remove the temporary directory that we created, since it is now zipped
echo (zipOutput_Python.cmd) Removing temp directory that was zipped
rmdir %DIR_TO_ZIP% /S /Q

echo.
echo (zipOutput_Python.cmd) DONE
echo ========================================================