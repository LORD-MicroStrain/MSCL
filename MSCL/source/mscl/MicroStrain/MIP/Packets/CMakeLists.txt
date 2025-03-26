set(MSCL_MICROSTRAIN_MIP_PACKETS_SOURCES
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

set(MSCL_SOURCES ${MSCL_SOURCES} ${MSCL_MICROSTRAIN_MIP_PACKETS_SOURCES} PARENT_SCOPE)
