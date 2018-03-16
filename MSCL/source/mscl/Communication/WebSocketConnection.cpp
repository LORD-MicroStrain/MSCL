/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#ifndef MSCL_DISABLE_WEBSOCKETS

#include "WebSocketConnection.h"
#include "mscl/Utils.h"

#ifdef _WIN32
#include <MSTcpIP.h>
#endif

namespace mscl 
{
    WebSocketConnection::WebSocketConnection(const std::string& serverAddress, uint16 serverPort) :
        m_host(serverAddress),
        m_port(serverPort)
    {
        m_type = Connection::connectionType_webSocket;
        establishConnection(); 
    }
    
    std::string WebSocketConnection::description()
    {
        return "WebSocket";
    }
    
    void WebSocketConnection::establishConnection()
    {
        namespace websocket = boost::beast::websocket;

        //if the connection has not been established
        if(!m_established)
        {
            try
            {
                //setup the m_ioService
                m_ioService.reset(new boost::asio::io_service);

                //create a resolver to turn the server name into a TCP endpoint
                tcp::resolver resolver(*m_ioService);

                if(m_host.find("ws://") != 0)
                {
                    throw Error_InvalidTcpServer(0, "The web socket host name is invalid.");
                }

                //the number of characters in "ws://"
                static const size_t MAIN_URL_START_POS = 5;

                std::string target = "/";

                //find the position of the slash after the host
                size_t nextSlashPosition = m_host.find("/", MAIN_URL_START_POS);
                if(nextSlashPosition == m_host.npos)
                {
                    nextSlashPosition = m_host.length();
                }
                else
                {
                    //add the rest of the url to the target
                    target += m_host.substr(nextSlashPosition + 1, m_host.size() - 1);
                }

                std::string mainUrl = m_host.substr(MAIN_URL_START_POS, nextSlashPosition - MAIN_URL_START_POS);

                //create the resolver query with our address and port
                tcp::resolver::query query(mainUrl, Utils::toStr(m_port));

                //resolve the query and get the endpoint iterator
                tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
                tcp::resolver::iterator end;

                m_ioPort.reset(new websocket::stream<tcp::socket>(*m_ioService));

                m_ioPort->binary(true);

                //iterate over the endpoints until we find one that successfully connects
                boost::system::error_code error = boost::asio::error::host_not_found;
                while(error && endpoint_iterator != end)
                {
                    m_ioPort->next_layer().close();
                    m_ioPort->next_layer().connect(*endpoint_iterator++, error);
                }

                //if we didn't find any good endpoints
                if(error)
                {
                    throw boost::system::system_error(error);    //this gets caught below
                }

                //websocket handshake
                m_ioPort->handshake(m_host, target, error);

                //if we failed the handshake
                if(error)
                {
                    throw boost::system::system_error(error);    //this gets caught below
                }

#ifdef _WIN32
                //enable and configure the keep-alive
                struct tcp_keepalive alive;
                alive.onoff = 1;                    //enable keep-alive
                alive.keepalivetime = 30000;        //how long before starting to send keep-alive (milliseconds)
                alive.keepaliveinterval = 1000;     //how often after the keepalivetime to send a keep-alive packet (milliseonds)

                DWORD dwBytesRet = 0;

                WSAIoctl(m_ioPort->next_layer().native(), SIO_KEEPALIVE_VALS, &alive, sizeof(alive), NULL, 0, &dwBytesRet, NULL, NULL);
#endif

                //setup m_comm by creating a new BoostCommunication object using the serial_port and io_service we created
                m_comm.reset(new BoostCommunication<websocket::stream<tcp::socket>>(std::move(m_ioService), std::move(m_ioPort)));

                //create/start the read thread to parse incoming data
                m_readThread.reset(new std::thread(&WebSocketConnection::startIoThread, this));
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

#endif // MSCL_DISABLE_WEBSOCKETS
