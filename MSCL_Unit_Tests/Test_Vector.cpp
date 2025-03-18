/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Vector.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(Vector_Test)

BOOST_AUTO_TEST_CASE(Vector_valuesType)
{
    ByteStream b;
    Vector v(valueType_float, b);

    //check that the value type is correct
    BOOST_CHECK_EQUAL(v.valuesType(), valueType_float);


    Vector v2(valueType_int32, b);

    //check that the value type is correct
    BOOST_CHECK_EQUAL(v2.valuesType(), valueType_int32);
}

BOOST_AUTO_TEST_CASE(Vector_size)
{
    ByteStream b;
    Vector v(valueType_float, b);

    Vector v3;


    //check that the size is 0
    BOOST_CHECK_EQUAL(v.size(), 0);
    BOOST_CHECK_EQUAL(v3.size(), 0);

    //add 7 floats to the Vector
    b.append_float(1.0f);
    b.append_float(1.0f);
    b.append_float(1.0f);
    b.append_float(1.0f);
    b.append_float(1.0f);
    b.append_float(1.0f);
    b.append_float(1.0f);
    Vector v2(valueType_float, b);

    //check that the size is 7
    BOOST_CHECK_EQUAL(v2.size(), 7);
}

BOOST_AUTO_TEST_CASE(Vector_atFloat)
{
    //add 7 floats to the Vector
    ByteStream b;
    b.append_float(1.0f);
    b.append_float(2.0f);
    b.append_float(3.0f);
    b.append_float(5.0f);
    b.append_float(6.0f);
    b.append_float(7.0f);
    b.append_float(1.234f);
    Vector v(valueType_float, b);

    //check that the values are correct at the given indices
    BOOST_CHECK_CLOSE(v.as_floatAt(0), 1.0, 0.001);
    BOOST_CHECK_CLOSE(v.as_floatAt(1), 2.0, 0.001);
    BOOST_CHECK_CLOSE(v.as_floatAt(2), 3.0, 0.001);
    BOOST_CHECK_CLOSE(v.as_floatAt(3), 5.0, 0.001);
    BOOST_CHECK_CLOSE(v.as_floatAt(4), 6.0, 0.001);
    BOOST_CHECK_CLOSE(v.as_floatAt(5), 7.0, 0.001);
    BOOST_CHECK_CLOSE(v.as_floatAt(6), 1.234, 0.001);

    //check that asking for an invalid index throws an exception
    BOOST_CHECK_THROW(v.as_floatAt(7), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Vector_atUint16)
{
    //add 7 values to the Vector
    ByteStream b;
    b.append_uint16(1);
    b.append_uint16(2);
    b.append_uint16(3);
    b.append_uint16(5);
    b.append_uint16(6);
    b.append_uint16(7);
    b.append_uint16(978);
    Vector v(valueType_uint16, b);

    //check that the values are correct at the given indices
    BOOST_CHECK_EQUAL(v.as_uint16At(0), 1);
    BOOST_CHECK_EQUAL(v.as_uint16At(1), 2);
    BOOST_CHECK_EQUAL(v.as_uint16At(2), 3);
    BOOST_CHECK_EQUAL(v.as_uint16At(3), 5);
    BOOST_CHECK_EQUAL(v.as_uint16At(4), 6);
    BOOST_CHECK_EQUAL(v.as_uint16At(5), 7);
    BOOST_CHECK_EQUAL(v.as_uint16At(6), 978);

    //check that asking for an invalid index throws an exception
    BOOST_CHECK_THROW(v.as_uint16At(7), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
