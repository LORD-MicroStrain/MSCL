/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Inertial/Packets/InertialDataPacket.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialDataPoint_Test)

BOOST_AUTO_TEST_CASE(InertialDataPoint_DefaultConstructor)
{
    InertialDataPoint p;

    //make sure the member variables are all set correctly
    BOOST_CHECK_EQUAL(p.field(), 0);
    BOOST_CHECK_EQUAL(p.qualifier(), 0);
    BOOST_CHECK_EQUAL(p.valid(), false);
    BOOST_CHECK_EQUAL(p.storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(p.as_float(), 0.0);
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_Constructor)
{
    ByteStream bytes;
    bytes.append_float(1.234f);

    float x = 1.234f;

    InertialDataPoint p(InertialTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC, InertialTypes::CH_X, valueType_float, anyType(x), true);

    //make sure the member variables are all set correctly
    BOOST_CHECK_EQUAL(p.field(), InertialTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC);
    BOOST_CHECK_EQUAL(p.qualifier(), InertialTypes::CH_X);
    BOOST_CHECK_EQUAL(p.storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(p.channelName(), "rawAccelX");

    BOOST_CHECK_CLOSE(p.as_float(), 1.234, 0.0001);
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asVector)
{
    ByteStream bytes;
    bytes.append_uint16(123);
    bytes.append_uint16(456);

    InertialDataPoint p(InertialTypes::CH_FIELD_SENSOR_ORIENTATION_QUATERNION, InertialTypes::CH_QUATERNION, valueType_Vector, anyType(Vector(valueType_uint16, bytes)), true);

    //check that accessing the Vector data incorrectly throws an exception
    BOOST_CHECK_THROW(p.as_float(), Error_BadDataType);
    BOOST_CHECK_THROW(p.as_Matrix(), Error_BadDataType);
    BOOST_CHECK_THROW(p.as_int16(), Error_BadDataType);

    //check that the values are good
    BOOST_CHECK_EQUAL(p.as_Vector().as_uint16At(0), 123);
    BOOST_CHECK_EQUAL(p.as_Vector().as_uint16At(1), 456);
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asMatrix)
{
    ByteStream bytes;
    bytes.append_uint16(0);
    bytes.append_uint16(1);

    InertialDataPoint p(InertialTypes::CH_FIELD_SENSOR_ORIENTATION_MATRIX, InertialTypes::CH_MATRIX, valueType_Matrix, anyType(Matrix(1, 2, valueType_uint16, bytes)), true);

    //check that accessing the Matrix data incorrectly throws an exception
    BOOST_CHECK_THROW(p.as_float(), Error_BadDataType);
    BOOST_CHECK_THROW(p.as_uint16(), Error_BadDataType);
    BOOST_CHECK_THROW(p.as_Vector(), Error_BadDataType);

    //check that the values are good
    BOOST_CHECK_EQUAL(p.as_Matrix().as_uint16At(0, 0), 0);
    BOOST_CHECK_EQUAL(p.as_Matrix().as_uint16At(0, 1), 1);
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asBytes)
{
    ByteStream bytes;
    bytes.append_uint8(1);
    bytes.append_uint8(3);
    bytes.append_uint8(5);

    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_UNKNOWN, valueType_Bytes, anyType(bytes.data()), true);

    //check that the values are good
    BOOST_CHECK_EQUAL(p.as_Bytes().at(0), 1);
    BOOST_CHECK_EQUAL(p.as_Bytes().at(1), 3);
    BOOST_CHECK_EQUAL(p.as_Bytes().at(2), 5);
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asTimestamp)
{
    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_TIMESTAMP, valueType_Timestamp, anyType(Timestamp(1363189940788455000)), true);
    BOOST_CHECK_EQUAL(p.as_Timestamp().str(), "2013-03-13 15:52:20.788455000");

    InertialDataPoint p1((InertialTypes::ChannelField)0, InertialTypes::CH_TIMESTAMP, valueType_float, anyType(3.14f), true);
    BOOST_CHECK_THROW(p1.as_Timestamp(), Error_BadDataType);
}


