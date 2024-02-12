/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/Erase.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(Erase_Test)

BOOST_AUTO_TEST_CASE(Erase_BuildCommand)
{
    //create a LongPing command
    ByteStream b = Erase::buildCommand(4794);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x06);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x12);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0xBA);
    BOOST_CHECK_EQUAL(b.read_uint32(3), 0x08100CFF);
}

BOOST_AUTO_TEST_CASE(Erase_Match_SuccessResponse)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Erase::Response response(rc);

    Bytes bytes;
    bytes.push_back(0x06);    //success response

    DataBuffer buffer(bytes);

    //check that match returns true
    BOOST_CHECK_EQUAL(response.match(buffer), true);

    //check that the result of the ping is true
    BOOST_CHECK_EQUAL(response.success(), true);
}

BOOST_AUTO_TEST_CASE(Erase_Match_FailResponse)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Erase::Response response(rc);

    Bytes bytes;
    bytes.push_back(0x21);    //fail response

    DataBuffer buffer(bytes);

    //check that match returns true
    BOOST_CHECK_EQUAL(response.match(buffer), true);

    //check that the result of the ping is false
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(Erase_Match_Fail)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Erase::Response response(rc);

    Bytes bytes;
    bytes.push_back(0x45);    //bad bytes

    DataBuffer buffer(bytes);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the ping is false
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(Erase_Match_Fail_ByteSize)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Erase::Response response(rc);

    Bytes bytes;    //empty bytes        

    DataBuffer buffer(bytes);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the ping is false
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_SUITE_END()