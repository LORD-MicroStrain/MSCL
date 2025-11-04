set(MSCL_MICROSTRAIN_WIRELESS_CONFIGURATION_FILES
    "${CMAKE_CURRENT_LIST_DIR}/ActivitySense.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ActivitySense.h"
    "${CMAKE_CURRENT_LIST_DIR}/BaseStationConfig.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/BaseStationConfig.h"
    "${CMAKE_CURRENT_LIST_DIR}/BaseStationEeprom.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/BaseStationEeprom.h"
    "${CMAKE_CURRENT_LIST_DIR}/BaseStationEepromHelper.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/BaseStationEepromHelper.h"
    "${CMAKE_CURRENT_LIST_DIR}/BaseStationEepromMap.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/BaseStationEepromMap.h"
    "${CMAKE_CURRENT_LIST_DIR}/ConfigIssue.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ConfigIssue.h"
    "${CMAKE_CURRENT_LIST_DIR}/DataModeMask.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/DataModeMask.h"
    "${CMAKE_CURRENT_LIST_DIR}/Eeprom.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Eeprom.h"
    "${CMAKE_CURRENT_LIST_DIR}/EepromLocation.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/EepromLocation.h"
    "${CMAKE_CURRENT_LIST_DIR}/EventTriggerOptions.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/EventTriggerOptions.h"
    "${CMAKE_CURRENT_LIST_DIR}/FatigueOptions.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/FatigueOptions.h"
    "${CMAKE_CURRENT_LIST_DIR}/HistogramOptions.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/HistogramOptions.h"
    "${CMAKE_CURRENT_LIST_DIR}/InputRange.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InputRange.h"
    "${CMAKE_CURRENT_LIST_DIR}/MockNodeEeprom.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/MockNodeEeprom.h"
    "${CMAKE_CURRENT_LIST_DIR}/NodeEeprom.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/NodeEeprom.h"
    "${CMAKE_CURRENT_LIST_DIR}/NodeEepromHelper.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/NodeEepromHelper.h"
    "${CMAKE_CURRENT_LIST_DIR}/NodeEepromMap.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/NodeEepromMap.h"
    "${CMAKE_CURRENT_LIST_DIR}/SyncNodeConfig.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SyncNodeConfig.h"
    "${CMAKE_CURRENT_LIST_DIR}/TempSensorOptions.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/TempSensorOptions.h"
    "${CMAKE_CURRENT_LIST_DIR}/WirelessNodeConfig.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WirelessNodeConfig.h"
)

# Filter and add the source files to the target
set(MSCL_MICROSTRAIN_WIRELESS_CONFIGURATION_SOURCES ${MSCL_MICROSTRAIN_WIRELESS_CONFIGURATION_FILES})
list(FILTER MSCL_MICROSTRAIN_WIRELESS_CONFIGURATION_SOURCES INCLUDE REGEX "^.*\\.(c|cpp)$")
target_sources("${MSCL_LIBRARY}" PRIVATE "${MSCL_MICROSTRAIN_WIRELESS_CONFIGURATION_SOURCES}")

# Filter and add the header files to the target using file sets
set(MSCL_MICROSTRAIN_WIRELESS_CONFIGURATION_HEADERS ${MSCL_MICROSTRAIN_WIRELESS_CONFIGURATION_FILES})
list(FILTER MSCL_MICROSTRAIN_WIRELESS_CONFIGURATION_HEADERS INCLUDE REGEX "^.*\\.(h|hpp)$")
target_sources("${MSCL_LIBRARY}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    FILES "${MSCL_MICROSTRAIN_WIRELESS_CONFIGURATION_HEADERS}"
)
