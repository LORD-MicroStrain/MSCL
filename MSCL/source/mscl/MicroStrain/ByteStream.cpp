/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "ByteStream.h"
#include "mscl/Utils.h"

#include <numeric>    //for std::accumulate

namespace mscl
{
    ByteStream::ByteStream(bool bigEndian):
        m_bigEndian(bigEndian)
    {
    }

    ByteStream::ByteStream(Bytes bytesToCopy, bool bigEndian):
        m_bytes(bytesToCopy),
        m_bigEndian(bigEndian)
    {
    }

    //byte access operator
    uint8& ByteStream::operator [](const std::size_t index)
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(index, 1);

        return m_bytes[index];
    }

    const uint8& ByteStream::operator [](const std::size_t index) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(index, 1);

        return m_bytes[index];
    }

    //compares two byte streams to see if they are equal
    bool operator ==(ByteStream& stream1, ByteStream& stream2)
    {
        return stream1.data() == stream2.data();
    }

    //add a single byte to the bytestream
    void ByteStream::append_uint8(uint8 value)
    {
        m_bytes.push_back(value);
    }

    //add a WORD (2 bytes) to the bytestream
    void ByteStream::append_int16(int16 value)
    {
        m_bytes.push_back( Utils::msb(value) );
        m_bytes.push_back( Utils::lsb(value) );
    }

    //add a WORD (2 bytes) to the bytestream
    void ByteStream::append_uint16(uint16 value)
    {
        m_bytes.push_back( Utils::msb(value) );
        m_bytes.push_back( Utils::lsb(value) );
    }

    //add a DWORD (4 bytes) to the bytestream
    void ByteStream::append_uint32(uint32 value)
    {
        uint8 b1, b2, b3, b4;
         
        //split the value into 4 bytes
        Utils::split_uint32(value, b1, b2, b3, b4);

        m_bytes.push_back(b1);
        m_bytes.push_back(b2);
        m_bytes.push_back(b3);
        m_bytes.push_back(b4);
    }

    //add a float (4 bytes) to the bytestream
    void ByteStream::append_float(float value)
    {
        uint8 b1, b2, b3, b4;

        //if the ByteStream has big endian floats
        if(m_bigEndian)
        {
            //split the value into 4 bytes (system to big endian)
            Utils::split_float_big_endian(value, b1, b2, b3, b4);
        }
        else
        {
            //split the value into 4 bytes (system to little endian)
            Utils::split_float_little_endian(value, b1, b2, b3, b4);
        }

        m_bytes.push_back(b1);
        m_bytes.push_back(b2);
        m_bytes.push_back(b3);
        m_bytes.push_back(b4);
    }

    //add a double (8 bytes) to the bytestream
    void ByteStream::append_double(double value)
    {
        uint8 b1, b2, b3, b4, b5, b6, b7, b8;

        //if the ByteStream has big endian doubles
        if(m_bigEndian)
        {
            //split the value into 8 bytes (system to big endian)
            Utils::split_double_big_endian(value, b1, b2, b3, b4, b5, b6, b7, b8);
        }
        else
        {
            //split the value into 8 bytes (system to little endian)
            Utils::split_double_little_endian(value, b1, b2, b3, b4, b5, b6, b7, b8);
        }

        m_bytes.push_back(b1);
        m_bytes.push_back(b2);
        m_bytes.push_back(b3);
        m_bytes.push_back(b4);
        m_bytes.push_back(b5);
        m_bytes.push_back(b6);
        m_bytes.push_back(b7);
        m_bytes.push_back(b8);
    }

    void ByteStream::append_string(const std::string& str)
    {
        m_bytes.insert(m_bytes.end(), str.begin(), str.end());
    }

    void ByteStream::appendBytes(const Bytes& bytes)
    {
        m_bytes.insert(m_bytes.end(), bytes.begin(), bytes.end());
    }

    //appends the entire contents of a bytestream of the end of another bytestream
    void ByteStream::appendByteStream(const ByteStream& otherStream)
    {
        const Bytes& data = otherStream.data();

        m_bytes.insert(m_bytes.end(), data.begin(), data.end());
    }

    int8 ByteStream::read_int8(std::size_t position) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 1);

        return static_cast<int8>(m_bytes.at(position));
    }

    //reads 1 BYTE from the bytestream
    uint8 ByteStream::read_uint8(std::size_t position) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 1);

        return m_bytes.at(position);
    }

    //read a WORD (2 bytes) from the bytestream
    int16 ByteStream::read_int16(std::size_t position) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 2);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);

        return Utils::make_int16(b1, b2);
    }

    //read a WORD (2 bytes) from the bytestream
    uint16 ByteStream::read_uint16(std::size_t position) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 2);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);

        return Utils::make_uint16(b1, b2);
    }

    //read a DWORD (4 bytes) from the bytestream
    uint32 ByteStream::read_uint32(std::size_t position) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 4);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);
        uint8 b3 = m_bytes.at(position + 2);
        uint8 b4 = m_bytes.at(position + 3);

        return Utils::make_uint32(b1, b2, b3, b4);
    }

    //read a float (4 bytes) from the bytestream
    float ByteStream::read_float(std::size_t position) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 4);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);
        uint8 b3 = m_bytes.at(position + 2);
        uint8 b4 = m_bytes.at(position + 3);

        //if the ByteStream contains big endian floats
        if(m_bigEndian)
        {
            //convert the big endian bytes to a system endian float
            return Utils::make_float_big_endian(b1, b2, b3, b4);
        }
        else
        {
            //convert the little endian bytes to a system endian float
            return Utils::make_float_little_endian(b1, b2, b3, b4);
        }
    }

    double ByteStream::read_double(std::size_t position) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 8);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);
        uint8 b3 = m_bytes.at(position + 2);
        uint8 b4 = m_bytes.at(position + 3);
        uint8 b5 = m_bytes.at(position + 4);
        uint8 b6 = m_bytes.at(position + 5);
        uint8 b7 = m_bytes.at(position + 6);
        uint8 b8 = m_bytes.at(position + 7);

        //if the ByteStream contains big endian floats
        if(m_bigEndian)
        {
            //convert the big endian bytes to a system endian double
            return Utils::make_double_big_endian(b1, b2, b3, b4, b5, b6, b7, b8);
        }
        else
        {
            //convert the little endian bytes to a system endian double
            return Utils::make_double_little_endian(b1, b2, b3, b4, b5, b6, b7, b8);
        }
    }

    std::string ByteStream::read_string(std::size_t position, std::size_t length) const
    {
        //verify that the position + length being asked for is in range
        verifyBytesInStream(position, length);

        //find the start and end iterators
        Bytes::const_iterator start = m_bytes.begin() + position;
        Bytes::const_iterator end = start + length;

        //build a string from the bytes
        return std::string(start, end);
    }

    //Gets the byte stream as a vector of bytes (Bytes)
    Bytes& ByteStream::data()
    {
        return m_bytes;
    }

    const Bytes& ByteStream::data() const
    {
        return m_bytes;
    }

    //Gets the size of the byte stream (equivalent of std::vector.size())
    std::size_t ByteStream::size() const
    {
        return m_bytes.size();
    }

    void ByteStream::clear()
    {
        m_bytes.clear();
    }

    bool ByteStream::empty()
    {
        return m_bytes.empty();
    }

    //Resizes the byte stream (equivalent of std::vector.resize())
    void ByteStream::resize(std::size_t size)
    {
        m_bytes.resize(size);
    }

    void ByteStream::set(const Bytes& bytes)
    {
        m_bytes = bytes;
    }

    Bytes::iterator ByteStream::begin()
    {
        return m_bytes.begin();
    }

    Bytes::iterator ByteStream::end()
    {
        return m_bytes.end();
    }

    //Function: calculateSimpleChecksum
    //    Calculates the simple checksum (simple addition of bytes) of the current bytestream
    uint16 ByteStream::calculateSimpleChecksum(std::size_t from, std::size_t to) const
    {
        assert(from <= to);                //Start position is after the End position
        
        std::size_t numBytesToRead = (to + 1) - from;

        //check for out of bounds
        verifyBytesInStream(from, numBytesToRead);

        uint16 startValue = 0;

        //add up all the bytes requested
        uint16 checksum = std::accumulate(m_bytes.begin() + from, m_bytes.begin() + to + 1, startValue);

        return checksum;
    }

    //Function: calculateFletcherChecksum
    //    Calculates the Fletcher checksum (position dependent checksum) of the current bytestream
    uint16 ByteStream::calculateFletcherChecksum(std::size_t from, std::size_t to) const
    {
        assert(from < to);                //Start position is after the End position

        std::size_t numBytesToRead = (to + 1) - from;

        //check for out of bounds
        verifyBytesInStream(from, numBytesToRead);

        uint8 checksumByte1 = 0;
        uint8 checksumByte2 = 0;
        uint16 finalChecksum;

        //loop through the bytes vector
        for(std::size_t byteItr = from; byteItr <= to; byteItr++)
        {
            //add the current value to the first checksum byte
            checksumByte1 += m_bytes.at(byteItr);

            //add the current sum of the bytes to checksumByte2
            checksumByte2 += checksumByte1;
        }

        //get the final checksum from the 2 bytes
        finalChecksum = Utils::make_uint16(checksumByte1, checksumByte2);

        return finalChecksum;
    }

    //verifyBytesInStream
    //verifies that the position asked for exists in the ByteStream
    void ByteStream::verifyBytesInStream(std::size_t position, std::size_t length) const
    {
        //the last position we need to check for given the asking position and length
        std::size_t endPosition = position + (length - 1);

        //if the position being asked for is out of range of the bytestream
        if(endPosition >= m_bytes.size())
        {
            throw std::out_of_range("The requested position is out of range");
        }
    }
}