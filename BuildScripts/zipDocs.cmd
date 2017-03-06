@echo off

REM Paths to copy all of the output files to
SET DOCS_OUTPUT_DIR="..\Output\MSCL\Documentation\MSCL Documentation"
SET API_DOCS_OUTPUT_DIR="..\Output\MSCL\Documentation\MSCL API Documentation"
SET GS_OUTPUT_DIR="..\Output\MSCL\Documentation\Getting Started"
SET EX_OUTPUT_DIR="..\Output\MSCL\Examples\"

REM Paths to the folders that need to be zipped up
SET DOCS_TO_ZIP="..\Output\MSCL\Documentation"
SET EX_TO_ZIP="..\Output\MSCL\Examples"

REM Paths/FileNames of the resulting zip files
SET DOCS_ZIP_OUT="..\Output\Documentation.zip"
SET EX_ZIP_OUT="..\Output\Examples.zip"

REM set the current directory to this file's directory
cd /d %~dp0

echo ========================================================
echo (zipDocs.cmd) START - ZIP ALL OF THE MSCL OUTPUT
echo.

REM copy the output/result files into a single directory structure 
echo (zipDocs.cmd) Copying files
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
xcopy "..\MSCL_Examples\*.m" %EX_OUTPUT_DIR% /exclude:outputExcludeList.txt /i /s

REM copy the MSCL_Examples dependencies folder
echo (zipDocs.cmd) Copying example dependencies folder
xcopy "..\MSCL_Examples\dependencies" %EX_OUTPUT_DIR%\dependencies /i /T /E

REM remove old .zip files if they already exist
echo (zipDocs.cmd) Deleting zip files if they already exist
del %DOCS_ZIP_OUT%
del %EX_ZIP_OUT%

REM zip the output that we just created
echo (zipDocs.cmd) Zipping Output files
7z a %DOCS_ZIP_OUT% %DOCS_TO_ZIP% 
7z a %EX_ZIP_OUT% %EX_TO_ZIP%

REM remove the temporary directory that we created, since it is now zipped
echo (zipDocs.cmd) Removing temp directory that was zipped

echo.
echo (zipDocs.cmd) DONE
echo ========================================================