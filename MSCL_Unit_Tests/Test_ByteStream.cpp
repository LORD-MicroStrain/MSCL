/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>
#include <turtle/mock.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(ByteStream_Test)

//===================================================================================================================
//                                                ByteStream Operators
//===================================================================================================================
BOOST_AUTO_TEST_SUITE(ByteStream_Operators)

BOOST_AUTO_TEST_CASE(ByteStream_BytesConstructorAtOperator)
{
    //build the data to send to the ByteStream copy constructor
    Bytes dataToCopy;
    dataToCopy.push_back(1);
    dataToCopy.push_back(2);
    dataToCopy.push_back(8);
    dataToCopy.push_back(9);

    //build the ByteStream using the Copy Constructor
    ByteStream data(dataToCopy);

    //check that the length of the data is what we think it should be
    BOOST_CHECK_EQUAL(data.size(), 4);

    //check that each byte is what it should be using the [] operator
    BOOST_CHECK_EQUAL(data[0], 1);
    BOOST_CHECK_EQUAL(data[1], 2);
    BOOST_CHECK_EQUAL(data[2], 8);
    BOOST_CHECK_EQUAL(data[3], 9);

    //build a const ByteStream
    const ByteStream constData(dataToCopy);

    //check that each byte is what it should be using the [] operator
    BOOST_CHECK_EQUAL(constData[0], 1);
    BOOST_CHECK_EQUAL(constData[1], 2);
    BOOST_CHECK_EQUAL(constData[2], 8);
    BOOST_CHECK_EQUAL(constData[3], 9);
}

BOOST_AUTO_TEST_CASE(ByteStream_CopyConstructorAtOperator)
{
    //build the data to send to the ByteStream copy constructor
    Bytes dataToCopy;
    dataToCopy.push_back(1);
    dataToCopy.push_back(2);
    dataToCopy.push_back(8);
    dataToCopy.push_back(9);

    //build the ByteStream using the Copy Constructor
    ByteStream data(dataToCopy);

    //build a const ByteStream
    ByteStream moreData(data);

    //check that each byte is what it should be using the [] operator
    BOOST_CHECK_EQUAL(moreData[0], 1);
    BOOST_CHECK_EQUAL(moreData[1], 2);
    BOOST_CHECK_EQUAL(moreData[2], 8);
    BOOST_CHECK_EQUAL(moreData[3], 9);

    //check that the original ByteStream is still ok
    BOOST_CHECK_EQUAL(data[0], 1);
    BOOST_CHECK_EQUAL(data[1], 2);
    BOOST_CHECK_EQUAL(data[2], 8);
    BOOST_CHECK_EQUAL(data[3], 9);
}

BOOST_AUTO_TEST_CASE(ByteStream_EqualOperator)
{
    //build the data to send to the ByteStream
    Bytes dataToCopy;
    dataToCopy.push_back(1);
    dataToCopy.push_back(2);
    dataToCopy.push_back(8);
    dataToCopy.push_back(9);

    //build the ByteStreams
    ByteStream bytes1(dataToCopy);
    ByteStream bytes2(dataToCopy);

    //check that the ByteStreams are equal
    BOOST_CHECK_EQUAL((bytes1 == bytes2), true);

    //add a byte to one of the ByteStreams
    bytes1.append_uint8(5);

    //check that the ByteStreams are no longer equal
    BOOST_CHECK_EQUAL((bytes1 == bytes2), false);
}

