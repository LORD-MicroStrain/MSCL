#!/bin/sh

#Paths to copy all of the output files to
CPP_HEADERS_OUTPUT_DIR='../Output/MSCL/C++/include'
CPP_LIBS_OUTPUT_DIR='../Output/MSCL/C++/lib'
PYTHON_OUTPUT_DIR='../Output/MSCL/Python'
EX_OUTPUT_DIR='../Output/MSCL/Examples/'

#Paths to the folders that need to be zipped up
CPP_TO_ZIP='../Output/MSCL/C++'
PYTHON_TO_ZIP='../Output/MSCL/Python'
EX_TO_ZIP='../Output/MSCL/Examples'
DIR_TO_ZIP='../Output/MSCL'

#Paths/FileNames of the resulting zip files
CPP_ZIP_OUT='../Output/C++.zip'
PYTHON_ZIP_OUT='../Output/Python.zip'
EX_ZIP_OUT='../Output/Examples.zip'
OUTPUT_ZIP='../Output/MSCL.zip'

#set the current directory to this file's directory
cd "$(cd -P -- $(dirname -- $0) && pwd -P)"

echo '========================================================'
echo '(zipOutput.sh) START - ZIP ALL OF THE MSCL OUTPUT'

#copy all the Public C++ header files
echo '(zipOutput.sh) Copying public header files'
python copyPublicHeaders.py '../MSCL/source' $CPP_HEADERS_OUTPUT_DIR

#copy the output/result files into a single directory structure 
echo '(zipOutput.sh) Copying files'
rsync -arv --prune-empty-dirs --exclude='.svn' --include='*/' --include='*.so' --exclude='*' '../Output/C++/' $CPP_LIBS_OUTPUT_DIR
rsync -arv --prune-empty-dirs --exclude='.svn' --include='*/' --include='*.py' --include='*.so' --exclude='*' '../Output/Python/' $PYTHON_OUTPUT_DIR
rsync -arv --prune-empty-dirs --exclude='.svn' --exclude='dependencies/' --include='*/' --include='*.h' --include='readme.txt' --include='*.sln' --include='*.props' --include='*.cpp' --include='*.vcxproj' --include='*.cs' --include='*.csproj' --include='*.py' --include='*.vi' --exclude='*' '../MSCL_Examples/' $EX_OUTPUT_DIR

#copy the MSCL_Examples dependencies folder
echo '(zipOutput.sh) Copying example dependencies folder'
rsync -arv --exclude='.svn' --include='*/' --include='dependencies/' --exclude='*' '../MSCL_Examples/' $EX_OUTPUT_DIR

#remove old .zip files if they already exist
echo '(zipOutput.sh) Deleting zip files if they already exist'
rm -f $CPP_ZIP_OUT
rm -f $PYTHON_ZIP_OUT
rm -f $EX_ZIP_OUT
rm -f $OUTPUT_ZIP

#zip the output that we just created
echo '(zipOutput.sh) Zipping Output files'
7z a $OUTPUT_ZIP $DIR_TO_ZIP
7z a $CPP_ZIP_OUT $CPP_TO_ZIP
7z a $PYTHON_ZIP_OUT $PYTHON_TO_ZIP
7z a $EX_ZIP_OUT $EX_TO_ZIP

#remove the temp directory that we created, since it is now zipped
echo '(zipOutput.sh) Removing temp directory that was zipped'
rm -rf $DIR_TO_ZIP

echo '(zipOutput.sh) DONE'
echo '========================================================'