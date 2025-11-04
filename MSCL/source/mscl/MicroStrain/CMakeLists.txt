add_subdirectory(Displacement)
add_subdirectory(Inertial)
add_subdirectory(MIP)
add_subdirectory(RTK)
add_subdirectory(Wireless)

set(MSCL_MICROSTRAIN_FILES
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

# Filter and add the source files to the target
set(MSCL_MICROSTRAIN_SOURCES ${MSCL_MICROSTRAIN_FILES})
list(FILTER MSCL_MICROSTRAIN_SOURCES INCLUDE REGEX "^.*\\.(c|cpp)$")
target_sources("${MSCL_LIBRARY}" PRIVATE "${MSCL_MICROSTRAIN_SOURCES}")

# Filter and add the header files to the target using file sets
set(MSCL_MICROSTRAIN_HEADERS ${MSCL_MICROSTRAIN_FILES})
list(FILTER MSCL_MICROSTRAIN_HEADERS INCLUDE REGEX "^.*\\.(h|hpp)$")
target_sources("${MSCL_LIBRARY}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    FILES "${MSCL_MICROSTRAIN_HEADERS}"
)
