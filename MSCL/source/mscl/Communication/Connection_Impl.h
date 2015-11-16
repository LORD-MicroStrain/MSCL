/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <boost/circular_buffer.hpp>
#include <string>
#include <thread>
#include "BoostCommunication.h"
#include <functional>

namespace mscl
{
    class DataBuffer;
    class ByteStream;

    //Class: Connection_Impl_Base
    //    An Abstract Base Class for various connection types.
    class Connection_Impl_Base
    {
    protected:
        Connection_Impl_Base() {};    //protected default constructor

    public:
        //Destructor: ~Connection_Impl_Base
        //    Destroys the Connection_Impl_Base object
        virtual ~Connection_Impl_Base() {};

    private:
        Connection_Impl_Base(const Connection_Impl_Base&);                    //copy constructor disabled
        Connection_Impl_Base& operator=(const Connection_Impl_Base&);        //assignment operator disabled

    protected:
        //Function: establishConnection
        //    Initializes and opens the current connection.
        virtual void establishConnection() = 0;

    public:
        //Function: description
        //    Gets a description of the connection as a string
        //
        //Returns:
        //    A description of the connection
        virtual std::string description() = 0;

        //Function: disconnect
        //    Closes the current connection.
        virtual void disconnect() = 0;

        //Function: reconnect
        //    Reopens a connection that has been disconnected.
        virtual void reconnect() = 0;

        //Function: registerParser
        //    Registers a function to handle the parsing of data when it is read in.
        //
        //Parameters:
        //    parseFunction - The function to call to parse data that is read in.
        //
        //Exceptions:
        //    - <Error_Connection>: The connection is already in use.
        virtual void registerParser(std::function<void(DataBuffer&)> parseFunction) = 0;

        //Function: unregisterParser
        //    Unregisters the function to handle the parsing of data when it is read in
        virtual void unregisterParser() = 0;

        //Function: throwIfError
        //    Throws an exception if a connection error has occurred.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred.
        virtual void throwIfError() = 0;

        //Function: write
        //    Writes bytes to the port via the BoostCommunication object.
        //    
        //Parameters:
        //    data - the bytes that will be written to the port.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        virtual void write(const ByteStream& data) = 0;

        //Function: write
        //    Writes the given bytes to the port via the BoostCommunication object.
        //
        //Parameters:
        //    bytes - The bytes to write.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        virtual void write(const Bytes& bytes) = 0;

        //Function: clearBuffer
        //    Resets the read buffer.
        virtual void clearBuffer() = 0;

        //Function: rawByteMode
        //    Puts the connection into "Raw Byte Mode." 
        //    "Raw Byte Mode" stops the data from being sent/parsed from any attached devices (BaseStation, InertialNode, etc.)
        //    and instead sends all data into a raw circular data buffer that can be accessed by calling <getRawBytes> on this Connection object.
        //    Disabling this mode will start sending all data back to the previous attached device, if still available.
        //
        //Parameters:
        //    enable - whether to enable raw byte mode (true), or disable raw byte mode (false).
        //
        //Exceptions:
        //    - <Error_Connection>: The connection has been disconnected.
        virtual void rawByteMode(bool enable) = 0;

        //Function: getRawBytes
        //    Gets all of the raw bytes that are available that have been collected when the Connection is in "Raw Byte Mode."
        //    If the Connection has not been put into "Raw Byte Mode" by calling <rawByteMode>, no data can be retrieved from this function.
        //
        //Parameters:
        //    bytes - A <Bytes> vector to hold the result.
        //    timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //    maxBytes - The maximum number of bytes to return. If this is 0 (default), all bytes will be returned.
        virtual void getRawBytes(Bytes& bytes, uint32 timeout = 0, uint32 maxBytes = 0) = 0;
    };




