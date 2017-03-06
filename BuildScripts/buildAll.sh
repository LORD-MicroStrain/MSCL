#!/bin/sh

echo '========================================================'
echo '(buildAll.sh) STARTING MSCL BUILD'

#for now, bjam needs this folder to exist
echo '(buildAll.sh) Creating the build\swig-python directory'
mkdir -p build/swig-python

#build the C++ and Python extensions
echo '(buildAll.sh) Running BJAM (C++)'
bjam MSCL//stage_c++ release

#have to do this twice to copy the mscl.py (BUG)
echo '(buildAll.sh) Running BJAM (Python)'
bjam MSCL//stage_python_x86 release
echo '(buildAll.sh) Running BJAM (Python) (2)'
bjam MSCL//stage_python_x86 release

#build the Unit Tests
echo '(buildAll.sh) Building Unit Tests'
bjam MSCL_Unit_Tests release

#Run the Unit Tests
echo '(buildAll.sh) Running Unit Tests'
build/MSCL_Unit_Tests/gcc-host/release/mscl_unit_tests --output_format=XML --log_level=all --report_level=no 1>"MSCL_Unit_Tests/unitTestResults.xml"

#zip everything up
echo '(buildAll.sh) Zipping the MSCL Output'
bash BuildScripts/zipOutput.sh


echo '(buildAll.sh) DONE'
echo '========================================================'