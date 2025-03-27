set(MSCL_COMMUNICATION_SOURCES
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
    list(APPEND MSCL_COMMUNICATION_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/UpnpDeviceFinderCallback.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/UpnpDeviceFinderCallback.h"
        "${CMAKE_CURRENT_LIST_DIR}/UpnpService.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/UpnpService.h"
        "${CMAKE_CURRENT_LIST_DIR}/WsdaFinder.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/WsdaFinder.h"
    )
elseif(UNIX AND NOT APPLE)
    list(APPEND MSCL_COMMUNICATION_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/UnixSocketConnection.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/UnixSocketConnection.h"
    )
endif()

set(MSCL_SOURCES ${MSCL_SOURCES} ${MSCL_COMMUNICATION_SOURCES} PARENT_SCOPE)
