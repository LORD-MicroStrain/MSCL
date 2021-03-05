/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#ifndef MSCL_DISABLE_WEBSOCKETS
#ifndef MSCL_DISABLE_SSL

#include "WebSocketSecureConnection.h"
#include "mscl/Utils.h"

#ifdef _WIN32
#include <MSTcpIP.h>
#endif

#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/ssl.hpp>

namespace mscl 
{
    WebSocketSecureConnection::WebSocketSecureConnection(const std::string& serverAddress, uint16 serverPort) :
        m_host(serverAddress),
        m_port(serverPort),
        m_sslContext(boost::asio::ssl::context::sslv23_client)
    {
        m_type = Connection::connectionType_webSocket;
        establishConnection(); 
    }
    
    std::string WebSocketSecureConnection::description()
    {
        return "Secure WebSocket";
    }
    
    void WebSocketSecureConnection::establishConnection()
    {
        namespace websocket = boost::beast::websocket;
        namespace ssl = boost::asio::ssl;
        
        //if the connection has not been established
        if(!m_established)
        {
            try
            {
                //setup the m_ioContext
                m_ioContext.reset(new boost::asio::io_context);

                //load_root_certificates(m_sslContext);

                //create a resolver to turn the server name into a TCP endpoint
                tcp::resolver resolver(*m_ioContext);

                if(m_host.find("wss://") != 0)
                {
                    throw Error_InvalidTcpServer(0, "The web socket host name is invalid.");
                }

                //the number of characters in "wss://"
                static const size_t MAIN_URL_START_POS = 6;

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

                m_ioPort.reset(new websocket::stream<ssl::stream<tcp::socket>>(*m_ioContext, m_sslContext));

                m_ioPort->binary(true);

                //iterate over the endpoints until we find one that successfully connects
                boost::system::error_code error = boost::asio::error::host_not_found;
                while(error && endpoint_iterator != end)
                {
                    m_ioPort->next_layer().next_layer().close();
                    m_ioPort->next_layer().next_layer().connect(*endpoint_iterator++, error);
                }

                //if we didn't find any good endpoints
                if(error)
                {
                    throw boost::system::system_error(error);    //this gets caught below
                }

                //SSL handshake
                m_ioPort->next_layer().handshake(ssl::stream_base::client, error);

                //if we failed the handshake
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

                WSAIoctl(m_ioPort->next_layer().next_layer().native_handle(), SIO_KEEPALIVE_VALS, &alive, sizeof(alive), NULL, 0, &dwBytesRet, NULL, NULL);
#endif

                //setup m_comm by creating a new BoostCommunication object using the serial_port and io_context we created
                m_comm.reset(new BoostCommunication<websocket::stream<ssl::stream<tcp::socket>>>(std::move(m_ioContext), std::move(m_ioPort)));

                //create/start the read thread to parse incoming data
                m_readThread.reset(new std::thread(&WebSocketSecureConnection::startIoThread, this));
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

#endif // MSCL_DISABLE_SSL
#endif // MSCL_DISABLE_WEBSOCKETS
