# Make sure we can find swig
if(POLICY CMP0078)
    cmake_policy(SET CMP0078 NEW)
endif()

if(POLICY CMP0086)
    cmake_policy(SET CMP0086 NEW)
endif()

set(Python2_USE_STATIC_LIBS OFF)
set(Python2_REQUIRED_COMPONENTS
    "Interpreter"
    "Development"
)
find_package("Python2" REQUIRED COMPONENTS ${Python2_REQUIRED_COMPONENTS})
