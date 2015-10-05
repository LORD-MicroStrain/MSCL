/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once
#include <boost/asio.hpp>
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
	//Class: BoostCommunication
	//	The BoostCommunication object that is used for actual read/write communication for all Connection objects
	template <typename IO_Object>
	class BoostCommunication
	{
	private:
		static const int ERROR_CODE_CONNECTION_RESET = 10054;
		static const int ERROR_CODE_IO_ABORTED = 995;
		static const int ERROR_CODE_DEVICE_NOT_RECOGNIZED = 22;

	public:
		//Constructor: BoostCommunication
		//	Initializes the BoostCommunication object
		//	
		//Parameters:
		//	ioService - boost io_service
		//	ioObj - boost io_object passed (Template)
		BoostCommunication(std::unique_ptr<boost::asio::io_service> ioService, std::unique_ptr<IO_Object> ioObj);

		//Destructor: ~BoostCommunication
		//	Destroys the BoostCommunication object
		~BoostCommunication();

	private:
		BoostCommunication();										//default constructor disabled
		BoostCommunication(const BoostCommunication&);				//copy constructor disabled
		BoostCommunication& operator=(const BoostCommunication&);	//assignment operator disabled

	private:
		//Variable: m_ioService
		//	Boost io_service needed in communication
		std::unique_ptr<boost::asio::io_service> m_ioService;

		//Variable: m_ioObject
		//	Boost io_object used to communicate (serial_port, ip::tcp::socket, etc.)
		std::unique_ptr<IO_Object> m_ioObject;

		//Variable: m_readBuffer
		//	The <DataBuffer> to hold all the bytes read in
		DataBuffer m_readBuffer;

		//Variable: m_bufferWriter
		//	The <BufferWriter> used to write bytes to the <DataBuffer>
		BufferWriter m_bufferWriter;

		//Variable: m_parseDataFunction
		//	The function to send all the read in data to. If null, the data will be thrown out.
		std::function<void(DataBuffer&)> m_parseDataFunction;

		//Variable: m_parseFunctionMutex
		//	The mutex used to access/change the parse data function.
		std::recursive_mutex m_parseFunctionMutex;

	public:
		//Function: write
		//	Uses boost to write bytes to the io_object. Blocks until the write completes
		//
		//Parameters:
		//	data - the bytes to be written
		void write(const std::vector<uint8>& data) const;

		//Function: clearBuffer
		//	Clears the read buffer.
		void clearBuffer();

		//Function: startReadLoop
		//	Starts the main read loop that reads in all data using boost
		//
		//Returns:
		//	The ByteStream object holding the read in bytes
		void startReadLoop();

		//Function: readSome
		//	Performs the actual port read of bytes.
		void readSome();

		//Function: readLoopHandler
		//	The read handler for the read loop, called when data comes in or the read operation has been canceled
		//	
		//Parameters:
		//	error - boost error code
		//	bytes_transferred - number of bytes read in
		//
		//Exceptions:
		//	Error_Connection - I/O error occurred, the I/O service has been stopped
		void readLoopHandler(const boost::system::error_code &error, std::size_t bytes_transferred);

		//Function: stopIoService
		//	Stops the current boost::asio::io_service so no more reads or writes will happen
		void stopIoService();

		//Function: stopIoServiceError
		//	Stops the current boost::asio::io_service due to an error
		void stopIoServiceError(int errorCode);

		//Function: setParseFunction
		//	Sets the function to be called when data is read in.
		//
		//Parameters:
		//	fn - The function to set as the parser function.
		void setParseFunction(std::function<void(DataBuffer&)> fn);
	};


	//Constructor
	template <typename IO_Object>
	BoostCommunication<IO_Object>::BoostCommunication(std::unique_ptr<boost::asio::io_service> ioService, std::unique_ptr<IO_Object> ioObj):
		m_ioService(std::move(ioService)),
		m_ioObject(std::move(ioObj)),
		m_readBuffer(1024 * 1000),
		m_bufferWriter(m_readBuffer.getBufferWriter()),
		m_parseDataFunction(nullptr)
	{
	}

	template <typename IO_Object>
	BoostCommunication<IO_Object>::~BoostCommunication()
	{
		//need to destroy the serial_port object BEFORE the io_service object, or else an access violation will occur
		m_ioObject.reset();
		m_ioService.reset();
	}

	template <typename IO_Object>
	//write function that uses boost to write to io_object
	void BoostCommunication<IO_Object>::write(const std::vector<uint8>& data) const
	{
		try
		{
			//write all the data (blocks until all is written)
			boost::asio::write(
				*m_ioObject,										//the ioObject (serial_port)
				boost::asio::buffer(data, data.size()));			//the buffer that contains the data to be written;	
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
	void BoostCommunication<IO_Object>::setParseFunction(std::function<void(DataBuffer&)> fn)
	{
		//for thread safety
		rec_mutex_lock_guard lock(m_parseFunctionMutex);

		m_parseDataFunction = fn;
	}

	template <typename IO_Object>
	void BoostCommunication<IO_Object>::startReadLoop()
	{
		m_ioService->reset();

		//get the BufferWriter for our current read buffer
		m_bufferWriter = m_readBuffer.getBufferWriter();

		//perform the actual port read
		readSome();

		try
		{
			//start the async_read operation
			m_ioService->run();
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
			boost::asio::buffer(m_bufferWriter.buffer(), m_bufferWriter.size()),		//the buffer that will be filled with data
			std::bind(&BoostCommunication::readLoopHandler, this,	//the read handler function
			std::placeholders::_1,		//error
			std::placeholders::_2));	//bytes_transferred
	}

	template <typename IO_Object>
	void BoostCommunication<IO_Object>::stopIoService()
	{
		m_ioService->post([]() { throw Error_Connection("Stopping Data Thread."); });
	}

	template <typename IO_Object>
	void BoostCommunication<IO_Object>::stopIoServiceError(int errorCode)
	{
		m_ioService->post([&errorCode]() { throw Error_Connection(errorCode); });
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

			if(m_parseDataFunction)
			{
				//commit any bytes that were read
				m_bufferWriter.commit(bytes_transferred);

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