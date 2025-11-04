set(MSCL_MICROSTRAIN_MIP_COMMANDS_FILES
    "${CMAKE_CURRENT_LIST_DIR}/CyclePower.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CyclePower.h"
    "${CMAKE_CURRENT_LIST_DIR}/GenericMipCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/GenericMipCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/GetDeviceDescriptorSets.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/GetDeviceDescriptorSets.h"
    "${CMAKE_CURRENT_LIST_DIR}/GetDeviceInfo.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/GetDeviceInfo.h"
    "${CMAKE_CURRENT_LIST_DIR}/GetExtendedDeviceDescriptorSets.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/GetExtendedDeviceDescriptorSets.h"
    "${CMAKE_CURRENT_LIST_DIR}/GPSTimeUpdate.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/GPSTimeUpdate.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipCmdResponse.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipCmdResponse.h"
    "${CMAKE_CURRENT_LIST_DIR}/MipCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MipCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/MIP_Commands.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MIP_Commands.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mip_SetToIdle.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Mip_SetToIdle.h"
    "${CMAKE_CURRENT_LIST_DIR}/Ping.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Ping.h"
    "${CMAKE_CURRENT_LIST_DIR}/Resume.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Resume.h"
)

# Filter and add the source files to the target
set(MSCL_MICROSTRAIN_MIP_COMMANDS_SOURCES ${MSCL_MICROSTRAIN_MIP_COMMANDS_FILES})
list(FILTER MSCL_MICROSTRAIN_MIP_COMMANDS_SOURCES INCLUDE REGEX "^.*\\.(c|cpp)$")
target_sources("${MSCL_LIBRARY}" PRIVATE "${MSCL_MICROSTRAIN_MIP_COMMANDS_SOURCES}")

# Filter and add the header files to the target using file sets
set(MSCL_MICROSTRAIN_MIP_COMMANDS_HEADERS ${MSCL_MICROSTRAIN_MIP_COMMANDS_FILES})
list(FILTER MSCL_MICROSTRAIN_MIP_COMMANDS_HEADERS INCLUDE REGEX "^.*\\.(h|hpp)$")
target_sources("${MSCL_LIBRARY}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    FILES "${MSCL_MICROSTRAIN_MIP_COMMANDS_HEADERS}"
)
