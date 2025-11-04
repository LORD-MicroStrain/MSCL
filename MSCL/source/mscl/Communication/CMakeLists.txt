set(MSCL_COMMUNICATION_FILES
    "${CMAKE_CURRENT_LIST_DIR}/BoostCommunication.h"
    "${CMAKE_CURRENT_LIST_DIR}/Connection.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Connection.h"
    "${CMAKE_CURRENT_LIST_DIR}/ConnectionDebugData.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ConnectionDebugData.h"
    "${CMAKE_CURRENT_LIST_DIR}/Connection_Impl.h"
    "${CMAKE_CURRENT_LIST_DIR}/Devices.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Devices.h"
    "${CMAKE_CURRENT_LIST_DIR}/MockConnection.h"
    "${CMAKE_CURRENT_LIST_DIR}/NativeSerialPort.h"
    "${CMAKE_CURRENT_LIST_DIR}/NativeSerialPort_linux.h"
    "${CMAKE_CURRENT_LIST_DIR}/NativeSerialPort_Win32.h"
    "${CMAKE_CURRENT_LIST_DIR}/OperatingSystemErrorCodes.h"
    "${CMAKE_CURRENT_LIST_DIR}/RawBytePacket.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/RawBytePacket.h"
    "${CMAKE_CURRENT_LIST_DIR}/RawBytePacketCollector.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/RawBytePacketCollector.h"
    "${CMAKE_CURRENT_LIST_DIR}/SerialConnection.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SerialConnection.h"
    "${CMAKE_CURRENT_LIST_DIR}/TcpIpConnection.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/TcpIpConnection.h"
    "${CMAKE_CURRENT_LIST_DIR}/WebSocketConnection.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WebSocketConnection.h"
    "${CMAKE_CURRENT_LIST_DIR}/WebSocketSecureConnection.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WebSocketSecureConnection.h"
)

if(WIN32)
    list(APPEND MSCL_COMMUNICATION_FILES
        "${CMAKE_CURRENT_LIST_DIR}/UpnpDeviceFinderCallback.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/UpnpDeviceFinderCallback.h"
        "${CMAKE_CURRENT_LIST_DIR}/UpnpService.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/UpnpService.h"
        "${CMAKE_CURRENT_LIST_DIR}/WsdaFinder.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/WsdaFinder.h"
    )
elseif(UNIX AND NOT APPLE)
    list(APPEND MSCL_COMMUNICATION_FILES
        "${CMAKE_CURRENT_LIST_DIR}/UnixSocketConnection.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/UnixSocketConnection.h"
    )
endif()

# Filter and add the source files to the target
set(MSCL_COMMUNICATION_SOURCES ${MSCL_COMMUNICATION_FILES})
list(FILTER MSCL_ROOT_SOURCES INCLUDE REGEX "^.*\\.(c|cpp)$")
target_sources("${MSCL_LIBRARY}" PRIVATE "${MSCL_COMMUNICATION_SOURCES}")

# Filter and add the header files to the target using file sets
set(MSCL_COMMUNICATION_HEADERS ${MSCL_COMMUNICATION_FILES})
list(FILTER MSCL_COMMUNICATION_HEADERS INCLUDE REGEX "^.*\\.(h|hpp)$")
target_sources("${MSCL_LIBRARY}" PUBLIC
    FILE_SET "${MSCL_HEADER_FILE_SET}"
    FILES "${MSCL_COMMUNICATION_HEADERS}"
)
