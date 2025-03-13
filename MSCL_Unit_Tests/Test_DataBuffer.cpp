/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/DataBuffer.h"

#include <boost/test/unit_test.hpp>
#include <turtle/mock.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(DataBuffer_Test)

BOOST_AUTO_TEST_CASE(DataBuffer_Bytes_Constructor)
{
    //create the Bytes data
    Bytes data;
    data.push_back(0x01);
    data.push_back(0x02);
    data.push_back(0x03);
    data.push_back(0x04);
    data.push_back(0x05);
    data.push_back(0x06);

    //create a DataBuffer, sending the Bytes data to the constuctor
    DataBuffer b(data);

    //check that the size of the buffer is 6
    BOOST_CHECK_EQUAL(b.size(), 6);

    //check that readByte() returns the correct byte
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x01);

    //check that readWord() returns the correct word
    BOOST_CHECK_EQUAL(b.read_uint16(), 0x0203);

    //check that readWord() returns the correct word
    BOOST_CHECK_EQUAL(b.read_uint16(), 0x0405);

    //check that readByte() returns the correct byte
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x06);

    //check that reading a byte now throws an exception
    BOOST_CHECK_THROW(b.read_uint8(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(DataBuffer_ByteStream_Constructor)
{
    //create the Bytes data
    Bytes data;
    data.push_back(0x01);
    data.push_back(0x02);
    data.push_back(0x03);
    data.push_back(0x04);
    data.push_back(0x05);
    data.push_back(0x06);

    //build the ByteStream using the Bytes
    ByteStream byteStream(data);

    //create a DataBuffer, sending the Bytes data to the constuctor
    DataBuffer b(byteStream);

    //check that the size of the buffer is 6
    BOOST_CHECK_EQUAL(b.size(), 6);

    //check that readByte() returns the correct byte
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x01);

    //check that readWord() returns the correct word
    BOOST_CHECK_EQUAL(b.read_uint16(), 0x0203);

    //check that readWord() returns the correct word
    BOOST_CHECK_EQUAL(b.read_uint16(), 0x0405);

    //check that readByte() returns the correct byte
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x06);

    //check that reading a byte now throws an exception
    BOOST_CHECK_THROW(b.read_uint8(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(DataBuffer_Size)
{
    DataBuffer b(1024);

    //check the size is what we set it to in the constructor
    BOOST_CHECK_EQUAL(b.size(), 1024);
}

BOOST_AUTO_TEST_CASE(DataBuffer_ReadEmptyBuffer)
{
    DataBuffer b(10);

    //check that reading a byte throws an exception
    BOOST_CHECK_THROW(b.read_uint8(), std::out_of_range);

    //check that reading a word throws an exception
    BOOST_CHECK_THROW(b.read_uint16(), std::out_of_range);

    //check that reading a DWord throws an exception
    BOOST_CHECK_THROW(b.read_uint32(), std::out_of_range);

    BOOST_CHECK_THROW(b.read_double(), std::out_of_range);

    BOOST_CHECK_THROW(b.read_float(), std::out_of_range);

    BOOST_CHECK_THROW(b.read_int16(), std::out_of_range);

    BOOST_CHECK_THROW(b.read_int8(), std::out_of_range);

    BOOST_CHECK_THROW(b.read_string(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(DataBuffer_NoRoomToWrite)
{
    Bytes data;
    data.push_back(0x01);
    data.push_back(0x02);

    //create a DataBuffer with the Bytes
    DataBuffer b(data);

    BufferWriter bw = b.getBufferWriter();

    //make sure the buffer writer is empty
    BOOST_CHECK_EQUAL(bw.size(), 0);
    BOOST_CHECK(bw.buffer() == NULL);
}

BOOST_AUTO_TEST_CASE(DataBuffer_MoreToRead)
{
    DataBuffer b(1024);

    //check that moreToRead() returns false
    BOOST_CHECK_EQUAL(b.moreToRead(), false);

    BufferWriter bw = b.getBufferWriter();
    bw.commit(1);

    //check that moreToRead() returns true now that we added a byte
    BOOST_CHECK_EQUAL(b.moreToRead(), true);

    b.read_uint8();

    //check that moreToRead() returns false since we read the 1 byte that was added
    BOOST_CHECK_EQUAL(b.moreToRead(), false);
}

BOOST_AUTO_TEST_CASE(DataBuffer_resetBuffer)
{
    DataBuffer b(7);
    BufferWriter bw = b.getBufferWriter();
    bw.buffer()[0] = 0x01;
    bw.buffer()[1] = 0x02;
    bw.buffer()[2] = 0x03;
    bw.buffer()[3] = 0x04;
    bw.buffer()[4] = 0x05;
    bw.buffer()[5] = 0x06;
    bw.buffer()[6] = 0x07;
    bw.commit(7);

    //check that bytesRemaining is the amount of bytes we added
    BOOST_CHECK_EQUAL(b.bytesRemaining(), 7);

    b.read_uint8();    //move the read pointer forward 1 byte

    //check that bytesRemaining has been updated
    BOOST_CHECK_EQUAL(b.bytesRemaining(), 6);

    //reset the buffer (sets read and append position back to 0)
    b.resetBuffer();

    //check that bytesRemaining is the amount of bytes we added
    BOOST_CHECK_EQUAL(b.bytesRemaining(), 0);

    //check that reading a byte throws an exception
    BOOST_CHECK_THROW(b.read_uint8(), std::out_of_range);

    BufferWriter bw2 = b.getBufferWriter();
    bw2.buffer()[0] = 0x12;
    bw2.commit(1);

    //check that bytesRemaining is the amount of bytes we added
    BOOST_CHECK_EQUAL(b.bytesRemaining(), 1);

    BOOST_CHECK_EQUAL(b.read_uint8(), 0x12);
}

BOOST_AUTO_TEST_CASE(DataBuffer_Read)
{
    DataBuffer b(7);
    BufferWriter bw = b.getBufferWriter();
    bw.buffer()[0] = 0x01;
    bw.buffer()[1] = 0x02;
    bw.buffer()[2] = 0x03;
    bw.buffer()[3] = 0x04;
    bw.buffer()[4] = 0x05;
    bw.buffer()[5] = 0x06;
    bw.buffer()[6] = 0x07;
    bw.commit(7);

    BOOST_CHECK_EQUAL(bw.size(), 7);

    //check that readByte() returns the correct byte
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x01);

    //check that readWord() returns the correct word
    BOOST_CHECK_EQUAL(b.read_uint16(), 0x0203);

    //check that readDWord() returns the correct dword
    BOOST_CHECK_EQUAL(b.read_uint32(), 0x04050607);
}

BOOST_AUTO_TEST_CASE(DataBuffer_Read_int8)
{
    DataBuffer b(2);
    BufferWriter bw = b.getBufferWriter();
    bw.buffer()[0] = 150;
    bw.buffer()[1] = 45;
    bw.commit(2);

    BOOST_CHECK_EQUAL(bw.size(), 2);

    //check that read_int8() returns the correct byte
    BOOST_CHECK_EQUAL(static_cast<int16>(b.read_int8()), -106);

    //check that read_int8() returns the correct word
    BOOST_CHECK_EQUAL(static_cast<int16>(b.read_int8()), 45);

    //check that reading again throws an exception
    BOOST_CHECK_THROW(b.read_int8(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(DataBuffer_read_float)
{
    ByteStream bs;
    bs.append_float(5.123f);
    DataBuffer b(bs.data());

    //check that the correct float is read
    BOOST_CHECK_CLOSE(b.read_float(), 5.123, 0.001);

    //check that reading again throws an exception
    BOOST_CHECK_THROW(b.read_float(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(DataBuffer_read_string)
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
    DataBuffer b(bs.data());

    //check that the correct string is read
    BOOST_CHECK_EQUAL(b.read_string(5), "Hello");

    //check that the correct string is read
    BOOST_CHECK_EQUAL(b.read_string(5), "World");

    BOOST_CHECK_THROW(b.read_string(4), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(DataBuffer_ShiftToStart)
{
    DataBuffer b(10);

    BufferWriter bw = b.getBufferWriter();
    bw.buffer()[0] = 0x01;
    bw.buffer()[1] = 0x02;
    bw.buffer()[2] = 0x03;
    bw.buffer()[3] = 0x04;
    bw.buffer()[4] = 0x05;
    bw.buffer()[5] = 0x06;
    bw.commit(6);

    //check that bytesRemaining is the amount of bytes we added
    BOOST_CHECK_EQUAL(b.bytesRemaining(), 6);

    //check that the byte we read is correct
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x01);

    //check that the bytesRemaining has decreased by 1
    BOOST_CHECK_EQUAL(b.bytesRemaining(), 5);

    b.shiftExtraToStart();    //shift all the extra bytes (those that haven't been read yet), back to the start

    //check that the bytesRemaining has stayed the same after we shiftedExtraToStart()
    BOOST_CHECK_EQUAL(b.bytesRemaining(), 5);

    //check that reading another byte gives the correct value
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x02);
}

BOOST_AUTO_TEST_CASE(DataBuffer_Peek)
{
    DataBuffer b(2);
    BufferWriter bw = b.getBufferWriter();
    bw.buffer()[0] = 0x01;
    bw.buffer()[1] = 0x02;
    bw.commit(2);

    //check that there are 2 bytes remaining
    BOOST_CHECK_EQUAL(b.bytesRemaining(), 2);

    //check that calling peekByte returns the first byte
    BOOST_CHECK_EQUAL(b.peekByte(), 0x01);

    //check that calling peekByte again still returns the first byte (hasn't moved the read position)
    BOOST_CHECK_EQUAL(b.peekByte(), 0x01);

    //check that bytesRemaining() still returns 2 as if nothing was read
    BOOST_CHECK_EQUAL(b.bytesRemaining(), 2);

    b.read_uint8();

    //check that peekByte now returns 0x02 after really reading a byte
    BOOST_CHECK_EQUAL(b.peekByte(), 0x02);

    b.read_uint8();

    //check that peekByte throws an out_of_range exception now that there is nothing left to read
    BOOST_CHECK_THROW(b.peekByte(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE(ReadBufferSavePoint_Test)

BOOST_AUTO_TEST_CASE(SavePoint_Revert)
{
    Bytes data;
    data.push_back(0x01);
    data.push_back(0x02);
    data.push_back(0x03);
    data.push_back(0x04);
    data.push_back(0x05);

    DataBuffer b(data);

    //create scope for the save point
    {
        //create a save point for the databuffer
        ReadBufferSavePoint savePoint(&b);

        //check that peeking and reading bytes gives the correct results
        BOOST_CHECK_EQUAL(b.peekByte(), 0x01);
        BOOST_CHECK_EQUAL(b.read_uint8(), 0x01);
        BOOST_CHECK_EQUAL(b.read_uint8(), 0x02);
        BOOST_CHECK_EQUAL(b.read_uint8(), 0x03);

        //revert the data buffer to the save point
        savePoint.revert();

        //check that peeking and reading bytes gives the same results as before, since the position was reverted
        BOOST_CHECK_EQUAL(b.peekByte(), 0x01);
        BOOST_CHECK_EQUAL(b.read_uint8(), 0x01);
        BOOST_CHECK_EQUAL(b.read_uint8(), 0x02);
        BOOST_CHECK_EQUAL(b.read_uint8(), 0x03);
    }

    //check that peeking and reading bytes gives the same results as before, since the position was reverted due to the save point going out of scope
    BOOST_CHECK_EQUAL(b.peekByte(), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x03);
}

BOOST_AUTO_TEST_CASE(SavePoint_Commit)
{
    Bytes data;
    data.push_back(0x01);
    data.push_back(0x02);
    data.push_back(0x03);
    data.push_back(0x04);
    data.push_back(0x05);
    data.push_back(0x06);

    DataBuffer b(data);

    //create a save point for the databuffer
    ReadBufferSavePoint savePoint(&b);

    //check that peeking and reading bytes gives the correct results
    BOOST_CHECK_EQUAL(b.peekByte(), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x03);

    //commit the data buffer to its current position
    savePoint.commit();

    //call revert() to prove it doesn't do anything since we already committed
    savePoint.revert();

    //check that peeking and reading bytes gives the same results as before, since the position was reverted
    BOOST_CHECK_EQUAL(b.peekByte(), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x05);
    BOOST_CHECK_EQUAL(b.read_uint8(), 0x06);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
