add_subdirectory(Commands)
add_subdirectory(Packets)

set(MSCL_MICROSTRAIN_MIP_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/MipBuiltInTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipBuiltInTest.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipChannel.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipChannel.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipDataField.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipDataField.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipDataPoint.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipDataPoint.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipModels.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipModels.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipNode.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipNode.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipNodeFeatures.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipNodeFeatures.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipNodeInfo.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipNodeInfo.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipNode_Impl.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipNode_Impl.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipParser.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipParser.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipTypes.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipTypes.h"
)

set(MSCL_SOURCES ${MSCL_SOURCES} ${MSCL_MICROSTRAIN_MIP_SOURCES} PARENT_SCOPE)
