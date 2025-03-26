add_subdirectory(Commands)
add_subdirectory(Packets)

set(MSCL_MICROSTRAIN_INERTIAL_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/EulerAngles.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/EulerAngles.h"
    "${CMAKE_CURRENT_LIST_DIR}/ExposedInertialTypes.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ExposedInertialTypes.h"
    "${CMAKE_CURRENT_LIST_DIR}/InertialNode.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InertialNode.h"
    "${CMAKE_CURRENT_LIST_DIR}/PositionVelocity.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PositionVelocity.h"
)

set(MSCL_SOURCES ${MSCL_SOURCES} ${MSCL_MICROSTRAIN_INERTIAL_SOURCES} PARENT_SCOPE)
