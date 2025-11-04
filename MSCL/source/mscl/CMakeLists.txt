add_subdirectory(Communication)
add_subdirectory(MicroStrain)

# Generate the version header file (This uses the MSCL_CURRENT_YEAR variable)
set(VERSION_FILE "LibVersion.h")
set(MSCL_VERSION_IN_FILE "${MSCL_MODULE_DIR}/${VERSION_FILE}.in")
set(MSCL_VERSION_OUT_FILE "${CMAKE_CURRENT_LIST_DIR}/${VERSION_FILE}")
configure_file(${MSCL_VERSION_IN_FILE} ${MSCL_VERSION_OUT_FILE})

# Configure the precompiled header
set(MSCL_PCH_FILE "${CMAKE_CURRENT_LIST_DIR}/stdafx.h")
target_precompile_headers(${MSCL_LIBRARY} PUBLIC
    "${MSCL_PCH_FILE}"
)

set(MSCL_ROOT_FILES
    "${MSCL_VERSION_OUT_FILE}"
    "${MSCL_PCH_FILE}"
    "${CMAKE_CURRENT_LIST_DIR}/Bin.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Bin.h"
    "${CMAKE_CURRENT_LIST_DIR}/BitMask.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/BitMask.h"
    "${CMAKE_CURRENT_LIST_DIR}/Endianness.h"
    "${CMAKE_CURRENT_LIST_DIR}/Exceptions.h"
    "${CMAKE_CURRENT_LIST_DIR}/HighResClock.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/HighResClock.h"
    "${CMAKE_CURRENT_LIST_DIR}/Histogram.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Histogram.h"
    "${CMAKE_CURRENT_LIST_DIR}/mscl.h"
    "${CMAKE_CURRENT_LIST_DIR}/ScopeHelper.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ScopeHelper.h"
    "${CMAKE_CURRENT_LIST_DIR}/simple_any.h"
    "${CMAKE_CURRENT_LIST_DIR}/TimedCondition.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/TimedCondition.h"
    "${CMAKE_CURRENT_LIST_DIR}/TimeSpan.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/TimeSpan.h"
    "${CMAKE_CURRENT_LIST_DIR}/Timestamp.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Timestamp.h"
    "${CMAKE_CURRENT_LIST_DIR}/TimestampCounter.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/TimestampCounter.h"
    "${CMAKE_CURRENT_LIST_DIR}/Types.h"
    "${CMAKE_CURRENT_LIST_DIR}/Utils.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Utils.h"
    "${CMAKE_CURRENT_LIST_DIR}/Utils_Win32.h"
    "${CMAKE_CURRENT_LIST_DIR}/Value.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Value.h"
    "${CMAKE_CURRENT_LIST_DIR}/Version.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Version.h"
    "${CMAKE_CURRENT_LIST_DIR}/WMI_Helper.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WMI_Helper.h"
)

# Filter and add the source files to the target
set(MSCL_ROOT_SOURCES ${MSCL_ROOT_FILES})
list(FILTER MSCL_ROOT_SOURCES INCLUDE REGEX "^.*\\.(c|cpp)$")
target_sources("${MSCL_LIBRARY}" PRIVATE "${MSCL_ROOT_SOURCES}")

# Filter and add the header files to the target using file sets
set(MSCL_ROOT_HEADERS ${MSCL_ROOT_FILES})
list(FILTER MSCL_ROOT_HEADERS INCLUDE REGEX "^.*\\.(h|hpp)$")
target_sources("${MSCL_LIBRARY}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    FILES "${MSCL_ROOT_HEADERS}"
)
