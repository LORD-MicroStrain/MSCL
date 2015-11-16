/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include "mscl/Types.h"
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
        ByteStream(bool bigEndian=true);

        //Constructor: ByteStream
        //    Constructor to create a ByteStream object, passing in the bytes to store in the stream
        //
        //Parameters:
        //    bytesToCopy - The vector of bytes to copy into the ByteStream
        //    bigEndian - Whether this ByteStream contains floating point data in big endian (true) or little endian(false) (default of true)
        explicit ByteStream(Bytes bytesToCopy, bool bigEndian=true);

        //Destructor: ~ByteStream
        //    Default destructor for the ByteStream object
        virtual ~ByteStream(){};

    private:
        //Variable: m_bytes
        //    The data stream object that holds all the bytes
        Bytes m_bytes;

        //Variable: m_bigEndian
        //    Whether the ByteStream is big endian (true) or little endian (false)
        bool m_bigEndian;

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

        //Function: append_int16
        //    Appends a 2-byte signed integer to the byte stream
        //
        //Parameters:
        //    value - The 2-byte int16 to be added to the byte stream
        void append_int16(int16 value);

        //Function: append_uint16
        //    Appends a 2-byte unsigned integer to the byte stream
        //
        //Parameters:
        //    value - The 2-byte uint16 to be added to the byte stream
        void append_uint16(uint16 value);

        //Function: append_uint32
        //    Appends a 4-byte unsigned integer to the byte stream
        //
        //Parameters:
        //    value - The 4-byte uint32 to be added to the byte stream
        void append_uint32(uint32 value);

        //Function: append_float
        //    Appends a 4-byte float to the byte stream
        //
        //Parameters:
        //    valye - The 4-byte float to be added to the byte stream
        void append_float(float value);

        //Function: append_double
        //    Appends an 8-byte double to the byte stream
        //
        //Parameters:
        //    valye - The 8-byte double to be added to the byte stream
        void append_double(double value);

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
        //
        //Returns:
        //    The int16 at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        int16 read_int16(std::size_t position) const;

        //Function: read_uint16
        //    Reads a 2-byte unsigned integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //
        //Returns:
        //    The uint16 at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint16 read_uint16(std::size_t position) const;

        //Function: read_uint32
        //    Reads a 4-byte unsigned integer from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //
        //Returns:
        //    The uint32 at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint32 read_uint32(std::size_t position) const;

        //Function: read_float
        //    Reads a 4-byte float from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //
        //Returns:
        //    The float at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        float read_float(std::size_t position) const;

        //Function: read_double
        //    Reads an 8-byte double from the byte stream
        //
        //Parameters:
        //    position - The 0-based position to read from
        //
        //Returns:
        //    The double at the requested position
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        double read_double(std::size_t position) const;

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
        bool empty();

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

        //Function: end
        //    Gets an iterator referring to the "past-the-end" element in the ByteStream. (equivalent of std::vector::begin())
        //
        //Returns:
        //    An iterator referring to the "past-the-end" element in the ByteStream
        Bytes::iterator end();

        //Function: calculateSimpleChecksum
        //    Calculates the simple checksum (simple addition of bytes)on the ByteStream
        //
        //Parameters:
        //    from - The 0-based starting position in the bytes vector to start calculating the checksum (includes this byte)
        //    to - The 0-based end position in the bytes vector to end calculating the checksum (includes this byte)
        //
        //Returns:
        //    The simple checksum (addition of bytes) of the ByteStream
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
        //    The Fletcher checksum of the ByteStream
        //
        //Exceptions:
        //    - std::out_of_range: The index requested is out of range
        uint16 calculateFletcherChecksum(std::size_t from, std::size_t to) const;

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