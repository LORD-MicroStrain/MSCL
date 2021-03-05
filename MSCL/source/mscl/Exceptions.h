/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <exception>
#include <string>

#include "mscl/Types.h"
#include "mscl/MicroStrain/Wireless/Configuration/ConfigIssue.h"

namespace mscl
{
    //API Title: Exceptions
    //    Contains all the MicroStrain custom exceptions that can be thrown in MSCL

    //API Class: Error
    //    The generic MicroStrain exception (base class)
    class Error : public std::exception 
    {
    protected:
        //Variable: m_description
        //    the description of the error to be thrown,
        //    default value of "The MSCL has thrown an exception."
        std::string m_description;

    public:
        //API Constructor: Error
        //    Initializes the Error object with the default description
        Error() :
            m_description("MSCL has thrown an exception.")
        {}

        //API Constructor: Error
        //    Initializes the Error object with a custom description
        //
        //Parameters:
        //    description - the description of the error to be thrown
        Error(const std::string& description) :
            m_description(description)
        {}

        virtual ~Error() throw()
        {}

        //API Function: what
        //    overriding the default std::exception what() function,
        //    gets the description of the thrown exception
        const char* what () const throw ()
        {
            return m_description.c_str();
        }

#ifdef SWIGPYTHON
        const char* __str__ () const throw()
        {
            return what();
        }
#endif
    };

    //API Class: Error_NotSupported
    //    A command/feature was attempted to be used that was not supported.
    class Error_NotSupported: public Error
    {
    public:
        //API Constructor: Error_NotSupported
        //    Initializes the Error_NotSupported object with a default description
        Error_NotSupported():
            Error("This feature is not supported.")
        {}

        //API Constructor: Error_NotSupported
        //    Initializes the Error_NotSupported object with a custom description
        //
        //Parameters:
        //    description - the description of the error to be thrown
        Error_NotSupported(const std::string& description) :
            Error(description)
        {}

        ~Error_NotSupported() throw()
        {}
    };

    //API Class: Error_NoData
    //    There is no data available to be accessed
    class Error_NoData : public Error
    {
    public:
        //API Constructor: Error_NoData
        //    Initializes the Error_NoData object with a default description
        Error_NoData():
            Error("No data is available.")
        {}

        //API Constructor: Error_NoData
        //    Initializes the Error_NoData object with a custom description
        //
        //Parameters:
        //    description - the description of the error to be thrown
        Error_NoData(const std::string& description):
            Error(description)
        {}

        ~Error_NoData() throw()
        {}
    };

    //API Class: Error_BadDataType
    //    Data of one type was accessed as another type (simple_any)
    class Error_BadDataType : public Error
    {
    public:
        //API Constructor: Error_BadDataType
        //    Intializes the Error_BadDataType object with a default description
        Error_BadDataType() :
            Error("Data was accessed using the wrong data type.")
        {}

        ~Error_BadDataType() throw()
        {}
    };

    //API Class: Error_UnknownSampleRate
    //    The sample rate is invalid or unknown for the given device
    class Error_UnknownSampleRate : public Error
    {
    public:
        //API Constructor: Error_UnknownSampleRate
        //    Initializes the Error_UnknownSampleRate object with a default description
        Error_UnknownSampleRate() :
            Error("Unknown Sample Rate.")
        {}

        //API Constructor: Error_UnknownSampleRate
        //    Initializes the Error_UnknownSampleRate object with a custom description
        //
        //Parameters:
        //    description - the description of the error to be thrown
        Error_UnknownSampleRate(const std::string& description) :
            Error(description)
        {}

        ~Error_UnknownSampleRate() throw()
        {
        }
    };

    //API Class: Error_Communication
    //    The exception for failing to communicate with a device.
    class Error_Communication : public Error
    {
    public:
        //API Constructor: Error_Communication
        //    Initializes the Error_Communication object.
        Error_Communication() :
            Error("Failed to communicate with the device.")
        {
        }

        //API Constructor: Error_Communication
        //    Initializes the Error_Communication object.
        //
        //Parameters:
        //    description - the description to set
        Error_Communication(const std::string& description) :
            Error(description)
        {
        }

