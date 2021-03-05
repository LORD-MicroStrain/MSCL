/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <functional>
#include <string>
#include <memory>
#include "mscl/Types.h"
#include "ConnectionDebugData.h"
#include "RawBytePacketCollector.h"

namespace mscl
{
    class Connection_Impl_Base;
    class DataBuffer;
    class ByteStream;

    //API Class: Connection
    //    The Connection object that is used for communication.
    class Connection
    {
        friend class BaseStation_Impl;
        friend class MipNode_Impl;

    public:
        //API Enums: ConnectionType
        //  Represents the types of channels on Wireless Nodes.
        //
        //  connectionType_serial       - 0 - Serial Connection
        //  connectionType_tcp          - 1 - TCP/IP Connection
        //  connectionType_webSocket    - 2 - Web Socket Connection
        //  connectionType_unixSocket   - 3 - Unix Socket Connection
        enum ConnectionType
        {
            connectionType_serial = 0,
            connectionType_tcp = 1,
            connectionType_webSocket = 2,
            connectionType_unixSocket = 3
        };

#ifndef SWIG
        //Constructor: Connection
        //    Creates a Connection object with the given implementation.
        //    Note: This constructor should not be used in most cases.
        //          Please use the static <Serial>, <TcpIp>, and <UnixSocket> functions.
        //
        //Parameters:
        //    impl - The <Connection_Impl> to use for this Connection.
        Connection(std::shared_ptr<Connection_Impl_Base> impl);
#endif

        Connection(){};

        //API Function: Serial
        //    A static function for creating a Connection object with a <SerialConnection> implementation.
        //    Use this function if you know the specific baud rate you want to connect at.
        //    A connection with the specified port will be established.
        //
        //Parameters:
        //    port - The actual string name of the COM port (ex. "COM26")
        //    baudRate - The baud rate at which to open the COM port (ex. 921600).
        //
        //Returns:
        //    A <Connection> object created with a <SerialConnection> implementation.
        //
        //Exceptions:
        //    - <Error_InvalidSerialPort>: the specified com port is invalid
        //    - <Error_Connection>: failed to get or set com port parameters
        static Connection Serial(const std::string& port, uint32 baudRate);

        //API Function: Serial
        //    A static function for creating a Connection object with a <SerialConnection> implementation,
        //    and attempting to automatically determine/use the baud rate by utilizing <Devices::listPorts>.
        //    A connection with the specified port will be established.
        //
        //Parameters:
        //    port - The actual string name of the COM port (ex. "COM26")
        //
        //Returns:
        //    A <Connection> object created with a <SerialConnection> implementation.
        //
        //Exceptions:
        //    - <Error_InvalidSerialPort>: the specified com port is invalid
        //    - <Error_Connection>: failed to get or set com port parameters
        static Connection Serial(const std::string& port);

        //API Function: TcpIp
        //    A static function for creating a Connection object with a <TcpIpConnection> implementation.
        //    A connection with the specified address/port will be established.
        //
        //Parameters:
        //    serverAddress - The server address (domain name or ip address) to connect to.
        //    serverPort - The server port to connect to.
        //    interfaceAddress - The address of the specific ethernet adapter to use for the connection (optional).
        //
        //Returns:
        //    A <Connection> object created with a <TcpIpConnection> implementation.
        //
        //Exceptions:
        //    - <Error_InvalidTcpServer>: the specified server address and/or server port is invalid.
        static Connection TcpIp(const std::string& serverAddress, uint16 serverPort, const std::string& interfaceAddress = "");

#ifndef MSCL_DISABLE_WEBSOCKETS
        //API Function: WebSocket
        //    A static function for creating a Connection object with a <WebSocketConnection> or <WebSocketSecureConnection> implementation.
        //    A connection with the specified host/port will be established.
        //    Note: This requires the "host" string to be in the form "wss://mscl.example.com" (for a Secure Web Socket) or "ws://mscl.example.com" for a standard HTTP Web Socket
        //
        //Parameters:
        //    host - The host name to connect to. For example, "wss://mscl.example.com" (for a Secure Web Socket) or "ws://mscl.example.com" for a standard HTTP Web Socket.
        //    port - The port to connect to.
        //
        //Returns:
        //    A <Connection> object created with a Web Socket implementation.
        //
        //Exceptions:
        //    - <Error_InvalidTcpServer>: the specified server address and/or server port is invalid.
        static Connection WebSocket(const std::string& host, uint16 port);
#endif
        
#ifdef UNIX_BUILD
        //API Function: UnixSocket
        //    A generator function for <Connection> objects with a <UnixSocketConnection> implementation (Unix builds only).
        //    A connection with the specified path will be established.
        //
        //Parameters:
        //    path - The a path to the unix socket
        //
        //Returns:
        //    The generated <Connection> object.
        //
        //Exceptions:
        //    - <Error_InvalidUnixSocket>: failed to connect to the specified unix socket path.
        static Connection UnixSocket(const std::string& path);
#endif

