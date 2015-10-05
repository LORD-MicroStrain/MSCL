/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "Connection.h"
#include "Connection_Impl.h"
#include "BoostCommunication.h"

#include <boost/asio.hpp>

#include <string>

namespace mscl 
{
	//Class: TcpIpConnection
	//	A <Connection_Impl> derived class that represents a tcp/ip connection.
	class TcpIpConnection final : public Connection_Impl<boost::asio::ip::tcp::socket>
	{
		friend Connection Connection::TcpIp(const std::string& serverAddress, uint16 serverPort);
	
	public:
		//Function: description
		//	Gets a description of the connection.
		//
		//Returns:
		//	A description of the connection, in the form "TCP/IP, serverAddress:serverPort".
		virtual std::string description();

	private:
		TcpIpConnection();									//default constructor disabled
		TcpIpConnection(const TcpIpConnection&);			//copy constructor disabled
		TcpIpConnection& operator=(const TcpIpConnection&);	//assignment operator disabled

		//Constructor: TcpIpConnection
		//	Creates a TcpIpConnection object.
		//
		//Parameters:
		//	serverAddress - The server address (domain name or ip address) to connect to.
		//	serverPort - The server port to connect to.
		TcpIpConnection(const std::string& serverAddress, uint16 serverPort);

		//Function: establishConnection
		//	Initializes and opens the current connection.
		//
		//Exceptions:
		//	- <Error_InvalidTcpServer>: the specified server address and/or server port is invalid.
		virtual void establishConnection();
	
	private:
		typedef boost::asio::ip::tcp tcp;

		//Variable: m_path
		//	The server address (url or ip address).
		std::string m_serverAddress;

		//Variable: m_serverPort
		//	The server port for the connection.
		uint16 m_serverPort;
	};

}
