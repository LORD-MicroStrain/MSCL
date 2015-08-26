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
#pragma once

#include <boost/asio.hpp>
#include "Connection.h"
#include "Connection_Impl.h"
#include "BoostCommunication.h"
#include "mscl/Types.h"

namespace mscl
{
	//Class: SerialConnection
	//	A <Connection_Impl> derived class that represents a serial connection.
	class SerialConnection final : public Connection_Impl<boost::asio::serial_port>
	{
		friend Connection Connection::Serial(const std::string& port, uint32 baudRate);

	private:
		SerialConnection();										//default constructor disabled
		SerialConnection(const SerialConnection&);				//copy constructor disabled
		SerialConnection& operator=(const SerialConnection&);	//assignment operator disabled
	
	private:
		//Constructor: SerialConnection
		//	Initializes the SerialConnection object.
		//
		//Parameters:
		//	port - The actual string name of the COM port (ex. "COM26")
		//	baudRate - The baud rate at which to open the COM port (default of 921600)
		//
		//Exceptions:
		//	- <Error_InvalidSerialPort>: the specified com port is invalid
		//	- <Error_Connection>: failed to get or set com port parameters
		explicit SerialConnection(const std::string& port, uint32 baudRate = 921600);

	public:
		//Destructor: ~SerialConnection
		//	Destroys the SerialConnection object
		virtual ~SerialConnection() {};

	private:
		//Variable: m_port
		//	The string name of the port (ex. "COM26")
		std::string m_port;
		
		//Variable: m_baudRate
		//	The baud rate of the connection
		uint32 m_baudRate;

	public:
		//Function: description
		//	Gets a description of the connection as a string
		//
		//Returns:
		//	A description of the connection
		virtual std::string description();

	private:
		//Function: establishConnection
		//	Initializes and opens the current connection
		//
		//Exceptions:
		//	- <Error_InvalidSerialPort>: the specified com port is invalid
		//	- <Error_Connection>: failed to get or set com port parameters
		virtual void establishConnection();
	};

}