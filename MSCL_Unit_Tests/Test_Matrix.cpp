/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Matrix.h"
#include "mscl/MicroStrain/ByteStream.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(Matrix_Test)

BOOST_AUTO_TEST_CASE(Matrix_defaultConstructor)
{
    Matrix m;

    //check the matrix initialized correctly
    BOOST_CHECK_EQUAL(m.rows(), 0);
    BOOST_CHECK_EQUAL(m.columns(), 0);
}

BOOST_AUTO_TEST_CASE(Matrix_valuesType)
{
    ByteStream b;
    Matrix m(0, 0, valueType_float, b);

    //check that the value type is correct
    BOOST_CHECK_EQUAL(m.valuesType(), valueType_float);


    Matrix m2(0, 0, valueType_int32, b);

    //check that the value type is correct
    BOOST_CHECK_EQUAL(m2.valuesType(), valueType_int32);
}

BOOST_AUTO_TEST_CASE(Matrix_rows_columns)
{
    ByteStream b;
    Matrix m(10, 12, valueType_float, b);

    //check that the number of rows is correct
    BOOST_CHECK_EQUAL(m.rows(), 10);

    //check that the number of columns is correct
    BOOST_CHECK_EQUAL(m.columns(), 12);
}

BOOST_AUTO_TEST_CASE(Matrix_atFloat)
{
    //add 6 floats to the Matrix
    ByteStream b;
    b.append_float(1.0f);    //row 0, col 0
    b.append_float(2.0f);    //row 0, col 1
    b.append_float(3.0f);    //row 0, col 2
    b.append_float(5.0f);    //row 1, col 0
    b.append_float(6.0f);    //row 1, col 1
    b.append_float(1.234f);    //row 1, col 2

    //create a 2x3 Matrix
    Matrix m(2, 3, valueType_float, b);
    
    //check that the values are correct at the given indices
    BOOST_CHECK_CLOSE(m.as_floatAt(0, 0), 1.0, 0.001);
    BOOST_CHECK_CLOSE(m.as_floatAt(0, 1), 2.0, 0.001);
    BOOST_CHECK_CLOSE(m.as_floatAt(0, 2), 3.0, 0.001);
    BOOST_CHECK_CLOSE(m.as_floatAt(1, 0), 5.0, 0.001);
    BOOST_CHECK_CLOSE(m.as_floatAt(1, 1), 6.0, 0.001);
    BOOST_CHECK_CLOSE(m.as_floatAt(1, 2), 1.234, 0.001);

    //check that asking for an invalid index throws an exception
    BOOST_CHECK_THROW(m.as_floatAt(0, 3), std::out_of_range);
    BOOST_CHECK_THROW(m.as_floatAt(2, 0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Matrix_atUint16)
{
    //add 8 values to the Matrix
    ByteStream b;
    b.append_uint16(1);        //row 0, col 0
    b.append_uint16(2);        //row 0, col 1
    b.append_uint16(3);        //row 1, col 0
    b.append_uint16(4);        //row 1, col 1
    b.append_uint16(5);        //row 2, col 0
    b.append_uint16(6);        //row 2, col 1
    b.append_uint16(7);        //row 3, col 0
    b.append_uint16(12345);    //row 3, col 1

    //create a 4x2 Matrix
    Matrix m(4, 2, valueType_uint16, b);
    
    //check that the values are correct at the given indices
    BOOST_CHECK_EQUAL(m.as_uint16At(0, 0), 1);
    BOOST_CHECK_EQUAL(m.as_uint16At(0, 1), 2);
    BOOST_CHECK_EQUAL(m.as_uint16At(1, 0), 3);
    BOOST_CHECK_EQUAL(m.as_uint16At(1, 1), 4);
    BOOST_CHECK_EQUAL(m.as_uint16At(2, 0), 5);
    BOOST_CHECK_EQUAL(m.as_uint16At(2, 1), 6);
    BOOST_CHECK_EQUAL(m.as_uint16At(3, 0), 7);
    BOOST_CHECK_EQUAL(m.as_uint16At(3, 1), 12345);

    //check that asking for an invalid index throws an exception
    BOOST_CHECK_THROW(m.as_uint16At(0, 2), std::out_of_range);
    BOOST_CHECK_THROW(m.as_uint16At(4, 0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Matrix_as_uint8At)
{
    //add 8 values to the Matrix
    ByteStream b;
    b.append_uint8(1);        //row 0, col 0
    b.append_uint8(2);        //row 0, col 1
    b.append_uint8(3);        //row 1, col 0
    b.append_uint8(4);        //row 1, col 1
    b.append_uint8(5);        //row 2, col 0
    b.append_uint8(6);        //row 2, col 1
    b.append_uint8(7);        //row 3, col 0
    b.append_uint8(8);        //row 3, col 1

    //create a 4x2 Matrix
    Matrix m(4, 2, valueType_uint8, b);

    //check that the values are correct at the given indices
    BOOST_CHECK_EQUAL(m.as_uint8At(0, 0), 1);
    BOOST_CHECK_EQUAL(m.as_uint8At(0, 1), 2);
    BOOST_CHECK_EQUAL(m.as_uint8At(1, 0), 3);
    BOOST_CHECK_EQUAL(m.as_uint8At(1, 1), 4);
    BOOST_CHECK_EQUAL(m.as_uint8At(2, 0), 5);
    BOOST_CHECK_EQUAL(m.as_uint8At(2, 1), 6);
    BOOST_CHECK_EQUAL(m.as_uint8At(3, 0), 7);
    BOOST_CHECK_EQUAL(m.as_uint8At(3, 1), 8);

    //check that asking for an invalid index throws an exception
    BOOST_CHECK_THROW(m.as_uint8At(0, 2), std::out_of_range);
    BOOST_CHECK_THROW(m.as_uint8At(4, 0), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()