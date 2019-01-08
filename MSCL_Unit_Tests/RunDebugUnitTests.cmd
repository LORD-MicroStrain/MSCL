@echo off

set /p testName="Enter Test Name: " %=%

IF "%testName%"=="all" (
    "build\Debug (C++)\MSCL_Unit_Tests.exe" --log_level=all --report_level=no
) ELSE (
    "build\Debug (C++)\MSCL_Unit_Tests.exe" --log_level=all --report_level=no --run_test="%testName%"
)