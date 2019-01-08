/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/Value.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(Value_Test)

BOOST_AUTO_TEST_CASE(Value_as_float)
{
    Value val_float(valueType_float, anyType((float)123.456f));
    Value val_double(valueType_double, anyType((double)1.761234));
    Value val_uint16(valueType_uint16, anyType((uint16)12));
    Value val_uint32(valueType_uint32, anyType((uint32)1234567890));
    Value val_int16(valueType_int16, anyType((int16)-48));
    Value val_int32(valueType_int32, anyType((int32)-34));
    Value val_uint8(valueType_uint8, anyType((uint8)12));
    Value val_bool(valueType_bool, anyType(true));
    Value val_string(valueType_string, anyType((std::string)"789"));

    //check the result of calling as_float
    BOOST_CHECK_CLOSE(val_float.as_float(), 123.456, 0.1);
    BOOST_CHECK_CLOSE(val_double.as_float(), 1.761234, 0.1);
    BOOST_CHECK_EQUAL(val_uint16.as_float(), 12.0);
    BOOST_CHECK_CLOSE(val_uint32.as_float(), 1234567890.0, 0.1);
    BOOST_CHECK_EQUAL(val_int16.as_float(), -48.0);
    BOOST_CHECK_EQUAL(val_int32.as_float(), -34.0);
    BOOST_CHECK_EQUAL(val_uint8.as_float(), 12.0);
    BOOST_CHECK_EQUAL(val_bool.as_float(), 1.0);
    BOOST_CHECK_CLOSE(val_string.as_float(), 789.0, 0.001);
}

BOOST_AUTO_TEST_CASE(Value_as_double)
{
    Value val_float(valueType_float, anyType((float)123.456f));
    Value val_double(valueType_double, anyType((double)1.7E50));
    Value val_uint16(valueType_uint16, anyType((uint16)12));
    Value val_uint32(valueType_uint32, anyType((uint32)1234567890));
    Value val_int16(valueType_int16, anyType((int16)-48));
    Value val_int32(valueType_int32, anyType((int32)-34));
    Value val_uint8(valueType_uint8, anyType((uint8)12));
    Value val_bool(valueType_bool, anyType(true));
    Value val_string(valueType_string, anyType((std::string)"789.9456"));

    //check the result of calling as_double
    BOOST_CHECK_CLOSE(val_float.as_double(), 123.456, 0.1);
    BOOST_CHECK_CLOSE(val_double.as_double(), 1.7E50, 0.1);
    BOOST_CHECK_EQUAL(val_uint16.as_double(), 12.0);
    BOOST_CHECK_CLOSE(val_uint32.as_double(), 1234567890.0, 0.1);
    BOOST_CHECK_EQUAL(val_int16.as_double(), -48.0);
    BOOST_CHECK_EQUAL(val_int32.as_double(), -34.0);
    BOOST_CHECK_EQUAL(val_uint8.as_double(), 12.0);
    BOOST_CHECK_EQUAL(val_bool.as_double(), 1.0);
    BOOST_CHECK_CLOSE(val_string.as_double(), 789.9456, 0.001);
}

BOOST_AUTO_TEST_CASE(Value_as_uint8)
{
    Value val_float(valueType_float, anyType((float)123.456f));
    Value val_double(valueType_double, anyType((double)1.7E50));
    Value val_uint16(valueType_uint16, anyType((uint16)12));
    Value val_uint32(valueType_uint32, anyType((uint32)1234567890));
    Value val_int16(valueType_int16, anyType((int16)-48));
    Value val_int32(valueType_int32, anyType((int32)34));
    Value val_uint8(valueType_uint8, anyType((uint8)12));
    Value val_bool(valueType_bool, anyType(true));
    Value val_string(valueType_string, anyType((std::string)"240"));

    //check the result of calling as_uint8
    BOOST_CHECK_EQUAL(val_float.as_uint8(), 123);
    BOOST_CHECK_EQUAL(val_double.as_uint8(), 0);
    BOOST_CHECK_EQUAL(val_uint16.as_uint8(), 12);
    BOOST_CHECK_EQUAL(val_uint32.as_uint8(), 0xd2);
    BOOST_CHECK_EQUAL(val_int16.as_uint8(), 0xd0);
    BOOST_CHECK_EQUAL(val_int32.as_uint8(), 34);
    BOOST_CHECK_EQUAL(val_uint8.as_uint8(), 12);
    BOOST_CHECK_EQUAL(val_bool.as_uint8(), 1);
    BOOST_CHECK_EQUAL(val_string.as_uint8(), 240);
}