    //Class: Connection_Impl
    //    An Abstract Base Class for various connection types. 
    //    This class uses a template for the Comm Object and contains default functionality for connection types.
    //
    //See Also:
    //  <SerialConnection>
    template <typename Comm_Object>
    class Connection_Impl : public Connection_Impl_Base
    {    
    protected:
        Connection_Impl();    //protected default constructor

    private:
        Connection_Impl(const Connection_Impl&);                //copy constructor disabled
        Connection_Impl& operator=(const Connection_Impl&);        //assignment operator disabled

    public:
        //Destructor: ~Connection_Impl
        //    Destroys the Connection_Impl object
        virtual ~Connection_Impl();

    protected:
        //Variable: m_comm
        //    A <BoostCommunication> object used for actual read/write operations.
        std::unique_ptr< BoostCommunication<Comm_Object> > m_comm;

        //Variable: m_ioService
        //    The boost::asio::io_service object.
        std::unique_ptr<boost::asio::io_service> m_ioService;

        //Variable: m_ioPort
        //    The actual boost communication object (ex. boost::asio::serial_port, tcp::socket, etc.)
        std::unique_ptr<Comm_Object> m_ioPort;

        //Variable: m_readThread
        //    The thread used to run the operation of reading in bytes from the BaseStation.
        std::unique_ptr<std::thread> m_readThread;

        //Variable: m_established
        //    true if the connection has been established, false otherwise.
        bool m_established;

        //Variable: m_parseFunction
        //    The function to call to parse data that is read in.
        std::function<void(DataBuffer&)> m_parseFunction;

    private:
        //Variable: m_rawByteBuffer
        //    The circular buffer to store data when in "Raw Byte Mode."
        boost::circular_buffer_space_optimized<uint8> m_rawByteBuffer;

        //Variable: m_rawByteBufferCondition
        //    Allows the raw byte buffer to know when data has been added.
        std::condition_variable m_rawByteBufferCondition;

        //Variable: m_connectionError
        //    true if an error has occurred with the connection, false otherwise.
        bool m_connectionError;

        //Variable: m_errorCode
        //    The error code of the connection error, if there was a connection error.
        int m_errorCode;

        //Variable: m_errorMsg
        //    The error message of the connection error, if there was a connection error.
        std::string m_errorMsg;

        //Variable: m_rawByteMode
        //    true if the connection is in "Raw Byte Mode", false otherwise.
        bool m_rawByteMode;

        //Variable: m_rawDataMutex
        //    The mutex used to access the "Raw Byte Mode" buffer.
        std::mutex m_rawDataMutex;

    protected:
        //Function: establishConnection
        //    Initializes and opens the current connection.
        virtual void establishConnection() = 0;

    public:
        //Function: description
        //    Gets a description of the connection as a string.
        //
        //Returns:
        //    A description of the connection.
        virtual std::string description() = 0;

        //Function: disconnect
        //    Closes the current connection.
        virtual void disconnect() override;

        //Function: reconnect
        //    Reopens a connection that has been disconnected.
        virtual void reconnect() override;

        //Function: registerParser
        //    Registers a function to handle the parsing of data when it is read in.
        //
        //Parameters:
        //    parseFunction - The function to call to parse data that is read in.
        //
        //Exceptions:
        //    - <Error>: a data parsing function has already been registered.
        virtual void registerParser(std::function<void(DataBuffer&)> parseFunction) final;

        //Function: unregisterParser
        //    Unregisters the function to handle the parsing of data when it is read in.
        virtual void unregisterParser() final;

        //Function: throwIfError
        //    Throws an exception if a connection error has occurred.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred.
        virtual void throwIfError() final;

        //Function: write
        //    Writes bytes to the port via the BoostCommunication object.
        //    
        //Parameters:
        //    data - the bytes that will be written to the port.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        virtual void write(const ByteStream& data) final;

        //Function: write
        //    Writes the given bytes to the port via the BoostCommunication object.
        //
        //Parameters:
        //    bytes - The bytes to write.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        virtual void write(const Bytes& bytes) final;

