add_subdirectory(Commands)

set(MSCL_MICROSTRAIN_DISPLACEMENT_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/DisplacementModels.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/DisplacementModels.h"
    "${CMAKE_CURRENT_LIST_DIR}/DisplacementNode.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/DisplacementNode.h"
)

set(MSCL_SOURCES ${MSCL_SOURCES} ${MSCL_MICROSTRAIN_DISPLACEMENT_SOURCES} PARENT_SCOPE)
