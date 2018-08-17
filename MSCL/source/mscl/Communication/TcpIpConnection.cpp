/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include <boost/lambda/lambda.hpp>

#include "TcpIpConnection.h"
#include "mscl/Utils.h"

#ifdef _WIN32
#include <MSTcpIP.h>
#endif

namespace mscl 
{
    TcpIpConnection::TcpIpConnection(const std::string& serverAddress, uint16 serverPort, const std::string& interfaceAddress) :
        m_serverAddress(serverAddress),
        m_serverPort(serverPort),
        m_interfaceAddress(interfaceAddress),
        m_cancelDeadline(false),
        m_deadlineTimer(nullptr)
    {
        m_type = Connection::connectionType_tcp;
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

                m_deadlineTimer.reset(new boost::asio::deadline_timer(*m_ioService));
                m_deadlineTimer->expires_at(boost::posix_time::pos_infin);

                boost::system::error_code error = boost::asio::error::would_block;
                m_deadlineTimer->async_wait(std::bind(&TcpIpConnection::checkDeadline, this, error));

                //iterate over the endpoints until we find one that successfully connects
                while(error && endpoint_iterator != end)
                {
                    m_ioPort->close();

                    m_ioPort->open(static_cast<tcp::endpoint>(*endpoint_iterator).protocol());

                    if(m_interfaceAddress != "")
                    {
                        tcp::endpoint interfaceEndpoint(tcp::endpoint(boost::asio::ip::address::from_string(m_interfaceAddress), 0));

                        m_ioPort->set_option(tcp::acceptor::reuse_address(true));
                        m_ioPort->bind(interfaceEndpoint);
                    }

                    m_ioPort->set_option(tcp::no_delay(true));

                    //attempt to connect, with a deadline timer of 5 seconds
                    m_deadlineTimer->expires_from_now(boost::posix_time::seconds(5));
                    m_ioPort->async_connect(*endpoint_iterator++, boost::lambda::var(error) = boost::lambda::_1);
                    do
                    {
                        m_ioService->run_one();
                    }
                    while(error == boost::asio::error::would_block);
                }

                //if we didn't find any good endpoints
                if(error || !m_ioPort->is_open())
                {
                    throw boost::system::system_error(
                        error ? error : boost::asio::error::operation_aborted);    //this gets caught below
                }

                m_cancelDeadline = true;
                m_deadlineTimer->expires_at(boost::asio::deadline_timer::traits_type::now());
                m_deadlineTimer->wait();

#ifdef _WIN32
                //enable and configure the keep-alive
                struct tcp_keepalive alive;
                alive.onoff = 1;                    //enable keep-alive
                alive.keepalivetime = 30000;        //how long before starting to send keep-alive (milliseconds)
                alive.keepaliveinterval = 1000;     //how often after the keepalivetime to send a keep-alive packet (milliseonds)

                DWORD dwBytesRet = 0;

                WSAIoctl(m_ioPort->native_handle(), SIO_KEEPALIVE_VALS, &alive, sizeof(alive), NULL, 0, &dwBytesRet, NULL, NULL);
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

    void TcpIpConnection::checkDeadline(const boost::system::error_code& error)
    {
        if(error == boost::asio::error::operation_aborted || m_cancelDeadline)
        {
            return;
        }

        // Check whether the deadline has passed. We compare the deadline against
        // the current time since a new asynchronous operation may have moved the
        // deadline before this actor had a chance to run.
        if(m_deadlineTimer->expires_at() <= boost::asio::deadline_timer::traits_type::now())
        {
            if(m_cancelDeadline)
            {
                return;
            }

            // The deadline has passed. The socket is closed so that any outstanding
            // asynchronous operations are cancelled. This allows the blocked
            // connect(), read_line() or write_line() functions to return.
            boost::system::error_code ignored_ec;
            if(m_ioPort)
            {
                m_ioPort->close(ignored_ec);
            }

            // There is no longer an active deadline. The expiry is set to positive
            // infinity so that the actor takes no action until a new deadline is set.
            m_deadlineTimer->expires_at(boost::posix_time::pos_infin);

            return;
        }

        if(m_cancelDeadline)
        {
            return;
        }

        // Put the actor back to sleep.
        m_deadlineTimer->async_wait(std::bind(&TcpIpConnection::checkDeadline, this, error));
    }
}