BOOST_AUTO_TEST_CASE(ByteStream_Resize)
{
    ByteStream bytes;

    bytes.append_uint8(0x01);

    //check that the bytestream has an initial size of 0
    BOOST_CHECK_EQUAL(bytes.size(), 1);

    //resize the bytestream to 5
    bytes.resize(5);

    //check that the size is now 5
    BOOST_CHECK_EQUAL(bytes.size(), 5);

    //check that the bytes are what we think they are
    BOOST_CHECK_EQUAL(bytes[0], 1);
    BOOST_CHECK_EQUAL(bytes[1], 0);
    BOOST_CHECK_EQUAL(bytes[2], 0);
    BOOST_CHECK_EQUAL(bytes[3], 0);
    BOOST_CHECK_EQUAL(bytes[4], 0);

    //resize the bytestream to 2 (shrink)
    bytes.resize(2);

    //check that the size is now 2
    BOOST_CHECK_EQUAL(bytes.size(), 2);

    //check that the bytes are what we think they are
    BOOST_CHECK_EQUAL(bytes[0], 1);
    BOOST_CHECK_EQUAL(bytes[1], 0);

    //check that accessing outside of the bytestream throws an exception
    BOOST_CHECK_THROW(bytes[2], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ByteStream_BeginEnd)
{
    ByteStream bytes;
    bytes.append_uint8(0x01);
    bytes.append_uint8(0x02);
    bytes.append_uint8(0x03);

    //create an iterator by calling bytes.begin()
    Bytes::iterator it = bytes.begin();

    //check that the iterator points at the correct value
    BOOST_CHECK_EQUAL(*it, 0x01);

    //move the iterator to the end of the items
    it++;
    it++;
    it++;

    //check that the iterator now points at bytes.end()
    BOOST_CHECK_EQUAL((it == bytes.end()), true);
}

BOOST_AUTO_TEST_SUITE_END()


//===================================================================================================================
//                                                ByteStream Append Functions
//===================================================================================================================
BOOST_AUTO_TEST_SUITE(ByteStream_AppendFunctions)

BOOST_AUTO_TEST_CASE(ByteStream_Append_uint8)
{
    ByteStream bytes;

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    //add a byte to the ByteStream using appendByte
    bytes.append_uint8(0x05);

    //check that the bytestream now has a size of 1
    BOOST_CHECK_EQUAL(bytes.size(), 1);

    //check that the first byte in the bytestream is what it should be
    BOOST_CHECK_EQUAL(bytes[0], 0x05);

    //add another byte to the ByteStream using appendByte
    bytes.append_uint8(0x07);

    //check that the bytestream now has a size of 2
    BOOST_CHECK_EQUAL(bytes.size(), 2);

    //check that the bytes in the bytestream are what they should be
    BOOST_CHECK_EQUAL(bytes[0], 0x05);
    BOOST_CHECK_EQUAL(bytes[1], 0x07);
}

BOOST_AUTO_TEST_CASE(ByteStream_Append_uint16)
{
    ByteStream bytes;

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    //append the word to the bytestream
    bytes.append_uint16(0x1234);

    //check that the bytestream now has 2 bytes (1 word)
    BOOST_CHECK_EQUAL(bytes.size(), 2);

    //check that the bytes are what they should be
    BOOST_CHECK_EQUAL(bytes[0], 0x12);
    BOOST_CHECK_EQUAL(bytes[1], 0x34);

    //append another word to the bytestream
    bytes.append_uint16(0x5678);

    //check that the bytestream now has 4 bytes (2 words)
    BOOST_CHECK_EQUAL(bytes.size(), 4);

    //check that the bytes are what they should be
    BOOST_CHECK_EQUAL(bytes[0], 0x12);
    BOOST_CHECK_EQUAL(bytes[1], 0x34);
    BOOST_CHECK_EQUAL(bytes[2], 0x56);
    BOOST_CHECK_EQUAL(bytes[3], 0x78);
}

BOOST_AUTO_TEST_CASE(ByteStream_Append_uint32)
{
    ByteStream bytes;

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    bytes.append_uint32(0x12345678);

    //check that the bytestream now has 4 bytes (1 DWord)
    BOOST_CHECK_EQUAL(bytes.size(), 4);

    //check that the bytes are what they should be
    BOOST_CHECK_EQUAL(bytes[0], 0x12);
    BOOST_CHECK_EQUAL(bytes[1], 0x34);
    BOOST_CHECK_EQUAL(bytes[2], 0x56);
    BOOST_CHECK_EQUAL(bytes[3], 0x78);

    //append another DWord to the bytestream
    bytes.append_uint32(0x19283746);

    //check that the bytestream now has 8 bytes (2 DWords)
    BOOST_CHECK_EQUAL(bytes.size(), 8);

    //check that the bytes are what they should be
    BOOST_CHECK_EQUAL(bytes[0], 0x12);
    BOOST_CHECK_EQUAL(bytes[1], 0x34);
    BOOST_CHECK_EQUAL(bytes[2], 0x56);
    BOOST_CHECK_EQUAL(bytes[3], 0x78);
    BOOST_CHECK_EQUAL(bytes[4], 0x19);
    BOOST_CHECK_EQUAL(bytes[5], 0x28);
    BOOST_CHECK_EQUAL(bytes[6], 0x37);
    BOOST_CHECK_EQUAL(bytes[7], 0x46);
}

BOOST_AUTO_TEST_CASE(ByteStream_Append_float)
{
    ByteStream bytes;
    ByteStream bytesLittleEndian;

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    bytes.append_float(123.456787109375f);

    //check that the bytestream now has 4 bytes
    BOOST_CHECK_EQUAL(bytes.size(), 4);

    //check that the bytes are what they should be
    BOOST_CHECK_EQUAL(bytes[0], 0x42);
    BOOST_CHECK_EQUAL(bytes[1], 0xF6);
    BOOST_CHECK_EQUAL(bytes[2], 0xE9);
    BOOST_CHECK_EQUAL(bytes[3], 0xE0);

    BOOST_CHECK_CLOSE(bytes.read_float(0), 123.45678, 0.00001);

    bytesLittleEndian.append_float(123.456787109375f, Utils::littleEndian);

    //check that the bytes are what they should be
    BOOST_CHECK_EQUAL(bytesLittleEndian[0], 0xE0);
    BOOST_CHECK_EQUAL(bytesLittleEndian[1], 0xE9);
    BOOST_CHECK_EQUAL(bytesLittleEndian[2], 0xF6);
    BOOST_CHECK_EQUAL(bytesLittleEndian[3], 0x42);

    BOOST_CHECK_CLOSE(bytesLittleEndian.read_float(0, Utils::littleEndian), 123.45678, 0.00001);
}

BOOST_AUTO_TEST_CASE(ByteStream_Append_double)
{
    ByteStream bytes;
    ByteStream bytesLittleEndian;

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    bytes.append_double(12.34567);

    //check that the bytestream now has 8 bytes
    BOOST_CHECK_EQUAL(bytes.size(), 8);

    //check that the bytes are what they should be
    BOOST_CHECK_EQUAL(bytes[0], 0x40);
    BOOST_CHECK_EQUAL(bytes[1], 0x28);
    BOOST_CHECK_EQUAL(bytes[2], 0xB0);
    BOOST_CHECK_EQUAL(bytes[3], 0xFB);
    BOOST_CHECK_EQUAL(bytes[4], 0xA8);
    BOOST_CHECK_EQUAL(bytes[5], 0x82);
    BOOST_CHECK_EQUAL(bytes[6], 0x6A);
    BOOST_CHECK_EQUAL(bytes[7], 0xA9);

    BOOST_CHECK_CLOSE(bytes.read_double(0), 12.34567, 0.00001);

    bytesLittleEndian.append_double(12.34567, Utils::littleEndian);

    //check that the bytes are what they should be
    BOOST_CHECK_EQUAL(bytesLittleEndian[0], 0xA9);
    BOOST_CHECK_EQUAL(bytesLittleEndian[1], 0x6A);
    BOOST_CHECK_EQUAL(bytesLittleEndian[2], 0x82);
    BOOST_CHECK_EQUAL(bytesLittleEndian[3], 0xA8);
    BOOST_CHECK_EQUAL(bytesLittleEndian[4], 0xFB);
    BOOST_CHECK_EQUAL(bytesLittleEndian[5], 0xB0);
    BOOST_CHECK_EQUAL(bytesLittleEndian[6], 0x28);
    BOOST_CHECK_EQUAL(bytesLittleEndian[7], 0x40);

    BOOST_CHECK_CLOSE(bytesLittleEndian.read_double(0, Utils::littleEndian), 12.34567, 0.00001);
}

BOOST_AUTO_TEST_CASE(ByteStream_Append_string)
{
    ByteStream bytes;

    std::string test = "Hello World!";

    bytes.append_string(test);

    BOOST_CHECK_EQUAL(bytes.read_string(0, test.length()), test);
}

BOOST_AUTO_TEST_CASE(ByteStream_AppendByteStream)
{
    ByteStream bytes, bytesToAppend;

    //build the bytestream that we are going to append to the original bytestream
    bytesToAppend.append_uint32(0x12349876);

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    //append the build bytestream to the original bytestream
    bytes.appendByteStream(bytesToAppend);

    //check that the original bytestream has 4 bytes in it now
    BOOST_CHECK_EQUAL(bytes.size(), 4);

    //check that the bytes are what they should be
    BOOST_CHECK_EQUAL(bytes[0], 0x12);
    BOOST_CHECK_EQUAL(bytes[1], 0x34);
    BOOST_CHECK_EQUAL(bytes[2], 0x98);
    BOOST_CHECK_EQUAL(bytes[3], 0x76);
}

BOOST_AUTO_TEST_SUITE_END()


//===================================================================================================================
//                                                ByteStream Read Functions
//===================================================================================================================
BOOST_AUTO_TEST_SUITE(ByteStream_ReadFunctions)

BOOST_AUTO_TEST_CASE(ByteStream_Read_int8)
{
    ByteStream bytes;

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    //adding overflowed values for an uint8
    //which should cause the read_int8 to return the result of a negative value
    bytes.append_uint8(128);
    bytes.append_uint8(150);
    bytes.append_uint8(45);

    //check that readByte returns the correct bytes
    BOOST_CHECK_EQUAL(static_cast<int16>(bytes.read_int8(0)), -128);
    BOOST_CHECK_EQUAL(static_cast<int16>(bytes.read_int8(1)), -106);
    BOOST_CHECK_EQUAL(static_cast<int16>(bytes.read_int8(2)), 45);

    //check that readByte outside of the bytestream range throws an exception
    BOOST_CHECK_THROW(bytes.read_int8(3), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ByteStream_Read_uint8)
{
    ByteStream bytes;

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    //add bytes to the ByteStream
    bytes.append_uint16(0x1234);

    //check that readByte returns the correct bytes
    BOOST_CHECK_EQUAL(bytes.read_uint8(0), 0x12);
    BOOST_CHECK_EQUAL(bytes.read_uint8(1), 0x34);

    //check that readByte outside of the bytestream range throws an exception
    BOOST_CHECK_THROW(bytes.read_uint8(2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ByteStream_Read_uint16)
{
    ByteStream bytes;

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    //add bytes to the ByteStream
    bytes.append_uint16(0x1234);
    bytes.append_uint16(0x5678);

    //check that readWord returns the correct bytes
    BOOST_CHECK_EQUAL(bytes.read_uint16(0), 0x1234);
    BOOST_CHECK_EQUAL(bytes.read_uint16(1), 0x3456);
    BOOST_CHECK_EQUAL(bytes.read_uint16(2), 0x5678);

    //check that readWord outside of the bytestream range throws an exception
    BOOST_CHECK_THROW(bytes.read_uint16(3), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ByteStream_Read_uint24)
{
    ByteStream bytes;

    bytes.append_uint8(0x01);
    bytes.append_uint8(0x23);
    bytes.append_uint8(0x45);
    BOOST_CHECK_EQUAL(bytes.read_uint24(0), 0x012345);

    bytes.clear();

    bytes.append_uint8(0x45);
    bytes.append_uint8(0x23);
    bytes.append_uint8(0x01);
    BOOST_CHECK_EQUAL(bytes.read_uint24(0, Utils::littleEndian), 0x012345);
}

BOOST_AUTO_TEST_CASE(ByteStream_Read_uint32)
{
    ByteStream bytes;

    //check that the bytestream is empty to begin with
    BOOST_CHECK_EQUAL(bytes.size(), 0);

    //add bytes to the ByteStream
    bytes.append_uint32(0x12345678);
    bytes.append_uint32(0xAB);

    //check that readDWord returns the correct bytes
    BOOST_CHECK_EQUAL(bytes.read_uint32(0), 0x12345678);
    BOOST_CHECK_EQUAL(bytes.read_uint32(1), 0x34567800);
    BOOST_CHECK_EQUAL(bytes.read_uint32(2), 0x56780000);
    BOOST_CHECK_EQUAL(bytes.read_uint32(3), 0x78000000);
    BOOST_CHECK_EQUAL(bytes.read_uint32(4), 0x000000AB);

    //check that readDWord outside of the bytestream range throws an exception
    BOOST_CHECK_THROW(bytes.read_uint32(5), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ByteStream_Read_int24)
{
    ByteStream bytes;

    //29489 (0x7331)
    bytes.append_uint8(0x00);
    bytes.append_uint8(0x73);
    bytes.append_uint8(0x31);
    BOOST_CHECK_EQUAL(bytes.read_int24(0), 29489);

    bytes.clear();

    //-29489 (0xFF8CCF)
    bytes.append_uint8(0xFF);
    bytes.append_uint8(0x8C);
    bytes.append_uint8(0xCF);
    BOOST_CHECK_EQUAL(bytes.read_int24(0), -29489);

    bytes.clear();

    //342 (0x0156)
    bytes.append_uint8(0x00);
    bytes.append_uint8(0x01);
    bytes.append_uint8(0x56);
    BOOST_CHECK_EQUAL(bytes.read_int24(0), 342);

    bytes.clear();

    //-342 (0xFFFEAA)
    bytes.append_uint8(0xFF);
    bytes.append_uint8(0xFE);
    bytes.append_uint8(0xAA);
    BOOST_CHECK_EQUAL(bytes.read_int24(0), -342);

    bytes.clear();

    //1263096 (0x1345F8)
    bytes.append_uint8(0x13);
    bytes.append_uint8(0x45);
    bytes.append_uint8(0xF8);
    BOOST_CHECK_EQUAL(bytes.read_int24(0), 1263096);

    bytes.clear();

    //1263096 (LITTLE ENDIAN)
    bytes.append_uint8(0xF8);
    bytes.append_uint8(0x45);
    bytes.append_uint8(0x13);

    BOOST_CHECK_EQUAL(bytes.read_int24(0, Utils::littleEndian), 1263096);
}

BOOST_AUTO_TEST_CASE(ByteStream_Read_float)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);

    //check that readFloat returns the correct value
    BOOST_CHECK_CLOSE(bytes.read_float(0), 1.234, 0.0001);

    //check that readFloat outside of the bytestream range throws an exception
    BOOST_CHECK_THROW(bytes.read_float(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ByteStream_Read_double)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_double(158.4678);

    //check that readFloat returns the correct value
    BOOST_CHECK_CLOSE(bytes.read_double(0), 158.4678, 0.0001);

    //check that readFloat outside of the bytestream range throws an exception
    BOOST_CHECK_THROW(bytes.read_double(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ByteStream_Read_string)
{
    ByteStream bs;

    bs.append_uint8(0x48);    //H
    bs.append_uint8(0x65);    //e
    bs.append_uint8(0x6C);    //l
    bs.append_uint8(0x6C);    //l
    bs.append_uint8(0x6F);    //o
    bs.append_uint8(0x57);    //W
    bs.append_uint8(0x6F);    //o
    bs.append_uint8(0x72);    //r
    bs.append_uint8(0x6C);    //l
    bs.append_uint8(0x64);    //d

    BOOST_CHECK_EQUAL(bs.read_string(1, 4), "ello");
    BOOST_CHECK_EQUAL(bs.read_string(2, 4), "lloW");
    BOOST_CHECK_EQUAL(bs.read_string(0, 10), "HelloWorld");
    BOOST_CHECK_THROW(bs.read_string(0, 11), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()


//===================================================================================================================
//                                                ByteStream Checksums
//===================================================================================================================
BOOST_AUTO_TEST_SUITE(ByteStream_Checksums)

BOOST_AUTO_TEST_CASE(ByteStream_SimpleChecksum)
{
    //create a bytestream with some bytes in it
    ByteStream bytes;
    bytes.append_uint32(0x12345678);

    //check that the simple checksum is what it should be
    BOOST_CHECK_EQUAL(bytes.calculateSimpleChecksum(0, 3), 0x114);

    //build a large bytestream with 280 bytes (70 DWords) of 0xFF
    ByteStream largeBytes;
    for(int i = 0; i < 70; i++)
    {
        largeBytes.append_uint32(0xFFFFFFFF);
    }

    //check that the simple checksum is what it should be
    BOOST_CHECK_EQUAL(largeBytes.calculateSimpleChecksum(0, largeBytes.size() - 1), 5864);
}

BOOST_AUTO_TEST_CASE(ByteStream_FletcherChecksum)
{
    //create a bytestream with some bytes in it
    ByteStream bytes;
    bytes.append_uint32(0x12345678);

    //check that the simple checksum is what it should be
    BOOST_CHECK_EQUAL(bytes.calculateFletcherChecksum(0, bytes.size() - 1), 5128);
}

BOOST_AUTO_TEST_CASE(ByteStream_CrcChecksum)
{
    {
        //128 random bytes
        Bytes bytes = {96, 175, 215, 192, 83, 5, 69, 144, 145, 88, 116, 84, 133, 250, 93, 145, 50, 136, 7, 243, 82, 64, 118, 32, 238, 145, 118, 153, 183, 43, 45, 170, 242, 128, 40, 192, 187, 4, 30, 116, 163, 89, 20, 12, 152, 76, 80, 5, 134, 6, 215, 10, 33, 233, 64, 116, 148, 8, 246, 76, 64, 19, 39, 28, 22, 133, 130, 49, 64, 72, 197, 224, 172, 15, 218, 68, 199, 236, 161, 172, 128, 218, 144, 181, 207, 57, 77, 68, 184, 1, 210, 60, 85, 13, 163, 127, 123, 42, 207, 228, 194, 105, 200, 226, 64, 57, 238, 56, 156, 238, 17, 105, 129, 243, 237, 146, 108, 82, 141, 245, 253, 175, 69, 171, 30, 69, 110, 93};
        ByteStream byteStream(bytes);

        BOOST_CHECK_EQUAL(byteStream.calculateCrcChecksum(0, bytes.size() - 1), 0x4a3d820f);
    }

    {
        //127 random bytes
        Bytes bytes = {69, 55, 190, 151, 239, 235, 171, 180, 139, 211, 108, 215, 223, 8, 71, 175, 89, 79, 52, 232, 129, 84, 108, 255, 124, 28, 123, 175, 33, 11, 117, 96, 13, 55, 137, 7, 126, 189, 222, 107, 62, 76, 173, 230, 95, 251, 203, 138, 167, 44, 250, 185, 172, 140, 60, 106, 58, 180, 154, 206, 226, 230, 38, 193, 180, 138, 168, 215, 103, 137, 126, 38, 16, 174, 218, 153, 8, 33, 84, 77, 92, 108, 209, 28, 131, 95, 141, 166, 238, 109, 213, 207, 25, 245, 82, 171, 237, 128, 118, 127, 205, 103, 58, 131, 157, 0, 210, 70, 83, 100, 131, 58, 136, 153, 96, 165, 151, 108, 89, 216, 70, 149, 225, 165, 177, 235, 227};
        ByteStream byteStream(bytes);

        BOOST_CHECK_EQUAL(byteStream.calculateCrcChecksum(0, bytes.size() - 1), 0xd9060681);
    }
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE_END()
