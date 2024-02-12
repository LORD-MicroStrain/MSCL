/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/BaseStation_Ping.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(BaseStationPing_Test)

BOOST_AUTO_TEST_CASE(BaseStationPing_BuildCommand)
{
    //create a LongPing command
    ByteStream b = BaseStation_Ping::buildCommand();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x01);
}

BOOST_AUTO_TEST_CASE(BaseStationPing_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_Ping::Response response(rc);

    Bytes bytes;
    bytes.push_back(0x01);    //success response

    DataBuffer buffer(bytes);

    //check that match returns true
    BOOST_CHECK_EQUAL(response.match(buffer), true);

    //check that the result of the ping is true
    BOOST_CHECK_EQUAL(response.success(), true);
}

BOOST_AUTO_TEST_CASE(BaseStationPing_Match_Fail)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_Ping::Response response(rc);

    Bytes bytes;
    bytes.push_back(0x45);    //fail response

    DataBuffer buffer(bytes);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the ping is false
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationPing_Match_Fail_ByteSize)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_Ping::Response response(rc);

    Bytes bytes;    //empty bytes        

    DataBuffer buffer(bytes);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the ping is false
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_SUITE_END()