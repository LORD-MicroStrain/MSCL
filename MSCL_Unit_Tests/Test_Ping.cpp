/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/MIP/Commands/Ping.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialPing_Test)

BOOST_AUTO_TEST_CASE(InertialPing_BuildCommand)
{
    //create a LongPing command
    ByteStream b = Ping::buildCommand();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0xE0);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0xC6);
}

BOOST_AUTO_TEST_CASE(InertialPing_GetResponseResult)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Ping::Response response(rc);

    MipCmdResponse r = response.result();

    //check that the the response result is what it should be
    BOOST_CHECK_EQUAL(r.success(), false);
    BOOST_CHECK_EQUAL(r.errorCode(), MipPacket::MIP_ACK_NACK_ERROR_NONE);
}

BOOST_AUTO_TEST_CASE(InertialPing_Match_Fail_DescSet)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Ping::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x01);
    fieldData.push_back(0x00);
    MipDataField field(0x04F1, fieldData); //invalid descriptor set

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(InertialPing_Match_Fail_FieldDataLen)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Ping::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x01);
    MipDataField field(0x01F1, fieldData); //bad field data length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(InertialPing_Match_Fail_FieldDesc)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Ping::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x01);
    fieldData.push_back(0x00);
    MipDataField field(0x0101, fieldData); //invalid field descriptor

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(InertialPing_Match_Fail_CommandEcho)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Ping::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x05);    //bad command echo
    fieldData.push_back(0x00);
    MipDataField field(0x01F1, fieldData);

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(InertialPing_Match_FailWithErrorCode)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Ping::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x01);
    fieldData.push_back(mscl::MipPacket::MIP_ACK_NACK_ERROR_CHECKSUM_INVALID);
    MipDataField field(0x01F1, fieldData); //good field, but with error code

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), true);
    BOOST_CHECK_EQUAL(response.result().success(), false);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_CHECKSUM_INVALID);
}

BOOST_AUTO_TEST_CASE(InertialPing_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Ping::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x01);
    fieldData.push_back(0x00);
    MipDataField field(0x01F1, fieldData); //good field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(field), true);
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
}

BOOST_AUTO_TEST_SUITE_END()