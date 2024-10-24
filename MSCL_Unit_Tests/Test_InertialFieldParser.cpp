/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Packets/MipFieldParser.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialFieldParser_Test)

BOOST_AUTO_TEST_CASE(InertialFieldParser_parseField)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //Accel 1 float
    bytes.append_float(0.0f);    //Accel 2 float
    bytes.append_float(0.0f);    //Accel 3 float

    MipDataField field(MipTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_EQUAL(data.at(1).as_float(), 0);
    BOOST_CHECK_EQUAL(data.at(2).as_float(), 0);
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_parseUnknown)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint32(0x3F9DF3B6);    //Accel 1 float
    bytes.append_uint32(0x00000000);    //Accel 2 float
    bytes.append_uint32(0x00000000);    //Accel 3 float

    MipDataField field(0, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Bytes);
}

BOOST_AUTO_TEST_SUITE_END()
