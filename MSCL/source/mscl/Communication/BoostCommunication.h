/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once
#include <boost/asio.hpp>

#ifndef MSCL_DISABLE_SSL
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/websocket/ssl.hpp>
#endif

#ifndef MSCL_DISABLE_WEBSOCKETS
#include <boost/beast.hpp>
#endif

#include <memory>
#include <mutex>
#include <functional>

#include "mscl/Exceptions.h"
#include "mscl/Types.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/DataBuffer.h"

namespace mscl
{
    namespace details
    {
        //generalized template function for writing to a IO_Object
        template <typename IO_Object>
        inline void writeAll(IO_Object& obj, const std::vector<uint8>& data)
        {
            boost::asio::write(
                obj,                                        //the ioObject (serial port, tcp socket, websocket)
                boost::asio::buffer(data, data.size()));    //the buffer that contains the data to be written
        }

#ifndef MSCL_DISABLE_WEBSOCKETS
        //specialized template function of the above for using tcp websockets
        template <>
        inline void writeAll(boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& obj, const std::vector<uint8>& data)
        {
            obj.write(boost::asio::buffer(data, data.size()));
        }

#ifndef MSCL_DISABLE_SSL
        //specialized template function of the above for using secure websockets
        template <>
        inline void writeAll(boost::beast::websocket::stream<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>& obj, const std::vector<uint8>& data)
        {
            obj.write(boost::asio::buffer(data, data.size()));
        }
#endif // MSCL_DISABLE_SSL
#endif // MSCL_DISABLE_WEBSOCKETS
    }

    //Class: BoostCommunication
    //    The BoostCommunication object that is used for actual read/write communication for all Connection objects
    template <typename IO_Object>
    class BoostCommunication
    {
    private:
        static const int ERROR_CODE_CONNECTION_RESET = 10054;
        static const int ERROR_CODE_IO_ABORTED = 995;
        static const int ERROR_CODE_DEVICE_NOT_RECOGNIZED = 22;

    public:
        //Constructor: BoostCommunication
        //    Initializes the BoostCommunication object
        //    
        //Parameters:
        //    ioContext - boost io_context
        //    ioObj - boost io_object passed (Template)
        BoostCommunication(std::unique_ptr<boost::asio::io_context> io_context, std::unique_ptr<IO_Object> ioObj);

        //Destructor: ~BoostCommunication
        //    Destroys the BoostCommunication object
        ~BoostCommunication();

    private:
        BoostCommunication() = delete;                                        //default constructor disabled
        BoostCommunication(const BoostCommunication&) = delete;               //copy constructor disabled
        BoostCommunication& operator=(const BoostCommunication&) = delete;    //assignment operator disabled

    private:
        //Variable: m_ioObject
        //    Boost io_object used to communicate (serial_port, ip::tcp::socket, etc.)
        std::unique_ptr<IO_Object> m_ioObject;

        //Variable: m_ioContext
        //    Boost io_context needed in communication
        std::unique_ptr<boost::asio::io_context> m_ioContext;

        //Variable: m_readBuffer
        //    The <DataBuffer> to hold all the bytes read in
        DataBuffer m_readBuffer;

        //Variable: m_bufferWriter
        //    The <BufferWriter> used to write bytes to the <DataBuffer>
        BufferWriter m_bufferWriter;

        //Variable: m_parseDataFunction
        //    The function to send all the read in data to. If null, the data will be thrown out.
        std::function<void(DataBuffer&)> m_parseDataFunction;

        //Variable: m_debugDataFunction
        //  The function to send a copy of the data to for debug logging. If null, the data will not be sent to it.
        std::function<void(const Bytes&, bool)> m_debugDataFunction;

        //Variable: m_parseFunctionMutex
        //    The mutex used to access/change the parse data function.
        std::recursive_mutex m_parseFunctionMutex;

    public:
        //Function: write
        //    Uses boost to write bytes to the io_object. Blocks until the write completes
        //
        //Parameters:
        //    data - the bytes to be written
        void write(const std::vector<uint8>& data) const;

        //Function: clearBuffer
        //    Clears the read buffer.
        void clearBuffer();

        //Function: byteReadPos
        //    Gets the read position from the byte buffer.
        std::size_t byteReadPos() const;

        //Function: byteAppendPos
        //    Gets the append position from the byte buffer.
        std::size_t byteAppendPos() const;

        //Function: startReadLoop
        //    Starts the main read loop that reads in all data using boost
        //
        //Returns:
        //    The ByteStream object holding the read in bytes
        void startReadLoop();

        //Function: readSome
        //    Performs the actual port read of bytes.
        void readSome();

        //Function: readLoopHandler
        //    The read handler for the read loop, called when data comes in or the read operation has been canceled
        //    
        //Parameters:
        //    error - boost error code
        //    bytes_transferred - number of bytes read in
        //
        //Exceptions:
        //    Error_Connection - I/O error occurred, the I/O service has been stopped
        void readLoopHandler(const boost::system::error_code &error, std::size_t bytes_transferred);

        //Function: stopIoService
        //    Stops the current boost::asio::io_context so no more reads or writes will happen
        void stopIoService();

        //Function: stopIoServiceError
        //    Stops the current boost::asio::io_context due to an error
        void stopIoServiceError(int errorCode);

        //Function: setParseFunction
        //    Sets the function to be called when data is read in.
        //
        //Parameters:
        //    fn - The function to set as the parser function.
        void setParseFunction(std::function<void(DataBuffer&)> fn);

        //Function: enableDebugMode
        //  Enables debug mode by setting the debug parsing function.
        //
        //Parameters:
        //  fn - The function to set as the debug parser function.
        void enableDebugMode(std::function<void(const Bytes&, bool)> fn);

