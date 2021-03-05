/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

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
#include "Connection.h"
#include "ConnectionDebugData.h"
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

        Connection_Impl_Base(const Connection_Impl_Base&) = delete;                 //copy constructor disabled
        Connection_Impl_Base& operator=(const Connection_Impl_Base&) = delete;      //assignment operator disabled

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

        //Function: type
        //  Gets the <Connection::ConnectionType>.
        virtual Connection::ConnectionType type() = 0;

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
        virtual void write(const ByteStream& data) const = 0;

        //Function: write
        //    Writes the given bytes to the port via the BoostCommunication object.
        //
        //Parameters:
        //    bytes - The bytes to write.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        virtual void write(const Bytes& bytes) const = 0;

        //Function: clearBuffer
        //    Resets the read buffer.
        virtual void clearBuffer() = 0;

        //Function: byteReadPos
        //    Gets the read position from the byte buffer.
        virtual std::size_t byteReadPos() const = 0;

        //Function: byteAppendPos
        //    Gets the append position from the byte buffer.
        virtual std::size_t byteAppendPos() const = 0;

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

        virtual bool rawByteMode() = 0;

        //Function: getRawBytes
        //    Gets all of the raw bytes that are available that have been collected when the Connection is in "Raw Byte Mode."
        //    If the Connection has not been put into "Raw Byte Mode" by calling <rawByteMode>, no data can be retrieved from this function.
        //
        //Parameters:
        //    bytes - A <Bytes> vector to hold the result.
        //    timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //    maxBytes - The maximum number of bytes to return. If this is 0 (default), all bytes will be returned.
        //    minBytes - The minimum number of bytes to parse before returning.
        virtual void getRawBytes(Bytes& bytes, uint32 timeout = 0, uint32 maxBytes = 0, uint32 minBytes = 0) = 0;

        virtual void getRawBytesWithPattern(Bytes& bytes, const uint8* pattern, size_t length, uint32 timeout = 0) = 0;

        //Function: debugMode
        //  Puts the connection into "Debug Mode." 
        //  "Debug Mode Mode" adds an additional container that gets filled when any write or read operations occur.
        //  Once debug mode is enabled, you can access this data with the <getDebugData> function.
        //  This does not interfere with standard data collection.
        //
        //Parameters:
        //  enable - whether to enable debug mode (true), or disable debug mode (false).
        //
        //Exceptions:
        //  - <Error_Connection>: The connection has been disconnected.
        virtual void debugMode(bool enable) = 0;

        virtual bool debugMode() = 0;

        //Function: getDebugData
        //  Gets the <ConnectionDebugData> that have been collected when the Connection is in "Debug Mode."
        //  If the Connection has not been put into "Debug Mode" by calling <debugMode>, no data can be retrieved from this function.
        //
        //Parameters:
        //  timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //
        //Returns:
        //  A <ConnectionDebugDataVec> containing all of the <ConnectionDebugData> that is available.
        //
        //Exceptions:
        //  - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        virtual void getDebugData(ConnectionDebugDataVec& data, uint32 timeout) = 0;

        //API Function: updateBaudRate
        //  Updates the serial connection baud rate. If this is not a serial connection, this function does nothing.
        //  Important: The connection to the port will be closed and re-opened at the new baud rate.
        //
        //Parameters:
        //  baudRate - the baud rate at which to reestablish the connection
        //
        //Exceptions:
        //  - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        virtual void updateBaudRate(uint32 baudRate) {};
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

        //Variable: m_ioContext
        //    The boost::asio::io_context object.
        std::unique_ptr<boost::asio::io_context> m_ioContext;

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

        //Variable: m_type
        //  The <Connection::ConnectionType> of this connection.
        Connection::ConnectionType m_type;

    private:
        //Variable: m_rawByteBuffer
        //    The circular buffer to store data when in "Raw Byte Mode."
        boost::circular_buffer_space_optimized<uint8> m_rawByteBuffer;

        //Variable: m_debugDataBuffer
        //    The circular buffer to store data when in "Debug Mode."
        boost::circular_buffer_space_optimized<ConnectionDebugData> m_debugDataBuffer;

        //Variable: m_rawByteBufferCondition
        //    Allows the raw byte buffer to know when data has been added.
        std::condition_variable m_rawByteBufferCondition;

        //Variable: m_debugBufferCondition
        //    Allows the debug data buffer to know when data has been added.
        std::condition_variable m_debugBufferCondition;

        //Variable: m_connectionError
        //    true if an error has occurred with the connection, false otherwise.
        mutable bool m_connectionError;

        //Variable: m_errorCode
        //    The error code of the connection error, if there was a connection error.
        mutable int m_errorCode;

        //Variable: m_errorMsg
        //    The error message of the connection error, if there was a connection error.
        mutable std::string m_errorMsg;

        //Variable: m_rawByteMode
        //    true if the connection is in "Raw Byte Mode", false otherwise.
        bool m_rawByteMode;

        //Variable: m_rawDataMutex
        //    The mutex used to access the "Raw Byte Mode" buffer.
        std::mutex m_rawDataMutex;

        //Variable: m_debugMode
        //  true if the connection is in "Debug Mode", false otherwise.
        bool m_debugMode;

        //Variable: m_debugDataMutex
        //  The mutex used to access the "Debug Mode" buffer.
        std::mutex m_debugDataMutex;

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

        //Function: type
        //  Gets the <Connection::ConnectionType>.
        virtual Connection::ConnectionType type() override;

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
        virtual void write(const ByteStream& data) const final;

        //Function: write
        //    Writes the given bytes to the port via the BoostCommunication object.
        //
        //Parameters:
        //    bytes - The bytes to write.
        //
        //Exceptions:
        //    - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        virtual void write(const Bytes& bytes) const final;

        //Function: clearBuffer
        //    Clears the read buffer.
        virtual void clearBuffer() final;

        //Function: byteReadPos
        //    Gets the read position from the byte buffer.
        virtual std::size_t byteReadPos() const final;

        //Function: byteAppendPos
        //    Gets the append position from the byte buffer.
        virtual std::size_t byteAppendPos() const final;

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

        //Function: rawByteMode
        //  Checks if raw byte mode is enabled (true) or disabled (false)
        virtual bool rawByteMode() final;

        //Function: getRawBytes
        //    Gets all of the raw bytes that are available that have been collected when the Connection is in "Raw Byte Mode."
        //    If the Connection has not been put into "Raw Byte Mode" by calling <rawByteMode>, no data can be retrieved from this function.
        //
        //Parameters:
        //    bytes - A <Bytes> vector to hold the result.
        //    timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //    maxBytes - The maximum number of bytes to return. If this is 0 (default), all bytes will be returned.
        //    minBytes - The minimum number of bytes to parse before returning.
        virtual void getRawBytes(Bytes& bytes, uint32 timeout = 0, uint32 maxBytes = 0, uint32 minBytes = 0) final;

        virtual void getRawBytesWithPattern(Bytes& bytes, const uint8* pattern, size_t length, uint32 timeout = 0) final;

        //Function: debugMode
        //  Puts the connection into "Debug Mode." 
        //  "Debug Mode Mode" adds an additional container that gets filled when any write or read operations occur.
        //  Once debug mode is enabled, you can access this data with the <getDebugData> function.
        //  This does not interfere with standard data collection.
        //
        //Parameters:
        //  enable - whether to enable debug mode (true), or disable debug mode (false).
        //
        //Exceptions:
        //  - <Error_Connection>: The connection has been disconnected.
        virtual void debugMode(bool enable) final;

        //Function: debugMode
        //  Checks if debug mode is enabled (true) or disabled (false)
        virtual bool debugMode() final;

        //Function: getDebugData
        //  Gets the <ConnectionDebugData> that have been collected when the Connection is in "Debug Mode."
        //  If the Connection has not been put into "Debug Mode" by calling <debugMode>, no data can be retrieved from this function.
        //
        //Parameters:
        //  timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0).
        //
        //Returns:
        //  A <ConnectionDebugDataVec> containing all of the <ConnectionDebugData> that is available.
        //
        //Exceptions:
        //  - <Error_Connection>: a connection error has occurred, such as the device being unplugged.
        virtual void getDebugData(ConnectionDebugDataVec& data, uint32 timeout) final;

    private:
        //Function: collectRawData
        //    The function to be sent to the communication object to parse data for "Raw Byte Mode."
        //
        //Parameters:
        //    data - The <DataBuffer> that contains all of the data that was read in from the connection.
        void collectRawData(DataBuffer& data);

        //Function: collectDebugData
        //  The function to be sent to the communication object to parse data for "Debug Mode."
        //
        //Parameters:
        //  data - The <Bytes> that contains all of the data that was read from or written to the connection.
        //  isRead - Whether the data is from a read operation (true) or a write operation (false).
        void collectDebugData(const Bytes& data, bool isRead);
    };

    template <typename Comm_Object>
    Connection_Impl<Comm_Object>::Connection_Impl():
        m_established(false),
        m_parseFunction(nullptr),
        m_rawByteBuffer(1024 * 1000),
        m_debugDataBuffer(5000),
        m_connectionError(false),
        m_errorCode(0),
        m_errorMsg(""),
        m_rawByteMode(false),
        m_debugMode(false)
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
    void Connection_Impl<Comm_Object>::write(const ByteStream& data) const
    {
        //get the Bytes and call the other write function
        write(data.data());
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::write(const Bytes& bytes) const
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
        //if there has been a connection error, or the comm object is invalid
        if(m_connectionError || !m_comm)
        {
            //throw a communication exception
            throw Error_Connection(m_errorMsg, m_errorCode);
        }

        m_comm->clearBuffer();
    }

    template <typename Comm_Object>
    std::size_t Connection_Impl<Comm_Object>::byteReadPos() const
    {
        //if there has been a connection error, or the comm object is invalid
        if(m_connectionError || !m_comm)
        {
            //throw a communication exception
            throw Error_Connection(m_errorMsg, m_errorCode);
        }

        return m_comm->byteReadPos();
    }

    template <typename Comm_Object>
    std::size_t Connection_Impl<Comm_Object>::byteAppendPos() const
    {
        //if there has been a connection error, or the comm object is invalid
        if(m_connectionError || !m_comm)
        {
            //throw a communication exception
            throw Error_Connection(m_errorMsg, m_errorCode);
        }

        return m_comm->byteAppendPos();
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
    Connection::ConnectionType Connection_Impl<Comm_Object>::type()
    {
        return m_type;
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
        catch(Error& e)
        {
            m_connectionError = true;
            m_errorMsg = e.what();

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
            //stop the boost io_context to stop all the reads and writes, and close the com port
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
    bool Connection_Impl<Comm_Object>::rawByteMode()
    {
        return m_rawByteMode;
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
    void Connection_Impl<Comm_Object>::getRawBytes(Bytes& bytes, uint32 timeout, uint32 maxBytes, uint32 minBytes)
    {
        //create a lock for thread safety
        std::unique_lock<std::mutex> lock(m_rawDataMutex);

        //set the number of bytes to all the available bytes
        size_t numBytes = m_rawByteBuffer.size();

        uint64 timeWaited = 0;
        std::chrono::high_resolution_clock::time_point timepoint;

        //if we don't have any bytes in the buffer and the user specified a timeout
        while((numBytes == 0 || numBytes < minBytes) && timeout > timeWaited)
        {
            timepoint = std::chrono::high_resolution_clock::now();

            //wait for the timeout or data to come in
            m_rawByteBufferCondition.wait_for(lock, std::chrono::milliseconds(timeout - timeWaited));

            timeWaited += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timepoint).count();

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

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::getRawBytesWithPattern(Bytes& bytes, const uint8* pattern, size_t length, uint32 timeout)
    {
        //create a lock for thread safety
        std::unique_lock<std::mutex> lock(m_rawDataMutex);

        auto timepoint = std::chrono::high_resolution_clock::now();

        uint64 timeWaited = 0;

        do
        {
            // Try to find the pattern in the buffer. Will not find partial matches at the end as they require more data.
            auto result = std::search(m_rawByteBuffer.begin(), m_rawByteBuffer.end(), pattern, pattern + length);

            // Found a match?
            if(result != m_rawByteBuffer.end())
            {
                size_t endPos = (result - m_rawByteBuffer.begin()) + length - 1;

                //add all of the bytes before and up to the end of the matched pattern to the result Bytes vector
                for(size_t byteItr = 0; byteItr <= endPos; ++byteItr)
                {
                    bytes.push_back(m_rawByteBuffer.front());
                    m_rawByteBuffer.pop_front();
                }

                return;
            }

            m_rawByteBufferCondition.wait_for(lock, std::chrono::milliseconds(timeout - timeWaited));

            // Update the timeout based on how long we just spent waiting.
            auto now = std::chrono::high_resolution_clock::now();
            timeWaited += std::chrono::duration_cast<std::chrono::milliseconds>(now - timepoint).count();
            timepoint = now;

        }
        while(timeWaited < timeout);
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::debugMode(bool enable)
    {
        //verify that we are actually changing the mode
        if(enable == m_debugMode) { return; }

        if(!m_established || !m_comm)
        {
            throw Error_Connection("Connection has been disconnected.");
        }

        //if we are enabling debug mode
        if(enable)
        {
            m_comm->enableDebugMode(std::bind(&Connection_Impl::collectDebugData, this, std::placeholders::_1, std::placeholders::_2));
        }
        else
        {
            m_comm->disableDebugMode();
        }

        m_debugMode = enable;
    }

    template <typename Comm_Object>
    bool Connection_Impl<Comm_Object>::debugMode()
    {
        return m_debugMode;
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::collectDebugData(const Bytes& data, bool isRead)
    {
        //create a scoped_lock for thread safety
        mutex_lock_guard lock(m_debugDataMutex);

        ConnectionDebugData debugData(isRead, data);

        m_debugDataBuffer.push_back(debugData);

        //notify any waiting functions that we have received data
        m_debugBufferCondition.notify_one();
    }

    template <typename Comm_Object>
    void Connection_Impl<Comm_Object>::getDebugData(ConnectionDebugDataVec& data, uint32 timeout)
    {
        //create a lock for thread safety
        std::unique_lock<std::mutex> lock(m_debugDataMutex);

        size_t debugDataSize = m_debugDataBuffer.size();

        //if we don't have any debug data in the buffer and the user specified a timeout
        if(debugDataSize == 0 && timeout > 0)
        {
            //wait for the timeout or data to come in
            m_debugBufferCondition.wait_for(lock, std::chrono::milliseconds(timeout));

            //update the debug data suze to our new size, if any
            debugDataSize = m_debugDataBuffer.size();
        }

        //set the result vector to the number of elements in the circular buffer
        data.reserve(debugDataSize);

        //add all of the bytes in the circular buffer to the Bytes vector
        for(size_t byteItr = 0; byteItr < debugDataSize; ++byteItr)
        {
            data.push_back(m_debugDataBuffer.front());
            m_debugDataBuffer.pop_front();
        }
    }
}