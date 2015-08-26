/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#include "stdafx.h"

#include "Connection.h"
#include "Connection_Impl.h"

#include "SerialConnection.h"
#include "TcpIpConnection.h"

#ifdef UNIX_SOCKETS
#include "UnixSocketConnection.h"
#endif

namespace mscl
{
	Connection::Connection(std::shared_ptr<Connection_Impl_Base> impl) :
		m_impl(impl)
	{
	}

	Connection Connection::Serial(const std::string& port, uint32 baudRate)//baudRate=921600
	{
		std::shared_ptr<Connection_Impl_Base> serial(new SerialConnection(port, baudRate));
		return Connection(serial);
	}

	Connection Connection::TcpIp(const std::string& serverAddress, uint16 serverPort)
	{
		std::shared_ptr<Connection_Impl_Base> tcpip(new TcpIpConnection(serverAddress, serverPort));
		return Connection(tcpip);
	}
	
#ifdef UNIX_SOCKETS
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

	void Connection::write(const ByteStream& data)
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

	void Connection::write(const Bytes& bytes)
	{ 
		m_impl->write(bytes); 
	}

	void Connection::throwIfError()
	{
		m_impl->throwIfError();
	}

	void Connection::writeStr(const std::string& bytes)										
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

	void Connection::rawByteMode(bool enable)
	{ 
		m_impl->rawByteMode(enable); 
	}

	Bytes Connection::getRawBytes(uint32 timeout, uint32 maxBytes)
	{
		Bytes result;
		m_impl->getRawBytes(result, timeout, maxBytes);
		return result;
	}

	std::string Connection::getRawBytesStr(uint32 timeout, uint32 maxBytes)
	{
		//get the raw bytes in a Bytes vector
		Bytes bytes;
		m_impl->getRawBytes(bytes, timeout, maxBytes);

		//convert the Bytes to a string
		std::string result(bytes.begin(), bytes.end());
		return result;
	}

	//====================================================================================================================================================
}