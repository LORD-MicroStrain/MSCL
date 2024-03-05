/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

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
        assert(m_readPosition <= m_appendPosition);

        return result;
    }

    std::size_t DataBuffer::appendPosition() const
    {
        return m_appendPosition;
    }

    std::size_t DataBuffer::readPosition() const
    {
        return m_readPosition;
    }

    uint8 DataBuffer::peekByte()
    {
        static const std::size_t READ_SIZE = 1;

        if(bytesRemaining() < READ_SIZE)
        {
            throw(std::out_of_range("No Data to read in buffer (peekByte)"));
        }

        //read the next byte in the buffer
        uint8 result = m_data.read_uint8(m_readPosition);

        //return the byte read
        return result;
    }

    void DataBuffer::skipBytes(std::size_t numBytesToSkip)
    {
        m_readPosition += numBytesToSkip;
    }

    int8 DataBuffer::read_int8()
    {
        static const std::size_t READ_SIZE = 1;

        if(bytesRemaining() < READ_SIZE)
        {
            throw(std::out_of_range("No data to read in buffer (read_int8)"));
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
        static const std::size_t READ_SIZE = 1;

        if(bytesRemaining() < READ_SIZE)
        {
            throw(std::out_of_range("No data to read in buffer (read_uint8)"));
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
        static const std::size_t READ_SIZE = 2;

        if(bytesRemaining() < READ_SIZE)
        {
            throw(std::out_of_range("No data to read in buffer (read_int16)"));
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
        static const std::size_t READ_SIZE = 2;

        if(bytesRemaining() < READ_SIZE)
        {
            throw(std::out_of_range("No data to read in buffer (read_uint16)"));
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
        static const std::size_t READ_SIZE = 4;

        if(bytesRemaining() < READ_SIZE)
        {
            throw(std::out_of_range("No data to read in buffer (read_uint32)"));
        }

        //read the next dword in the buffer
        uint32 result = m_data.read_uint32(m_readPosition);

        //read a dword, so move the position 4 bytes
        m_readPosition += READ_SIZE;

        //return the dword read
        return result;
    }

    uint64 DataBuffer::read_uint64()
    {
        static const std::size_t READ_SIZE = 8;

        if(bytesRemaining() < READ_SIZE)
        {
            throw(std::out_of_range("No data to read in buffer (read_uint64)"));
        }

        //read the next dword in the buffer
        uint64 result = m_data.read_uint64(m_readPosition);

        //read a dword, so move the position 4 bytes
        m_readPosition += READ_SIZE;

        //return the dword read
        return result;
    }

    float DataBuffer::read_float()
    {
        static const std::size_t READ_SIZE = 4;

        if(bytesRemaining() < READ_SIZE)
        {
            throw(std::out_of_range("No data to read in buffer (read_float)"));
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
        static const std::size_t READ_SIZE = 8;

        if(bytesRemaining() < READ_SIZE)
        {
            throw(std::out_of_range("No data to read in buffer (read_double)"));
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
            throw(std::out_of_range("No data to read in buffer (read_string)"));
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

    std::size_t DataBuffer::shiftExtraToStart()
    {
        std::size_t startReadPos = m_readPosition;

        //the number of extra bytes that need to be moved
        std::size_t numExtraBytes = m_appendPosition - m_readPosition;

        //if there is data that needs to be moved (appended to buffer, but not read in completely)
        //and we wouldn't just be copying to the same position
        if(numExtraBytes > 0 && m_readPosition != 0)
        {
            //copy any extra data back to the beginning of the buffer
            std::copy(m_data.begin() + m_readPosition, m_data.begin() + m_appendPosition, m_data.begin());
        }

        //reset the read position back to position 0
        m_readPosition = 0;

        //reset the append position to immediately after the bytes we just put at the beginning of the buffer
        m_appendPosition = numExtraBytes;

        return startReadPos;
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
        return BufferWriter(writeBuffer,
                            writeBufferSize,
                            &m_appendPosition);
    }

    void DataBuffer::resetBuffer()
    {
        m_appendPosition = 0;
        m_readPosition = 0;
    }

    Bytes DataBuffer::bytesToRead() const
    {
        Bytes result;

        //push all the bytes in the buffer into the circular buffer
        for(size_t byteItr = m_readPosition; byteItr < m_appendPosition; ++byteItr)
        {
            result.push_back(m_data.read_uint8(byteItr));
        }

        return result;
    }

    Bytes DataBuffer::bytesToRead(std::size_t startPos, std::size_t size) const
    {
        return Bytes(m_data.begin() + startPos, m_data.begin() + startPos + size);
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
