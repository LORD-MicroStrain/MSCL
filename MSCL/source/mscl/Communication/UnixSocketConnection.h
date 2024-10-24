/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "Connection.h"
#include "Connection_Impl.h"
#include "BoostCommunication.h"

#include <boost/asio.hpp>

#include <string>

namespace mscl {

//Class: UnixSocketConnection
//    A <Connection_Impl> derived class that represents a unix socket connection.
class UnixSocketConnection final : public Connection_Impl<boost::asio::local::stream_protocol::socket>
{
    friend Connection Connection::UnixSocket(const std::string& path);

public:
    //Function: description
    //    Gets a description of the connection.
    //
    //Returns:
    //    A description of the connection, in the form "UnixSocket, path".
    std::string description();

private:
    typedef boost::asio::local::stream_protocol Protocol;

    explicit UnixSocketConnection(const std::string& path);

    //Function: establishConnection
    //    Initializes and opens the current connection
    //
    //Exceptions:
    //    - <Error_InvalidUnixSocket>: the specified unix socket path is invalid
    void establishConnection();

    //Variable: m_path
    //    The path to the Unix Socket
    std::string m_path;

    UnixSocketConnection();                                            //default constructor disabled
    UnixSocketConnection(const UnixSocketConnection&);                //copy constructor disabled
    UnixSocketConnection& operator=(const UnixSocketConnection&);    //assignment operator disabled
};

}
