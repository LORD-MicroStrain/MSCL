/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "Connection.h"
#include "Connection_Impl.h"
#include "Devices.h"

#include "SerialConnection.h"
#include "TcpIpConnection.h"

#ifdef UNIX_BUILD
#include "UnixSocketConnection.h"
#endif

namespace mscl
{
    Connection::Connection(std::shared_ptr<Connection_Impl_Base> impl) :
        m_impl(impl)
    {
    }

    Connection Connection::Serial(const std::string& port, uint32 baudRate)
    {
        std::shared_ptr<Connection_Impl_Base> serial(new SerialConnection(port, baudRate));
        return Connection(serial);
    }

    Connection Connection::Serial(const std::string& port)
    {
        //attempt to automatically discover the baud rate setting
        auto ports = Devices::listPorts();
        uint32 baudRate = 921600;
        bool foundPort = false;

        for(auto i : ports)
        {
            if(i.first == port)
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

        return Connection::Serial(port, baudRate);
    }

    Connection Connection::TcpIp(const std::string& serverAddress, uint16 serverPort)
    {
        std::shared_ptr<Connection_Impl_Base> tcpip(new TcpIpConnection(serverAddress, serverPort));
        return Connection(tcpip);
    }
    
#ifdef UNIX_BUILD
    Connection Connection::UnixSocket(const std::string& path)
    {
        std::shared_ptr<Connection_Impl_Base> socket(new UnixSocketConnection(path));
        return Connection(socket);
    }
#endif

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

    ConnectionDebugDataVec Connection::getDebugData(uint32 timeout /*= 0*/)
    {
        ConnectionDebugDataVec result;
        m_impl->getDebugData(result, timeout);
        return result;
    }

    //====================================================================================================================================================
}