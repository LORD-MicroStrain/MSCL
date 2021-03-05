/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "mscl/Utils.h"
#include <string>

namespace mscl
{
    //Class: ByteStream
    //    A stream of bytes that is used to easily store and retrieve data 
    class ByteStream
    {
    public:
        //Constructor: ByteStream
        //    Default constructor to create a ByteStream object
        //
        //Parameters:
        //    bigEndian - Whether this ByteStream contains floating point data in big endian (true) or little endian(false) (default of true)
        ByteStream();

        //Constructor: ByteStream
        //    Constructor to create a ByteStream object, passing in the bytes to store in the stream
        //
        //Parameters:
        //    bytesToCopy - The vector of bytes to copy into the ByteStream
        //    bigEndian - Whether this ByteStream contains floating point data in big endian (true) or little endian(false) (default of true)
        explicit ByteStream(Bytes bytesToCopy);

        //Destructor: ~ByteStream
        //    Default destructor for the ByteStream object
        virtual ~ByteStream(){};

    private:
        //Variable: m_bytes
        //    The data stream object that holds all the bytes
        Bytes m_bytes;

    public:
        //Operator: []
        //    Accesses a single byte of the ByteStream
        //
        //Parameters:
        //    index - The 0-based index into the ByteStream
        //
        //Returns:
        //    The single byte in the ByteStream located at the requested index
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        //
        //See Also:
        //    <read_uint8>
        uint8& operator[] (const std::size_t index);
        const uint8& operator[] (const std::size_t index) const; 

        //Operator: ==
        //    Checks that two ByteStream objects are equal by comparing their data vectors
        //
        //Returns:
        //    true if the two ByteStreams are identical, false otherwise
        friend bool operator== (ByteStream& stream1, ByteStream& stream2);

    public:
        //Function: append_uint8
        //    Appends a 1-byte unsigned integer to the byte stream
        //
        //Parameters:
        //    value - The 1-byte uint8 to be added to the byte stream
        void append_uint8(uint8 value);

        //Function: append_int8
        //    Appends a 1-byte signed integer to the byte stream
        //
        //Parameters:
        //    value - The 1-byte int8 to be added to the byte stream
        //    endian - The <Utils::Endianness> to append the bytes in.
        void append_int8(int8 value);

        //Function: append_int16
        //    Appends a 2-byte signed integer to the byte stream
        //
        //Parameters:
        //    value - The 2-byte int16 to be added to the byte stream
        //    endian - The <Utils::Endianness> to append the bytes in.
        void append_int16(int16 value, Utils::Endianness endian=Utils::bigEndian);

        //Function: append_uint16
        //    Appends a 2-byte unsigned integer to the byte stream
        //
        //Parameters:
        //    value - The 2-byte uint16 to be added to the byte stream
        //    endian - The <Utils::Endianness> to append the bytes in.
        void append_uint16(uint16 value, Utils::Endianness endian = Utils::bigEndian);

        //Function: append_uint32
        //    Appends a 4-byte unsigned integer to the byte stream
        //
        //Parameters:
        //    value - The 4-byte uint32 to be added to the byte stream
        //    endian - The <Utils::Endianness> to append the bytes in.
        void append_uint32(uint32 value, Utils::Endianness endian = Utils::bigEndian);

        //Function: append_uint64
        //    Appends an 8-byte unsigned integer to the byte stream
        //
        //Parameters:
        //    value - The 8-byte uint64 to be added to the byte stream
        //    endian - The <Utils::Endianness> to append the bytes in.
        void append_uint64(uint64 value, Utils::Endianness endian = Utils::bigEndian);

        //Function: append_float
        //    Appends a 4-byte float to the byte stream
        //
        //Parameters:
        //    value - The 4-byte float to be added to the byte stream
        //    endian - The <Utils::Endianness> to append the bytes in.
        void append_float(float value, Utils::Endianness endian = Utils::bigEndian);

        //Function: append_double
        //    Appends an 8-byte double to the byte stream
        //
        //Parameters:
        //    value - The 8-byte double to be added to the byte stream
        //    endian - The <Utils::Endianness> to append the bytes in.
        void append_double(double value, Utils::Endianness endian = Utils::bigEndian);

        //Function: append_string
        //    Appends a string to the byte stream.
        //
        //Parameters:
        //    str - The string to append to the byte stream.
        void append_string(const std::string& str);

        //Function: appendBytes
        //    Appends a vector of bytes (uint8) to the end of the current ByteStream
        //
        //Parameters:
        //    bytes - The bytes to be appended to the byte stream
        void appendBytes(const Bytes& bytes);

        //Function: appendByteStream
        //    Appends the entire contents of a ByteStream to the end of the current ByteStream
        //
        //Parameters:
        //    otherStream - The ByteStream to be appended to the current ByteStream
        void appendByteStream(const ByteStream& otherStream);

        //Function: read_int8
        //    Reads a 1-byte signed integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //
        //Returns:
        //    The 1-byte int8 at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        int8 read_int8(std::size_t position) const;

        //Function: read_uint8
        //    Reads a 1-byte unsigned integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //
        //Returns:
        //    The 1-byte uint8 at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint8 read_uint8(std::size_t position) const;

        //Function: read_int16
        //    Reads a 2-byte signed integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The int16 at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        int16 read_int16(std::size_t position, Utils::Endianness endian = Utils::bigEndian) const;

        //Function: read_uint16
        //    Reads a 2-byte unsigned integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The uint16 at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint16 read_uint16(std::size_t position, Utils::Endianness endian = Utils::bigEndian) const;