        //Function: clearBuffer
        //    Clears the read buffer.
        virtual void clearBuffer() final;

        //Function: startIoThread
        //    Starts the main thread for reading in all the data and handling write commands
        void startIoThread();

        //Function: stopIoThread
        //    Stops the main thread, canceling all reading and writing
        void stopIoThread();

        //Function: rawByteMode
        //    Puts the connection into "Raw Byte Mode." 
        //    "Raw Byte Mode" stops the data from being sent/parsed from any attached devices (BaseStation, InertialNode, etc.)
        //    and instead sends all data into a raw circular data buffer that can be accessed by calling <getRawBytes> on this Connection object.
        //    Disabling this mode will start sending all data back to the previous attached device, if still available.
        //
        //Parameters:
        //    enable - whether to enable raw byte mode (true), or disable raw byte mode (false).
        //
        //Exceptions:
        //    - <Error_Connection>: The connection has been disconnected.
        virtual void rawByteMode(bool enable) final;

        //Function: getRawBytes
        //    Gets all of the raw bytes that are available that have been collected when the Connection is in "Raw Byte Mode."
        //    If the Connection has not been put into "Raw Byte Mode" by calling <rawByteMode>, no data can be retrieved from this function.
        //
        //Parameters:
        //    bytes - A <Bytes> vector to hold the result.
        //    timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //    maxBytes - The maximum number of bytes to return. If this is 0 (default), all bytes will be returned.
        virtual void getRawBytes(Bytes& bytes, uint32 timeout = 0, uint32 maxBytes = 0) final;

    private:
        //Function: collectRawData
        //    The function to be sent to the communication object to parse data for "Raw Byte Mode."
        //
        //Parameters:
        //    data - The <DataBuffer> that contains all of the data that was read in from the connection.
        void collectRawData(DataBuffer& data);
    };

    template <typename Comm_Object>
    Connection_Impl<Comm_Object>::Connection_Impl():
        m_established(false),
        m_parseFunction(nullptr),
        m_rawByteBuffer(1024 * 1000),
        m_connectionError(false),
        m_errorCode(0),
        m_errorMsg(""),
        m_rawByteMode(false)
    {
    }

    template <typename Comm_Object>
    Connection_Impl<Comm_Object>::~Connection_Impl()
    {
        disconnect();
    }

