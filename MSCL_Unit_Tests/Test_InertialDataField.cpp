/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(InertialDataField_Test)

BOOST_AUTO_TEST_CASE(InertialDataField_Constructor)
{
    MipDataField f;

    //check that the default field type of 0 is assigned
    BOOST_CHECK_EQUAL(f.fieldId(), 0);

    Bytes b;
    b.push_back(0x01);
    b.push_back(0x02);

    //build a MipDataField from the bytes
    MipDataField f1(MipTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC, b);

    BOOST_CHECK_EQUAL(f1.fieldId(), MipTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC);
    BOOST_CHECK_EQUAL(f1.fieldData().read_uint8(0), 0x01);
    BOOST_CHECK_EQUAL(f1.fieldData().read_uint8(1), 0x02);
}

BOOST_AUTO_TEST_SUITE_END()