        virtual ~Error_Communication() throw()
        {
        }
    };

    //API Class: Error_NodeCommunication
    //    The exception for failing to communicate with a <WirelessNode>.
    class Error_NodeCommunication : public Error_Communication
    {
    protected:
        //Variable: m_nodeAddress
        //    The node address of the <WirelessNode> that failed to communicate.
        NodeAddress m_nodeAddress;

    private:
        Error_NodeCommunication();    //disabled default constructor

    public:
        //API Constructor: Error_NodeCommunication
        //    Initializes the Error_NodeCommunication object.
        //
        //Parameters:
        //    nodeAddress - The node address of the <WirelessNode> that failed to communicate.
        Error_NodeCommunication(NodeAddress nodeAddress):
            Error_Communication("Failed to communicate with the Wireless Node."),
            m_nodeAddress(nodeAddress)
        {}

        //API Constructor: Error_NodeCommunication
        //    Initializes the Error_NodeCommunication object.
        //
        //Parameters:
        //    nodeAddress - The node address of the <WirelessNode> that failed to communicate.
        //    description - the description to set
        Error_NodeCommunication(NodeAddress nodeAddress, const std::string& description):
            Error_Communication(description),
            m_nodeAddress(nodeAddress)
        {}

        //API Function: nodeAddress
        //    gets the node address of the <WirelessNode> that failed to communicate
        const NodeAddress nodeAddress() const throw ()
        {
            return m_nodeAddress;
        }

        ~Error_NodeCommunication() throw()
        {
        }
    };

    //API Class: Error_Connection
    //    The generic connection exception.
    class Error_Connection : public Error
    {
    protected:
        //Variable: m_code
        //    the exception error code (system error codes)
        int m_code;

    public:
        //API Constructor: Error_Connection
        //    Initializes the Error_Connection object,
        //    sets the error code to a default of -1
        Error_Connection():
            Error("Connection error."),
            m_code(-1)
        {}

        //API Constructor: Error_Connection
        //    Initializes the Error_Connection object
        //
        //Parameters:
        //    code - the exception error code
        Error_Connection(int code):
            Error("Connection error."),
            m_code(code)
        {}

        //API Constructor: Error_Connection
        //    Initializes the Error_Connection object
        //
        //Parameters:
        //    description - the description to set
        Error_Connection(const std::string& description):
            Error(description),
            m_code(-1)
        {}

        //API Constructor: Error_Connection
        //    Initializes the Error_Connection object
        //
        //Parameters:
        //    description - the description to set
        //    code - the exception error code
        Error_Connection(const std::string& description, int code):
            Error(description),
            m_code(code)
        {
        }
        
        virtual ~Error_Connection() throw() {}

        //API Function: code
        //    gets the exception error code (system error codes, or -1 by default)
        const int code() const throw ()
        {
            return m_code;
        }

#ifdef SWIGPYTHON
        const int value () const throw()
        {
            return code();
        }
#endif
    };

    //API Class: Error_InvalidSerialPort
    //    There was an error with the specified COM Port.
    //
    //See Also:
    //    <Error_Connection>
    class Error_InvalidSerialPort : public Error_Connection
    {
    public:
        //API Constructor: Error_InvalidSerialPort
        //    Initializes the Error_InvalidSerialPort object
        //
        //Parameters:
        //    code - the exception error code
        Error_InvalidSerialPort(int code): 
            Error_Connection("Invalid Com Port.", code)
        {
        }

        ~Error_InvalidSerialPort() throw() {}
    };

    //API Class: Error_InvalidTcpServer
    //    There was an error with the specified TCP/IP Server.
    //
    //See Also:
    //    <Error_Connection>
    class Error_InvalidTcpServer : public Error_Connection
    {
    public:
        //API Constructor: Error_InvalidTcpServer
        //    Initializes the Error_InvalidTcpServer object
        //
        //Parameters:
        //    code - the exception error code
        Error_InvalidTcpServer(int code, const std::string& message):
            Error_Connection("Invalid TCP/IP Server: " + message, code)
        {}
            
        ~Error_InvalidTcpServer() throw() {}
    };
    
