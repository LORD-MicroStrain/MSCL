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

#include "TcpIpConnection.h"
#include "mscl/Utils.h"

#ifdef _WIN32
#include <MSTcpIP.h>
#endif

namespace mscl 
{
	TcpIpConnection::TcpIpConnection(const std::string& serverAddress, uint16 serverPort) :
		m_serverAddress(serverAddress),
		m_serverPort(serverPort)
	{
		establishConnection(); 
	}
	
	std::string TcpIpConnection::description()
	{
		return "TCP/IP, " + m_serverAddress + ":" + Utils::toStr(m_serverPort);
	}
	
	void TcpIpConnection::establishConnection()
	{
		//if the connection has not been established
		if(!m_established)
		{
			try
			{
				//setup the m_ioService
				m_ioService.reset(new boost::asio::io_service);

				//create a resolver to turn the server name into a TCP endpoint
				tcp::resolver resolver(*m_ioService);

				//create the resolver query with our address and port
				tcp::resolver::query query(m_serverAddress, Utils::toStr(m_serverPort));

				//resolve the query and get the endpoint iterator
				tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
				tcp::resolver::iterator end;

				//setup the m_ioPort
				m_ioPort.reset(new tcp::socket(*m_ioService));

				//iterate over the endpoints until we find one that successfully connects
				boost::system::error_code error = boost::asio::error::host_not_found;
				while(error && endpoint_iterator != end)
				{
					m_ioPort->close();
					m_ioPort->connect(*endpoint_iterator++, error);
				}

				//if we didn't find any good endpoints
				if(error)
				{
					throw boost::system::system_error(error);	//this gets caught below
				}

#ifdef _WIN32
				//enable and configure the keep-alive
				struct tcp_keepalive alive;
				alive.onoff = 1;					//enable keep-alive
				alive.keepalivetime = 30000;		//how long before starting to send keep-alive (milliseconds)
				alive.keepaliveinterval = 1000;		//how often after the keepalivetime to send a keep-alive packet (milliseonds)

				DWORD dwBytesRet = 0;

				WSAIoctl(m_ioPort->native(), SIO_KEEPALIVE_VALS, &alive, sizeof(alive), NULL, 0, &dwBytesRet, NULL, NULL);
#endif

				//setup m_comm by creating a new BoostCommunication object using the serial_port and io_service we created
				m_comm.reset(new BoostCommunication<tcp::socket>(std::move(m_ioService), std::move(m_ioPort)));

				//create/start the read thread to parse incoming data
				m_readThread.reset(new std::thread(&TcpIpConnection::startIoThread, this));
			}
			catch(boost::system::system_error& ex)
			{
				disconnect();

				throw Error_InvalidTcpServer(ex.code().value(), ex.code().message());
			}

			//the connection is now established
			m_established = true;
		}
	}
}
