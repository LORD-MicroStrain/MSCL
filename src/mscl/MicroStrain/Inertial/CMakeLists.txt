add_subdirectory(Commands)
add_subdirectory(Packets)

set(MSCL_MICROSTRAIN_INERTIAL_FILES
    "${CMAKE_CURRENT_LIST_DIR}/EulerAngles.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/EulerAngles.h"
    "${CMAKE_CURRENT_LIST_DIR}/ExposedInertialTypes.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ExposedInertialTypes.h"
    "${CMAKE_CURRENT_LIST_DIR}/InertialNode.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InertialNode.h"
    "${CMAKE_CURRENT_LIST_DIR}/PositionVelocity.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PositionVelocity.h"
)

# Filter and add the source files to the target
set(MSCL_MICROSTRAIN_INERTIAL_SOURCES ${MSCL_MICROSTRAIN_INERTIAL_FILES})
list(FILTER MSCL_MICROSTRAIN_INERTIAL_SOURCES INCLUDE REGEX "^.*\\.(c|cpp)$")
target_sources("${MSCL_CPP_TARGET}" PRIVATE
    ${MSCL_MICROSTRAIN_INERTIAL_SOURCES}
)

# Filter and add the header files to the target using file sets
set(MSCL_MICROSTRAIN_INERTIAL_HEADERS ${MSCL_MICROSTRAIN_INERTIAL_FILES})
list(FILTER MSCL_MICROSTRAIN_INERTIAL_HEADERS INCLUDE REGEX "^.*\\.(h|hpp)$")
target_sources("${MSCL_CPP_TARGET}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    FILES ${MSCL_MICROSTRAIN_INERTIAL_HEADERS}
)