    //API Class: Error_InvalidUnixSocket
    //    There was an error with the specified Unix Socket.
    //
    //See Also:
    //    <Error_Connection>
    class Error_InvalidUnixSocket : public Error_Connection
    {
    public:
        //API Constructor: Error_InvalidUnixSocket
        //    Initializes the Error_InvalidUnixSocket object
        //
        //Parameters:
        //    code - the exception error code
        Error_InvalidUnixSocket(int code, const std::string& message): 
            Error_Connection("Invalid Unix Socket: " + message, code)
        {}
        
        ~Error_InvalidUnixSocket() throw ()
        {}
    };

    //API Class: Error_MipCmdFailed
    //    The Inertial command has failed
    class Error_MipCmdFailed : public Error
    {
    protected:
        //Variable: m_code
        //    the exception error code (NACK error code)
        int m_code;

    public:
        //API Constructor: Error_MipCmdFailed
        //    Initializes the Error_MipCmdFailed object,
        //    sets the error code to a default of -1
        Error_MipCmdFailed() :
            Error("The Inertial command has failed."),
            m_code(-1)
        {}

        //API Constructor: Error_MipCmdFailed
        //    Initializes the Error_MipCmdFailed object,
        //    sets the error code to a default of -1
        Error_MipCmdFailed(const std::string& description) :
            Error(description),
            m_code(-1)
        {}

        //API Constructor: Error_MipCmdFailed
        //    Initializes the Error_MipCmdFailed object
        //
        //Parameters:
        //    code - the exception error code
        Error_MipCmdFailed(int code):
            Error("The Inertial command has failed."),
            m_code(code)
        {}

        Error_MipCmdFailed(int code, const std::string& message):
            Error(message),
            m_code(code)
        {}

        ~Error_MipCmdFailed() throw ()
        {
        }

        //API Function: code
        //    gets the exception error code
        const int code() const throw ()
        {
            return m_code;
        }

#ifdef SWIGPYTHON
        const int value () const throw()
        {
            return code();
        }
#endif
    };


    //API Class: Error_InvalidConfig
    //    The Configuration is invalid.
    class Error_InvalidConfig : public Error
    {
    private:
        //Variable: m_issues
        //    The <ConfigIssues> that caused the invalid configuration exception.
        ConfigIssues m_issues;

    public:
        Error_InvalidConfig():
            Error("Invalid Configuration.")
        {}

        //API Constructor: Error_InvalidConfig
        //    Initializes the Error_InvalidConfig object
        //
        //Parameters:
        //    issues - The <ConfigIssues> that caused the invalid configuration exception.
        Error_InvalidConfig(const ConfigIssues& issues):
            Error("Invalid Configuration:"),
            m_issues(issues)
        {
            for(auto i : m_issues)
            {
                //some issues show duplicate descriptions, filter those out
                if(m_description.find(i.description()) == std::string::npos)
                {
                    m_description += " " + i.description();
                }
            }
        }

        virtual ~Error_InvalidConfig() throw ()
        {}

        //API Function: issues
        //    Gets the <ConfigIssues> that caused the invalid configuration exception.
        ConfigIssues issues() const throw ()
        {
            return m_issues;
        }
    };

    //API Class: Error_InvalidNodeConfig
    //    The Configuration for a WirelessNode is invalid.
    class Error_InvalidNodeConfig : public Error_InvalidConfig
    {
    private:
        //Variable: m_nodeAddress
        //    The node address of the <WirelessNode> that the exception pertains to.
        NodeAddress m_nodeAddress;

    public:
        //API Constructor: Error_InvalidNodeConfig
        //    Initializes the Error_InvalidNodeConfig object
        //
        //Parameters:
        //    issues - The <ConfigIssues> that caused the invalid configuration exception.
        Error_InvalidNodeConfig(const ConfigIssues& issues, NodeAddress nodeAddress) :
            Error_InvalidConfig(issues),
            m_nodeAddress(nodeAddress)
        {
        }

        ~Error_InvalidNodeConfig() throw ()
        {
        }

        //API Function: nodeAddress
        //    Gets the node address of the Node that this exception pertains to.
        const NodeAddress nodeAddress() const throw ()
        {
            return m_nodeAddress;
        }
    };
}