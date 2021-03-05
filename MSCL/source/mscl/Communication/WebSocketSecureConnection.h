/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "Connection.h"
#include "Connection_Impl.h"
#include "BoostCommunication.h"

#include <boost/asio.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast.hpp>

#include <string>

namespace mscl 
{
    //Class: WebSocketSecureConnection
    //    A <Connection_Impl> derived class that represents a secure web socket connection.
    class WebSocketSecureConnection final : public Connection_Impl<boost::beast::websocket::stream<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>>
    {
        friend Connection Connection::WebSocket(const std::string& host, uint16 port);
    
    public:
        //Function: description
        //    Gets a description of the connection.
        //
        //Returns:
        //    A description of the connection, in the form "Secure WebSocket, serverAddress:serverPort".
        virtual std::string description();

    private:
        WebSocketSecureConnection() = delete;                                               //default constructor disabled
        WebSocketSecureConnection(const WebSocketSecureConnection&) = delete;               //copy constructor disabled
        WebSocketSecureConnection& operator=(const WebSocketSecureConnection&) = delete;    //assignment operator disabled

        //Constructor: WebSocketSecureConnection
        //    Creates a WebSocketSecureConnection object.
        //
        //Parameters:
        //    host - The host address to connect to.
        //    port - The port to connect to.
        WebSocketSecureConnection(const std::string& host, uint16 port);

        //Function: establishConnection
        //    Initializes and opens the current connection.
        //
        //Exceptions:
        //    - <Error_InvalidTcpServer>: the specified server address and/or server port is invalid.
        virtual void establishConnection();
    
    private:
        typedef boost::asio::ip::tcp tcp;

        //Variable: m_host
        //    The server host address
        std::string m_host;

        //Variable: m_port
        //    The port for the connection.
        uint16 m_port;

        boost::asio::ssl::context m_sslContext;
    };

}
