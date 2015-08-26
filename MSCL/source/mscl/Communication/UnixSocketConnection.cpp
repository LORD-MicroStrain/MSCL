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

#include "UnixSocketConnection.h"
#include "mscl/Utils.h"

namespace mscl 
{
	UnixSocketConnection::UnixSocketConnection(const std::string& path) :
		m_path(path)					//set the path
	{
		establishConnection(); 
	}
	
	std::string UnixSocketConnection::description()
	{
		return "UnixSocket, " + m_path;
	}
	
	void UnixSocketConnection::establishConnection()
	{
		//if the connection has not been established
		if(!m_established)
		{
			try
			{
				//setup the m_ioService
				m_ioService.reset(new boost::asio::io_service);

				//setup the m_ioPort
				Protocol::endpoint endpoint(m_path);
				m_ioPort.reset(new Protocol::socket(*m_ioService));
				m_ioPort->connect(endpoint);

				//setup m_comm by creating a new BoostCommunication object using the serial_port and io_service we created
				m_comm.reset(new BoostCommunication<Protocol::socket>(std::move(m_ioService), std::move(m_ioPort)));

				//create/start the read thread to parse incoming data
				m_readThread.reset(new std::thread(&UnixSocketConnection::startIoThread, this));
			}
			catch(boost::system::system_error& ex)
			{
				disconnect();

				throw Error_InvalidUnixSocket(ex.code().value(), ex.code().message());
			}

			//the connection is now established
			m_established = true;
		}
	}
}
