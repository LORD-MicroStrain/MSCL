# The exceptions interface is included in the main interface like a C++ header
# It is not needed to be included in this list
set(SWIG_SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/MSCL_Main_Interface.i"
)

# Include the Swig utilities file for easier binding configuration
# This will initialize everything needed to use Swig as well as include helper macros
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(mscl_swig_utilities)

# Build the C# bindings
if(MSCL_BUILD_CSHARP)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/csharp")
endif()

if(MSCL_BUILD_PYTHON)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/python")
endif()
