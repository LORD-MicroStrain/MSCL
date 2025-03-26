set(MSCL_MICROSTRAIN_INERTIAL_PACKETS_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_EstFilter.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_EstFilter.h"
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_GNSS.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_GNSS.h"
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_Sensor.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_Sensor.h"
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_Shared.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_Shared.h"
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_System.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InertialFieldParser_System.h"
)

set(MSCL_SOURCES ${MSCL_SOURCES} ${MSCL_MICROSTRAIN_INERTIAL_PACKETS_SOURCES} PARENT_SCOPE)