        static Connection Mock();

    private:
        //Variable: m_impl
        //    The <Connection_Impl_Base> that contains all the implementation logic for the Connection class.
        std::shared_ptr<Connection_Impl_Base> m_impl;

    private:
        //Function: registerParser
        //    Registers a function to handle the parsing of data when it is read in.
        //
        //Parameters:
        //    parseFunction - The function to call to parse data that is read in.
        //
        //Exceptions:
        //    - <Error_Connection>: The connection is already in use.
        void registerParser(std::function<void(DataBuffer&)> parseFunction);

        //Function: unregisterParser
        //    Unregisters the function to handle the parsing of data when it is read in.
        void unregisterParser();

        //Function: write
        //    Writes the specified bytes.
        //
        //Parameters:
        //    data - vector of data to be written
        void write(const ByteStream& data) const;

        //Function: throwIfError
        //    Throws an exception if a connection error has occurred.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred.
        void throwIfError();

        static std::string resolvePath(const std::string& path);

    public:
        //API Function: description
        //    Gets a description of the connection as a string.
        //
        //Returns:
        //    A description of the connection.
        std::string description();

        //API Function: type
        //  Gets the <ConnectionType> of the connection.
        //
        //Returns:
        //  A <ConnectionType> enum.
        ConnectionType type();

        //API Function: disconnect
        //    Closes the current connection.
        void disconnect();

        //API Function: reconnect
        //    Reopens a connection that has been disconnected.
        //
        //Exceptions:
        //    <Error_InvalidSerialPort> - the specified com port is invalid.
        //    <Error_InvalidTcpServer> - the specified server address and/or server port is invalid.
        //    <Error_InvalidUnixSocket> - failed to connect to the specified unix socket path.
        //    <Error_Connection> - failed to get or set com port parameters
        void reconnect();

        //API Function: write
        //    Writes the given bytes to the connection.
        //
        //Parameters:
        //    bytes - The bytes to write.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        void write(const Bytes& bytes) const;

        //API Function: writeStr
        //    Writes the given string (containing bytes) to the connection.
        //
        //Parameters:
        //    bytes - The string of bytes to write.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        void writeStr(const std::string& bytes) const;

        //Function: clearBuffer
        //    Resets the read buffer.
        //
        //Exceptions:
        //  - <Error_Connection>: The connection has been disconnected.
        void clearBuffer();

        //Function: byteReadPos
        //    Gets the read position from the byte buffer.
        //
        //Exceptions:
        //  - <Error_Connection>: The connection has been disconnected.
        std::size_t byteReadPos() const;

        //Function: byteAppendPos
        //    Gets the append position from the byte buffer.
        //
        //Exceptions:
        //  - <Error_Connection>: The connection has been disconnected.
        std::size_t byteAppendPos() const;

