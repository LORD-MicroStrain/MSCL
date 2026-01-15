/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Commands/Resume.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(Resume_Test)

BOOST_AUTO_TEST_CASE(Resume_BuildCommand)
{
    ByteStream b = Resume::buildCommand();
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x06);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0xE5);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0xCB);
}

BOOST_AUTO_TEST_CASE(Resume_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    Resume::Response response(rc);

    Bytes ackField;
    ackField.push_back(0x06);
    ackField.push_back(0x00);
    MipDataField field1(0x01F1, ackField); //good ack field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);
    BOOST_CHECK_EQUAL(response.result().success(), true);
}

BOOST_AUTO_TEST_SUITE_END()