        //Function: disableDebugMode
        //  Disables debug mode.
        void disableDebugMode();
    };


    //Constructor
    template <typename IO_Object>
    BoostCommunication<IO_Object>::BoostCommunication(std::unique_ptr<boost::asio::io_context> ioContext, std::unique_ptr<IO_Object> ioObj):
        m_ioObject(std::move(ioObj)),
        m_ioContext(std::move(ioContext)),
        m_readBuffer(1024 * 1000),
        m_bufferWriter(m_readBuffer.getBufferWriter()),
        m_parseDataFunction(nullptr),
        m_debugDataFunction(nullptr)
    {
    }

    template <typename IO_Object>
    BoostCommunication<IO_Object>::~BoostCommunication()
    {
        //need to destroy the serial_port object BEFORE the io_service object, or else an access violation will occur
        m_ioObject.reset();
        m_ioContext.reset();
    }

    template <typename IO_Object>
    //write function that uses boost to write to io_object
    void BoostCommunication<IO_Object>::write(const std::vector<uint8>& data) const
    {
        try
        {
            details::writeAll(*m_ioObject, data);

            if(m_debugDataFunction)
            {
                //log the written bytes with the debug log function
                m_debugDataFunction(data, false);
            }
        }
        catch(std::exception& e)
        {
            throw Error_Connection(e.what());
        }
    }

    template <typename IO_Object>
    void BoostCommunication<IO_Object>::clearBuffer()
    {
        //for thread safety
        rec_mutex_lock_guard lock(m_parseFunctionMutex);

        //reset the read buffer
        m_readBuffer.resetBuffer();

        //get a new BufferWriter from the current read buffer
        m_bufferWriter = m_readBuffer.getBufferWriter();
    }

    template <typename IO_Object>
    std::size_t BoostCommunication<IO_Object>::byteReadPos() const
    {
        return m_readBuffer.readPosition();
    }

    template <typename IO_Object>
    std::size_t BoostCommunication<IO_Object>::byteAppendPos() const
    {
        return m_readBuffer.appendPosition();
    }

    template <typename IO_Object>
    void BoostCommunication<IO_Object>::setParseFunction(std::function<void(DataBuffer&)> fn)
    {
        //for thread safety
        rec_mutex_lock_guard lock(m_parseFunctionMutex);

        m_parseDataFunction = fn;
    }

    template <typename IO_Object>
    void BoostCommunication<IO_Object>::enableDebugMode(std::function<void(const Bytes&, bool)> fn)
    {
        //for thread safety
        rec_mutex_lock_guard lock(m_parseFunctionMutex);

        m_debugDataFunction = fn;
    }

    template <typename IO_Object>
    void BoostCommunication<IO_Object>::disableDebugMode()
    {
        //for thread safety
        rec_mutex_lock_guard lock(m_parseFunctionMutex);

        m_debugDataFunction = nullptr;
    }

    template <typename IO_Object>
    void BoostCommunication<IO_Object>::startReadLoop()
    {
        m_ioContext->reset();

        //get the BufferWriter for our current read buffer
        m_bufferWriter = m_readBuffer.getBufferWriter();

        //perform the actual port read
        readSome();

        try
        {
            //start the async_read operation
            m_ioContext->run();
        }
        catch(Error_Connection& ex)
        {
            //if we have an actual error code
            if(ex.code() != -1)
            {
                //rethrow the exception
                throw;
            }
        }
    }

    template <typename IO_Object>
    void BoostCommunication<IO_Object>::readSome()
    {
        //start the boost async_read_some operation again, creating the read loop
        m_ioObject->async_read_some(
            boost::asio::buffer(m_bufferWriter.buffer(), m_bufferWriter.size()),        //the buffer that will be filled with data
            std::bind(&BoostCommunication::readLoopHandler, this,    //the read handler function
            std::placeholders::_1,        //error
            std::placeholders::_2));    //bytes_transferred
    }

    template <typename IO_Object>
    void BoostCommunication<IO_Object>::stopIoService()
    {
        m_ioContext->post([]() { throw Error_Connection("Stopping Data Thread."); });
    }

    template <typename IO_Object>
    void BoostCommunication<IO_Object>::stopIoServiceError(int errorCode)
    {
        m_ioContext->post([&errorCode]() { throw Error_Connection(errorCode); });
    }

    //read handler for the read loop, called when data has come in or the read operation has been canceled
    template <typename IO_Object>
    void BoostCommunication<IO_Object>::readLoopHandler(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        //if there wasn't an error and we got some bytes
        if(!error && bytes_transferred > 0)
        {
            //we got good data

            //for thread safety
            rec_mutex_lock_guard lock(m_parseFunctionMutex);

            std::size_t appendPos = m_readBuffer.appendPosition();

            if(m_debugDataFunction || m_parseDataFunction)
            {
                //commit any bytes that were read
                m_bufferWriter.commit(bytes_transferred);
            }

            if(m_debugDataFunction)
            {
                //log the read data bytes with the debug function
                m_debugDataFunction(m_readBuffer.bytesToRead(appendPos, bytes_transferred), true);
            }

            if(m_parseDataFunction)
            {
                //call the parseFunction to parse any data
                m_parseDataFunction(m_readBuffer);
            }

            //get a new BufferWriter from the current read buffer
            m_bufferWriter = m_readBuffer.getBufferWriter();

            //if the buffer writer has no room to write
            if(m_bufferWriter.size() == 0)
            {
                //the read buffer is full, so lets just throw it out and reset everything
                clearBuffer();
            }
        }
        else if(error)
        {
            //stop the I/O service
            stopIoService();

            //throw an exception
            throw Error_Connection(error.message(), error.value());
        }

        //perform the actual port read again
        readSome();
    }
}
