/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#include "stdafx.h"
#include "DataBuffer.h"
#include <assert.h>

namespace mscl
{
	BufferWriter::BufferWriter(uint8* buffer, std::size_t size, std::size_t* offset) : 
		  m_buffer(buffer),
		  m_size(size),
		  m_writeOffset(offset)
	{}

	uint8* BufferWriter::buffer() 
	{ 
		return m_buffer; 
	}

	std::size_t BufferWriter::size() 
	{ 
		return m_size; 
	}

	void BufferWriter::commit(std::size_t numBytesAdded) 
	{ 
		//move the position of the underlying DataBuffer's write offset (append position)
		*m_writeOffset += numBytesAdded; 
	}




	DataBuffer::DataBuffer(uint32 size) :
		m_appendPosition(0),
		m_readPosition(0)
	{
		m_data.resize(size);
	}

	DataBuffer::DataBuffer(const Bytes& data) :
		m_data(data),
		m_appendPosition(data.size()),
		m_readPosition(0)
	{
	}

	DataBuffer::DataBuffer(const ByteStream& data) :
		m_data(data),
		m_appendPosition(data.size()),
		m_readPosition(0)
	{
	}

	DataBuffer::~DataBuffer()
	{
	}

	std::size_t DataBuffer::size() const
	{
		return m_data.size();
	}

	std::size_t DataBuffer::bytesRemaining() const
	{
		std::size_t result = (m_appendPosition - m_readPosition);

		//make sure not negative
		assert(result >= 0);

		return result;
	}

	uint8 DataBuffer::peekByte()
	{
		static const uint32 READ_SIZE = 1;

		if(bytesRemaining() < READ_SIZE)
		{
			throw(std::out_of_range("No Data to read in buffer"));
		}

		//read the next byte in the buffer
		uint8 result = m_data.read_uint8(m_readPosition);

		//return the byte read
		return result;
	}

	int8 DataBuffer::read_int8()
	{
		static const uint32 READ_SIZE = 1;

		if(bytesRemaining() < READ_SIZE)
		{
			throw(std::out_of_range("No data to read in buffer"));
		}

		//read the next byte in the buffer
		int8 result = m_data.read_int8(m_readPosition);

		//read a byte, so move the position 1 byte
		m_readPosition += READ_SIZE;

		//return the byte read
		return result;
	}

	uint8 DataBuffer::read_uint8()
	{
		static const uint32 READ_SIZE = 1;

		if(bytesRemaining() < READ_SIZE)
		{
			throw(std::out_of_range("No data to read in buffer"));
		}

		//read the next byte in the buffer
		uint8 result = m_data.read_uint8(m_readPosition);

		//read a byte, so move the position 1 byte
		m_readPosition += READ_SIZE;

		//return the byte read
		return result;
	}

	int16 DataBuffer::read_int16()
	{
		static const uint32 READ_SIZE = 2;

		if(bytesRemaining() < READ_SIZE)
		{
			throw(std::out_of_range("No data to read in buffer"));
		}

		//read the next byte in the buffer
		int16 result = m_data.read_int16(m_readPosition);

		//read a byte, so move the position 2 bytes
		m_readPosition += READ_SIZE;

		//return the byte read
		return result;
	}

	uint16 DataBuffer::read_uint16()
	{
		static const uint32 READ_SIZE = 2;

		if(bytesRemaining() < READ_SIZE)
		{
			throw(std::out_of_range("No data to read in buffer"));
		}

		//read the next 2-byte word in the buffer
		uint16 result = m_data.read_uint16(m_readPosition);

		//read a word, so move the position 2 bytes
		m_readPosition += READ_SIZE;

		//return the word read
		return result;
	}

	uint32 DataBuffer::read_uint32()
	{
		static const uint32 READ_SIZE = 4;

		if(bytesRemaining() < READ_SIZE)
		{
			throw(std::out_of_range("No data to read in buffer"));
		}

		//read the next dword in the buffer
		uint32 result = m_data.read_uint32(m_readPosition);

		//read a dword, so move the position 4 bytes
		m_readPosition += READ_SIZE;

		//return the dword read
		return result;
	}

	float DataBuffer::read_float()
	{
		static const uint32 READ_SIZE = 4;

		if(bytesRemaining() < READ_SIZE)
		{
			throw(std::out_of_range("No data to read in buffer"));
		}

		//read the next dword in the buffer
		float result = m_data.read_float(m_readPosition);

		//read a dword, so move the position 4 bytes
		m_readPosition += READ_SIZE;

		//return the dword read
		return result;
	}

	double DataBuffer::read_double()
	{
		static const uint32 READ_SIZE = 8;

		if(bytesRemaining() < READ_SIZE)
		{
			throw(std::out_of_range("No data to read in buffer"));
		}

		//read the next dword in the buffer
		double result = m_data.read_double(m_readPosition);

		//read a dword, so move the position 4 bytes
		m_readPosition += READ_SIZE;

		//return the dword read
		return result;
	}

	std::string DataBuffer::read_string(std::size_t length)
	{
		if(bytesRemaining() < length)
		{
			throw(std::out_of_range("No data to read in buffer"));
		}

		//read the string in the buffer
		std::string result = m_data.read_string(m_readPosition, length);

		//read the string, so move the position the correct number of bytes
		m_readPosition += length;

		//return the string read
		return result;
	}

	bool DataBuffer::moreToRead() const
	{
		return (bytesRemaining() > 0);
	}

	void DataBuffer::shiftExtraToStart()
	{
		//the number of extra bytes that need to be moved
		std::size_t numExtraBytes = m_appendPosition - m_readPosition;

		//if there is data that needs to be moved (appended to buffer, but not read in completely)
		if(numExtraBytes > 0)
		{
			//copy any extra data back to the beginning of the buffer
			std::copy(m_data.begin() + m_readPosition, m_data.begin() + m_appendPosition, m_data.begin());
			//std::copy(&m_data[m_readPosition], &m_data[m_appendPosition], m_data.begin());
		}

		//reset the read position back to position 0
		m_readPosition = 0;

		//reset the append position to immediately after the bytes we just put at the beginning of the buffer
		m_appendPosition = numExtraBytes;
	}

	BufferWriter DataBuffer::getBufferWriter()
	{
		uint8* writeBuffer = NULL;
		std::size_t writeBufferSize;

		std::size_t totalSize = size();

		//if there is no room to append to this DataBuffer
		if(m_appendPosition >= totalSize)
		{
			writeBuffer = NULL;
			writeBufferSize = 0;
		}
		else
		{
			writeBuffer = &m_data[m_appendPosition];
			writeBufferSize = totalSize - m_appendPosition;
		}

		//create a BufferWriter using the current DataBuffer's information
		return BufferWriter(	writeBuffer, 
								writeBufferSize,
								&m_appendPosition
							);
	}

	void DataBuffer::resetBuffer()
	{
		m_appendPosition = 0;
		m_readPosition = 0;
	}

	//============================================================
	//ReadBufferSavePoint Methods
	ReadBufferSavePoint::ReadBufferSavePoint(DataBuffer* data) :
		m_data(data),
		m_savePosition(data->m_readPosition)
	{
	}

	ReadBufferSavePoint::~ReadBufferSavePoint()
	{
		//revert any read data when this save point is destroyed
		revert();
	}

	void ReadBufferSavePoint::revert()
	{
		//revert the data's read position back to the save position of this save point
		m_data->m_readPosition = m_savePosition;
	}

	void ReadBufferSavePoint::commit()
	{
		//set the save position to the data's current read position
		m_savePosition = m_data->m_readPosition;
	}
}