        //Function: read_uint24
        //    Reads a 3-byte unsigned integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    A uint32 containing the uint24 value at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint32 read_uint24(std::size_t position, Utils::Endianness endian = Utils::bigEndian) const;

        //Function: read_int24
        //    Reads a 3-byte signed integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    An int32 containing the int24 value at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        int32 read_int24(std::size_t position, Utils::Endianness endian = Utils::bigEndian) const;

        //Function: read_uint32
        //    Reads a 4-byte unsigned integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The uint32 at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint32 read_uint32(std::size_t position, Utils::Endianness endian = Utils::bigEndian) const;

        //Function: read_uint64
        //    Reads an 8-byte unsigned integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The uint64 at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint64 read_uint64(std::size_t position, Utils::Endianness endian = Utils::bigEndian) const;

        //Function: read_float
        //    Reads a 4-byte float from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The float at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        float read_float(std::size_t position, Utils::Endianness endian = Utils::bigEndian) const;

        //Function: read_double
        //    Reads an 8-byte double from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The double at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        double read_double(std::size_t position, Utils::Endianness endian = Utils::bigEndian) const;

        //Function: read_string
        //    Reads a string of the specified length from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to start reading from
        //    length - The size (number of characters) to read for
        //
        //Returns:
        //    The string at the requested position of the requested length
        //
        //Exceptions:
        //    -std::out_of_range: The index + length requested is out of range
        std::string read_string(std::size_t position, std::size_t length) const;

        //Function: data
        //    Gets the byte stream as a vector of bytes (Bytes)
        //
        //Returns:
        //    The byte stream as a vector of bytes (Bytes)
        Bytes& data();

        //Function: data
        //    Gets the byte stream as a vector of bytes (Bytes)
        //
        //Returns:
        //    The byte stream as a vector of bytes (Bytes)
        const Bytes& data() const;

        //Function: size
        //    Gets the size of the byte stream (equivalent of std::vector.size())
        //
        //Returns:
        //    The size of the byte stream (number of bytes)
        std::size_t size() const;

        //Function: clear
        //    Clears the byte stream (equivalent of std::vector.clear())
        void clear();

        //Function: empty
        //    Checks whether the vector is empty. (equivalent of std::vector::empty())
        //
        //Returns:
        //    true if the vector is empty (size is 0), false otherwise.
        bool empty() const;

        //Function: resize
        //    Resizes the byte stream (equivalent of std::vector.resize())
        void resize(std::size_t size);

        //Function: set
        //    Sets the underlying bytes to the given <Bytes>. 
        void set(const Bytes& bytes);

        //Function: begin
        //    Gets an iterator referring to the first element in the ByteStream (equivalent of std::vector::begin())
        //
        //Returns:
        //    An iterator referring to the first element in the ByteStream
        Bytes::iterator begin();

        //Function: begin
        //    Gets a constant iterator referring to the first element in the ByteStream (equivalent of std::vector::cbegin())
        //
        //Returns:
        //    A const_iterator referring to the first element in the ByteStream
        Bytes::const_iterator begin() const;

        //Function: end
        //    Gets an iterator referring to the "past-the-end" element in the ByteStream. (equivalent of std::vector::end())
        //
        //Returns:
        //    An iterator referring to the "past-the-end" element in the ByteStream
        Bytes::iterator end();

        //Function: end
        //    Gets an iterator referring to the "past-the-end" element in the ByteStream. (equivalent of std::vector::cend())
        //
        //Returns:
        //    A const_iterator referring to the "past-the-end" element in the ByteStream
        Bytes::const_iterator end() const;

        //Function: calculateSimpleChecksum
        //    Calculates the simple checksum (simple addition of bytes)on the ByteStream
        //
        //Parameters:
        //    from - The 0-based starting position in the bytes vector to start calculating the checksum (includes this byte)
        //    to - The 0-based end position in the bytes vector to end calculating the checksum (includes this byte)
        //
        //Returns:
        //    The simple checksum (addition of bytes) of the ByteStream for the given positions.
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint16 calculateSimpleChecksum(std::size_t from, std::size_t to) const;

        //Function: calculateFletcherChecksum
        //    Calculates the Fletcher checksum (position dependent checksum) on the ByteStream
        //
        //Parameters:
        //    from - The 0-based starting position in the bytes vector to start calculating the checksum (includes this byte)
        //    to - The 0-based end position in the bytes vector to end calculating the checksum (includes this byte)
        //
        //Returns:
        //    The Fletcher checksum of the ByteStream for the given positions.
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint16 calculateFletcherChecksum(std::size_t from, std::size_t to) const;

        //Function: calculateCrcChecksum
        //  Calculates the 32-bit CRC with polynomial 0x04C11DB7, an initial value of 0xFFFFFFFF, and inverted output.
        //
        //Parameters:
        //    from - The 0-based starting position in the bytes vector to start calculating the checksum (includes this byte)
        //    to - The 0-based end position in the bytes vector to end calculating the checksum (includes this byte)
        //
        //Returns:
        //  The CRC checksum of the ByteStream for the given positions.
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint32 calculateCrcChecksum(std::size_t from, std::size_t to) const;

        //Function: calculateCrcChecksum
        //  Calculates the 32-bit CRC with polynomial 0x04C11DB7, an initial value of 0xFFFFFFFF, and inverted output.
        //
        //Returns:
        //  The CRC checksum of all bytes in the ByteStream.
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint32 calculateCrcChecksum() const;

    private:
        //Function: verifyBytesInStream
        //    Checks that the current bytestream can read the requested data
        //
        //Parameters:
        //    position - The 0-based start position that is desired to read data from
        //    length - The amount of bytes desired to read
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        void verifyBytesInStream(std::size_t position, std::size_t length) const;
    };

}