    template<typename Comm_Object>
    void Connection_Impl<Comm_Object>::throwIfError()
    {
        if(m_connectionError)
        {
            throw Error_Connection(m_errorMsg, m_errorCode);
        }
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::write(const ByteStream& data)
    {
        //get the Bytes and call the other write function
        write(data.data());
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::write(const Bytes& bytes)
    {
        //if there has been a connection error, or the comm object is invalid
        if(m_connectionError || !m_comm)
        {
            //throw a communication exception
            throw Error_Connection(m_errorMsg, m_errorCode);
        }

        try
        {
            //write using the connection
            m_comm->write(bytes);
        }
        catch(Error_Connection& e)
        {
            //set the connection error to true
            m_connectionError = true;
            m_errorCode = e.code();
            m_errorMsg = e.what();
            
            //throw the connection through
            throw;
        }
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::clearBuffer()
    {
        m_comm->clearBuffer();
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::disconnect()
    {
        //stop the IO Thread
        stopIoThread();

        //reset the BoostCommunication object
        m_comm.reset();

        //we have no longer established a connection
        m_established = false;

        m_ioPort.reset();
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::reconnect()
    {
        establishConnection();

        //if a parse function already exists
        if(m_parseFunction)
        {
            m_comm->setParseFunction(m_parseFunction);
        }

        m_connectionError = false;
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::registerParser(std::function<void(DataBuffer&)> parseFunction)
    {
        //if the parse function isn't empty (already has been registered)
        if(m_parseFunction)
        {
            //throw an exception
            throw Error_Connection("The Connection is already in use.");
        }

        //if the comm object is invalid
        if(!m_comm)
        {
            throw Error_Connection();
        }

        //set the parser function to the passed in function
        m_parseFunction = parseFunction;

        if(!m_rawByteMode)
        {
            m_comm->setParseFunction(m_parseFunction);
        }
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::unregisterParser()
    {
        //set the parser function to empty
        m_parseFunction = nullptr;

        if(!m_rawByteMode && m_comm)
        {
            m_comm->setParseFunction(nullptr);
        }
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::startIoThread()
    {
        try
        {
            //start the read loop giving the BufferWriter and function to parse with
            m_comm->startReadLoop();
        }
        catch(Error_Connection& e)
        {
            //set the connection error to true
            m_connectionError = true;
            m_errorCode = e.code();
            m_errorMsg = e.what();
        }
        catch(Error&)
        {
            //buffer doesn't have more room to write, 
            //shouldn't happen when starting the read thread
            assert(false);
        }
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::stopIoThread()
    {
        //if the thread is running
        if(m_readThread.get())
        {
            //stop the boost io_service to stop all the reads and writes, and close the com port
            if(m_comm)
            {
                m_comm->stopIoService();
            }

            //block until the thread is stopped
            m_readThread->join();

            //dispose of the read thread object
            m_readThread.reset();
        }
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::rawByteMode(bool enable)
    {
        //verify that we are actually changing the mode
        if(enable == m_rawByteMode) { return; }

        if(!m_established || !m_comm)
        {
            throw Error_Connection("Connection has been disconnected.");
        }

        //if we are enabling raw byte mode
        if(enable)
        {
            //set the comm parse function to the collectRawData function
            m_comm->setParseFunction(std::bind(&Connection_Impl::collectRawData, this, std::placeholders::_1));

            m_rawByteMode = true;
        }
        else
        {
            //set the comm parse function back to the previous parse function (sets to null if none)
            m_comm->setParseFunction(m_parseFunction);

            m_rawByteMode = false;
        }
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::collectRawData(DataBuffer& data)
    {
        //create a scoped_lock for thread safety
        mutex_lock_guard lock(m_rawDataMutex);

        //push all the bytes in the buffer into the circular buffer
        size_t numBytes = data.bytesRemaining();
        for(size_t byteItr = 0; byteItr < numBytes; ++byteItr)
        {
            m_rawByteBuffer.push_back(data.read_uint8());
        }

        //notify any waiting functions that we have received data
        m_rawByteBufferCondition.notify_one();
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::getRawBytes(Bytes& bytes, uint32 timeout, uint32 maxBytes)
    {
        //create a lock for thread safety
        std::unique_lock<std::mutex> lock(m_rawDataMutex);

        //set the number of bytes to all the available bytes
        size_t numBytes = m_rawByteBuffer.size();

        //if we don't have any bytes in the buffer and the user specified a timeout
        if(numBytes == 0 && timeout > 0)
        {
            //wait for the timeout or data to come in
            m_rawByteBufferCondition.wait_for(lock, std::chrono::milliseconds(timeout));

            //update the number of bytes to our new buffer size, if any
            numBytes = m_rawByteBuffer.size();
        }

        //if the user specified a number of bytes
        if(maxBytes > 0)
        {
            //if the user specified less bytes than we have in the buffer
            if(maxBytes < numBytes)
            {
                //set the number of bytes to return to the max they requested
                numBytes = maxBytes;
            }
        }

        //set the result vector to the number of elements in the circular buffer
        bytes.reserve(numBytes);

        //add all of the bytes in the circular buffer to the Bytes vector
        for(size_t byteItr = 0; byteItr < numBytes; ++byteItr)
        {
            bytes.push_back(m_rawByteBuffer.front());
            m_rawByteBuffer.pop_front();
        }
    }
}