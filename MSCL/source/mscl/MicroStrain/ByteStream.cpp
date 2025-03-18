/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
    ByteStream::ByteStream()
    {
    }

    ByteStream::ByteStream(Bytes bytesToCopy) :
        m_bytes(bytesToCopy)
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

    //add a single byte to the bytestream
    void ByteStream::append_int8(int8 value)
    {
        m_bytes.push_back(static_cast<uint8>(value));
    }

    //add a WORD (2 bytes) to the bytestream
    void ByteStream::append_int16(int16 value, Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        uint8 low, high;

        Utils::split_int16(value, low, high, endian);

        m_bytes.push_back( low );
        m_bytes.push_back( high );
    }

    //add a WORD (2 bytes) to the bytestream
    void ByteStream::append_uint16(uint16 value, Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        uint8 low, high;

        Utils::split_uint16(value, low, high, endian);

        m_bytes.push_back(low);
        m_bytes.push_back(high);
    }

    //add a DWORD (4 bytes) to the bytestream
    void ByteStream::append_uint32(uint32 value, Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        uint8 b1, b2, b3, b4;

        //split the value into 4 bytes
        Utils::split_uint32(value, b1, b2, b3, b4, endian);

        m_bytes.push_back(b1);
        m_bytes.push_back(b2);
        m_bytes.push_back(b3);
        m_bytes.push_back(b4);
    }

    void ByteStream::append_uint64(uint64 value, Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        uint8 b1, b2, b3, b4, b5, b6, b7, b8;

        //split the value into 8 bytes
        Utils::split_uint64(value, b1, b2, b3, b4, b5, b6, b7, b8, endian);

        m_bytes.push_back(b1);
        m_bytes.push_back(b2);
        m_bytes.push_back(b3);
        m_bytes.push_back(b4);
        m_bytes.push_back(b5);
        m_bytes.push_back(b6);
        m_bytes.push_back(b7);
        m_bytes.push_back(b8);
    }

    //add a float (4 bytes) to the bytestream
    void ByteStream::append_float(float value, Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        uint8 b1, b2, b3, b4;

        //split the value into 4 bytes (system to user requested endian)
        Utils::split_float(value, b1, b2, b3, b4, endian);

        m_bytes.push_back(b1);
        m_bytes.push_back(b2);
        m_bytes.push_back(b3);
        m_bytes.push_back(b4);
    }

    //add a double (8 bytes) to the bytestream
    void ByteStream::append_double(double value, Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        uint8 b1, b2, b3, b4, b5, b6, b7, b8;

        //split the value into 8 bytes (system to user requested endian)
        Utils::split_double(value, b1, b2, b3, b4, b5, b6, b7, b8, endian);

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
    int16 ByteStream::read_int16(std::size_t position, Utils::Endianness endian /*= Utils::bigEndian*/) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 2);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);

        return Utils::make_int16(b1, b2, endian);
    }

    //read a WORD (2 bytes) from the bytestream
    uint16 ByteStream::read_uint16(std::size_t position, Utils::Endianness endian /*= Utils::bigEndian*/) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 2);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);

        return Utils::make_uint16(b1, b2, endian);
    }

    uint32 ByteStream::read_uint24(std::size_t position, Utils::Endianness endian /*= Utils::bigEndian*/) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 3);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);
        uint8 b3 = m_bytes.at(position + 2);

        if(endian == Utils::bigEndian)
        {
            //build a uint32 from the 3 bytes
            return Utils::make_uint32(0, b1, b2, b3, endian);
        }
        else
        {
            //build a uint32 from the 3 bytes
            return Utils::make_uint32(b1, b2, b3, 0, endian);
        }
    }

    int32 ByteStream::read_int24(std::size_t position, Utils::Endianness endian /*= Utils::bigEndian*/) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 3);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);
        uint8 b3 = m_bytes.at(position + 2);

        if(endian == Utils::bigEndian)
        {
            //if negative
            if(Utils::bitIsSet(b1, 7))
            {
                //build an int32 from the 3 bytes (flip the upper bytes to make negative)
                return Utils::make_int32(0xFF, b1, b2, b3, endian);
            }
            else
            {
                //build an int32 from the 3 bytes (flip the upper bytes to make negative)
                return Utils::make_int32(0x00, b1, b2, b3, endian);
            }
        }
        else
        {
            //if negative
            if(Utils::bitIsSet(b3, 7))
            {
                //build an int32 from the 3 bytes (flip the upper bytes to make negative)
                return Utils::make_int32(b1, b2, b3, 0xFF, endian);
            }
            else
            {
                //build an int32 from the 3 bytes (flip the upper bytes to make negative)
                return Utils::make_int32(b1, b2, b3, 0x00, endian);
            }
        }
    }

    //read a DWORD (4 bytes) from the bytestream
    uint32 ByteStream::read_uint32(std::size_t position, Utils::Endianness endian /*= Utils::bigEndian*/) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 4);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);
        uint8 b3 = m_bytes.at(position + 2);
        uint8 b4 = m_bytes.at(position + 3);

        return Utils::make_uint32(b1, b2, b3, b4, endian);
    }

    uint64 ByteStream::read_uint64(std::size_t position, Utils::Endianness endian /*= Utils::bigEndian*/) const
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

        return Utils::make_uint64(b1, b2, b3, b4, b5, b6, b7, b8, endian);
    }

    //read a float (4 bytes) from the bytestream
    float ByteStream::read_float(std::size_t position, Utils::Endianness endian /*= Utils::bigEndian*/) const
    {
        //verify that the position being asked for is in range
        verifyBytesInStream(position, 4);

        uint8 b1 = m_bytes.at(position);
        uint8 b2 = m_bytes.at(position + 1);
        uint8 b3 = m_bytes.at(position + 2);
        uint8 b4 = m_bytes.at(position + 3);

        //convert the bytes to a system endian float
        return Utils::make_float(b1, b2, b3, b4, endian);
    }

    double ByteStream::read_double(std::size_t position, Utils::Endianness endian /*= Utils::bigEndian*/) const
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

        //convert the bytes to a system endian double
        return Utils::make_double(b1, b2, b3, b4, b5, b6, b7, b8, endian);
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

    bool ByteStream::empty() const
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

    Bytes::const_iterator ByteStream::begin() const
    {
        return m_bytes.cbegin();
    }

    Bytes::iterator ByteStream::end()
    {
        return m_bytes.end();
    }

    Bytes::const_iterator ByteStream::end() const
    {
        return m_bytes.cend();
    }

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
        finalChecksum = (static_cast<uint16>(checksumByte1) << 8) | static_cast<uint16>(checksumByte2);

        return finalChecksum;
    }

    uint32 ByteStream::calculateCrcChecksum(std::size_t from, std::size_t to) const
    {
        assert(from < to);                //Start position is after the End position

        std::size_t numBytesToRead = (to + 1) - from;

        //check for out of bounds
        verifyBytesInStream(from, numBytesToRead);

        boost::crc_32_type crc;
        crc.process_bytes((m_bytes.data() + from), numBytesToRead);
        return crc.checksum();
    }

    uint32 ByteStream::calculateCrcChecksum() const
    {
        return calculateCrcChecksum(0, size() - 1);
    }

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
