add_subdirectory(Communication)
add_subdirectory(MicroStrain)

set(MSCL_ROOT_SOURCES
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
    "${CMAKE_CURRENT_LIST_DIR}/LibVersion.h"
    "${CMAKE_CURRENT_LIST_DIR}/mscl.h"
    "${CMAKE_CURRENT_LIST_DIR}/ScopeHelper.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ScopeHelper.h"
    "${CMAKE_CURRENT_LIST_DIR}/simple_any.h"
    "${CMAKE_CURRENT_LIST_DIR}/stdafx.h"
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

set(MSCL_SOURCES ${MSCL_SOURCES} ${MSCL_ROOT_SOURCES} PARENT_SCOPE)