        //API Function: rawByteMode
        //    Puts the connection into "Raw Byte Mode." 
        //    "Raw Byte Mode" stops the data from being sent/parsed from any attached devices (BaseStation, InertialNode, etc.)
        //    and instead sends all data into a raw circular data buffer that can be accessed by calling <getRawBytes> on this Connection object.
        //    Disabling this mode will start sending all data back to the previous attached device, if still available.
        //
        //Parameters:
        //    enable - whether to enable raw byte mode (true), or disable raw byte mode (false).
        //
        //Exceptions:
        //    - <Error_Connection>: The connection has been disconnected.
        void rawByteMode(bool enable);

        //API Function: rawByteMode
        //  Checks if raw byte mode is enabled or disabled. 
        //
        //Returns:
        //  true if raw byte mode is enabled, false if it is disabled.
        bool rawByteMode();

        //API Function: getRawBytes
        //    Gets the raw bytes that are available that have been collected when the Connection is in "Raw Byte Mode."
        //    If the Connection has not been put into "Raw Byte Mode" by calling <rawByteMode>, no data can be retrieved from this function.
        //
        //Parameters:
        //    timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //    maxBytes - The maximum number of bytes to return. If this is 0 (default), all bytes will be returned.
        //
        //Returns:
        //    A <Bytes> vector containing all of the raw bytes that are available.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        Bytes getRawBytes(uint32 timeout = 0, uint32 maxBytes = 0, uint32 minBytes = 0);

        //API Function: getRawBytesStr
        //    Gets the raw bytes that are available that have been collected when the Connection is in "Raw Byte Mode" as a string.
        //    If the Connection has not been put into "Raw Byte Mode" by calling <rawByteMode>, no data can be retrieved from this function.
        //
        //Parameters:
        //    timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //    maxBytes - The maximum number of bytes to return. If this is 0 (default), all bytes will be returned.
        //
        //Returns:
        //    A string containing all of the raw bytes that are available.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        std::string getRawBytesStr(uint32 timeout = 0, uint32 maxBytes = 0, uint32 minBytes = 0);

        //API Function: getRawBytesWithPattern
        //  Gets the raw bytes that are available that have been collected when the Connection is in "Raw Byte Mode", if a byte pattern is found.
        //  If the Connection has not been put into "Raw Byte Mode" by calling <rawByteMode>, no data can be retrieved from this function.
        //
        //Patameters:
        //  pattern - The <Bytes> containing the pattern of bytes to match.
        //  timeout - The timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //
        //Returns:
        //  A <Bytes> container with all of the bytes before and including the pattern bytes if the pattern was found, or an empty <Bytes> container otherwise.
        Bytes getRawBytesWithPattern(const Bytes& pattern, uint32 timeout = 0);

        //API Function: debugMode
        //  Puts the connection into "Debug Mode." 
        //  "Debug Mode" adds an additional container that gets filled when any write or read operations occur.
        //  Once debug mode is enabled, you can access this data with the <getDebugData> function.
        //  This does not interfere with standard data collection.
        //
        //Parameters:
        //  enable - whether to enable debug mode (true), or disable debug mode (false).
        //
        //Exceptions:
        //  - <Error_Connection>: The connection has been disconnected.
        void debugMode(bool enable);

        //API Function: debugMode
        //  Checks if debug mode is enabled or disabled.
        //
        //Returns:
        //  true if debug mode is enabled, false if it is disabled.
        bool debugMode();

        //API Function: getDebugData
        //  Gets the <ConnectionDebugData> that have been collected when the Connection is in "Debug Mode."
        //  If the Connection has not been put into "Debug Mode" by calling <debugMode>, no data can be retrieved from this function.
        //
        //Parameters:
        //  timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //
        //Returns:
        //  A <ConnectionDebugDataVec> containing all of the <ConnectionDebugData> that is available.
        //
        //Exceptions:
        //  - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        ConnectionDebugDataVec getDebugData(uint32 timeout = 0);

        //API Function: updateBaudRate
        //  Updates the serial connection baud rate. If this is not a serial connection, this function does nothing.
        //  Important: The connection to the port will be closed and re-opened at the new baud rate.
        //
        //Parameters:
        //  baudRate - the baud rate at which to reestablish the connection
        //
        //Exceptions:
        //  - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        void updateBaudRate(uint32 baudRate);
    };

}
