add_subdirectory(Commands)
add_subdirectory(Packets)

set(MSCL_MICROSTRAIN_MIP_FILES
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

# Filter and add the source files to the target
set(MSCL_MICROSTRAIN_MIP_SOURCES ${MSCL_MICROSTRAIN_MIP_FILES})
list(FILTER MSCL_MICROSTRAIN_MIP_SOURCES INCLUDE REGEX "^.*\\.(c|cpp)$")
target_sources("${MSCL_LIBRARY}" PRIVATE "${MSCL_MICROSTRAIN_MIP_SOURCES}")

# Filter and add the header files to the target using file sets
set(MSCL_MICROSTRAIN_MIP_HEADERS ${MSCL_MICROSTRAIN_MIP_FILES})
list(FILTER MSCL_MICROSTRAIN_MIP_HEADERS INCLUDE REGEX "^.*\\.(h|hpp)$")
target_sources("${MSCL_LIBRARY}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    FILES "${MSCL_MICROSTRAIN_MIP_HEADERS}"
)