BOOST_AUTO_TEST_SUITE(InertialDataPoint_asString)

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_uint8)
{
    uint8 val = 240;
    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_uint8, anyType(val), true);

    BOOST_CHECK_EQUAL(p.as_string(), "240");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_uint16)
{
    uint16 val = 25;
    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_uint16, anyType(val), true);

    BOOST_CHECK_EQUAL(p.as_string(), "25");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_uint32)
{
    uint32 val = 1234567890;
    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_uint32, anyType(val), true);

    BOOST_CHECK_EQUAL(p.as_string(), "1234567890");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_int16)
{
    int16 val = -36;
    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_int16, anyType(val), true);

    BOOST_CHECK_EQUAL(p.as_string(), "-36");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_int32)
{
    int32 val = 35;
    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_int32, anyType(val), true);

    BOOST_CHECK_EQUAL(p.as_string(), "35");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_float)
{
    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_float, anyType(1.23f), true);

    BOOST_CHECK_EQUAL(p.as_string(), "1.230000");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_double)
{
    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_double, anyType(4.56), true);

    BOOST_CHECK_EQUAL(p.as_string(), "4.560000");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_Vector)
{
    ByteStream bytes;
    bytes.append_uint16(123);
    bytes.append_uint16(456);
    bytes.append_uint16(789);

    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_Vector, anyType(Vector(valueType_uint16, bytes)), true);

    BOOST_CHECK_EQUAL(p.as_string(), "[123,456,789]");

    ByteStream bytes2;
    bytes2.append_float(1.23f);
    bytes2.append_float(4.56f);
    bytes2.append_float(7.89f);

    InertialDataPoint p2((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_Vector, anyType(Vector(valueType_float, bytes2)), true);

    BOOST_CHECK_EQUAL(p2.as_string(), "[1.23,4.56,7.89]");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_Matrix)
{
    ByteStream bytes;
    bytes.append_float(1.1f);
    bytes.append_float(2.0f);
    bytes.append_float(3.5f);
    bytes.append_float(7.0f);
    bytes.append_float(8.0f);
    bytes.append_float(99876.0f);

    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_Matrix, anyType(Matrix(3, 2, valueType_float, bytes)), true);

    BOOST_CHECK_EQUAL(p.as_string(), "[[1.1,2],[3.5,7],[8,99876]]");

    ByteStream bytes2;
    bytes2.append_uint16(1);
    bytes2.append_uint16(2);
    bytes2.append_uint16(3);
    bytes2.append_uint16(4);
    bytes2.append_uint16(5);
    bytes2.append_uint16(6);

    InertialDataPoint p2((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_Matrix, anyType(Matrix(3, 2, valueType_uint16, bytes2)), true);

    BOOST_CHECK_EQUAL(p2.as_string(), "[[1,2],[3,4],[5,6]]");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_Timestamp)
{
    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_Timestamp, anyType(Timestamp(1363189940788455000)), true);

    BOOST_CHECK_EQUAL(p.as_string(), "2013-03-13 15:52:20.788455000");
}

BOOST_AUTO_TEST_CASE(InertialDataPoint_asString_Bytes)
{
    ByteStream bytes;
    bytes.append_uint8(1);
    bytes.append_uint8(2);
    bytes.append_uint8(3);
    bytes.append_uint8(4);
    bytes.append_uint8(5);
    bytes.append_uint8(10);
    bytes.append_uint8(162);

    InertialDataPoint p((InertialTypes::ChannelField)0, InertialTypes::CH_X, valueType_Bytes, anyType(bytes.data()), true);

    BOOST_CHECK_EQUAL(p.as_string(), "0x01 0x02 0x03 0x04 0x05 0x0a 0xa2");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()