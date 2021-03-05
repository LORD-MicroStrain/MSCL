/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "Connection.h"
#include "Connection_Impl.h"
#include "BoostCommunication.h"

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>

#include <string>

namespace mscl 
{
    //Class: TcpIpConnection
    //    A <Connection_Impl> derived class that represents a tcp/ip connection.
    class TcpIpConnection final : public Connection_Impl<boost::asio::ip::tcp::socket>
    {
        friend Connection Connection::TcpIp(const std::string& serverAddress, uint16 serverPort, const std::string& interfaceAddress);
    
    public:
        //Function: description
        //    Gets a description of the connection.
        //
        //Returns:
        //    A description of the connection, in the form "TCP/IP, serverAddress:serverPort".
        virtual std::string description();

        TcpIpConnection() = delete;                                  //default constructor disabled
        TcpIpConnection(const TcpIpConnection&) = delete;            //copy constructor disabled
        TcpIpConnection& operator=(const TcpIpConnection&) = delete; //assignment operator disabled

    private:

        //Constructor: TcpIpConnection
        //    Creates a TcpIpConnection object.
        //
        //Parameters:
        //    serverAddress - The server address (domain name or ip address) to connect to.
        //    serverPort - The server port to connect to.
        //    interfaceAddress - The address of the specific ethernet adapter to use for the connection (optional).
        TcpIpConnection(const std::string& serverAddress, uint16 serverPort, const std::string& interfaceAddress = "");

        //Function: establishConnection
        //    Initializes and opens the current connection.
        //
        //Exceptions:
        //    - <Error_InvalidTcpServer>: the specified server address and/or server port is invalid.
        virtual void establishConnection();

        void checkDeadline(const boost::system::error_code& error);
    
    private:
        typedef boost::asio::ip::tcp tcp;

        //Variable: m_path
        //    The server address (url or ip address).
        std::string m_serverAddress;

        //Variable: m_serverPort
        //    The server port for the connection.
        uint16 m_serverPort;

        //Variable: m_interfaceAddress
        //    The optional interface to use for the TCP connection.
        std::string m_interfaceAddress;

        bool m_cancelDeadline;

        std::unique_ptr<boost::asio::deadline_timer> m_deadlineTimer;
    };

}
