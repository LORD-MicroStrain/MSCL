/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/BaseStation_SetBeacon.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

Bytes buildBaseSetBeaconResponse()
{
    //build success response
    Bytes bytes;
    bytes.push_back(0xBE);
    bytes.push_back(0xAC);

    return bytes;
}


BOOST_AUTO_TEST_SUITE(BaseStationSetBeacon_Test)

BOOST_AUTO_TEST_CASE(BaseStationSetBeacon_BuildCommand)
{
    const uint32 BEACON_TIME = 1358201247;

    //create a Set Beacon command
    ByteStream b = BaseStation_SetBeacon::buildCommand(BEACON_TIME);

    //check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint16(0), 0xBEAC);
    BOOST_CHECK_EQUAL(b.read_uint32(2), BEACON_TIME);
}

BOOST_AUTO_TEST_CASE(BaseStationSetBeacon_MatchSuccessResponse_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_SetBeacon::Response response(1, rc);

    DataBuffer buffer(buildBaseSetBeaconResponse());

    //check that match returns true
    BOOST_CHECK_EQUAL(response.match(buffer), true);

    //check that the result of the command is successful
    BOOST_CHECK_EQUAL(response.success(), true);
}

BOOST_AUTO_TEST_CASE(BaseStationSetBeacon_MatchSuccessResponse_FailNumBytes)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_SetBeacon::Response response(1, rc);

    Bytes b;
    b.push_back(0x04);

    DataBuffer buffer(b);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationSetBeacon_MatchSuccessResponse_FailByteMatch)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_SetBeacon::Response response(1, rc);

    Bytes b = buildBaseSetBeaconResponse();
    b[0] = 0x01;    //incorrect command byte

    DataBuffer buffer(b);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationSetBeacon_Wait_Timeout)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    //create the response for the BaseStation_SetBeacon command
    BaseStation_SetBeacon::Response response(1, rc);

    //wait for a quick timeout (no data has been sent/received)
    response.wait(1);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_SUITE_END()
