# The exceptions interface is included in the main interface like a C++ header
# It is not needed to be included in this list
set(SWIG_SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/MSCL_Main_Interface.i"
)

# Include the Swig utilities file for easier binding configuration
# This will initialize everything needed to use Swig as well as include helper macros
set(MSCL_SWIG_UTILITIES_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/cmake/mscl_swig_utilities.cmake")
include("${MSCL_SWIG_UTILITIES_SCRIPT}")

# Build the C# bindings
if(MSCL_BUILD_CSHARP)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/csharp")
endif()

if(MSCL_BUILD_PYTHON)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/python")
endif()