BOOST_AUTO_TEST_CASE(Value_as_uint16)
{
    Value val_float(valueType_float, anyType((float)123.456f));
    Value val_double(valueType_double, anyType((double)1.7E50));
    Value val_uint16(valueType_uint16, anyType((uint16)65531));
    Value val_uint32(valueType_uint32, anyType((uint32)1234567890));
    Value val_int16(valueType_int16, anyType((int16)-48));
    Value val_int32(valueType_int32, anyType((int32)65510));
    Value val_uint8(valueType_uint8, anyType((uint8)12));
    Value val_bool(valueType_bool, anyType(false));
    Value val_string(valueType_string, anyType((std::string)"240"));

    //check the result of calling as_uint16
    BOOST_CHECK_EQUAL(val_float.as_uint16(), 123);
    BOOST_CHECK_EQUAL(val_double.as_uint16(), 0);
    BOOST_CHECK_EQUAL(val_uint16.as_uint16(), 65531);
    BOOST_CHECK_EQUAL(val_uint32.as_uint16(), 722);
    BOOST_CHECK_EQUAL(val_int16.as_uint16(), 65488);
    BOOST_CHECK_EQUAL(val_int32.as_uint16(), 65510);
    BOOST_CHECK_EQUAL(val_uint8.as_uint16(), 12);
    BOOST_CHECK_EQUAL(val_bool.as_uint16(), 0);
    BOOST_CHECK_EQUAL(val_string.as_uint16(), 240);
}

BOOST_AUTO_TEST_CASE(Value_as_uint32)
{
    Value val_float(valueType_float, anyType((float)123.456f));
    Value val_double(valueType_double, anyType((double)65598.0));
    Value val_uint16(valueType_uint16, anyType((uint16)65531));
    Value val_uint32(valueType_uint32, anyType((uint32)1234567890));
    Value val_int16(valueType_int16, anyType((int16)-48));
    Value val_int32(valueType_int32, anyType((int32)65510));
    Value val_uint8(valueType_uint8, anyType((uint8)12));
    Value val_bool(valueType_bool, anyType(false));
    Value val_string(valueType_string, anyType((std::string)"789456"));

    //check the result of calling as_uint32
    BOOST_CHECK_EQUAL(val_float.as_uint32(), 123);
    BOOST_CHECK_EQUAL(val_double.as_uint32(), 65598);
    BOOST_CHECK_EQUAL(val_uint16.as_uint32(), 65531);
    BOOST_CHECK_EQUAL(val_uint32.as_uint32(), 1234567890);
    BOOST_CHECK_EQUAL(val_int16.as_uint32(), 4294967248);
    BOOST_CHECK_EQUAL(val_int32.as_uint32(), 65510);
    BOOST_CHECK_EQUAL(val_uint8.as_uint32(), 12);
    BOOST_CHECK_EQUAL(val_bool.as_uint32(), 0);
    BOOST_CHECK_EQUAL(val_string.as_uint32(), 789456);
}

BOOST_AUTO_TEST_CASE(Value_as_int16)
{
    Value val_float(valueType_float, anyType((float)-123.456f));
    Value val_double(valueType_double, anyType((double)65598.0));
    Value val_uint16(valueType_uint16, anyType((uint16)65531));
    Value val_uint32(valueType_uint32, anyType((uint32)32000));
    Value val_int16(valueType_int16, anyType((int16)-48));
    Value val_int32(valueType_int32, anyType((int32)65510));
    Value val_uint8(valueType_uint8, anyType((uint8)12));
    Value val_bool(valueType_bool, anyType(false));
    Value val_string(valueType_string, anyType((std::string)"789456"));

    //check the result of calling as_int16
    BOOST_CHECK_EQUAL(val_float.as_int16(), -123);
    BOOST_CHECK_EQUAL(val_double.as_int16(), 62);
    BOOST_CHECK_EQUAL(val_uint16.as_int16(), -5);
    BOOST_CHECK_EQUAL(val_uint32.as_int16(), 32000);
    BOOST_CHECK_EQUAL(val_int16.as_int16(), -48);
    BOOST_CHECK_EQUAL(val_int32.as_int16(), -26);
    BOOST_CHECK_EQUAL(val_uint8.as_int16(), 12);
    BOOST_CHECK_EQUAL(val_bool.as_int16(), 0);
    BOOST_CHECK_EQUAL(val_string.as_int16(), 3024);
}

