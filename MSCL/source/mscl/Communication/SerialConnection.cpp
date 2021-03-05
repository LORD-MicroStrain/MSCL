/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "OperatingSystemErrorCodes.h"
#include "SerialConnection.h"
#include "NativeSerialPort.h"
#include "mscl/Utils.h"

namespace mscl
{
    //The constructor that sets up the SerialConnection
    SerialConnection::SerialConnection(const std::string& port, uint32 baudRate):
        m_port(port),
        m_baudRate(baudRate)
    {
        m_type = Connection::connectionType_serial;
        establishConnection();
    }

    std::string SerialConnection::description()
    {
        return "Serial, " + m_port + ", " + Utils::toStr(m_baudRate);
    }
    
    //initializes and opens the serial connection
    void SerialConnection::establishConnection()
    {
        using ::boost::asio::io_context;
        using ::boost::asio::serial_port;
        using ::boost::asio::serial_port_base;

        //default flow control of None
        serial_port_base::flow_control::type flowControl = serial_port_base::flow_control::none;

        //for now we are assuming a buad rate of 3000000 enables hardware flow controls
        //TODO: we may need to reassess this in the future 
        if(m_baudRate == 3000000)
        {
            flowControl = serial_port_base::flow_control::hardware;
        }

        //if the connection has not been established
        if(!m_established)
        {
            try
            {
                //setup the m_ioContext
                m_ioContext.reset(new io_context());

                //setup the m_ioPort by creating a new serial_port using the io_context and port name
                m_ioPort.reset(new serial_port(*m_ioContext, getNativeSerialPort(m_port)));

                //create the serial port options
                const serial_port_base::baud_rate           BAUD(m_baudRate);                                       //Baud Rate
                const serial_port_base::character_size      CHAR_SIZE(8);                                           //Packet Size (default is 8 bits)
                const serial_port_base::flow_control        FLOW_CONTROL(flowControl);                              //Flow Control
                const serial_port_base::parity              PARITY(serial_port_base::parity::none);                 //Parity (default is none)
                const serial_port_base::stop_bits           STOP_BITS(serial_port_base::stop_bits::one);            //How many Stop Bits are used (default is one)

                //set all the serial port options on the port
                m_ioPort->set_option(BAUD);
                m_ioPort->set_option(CHAR_SIZE);
                m_ioPort->set_option(FLOW_CONTROL);
                m_ioPort->set_option(PARITY);
                m_ioPort->set_option(STOP_BITS);

                //setup m_comm by creating a new BoostCommunication object using the serial_port and io_service we created
                m_comm.reset(new BoostCommunication<serial_port>(std::move(m_ioContext), std::move(m_ioPort)));

                //create/start the read thread to parse incoming data
                m_readThread.reset(new std::thread(&SerialConnection::startIoThread, this));
            }
            catch(boost::system::system_error& ex)
            {
                disconnect();

                //get the boost error code
                int errorCode = ex.code().value();

                //convert to our own errors
                switch(errorCode)
                {
                    //Exception: Invalid Com Port
                    case osErrorCodes::FILE_NOT_FOUND:
                        throw Error_InvalidSerialPort(errorCode);

                    //TODO: Catch and Throw more custom errors here

                    default:
                        throw Error_Connection(errorCode);
                }
            }

            //the connection is now established
            m_established = true;
        }
    }

    void SerialConnection::updateBaudRate(uint32 baudRate)
    {
        if (m_baudRate == baudRate)
        {
            return;
        }

        disconnect();
        m_baudRate = baudRate;
        reconnect();
    }
}