/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Communication/Connection.h"

#include "mscl/Communication/Devices.h"
#include "mscl/Communication/MockConnection.h"
#include "mscl/Communication/SerialConnection.h"
#include "mscl/Communication/TcpIpConnection.h"

#ifndef MSCL_DISABLE_WEBSOCKETS
#include "mscl/Communication/WebSocketConnection.h"
#ifndef MSCL_DISABLE_SSL
#include "mscl/Communication/WebSocketSecureConnection.h"
#endif // !MSCL_DISABLE_SSL
#endif // !MSCL_DISABLE_WEBSOCKETS

#ifdef __linux__
#include "mscl/Communication/UnixSocketConnection.h"
#endif // __linux__

namespace mscl
{
    Connection::Connection(std::shared_ptr<Connection_Impl_Base> impl) :
        m_impl(impl)
    {
    }

    Connection Connection::Serial(const std::string& port, uint32 baudRate)
    {
        std::string resolvedPort = resolvePath(port);

        std::shared_ptr<Connection_Impl_Base> serial(new SerialConnection(resolvedPort, baudRate));
        return Connection(serial);
    }

    Connection Connection::Serial(const std::string& port)
    {
        std::string resolvedPort = resolvePath(port);

        //attempt to automatically discover the baud rate setting
        auto ports = Devices::listPorts();
        uint32 baudRate = 921600;
        bool foundPort = false;

        for(auto i : ports)
        {
            if(i.first == resolvedPort)
            {
                foundPort = true;
                baudRate = i.second.baudRate();
                if(baudRate == 0)
                {
                    baudRate = 921600;
                }
                break;
            }
        }

        if(!foundPort)
        {
            throw Error_InvalidSerialPort(-999);
        }

        return Serial(resolvedPort, baudRate);
    }

    Connection Connection::TcpIp(const std::string& serverAddress, uint16 serverPort, const std::string& interfaceAddress)
    {
        std::shared_ptr<Connection_Impl_Base> tcpip(new TcpIpConnection(serverAddress, serverPort, interfaceAddress));
        return Connection(tcpip);
    }

#ifndef MSCL_DISABLE_WEBSOCKETS
    Connection Connection::WebSocket(const std::string& host, uint16 port)
    {
        //if the host starts with ws:// (HTTP web socket)
        if(host.find("ws://") == 0)
        {
            std::shared_ptr<Connection_Impl_Base> webSocket(new WebSocketConnection(host, port));
            return Connection(webSocket);
        }

#ifndef MSCL_DISABLE_SSL
        //if the host starts with wss:// (HTTPS web socket)
        if(host.find("wss://") == 0)
        {
            std::shared_ptr<Connection_Impl_Base> webSocketSecure(new WebSocketSecureConnection(host, port));
            return Connection(webSocketSecure);
        }
#endif // MSCL_DISABLE_SSL

        throw Error_InvalidTcpServer(0, "The web socket host name is invalid.");
    }
#endif // MSCL_DISABLE_WEBSOCKETS

#ifdef __linux__
    Connection Connection::UnixSocket(const std::string& path)
    {
        std::shared_ptr<Connection_Impl_Base> socket(new UnixSocketConnection(path));
        return Connection(socket);
    }
#endif // __linux__

    Connection Connection::Mock()
    {
        std::shared_ptr<Connection_Impl_Base> mock(new MockConnection());
        return Connection(mock);
    }

    //====================================================================================================================================================
    //The following functions just get pushed through the Connection_Impl class containing the implementation of all these functions

    void Connection::registerParser(std::function<void(DataBuffer&)> parseFunction)
    {
        m_impl->registerParser(parseFunction);
    }

    void Connection::unregisterParser()
    {
        m_impl->unregisterParser();
    }

    void Connection::write(const ByteStream& data) const
    {
        m_impl->write(data);
    }

    std::string Connection::description()
    {
        return m_impl->description();
    }

    std::string Connection::port()
    {
        return m_impl->port();
    }

    Connection::ConnectionType Connection::type()
    {
        return m_impl->type();
    }

    void Connection::disconnect()
    {
        m_impl->disconnect();
    }

    void Connection::reconnect()
    {
        m_impl->reconnect();
    }

    void Connection::write(const Bytes& bytes) const
    {
        m_impl->write(bytes);
    }

    void Connection::throwIfError()
    {
        m_impl->throwIfError();
    }

    std::string Connection::resolvePath(const std::string& path)
    {
        std::string result = path;
        //Note: do nothing on Windows

#ifndef _WIN32
        //Linux specific code
        boost::filesystem::path p(path);

        if(boost::filesystem::is_symlink(p))
        {
            p = boost::filesystem::read_symlink(p);
            result = p.string();
        }
#endif

        return result;
    }

    void Connection::writeStr(const std::string& bytes) const
    {
        //convert the string to a Bytes vector
        Bytes data(bytes.begin(), bytes.end());

        //call the other write function
        m_impl->write(data);
    }

    void Connection::clearBuffer()
    {
        m_impl->clearBuffer();
    }

    std::size_t Connection::byteReadPos() const
    {
        return m_impl->byteReadPos();
    }

    std::size_t Connection::byteAppendPos() const
    {
        return m_impl->byteAppendPos();
    }

    void Connection::rawByteMode(bool enable)
    {
        m_impl->rawByteMode(enable);
    }

    bool Connection::rawByteMode()
    {
        return m_impl->rawByteMode();
    }

    Bytes Connection::getRawBytes(uint32 timeout, uint32 maxBytes, uint32 minBytes)
    {
        Bytes result;
        m_impl->getRawBytes(result, timeout, maxBytes, minBytes);
        return result;
    }

    std::string Connection::getRawBytesStr(uint32 timeout, uint32 maxBytes, uint32 minBytes)
    {
        //get the raw bytes in a Bytes vector
        Bytes bytes;
        m_impl->getRawBytes(bytes, timeout, maxBytes, minBytes);

        //convert the Bytes to a string
        std::string result(bytes.begin(), bytes.end());
        return result;
    }

    Bytes Connection::getRawBytesWithPattern(const Bytes& pattern, uint32 timeout)
    {
        Bytes result;
        m_impl->getRawBytesWithPattern(result, pattern.data(), pattern.size(), timeout);
        return result;
    }

    void Connection::debugMode(bool enable)
    {
        m_impl->debugMode(enable);
    }

    bool Connection::debugMode()
    {
        return m_impl->debugMode();
    }

    ConnectionDebugDataVec Connection::getDebugData(uint32 timeout /*= 0*/)
    {
        ConnectionDebugDataVec result;
        m_impl->getDebugData(result, timeout);
        return result;
    }

    void Connection::updateBaudRate(uint32 baudRate)
    {
        m_impl->updateBaudRate(baudRate);
    }

    //====================================================================================================================================================
}