BOOST_AUTO_TEST_CASE(Value_as_int32)
{
    Value val_float(valueType_float, anyType((float)-123.456f));
    Value val_double(valueType_double, anyType((double)-65598.0));
    Value val_uint16(valueType_uint16, anyType((uint16)65531));
    Value val_uint32(valueType_uint32, anyType((uint32)32000));
    Value val_int16(valueType_int16, anyType((int16)-48));
    Value val_int32(valueType_int32, anyType((int32)65510));
    Value val_uint8(valueType_uint8, anyType((uint8)12));
    Value val_bool(valueType_bool, anyType(false));
    Value val_string(valueType_string, anyType((std::string)"789456"));

    //check the result of calling as_uint32
    BOOST_CHECK_EQUAL(val_float.as_int32(), -123);
    BOOST_CHECK_EQUAL(val_double.as_int32(), -65598);
    BOOST_CHECK_EQUAL(val_uint16.as_int32(), 65531);
    BOOST_CHECK_EQUAL(val_uint32.as_int32(), 32000);
    BOOST_CHECK_EQUAL(val_int16.as_int32(), -48);
    BOOST_CHECK_EQUAL(val_int32.as_int32(), 65510);
    BOOST_CHECK_EQUAL(val_uint8.as_int32(), 12);
    BOOST_CHECK_EQUAL(val_bool.as_int32(), 0);
    BOOST_CHECK_EQUAL(val_string.as_int32(), 789456);
}

BOOST_AUTO_TEST_CASE(Value_as_bool)
{
    Value val_float(valueType_float, anyType((float)-345.10f));
    Value val_double(valueType_double, anyType((double)0.0001));
    Value val_double2(valueType_double, anyType((double)0.000));
    Value val_uint16(valueType_uint16, anyType((uint16)1));
    Value val_uint32(valueType_uint32, anyType((uint32)1));
    Value val_int16(valueType_int16, anyType((int16)0));
    Value val_int32(valueType_int32, anyType((int32)65510));
    Value val_uint8(valueType_uint8, anyType((uint8)12));
    Value val_bool(valueType_bool, anyType(false));
    Value val_string(valueType_string, anyType((std::string)"789456"));
    Value val_string2(valueType_string, anyType((std::string)"0000"));

    //check the result of calling as_bool
    BOOST_CHECK_EQUAL(val_float.as_bool(), true);
    BOOST_CHECK_EQUAL(val_double.as_bool(), true);
    BOOST_CHECK_EQUAL(val_double2.as_bool(), false);
    BOOST_CHECK_EQUAL(val_uint16.as_bool(), true);
    BOOST_CHECK_EQUAL(val_uint32.as_bool(), true);
    BOOST_CHECK_EQUAL(val_int16.as_bool(), false);
    BOOST_CHECK_EQUAL(val_int32.as_bool(), true);
    BOOST_CHECK_EQUAL(val_uint8.as_bool(), true);
    BOOST_CHECK_EQUAL(val_bool.as_bool(), false);
    BOOST_CHECK_EQUAL(val_string.as_bool(), true);
    BOOST_CHECK_EQUAL(val_string2.as_bool(), false);
}

BOOST_AUTO_TEST_CASE(Value_as_string)
{
    Value val_uint16(valueType_uint16, anyType((uint16)65531));
    Value val_uint32(valueType_uint32, anyType((uint32)32000));
    Value val_int16(valueType_int16, anyType((int16)-48));
    Value val_int32(valueType_int32, anyType((int32)65510));
    Value val_uint8(valueType_uint8, anyType((uint8)12));
    Value val_bool(valueType_bool, anyType(false));
    Value val_string(valueType_string, anyType((std::string)"hello world"));

    //check the result of calling as_string
    BOOST_CHECK_EQUAL(val_uint16.as_string(), "65531");
    BOOST_CHECK_EQUAL(val_uint32.as_string(), "32000");
    BOOST_CHECK_EQUAL(val_int16.as_string(), "-48");
    BOOST_CHECK_EQUAL(val_int32.as_string(), "65510");
    BOOST_CHECK_EQUAL(val_uint8.as_string(), "12");
    BOOST_CHECK_EQUAL(val_bool.as_string(), "0");
    BOOST_CHECK_EQUAL(val_string.as_string(), "hello world");
}

BOOST_AUTO_TEST_SUITE_END()