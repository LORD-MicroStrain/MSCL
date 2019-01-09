/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/ChecksumBuilder.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(ChecksumBuilder_Test)

BOOST_AUTO_TEST_CASE(ChecksumBuilder_AppendByte)
{
    //append bytes to the checksum builder
    ChecksumBuilder b;
    b.append_uint8(0x01);
    b.append_uint8(0x02);
    b.append_uint8(0x04);

    //check the checksum is good
    BOOST_CHECK_EQUAL(b.simpleChecksum(), 0x07);
}

BOOST_AUTO_TEST_CASE(ChecksumBuilder_AppendWord)
{
    //append word to the checksum builder
    ChecksumBuilder b;
    b.append_uint16(0x1234);
    b.append_uint8(0x02);
    b.append_uint8(0x04);

    //check the checksum is good
    BOOST_CHECK_EQUAL(b.simpleChecksum(), 0x4C);
}

BOOST_AUTO_TEST_CASE(ChecksumBuilder_AppendDWord)
{
    //append dword to the checksum builder
    ChecksumBuilder b;
    b.append_uint32(0x12345678);
    b.append_uint8(0x02);
    b.append_uint8(0x04);

    //check the checksum is good
    BOOST_CHECK_EQUAL(b.simpleChecksum(), 0x11A);
}

BOOST_AUTO_TEST_CASE(ChecksumBuilder_AppendBytes)
{
    Bytes data;
    data.push_back(0x01);
    data.push_back(0x02);
    data.push_back(0x04);

    //append bytes to the checksum builder
    ChecksumBuilder b;
    b.appendBytes(data);

    //check the checksum is good
    BOOST_CHECK_EQUAL(b.simpleChecksum(), 0x07);
}

BOOST_AUTO_TEST_CASE(ChecksumBuilder_AppendByteStream)
{
    ByteStream bs;
    bs.append_uint8(0x01);
    bs.append_uint8(0x02);
    bs.append_uint8(0x04);

    //append bytes to the checksum builder
    ChecksumBuilder b;
    b.appendByteStream(bs);

    //check the checksum is good
    BOOST_CHECK_EQUAL(b.simpleChecksum(), 0x07);
}

BOOST_AUTO_TEST_CASE(ChecksumBuilder_FletcherChecksum)
{
    ChecksumBuilder b;
    b.append_uint32(0x12345678);

    //check that the simple checksum is what it should be
    BOOST_CHECK_EQUAL(b.fletcherChecksum(), 5128);
}

BOOST_AUTO_TEST_SUITE_END()