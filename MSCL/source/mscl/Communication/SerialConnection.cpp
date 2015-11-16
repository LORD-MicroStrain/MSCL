/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

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
    SerialConnection::SerialConnection(const std::string& port, uint32 baudRate /*=921600*/):
        m_port(port),                    //set the port
        m_baudRate(baudRate)            //set the baud rate
    {
        establishConnection();
    }

    std::string SerialConnection::description()
    {
        return "Serial, " + m_port + ", " + Utils::toStr(m_baudRate);
    }
    
    //initializes and opens the serial connection
    void SerialConnection::establishConnection()
    {
        using ::boost::asio::io_service;
        using ::boost::asio::serial_port;
        using ::boost::asio::serial_port_base;

        //if the connection has not been established
        if(!m_established)
        {
            try
            {
                //setup the m_ioService
                m_ioService.reset(new io_service());

                //setup the m_ioPort by creating a new serial_port using the io_service and port name
                m_ioPort.reset(new serial_port(*m_ioService, getNativeSerialPort(m_port)));

                //create the serial port options
                const serial_port_base::baud_rate            BAUD(m_baudRate);                                        //Baud Rate
                const serial_port_base::character_size        CHAR_SIZE(8);                                            //Packet Size (default is 8 bits)
                const serial_port_base::flow_control        FLOW_CONTROL(serial_port_base::flow_control::none);        //Flow Control (default is none)
                const serial_port_base::parity                PARITY(serial_port_base::parity::none);                    //Parity (default is none)
                const serial_port_base::stop_bits            STOP_BITS(serial_port_base::stop_bits::one);            //How many Stop Bits are used (default is one)

                //set all the serial port options on the port
                m_ioPort->set_option(BAUD);
                m_ioPort->set_option(CHAR_SIZE);
                m_ioPort->set_option(FLOW_CONTROL);
                m_ioPort->set_option(PARITY);
                m_ioPort->set_option(STOP_BITS);

                //setup m_comm by creating a new BoostCommunication object using the serial_port and io_service we created
                m_comm.reset(new BoostCommunication<serial_port>(std::move(m_ioService), std::move(m_ioPort)));

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
}