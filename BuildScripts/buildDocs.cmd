@echo off

REM NaturalDocs must be set to an Environment Variable

REM Set Build Variables
SET OUTPUT_DIR=..\Output\Documentation\MSCL_Docs
SET OUTPUT_ZIP=..\Output\Documentation\MSCL_Docs.zip
SET DOCS_PROJECT_DIR=NaturalDocsProjects\MSCL_Docs_Project
SET API_OUTPUT_DIR=..\Output\Documentation\MSCL_API_Docs
SET API_DOCS_PROJECT_DIR=NaturalDocsProjects\MSCL_API_Docs_Project

:CREATEDOCS
echo.
echo ==================================================================
echo (buildDocs.cmd) START BUILDING NATURALDOCS DOCUMENTATION
echo.

REM set the current directory to this file's directory
cd /d %~dp0

echo (buildDocs.cmd) Creating NaturalDocs Output Directories

mkdir ..\Output\Documentation
mkdir %OUTPUT_DIR%
mkdir %DOCS_PROJECT_DIR%
mkdir %API_OUTPUT_DIR%
mkdir %API_DOCS_PROJECT_DIR%

echo (buildDocs.cmd) Creating MSCL Full (Internal) Documentation

REM create the documentation using NaturalDocs
call NaturalDocs -i "..\MSCL\source\mscl" -o FramedHTML %OUTPUT_DIR% -p %DOCS_PROJECT_DIR% -s msclDocsStyle

echo (buildDocs.cmd) Creating MSCL API Documentation

call NaturalDocs -i "..\MSCL\source\mscl" -o FramedHTML %API_OUTPUT_DIR% -p %API_DOCS_PROJECT_DIR% -s msclDocsStyle

echo.
echo (buildDocs.cmd) DONE
echo ==================================================================

:end