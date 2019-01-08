/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/MIP/Commands/Mip_SetToIdle.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace std;
using namespace mscl;

BOOST_AUTO_TEST_SUITE(Inertial_SetToIdle_Test)

BOOST_AUTO_TEST_CASE(Inertial_SetToIdle_BuildCommand)
{
    ByteStream b = Mip_SetToIdle::buildCommand();
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0xE1);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0xC7);
}

BOOST_AUTO_TEST_CASE(Inertial_SetToIdle_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Mip_SetToIdle::Response response(rc);
    
    Bytes ackField;
    ackField.push_back(0x02);
    ackField.push_back(0x00);
    MipDataField field1(0x01F1, ackField); //good ack field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);    
    BOOST_CHECK_EQUAL(response.result().success(), true);
}

BOOST_AUTO_TEST_SUITE_END()