set(MSCL_MICROSTRAIN_INERTIAL_PACKETS_FILES
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

# Filter and add the source files to the target
set(MSCL_MICROSTRAIN_INERTIAL_PACKETS_SOURCES ${MSCL_MICROSTRAIN_INERTIAL_PACKETS_FILES})
list(FILTER MSCL_MICROSTRAIN_INERTIAL_PACKETS_SOURCES INCLUDE REGEX "^.*\\.(c|cpp)$")
target_sources("${MSCL_LIBRARY}" PRIVATE "${MSCL_MICROSTRAIN_INERTIAL_PACKETS_SOURCES}")

# Filter and add the header files to the target using file sets
set(MSCL_MICROSTRAIN_INERTIAL_PACKETS_HEADERS ${MSCL_MICROSTRAIN_INERTIAL_PACKETS_FILES})
list(FILTER MSCL_MICROSTRAIN_INERTIAL_PACKETS_HEADERS INCLUDE REGEX "^.*\\.(h|hpp)$")
target_sources("${MSCL_LIBRARY}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    FILES "${MSCL_MICROSTRAIN_INERTIAL_PACKETS_HEADERS}"
)
