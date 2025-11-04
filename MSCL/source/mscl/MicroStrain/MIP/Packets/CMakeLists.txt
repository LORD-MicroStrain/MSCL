set(MSCL_MICROSTRAIN_MIP_PACKETS_FILES
    "${CMAKE_CURRENT_LIST_DIR}/MipDataPacket.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipDataPacket.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipFieldParser.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipFieldParser.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipFieldParser_Displacement.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipFieldParser_Displacement.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipPacket.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipPacket.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipPacketBuilder.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipPacketBuilder.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipPacketCollector.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipPacketCollector.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipSharedDataFields.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipSharedDataFields.h"
)

# Filter and add the source files to the target
set(MSCL_MICROSTRAIN_MIP_PACKETS_SOURCES ${MSCL_MICROSTRAIN_MIP_PACKETS_FILES})
list(FILTER MSCL_MICROSTRAIN_MIP_PACKETS_SOURCES INCLUDE REGEX "^.*\\.(c|cpp)$")
target_sources("${MSCL_LIBRARY}" PRIVATE "${MSCL_MICROSTRAIN_MIP_PACKETS_SOURCES}")

# Filter and add the header files to the target using file sets
set(MSCL_MICROSTRAIN_MIP_PACKETS_HEADERS ${MSCL_MICROSTRAIN_MIP_PACKETS_FILES})
list(FILTER MSCL_MICROSTRAIN_MIP_PACKETS_HEADERS INCLUDE REGEX "^.*\\.(h|hpp)$")
target_sources("${MSCL_LIBRARY}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    FILES "${MSCL_MICROSTRAIN_MIP_PACKETS_HEADERS}"
)
