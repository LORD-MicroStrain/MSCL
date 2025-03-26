add_subdirectory(Displacement)
add_subdirectory(Inertial)
add_subdirectory(MIP)
add_subdirectory(RTK)
add_subdirectory(Wireless)

set(MSCL_MICROSTRAIN_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Bitfield.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Bitfield.h"
    "${CMAKE_CURRENT_LIST_DIR}/ByteStream.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ByteStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/ChecksumBuilder.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ChecksumBuilder.h"
    "${CMAKE_CURRENT_LIST_DIR}/DataBuffer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/DataBuffer.h"
    "${CMAKE_CURRENT_LIST_DIR}/DataPoint.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/DataPoint.h"
    "${CMAKE_CURRENT_LIST_DIR}/LinearEquation.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/LinearEquation.h"
    "${CMAKE_CURRENT_LIST_DIR}/Matrix.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Matrix.h"
    "${CMAKE_CURRENT_LIST_DIR}/ResponseCollector.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ResponseCollector.h"
    "${CMAKE_CURRENT_LIST_DIR}/ResponsePattern.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ResponsePattern.h"
    "${CMAKE_CURRENT_LIST_DIR}/SampleRate.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SampleRate.h"
    "${CMAKE_CURRENT_LIST_DIR}/SampleUtils.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SampleUtils.h"
    "${CMAKE_CURRENT_LIST_DIR}/Vector.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Vector.h"
)

set(MSCL_SOURCES ${MSCL_SOURCES} ${MSCL_MICROSTRAIN_SOURCES} PARENT_SCOPE)
