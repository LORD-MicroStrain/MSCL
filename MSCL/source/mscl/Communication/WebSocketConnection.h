/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/Communication/Connection_Impl.h"

namespace mscl
{
    //Class: WebSocketConnection
    //    A <Connection_Impl> derived class that represents a web socket connection.
    class WebSocketConnection final : public Connection_Impl<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>>
    {
        friend Connection Connection::WebSocket(const std::string& host, uint16 port);

    public:
        //Function: description
        //    Gets a description of the connection.
        //
        //Returns:
        //    A description of the connection, in the form "WebSocket, serverAddress:serverPort".
        std::string description() override;

    private:
        WebSocketConnection() = delete;                                      //default constructor disabled
        WebSocketConnection(const WebSocketConnection&) = delete;            //copy constructor disabled
        WebSocketConnection& operator=(const WebSocketConnection&) = delete; //assignment operator disabled

        //Constructor: WebSocketConnection
        //    Creates a WebSocketConnection object.
        //
        //Parameters:
        //    host - The host address to connect to.
        //    port - The port to connect to.
        WebSocketConnection(const std::string& host, uint16 port);

        //Function: establishConnection
        //    Initializes and opens the current connection.
        //
        //Exceptions:
        //    - <Error_InvalidTcpServer>: the specified server address and/or server port is invalid.
        void establishConnection() override;

        typedef boost::asio::ip::tcp tcp;

        //Variable: m_host
        //    The server host address
        std::string m_host;

        //Variable: m_port
        //    The port for the connection.
        uint16 m_port;
    };
} // namespace mscl
