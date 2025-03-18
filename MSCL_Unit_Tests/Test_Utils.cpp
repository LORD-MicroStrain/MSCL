/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Utils.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(Utils_Test)

//===================================================================================================================
//                                                Utils Byte Conversions
//===================================================================================================================
BOOST_AUTO_TEST_SUITE(Utils_ByteOperations)

//Test the msb() and lsb() functions
BOOST_AUTO_TEST_CASE(Utils_MSB_LSB)
{
    //check that the msb of 0x12 is 0x00
    BOOST_CHECK_EQUAL( Utils::msb(0x12), 0x00 );

    //check that the msb of 0x3456 is 0x34
    BOOST_CHECK_EQUAL( Utils::msb(0x3456), 0x34 );

    //check that the lsb of 0x12 is 0x12
    BOOST_CHECK_EQUAL( Utils::lsb(0x12), 0x12 );

    //check that the lsb of 0x3456 is 0x56
    BOOST_CHECK_EQUAL( Utils::lsb(0x3456), 0x56 );
}

BOOST_AUTO_TEST_CASE(Utils_splitFloatBigEndian)
{
    uint8 b1, b2, b3, b4;

    Utils::split_float(123.456789f, b1, b2, b3, b4, Utils::bigEndian);

#if defined(BOOST_ENDIAN_LITTLE_BYTE) || defined(BOOST_LITTLE_ENDIAN)

    BOOST_CHECK_EQUAL(b1, 0x42);
    BOOST_CHECK_EQUAL(b2, 0xF6);
    BOOST_CHECK_EQUAL(b3, 0xE9);
    BOOST_CHECK_EQUAL(b4, 0xE0);

#else

    BOOST_CHECK_EQUAL(b1, 0xE0);
    BOOST_CHECK_EQUAL(b2, 0xE9);
    BOOST_CHECK_EQUAL(b3, 0xF6);
    BOOST_CHECK_EQUAL(b4, 0x42);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_splitFloatLittleEndian)
{
    uint8 b1, b2, b3, b4;

    Utils::split_float(123.456789f, b1, b2, b3, b4, Utils::littleEndian);

#if defined(BOOST_ENDIAN_LITTLE_BYTE) || defined(BOOST_LITTLE_ENDIAN)

    BOOST_CHECK_EQUAL(b1, 0xE0);
    BOOST_CHECK_EQUAL(b2, 0xE9);
    BOOST_CHECK_EQUAL(b3, 0xF6);
    BOOST_CHECK_EQUAL(b4, 0x42);

#else

    BOOST_CHECK_EQUAL(b1, 0x42);
    BOOST_CHECK_EQUAL(b2, 0xF6);
    BOOST_CHECK_EQUAL(b3, 0xE9);
    BOOST_CHECK_EQUAL(b4, 0xE0);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_makeFloatBigEndian)
{

#if defined(BOOST_ENDIAN_LITTLE_BYTE) || defined(BOOST_LITTLE_ENDIAN)

    float val = Utils::make_float(0x42, 0xF6, 0xE9, 0xE0, Utils::bigEndian);

    BOOST_CHECK_CLOSE(val, 123.456789, 0.00001);

#else

    float val = Utils::make_float(0xE0, 0xE9, 0xF6, 0x42, Utils::bigEndian);

    BOOST_CHECK_CLOSE(val, 123.456789, 0.00001);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_makeFloatLittleEndian)
{

#if defined(BOOST_ENDIAN_LITTLE_BYTE) || defined(BOOST_LITTLE_ENDIAN)

    float val = Utils::make_float(0xE0, 0xE9, 0xF6, 0x42, Utils::littleEndian);

    BOOST_CHECK_CLOSE(val, 123.456789, 0.00001);

#else

    float val = Utils::make_float(0x42, 0xF6, 0xE9, 0xE0, Utils::littleEndian);

    BOOST_CHECK_CLOSE(val, 123.456789, 0.00001);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_splitDoubleBigEndian)
{
    uint8 b1, b2, b3, b4, b5, b6, b7, b8;

    Utils::split_double(12.34567, b1, b2, b3, b4, b5, b6, b7, b8, Utils::bigEndian);

#if defined(BOOST_ENDIAN_LITTLE_BYTE) || defined(BOOST_LITTLE_ENDIAN)

    BOOST_CHECK_EQUAL(b1, 0x40);
    BOOST_CHECK_EQUAL(b2, 0x28);
    BOOST_CHECK_EQUAL(b3, 0xB0);
    BOOST_CHECK_EQUAL(b4, 0xFB);
    BOOST_CHECK_EQUAL(b5, 0xA8);
    BOOST_CHECK_EQUAL(b6, 0x82);
    BOOST_CHECK_EQUAL(b7, 0x6A);
    BOOST_CHECK_EQUAL(b8, 0xA9);

#else

    BOOST_CHECK_EQUAL(b1, 0xA9);
    BOOST_CHECK_EQUAL(b2, 0x6A);
    BOOST_CHECK_EQUAL(b3, 0x82);
    BOOST_CHECK_EQUAL(b4, 0xA8);
    BOOST_CHECK_EQUAL(b5, 0xFB);
    BOOST_CHECK_EQUAL(b6, 0xB0);
    BOOST_CHECK_EQUAL(b7, 0x28);
    BOOST_CHECK_EQUAL(b8, 0x40);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_splitDoubleLittleEndian)
{
    uint8 b1, b2, b3, b4, b5, b6, b7, b8;

    Utils::split_double(12.34567, b1, b2, b3, b4, b5, b6, b7, b8, Utils::littleEndian);

#if defined(BOOST_ENDIAN_LITTLE_BYTE) || defined(BOOST_LITTLE_ENDIAN)

    BOOST_CHECK_EQUAL(b1, 0xA9);
    BOOST_CHECK_EQUAL(b2, 0x6A);
    BOOST_CHECK_EQUAL(b3, 0x82);
    BOOST_CHECK_EQUAL(b4, 0xA8);
    BOOST_CHECK_EQUAL(b5, 0xFB);
    BOOST_CHECK_EQUAL(b6, 0xB0);
    BOOST_CHECK_EQUAL(b7, 0x28);
    BOOST_CHECK_EQUAL(b8, 0x40);

#else

    BOOST_CHECK_EQUAL(b1, 0x40);
    BOOST_CHECK_EQUAL(b2, 0x28);
    BOOST_CHECK_EQUAL(b3, 0xB0);
    BOOST_CHECK_EQUAL(b4, 0xFB);
    BOOST_CHECK_EQUAL(b5, 0xA8);
    BOOST_CHECK_EQUAL(b6, 0x82);
    BOOST_CHECK_EQUAL(b7, 0x6A);
    BOOST_CHECK_EQUAL(b8, 0xA9);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_makeDoubleBigEndian)
{

#if defined(BOOST_ENDIAN_LITTLE_BYTE) || defined(BOOST_LITTLE_ENDIAN)

    double val = Utils::make_double(0x40, 0x28, 0xb0, 0xfb, 0xa8, 0x82, 0x6a, 0xa9, Utils::bigEndian);

    BOOST_CHECK_CLOSE(val, 12.34567, 0.00001);

#else

    double val = Utils::make_double(0xa9, 0x6a, 0x82, 0xa8, 0xfb, 0xb0, 0x28, 0x40, Utils::bigEndian);

    BOOST_CHECK_CLOSE(val, 12.34567, 0.00001);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_makeDoubleLittleEndian)
{

#if defined(BOOST_ENDIAN_LITTLE_BYTE) || defined(BOOST_LITTLE_ENDIAN)

    double val = Utils::make_double(0xa9, 0x6a, 0x82, 0xa8, 0xfb, 0xb0, 0x28, 0x40, Utils::littleEndian);

    BOOST_CHECK_CLOSE(val, 12.34567, 0.00001);

#else

    double val = Utils::make_double(0x40, 0x28, 0xb0, 0xfb, 0xa8, 0x82, 0x6a, 0xa9, Utils::littleEndian);

    BOOST_CHECK_CLOSE(val, 12.34567, 0.00001);

#endif
}

//Test the splitWord() function
BOOST_AUTO_TEST_CASE(Utils_splitWord)
{
    uint8 msb, lsb;

    uint16 value = 0x1234;

    //convert the word value into 2 bytes
    Utils::split_uint16(value, msb, lsb);

    //verify that the msb is now 0x12
    BOOST_CHECK_EQUAL(msb, 0x12);

    //verify that the lsb is now 0x34
    BOOST_CHECK_EQUAL(lsb, 0x34);


    value = 0x56;

    //convert the word value into 2 bytes
    Utils::split_uint16(value, msb, lsb);

    //verify that the msb is now 0x00
    BOOST_CHECK_EQUAL(msb, 0x00);

    //verify that the lsb is now 0x56
    BOOST_CHECK_EQUAL(lsb, 0x56);
}

//Test the splitDWord() function
BOOST_AUTO_TEST_CASE(Utils_splitDWord)
{
    uint8 b1, b2, b3, b4;

    uint32 value = 0x12345678;

    //convert the dword value to 4 bytes
    Utils::split_uint32(value, b1, b2, b3, b4);

    //verify that b1 is now 0x12
    BOOST_CHECK_EQUAL(b1, 0x12);

    //verify that b2 is now 0x34
    BOOST_CHECK_EQUAL(b2, 0x34);

    //verify that b3 is now 0x56
    BOOST_CHECK_EQUAL(b3, 0x56);

    //verify that b4 is now 0x78
    BOOST_CHECK_EQUAL(b4, 0x78);


    uint16 wordVal = 0x1234;

    //convert the word value to 4 bytes
    Utils::split_uint32(wordVal, b1, b2, b3, b4);

    //verify that b1 is now 0x00
    BOOST_CHECK_EQUAL(b1, 0x00);

    //verify that b2 is now 0x00
    BOOST_CHECK_EQUAL(b2, 0x00);

    //verify that b3 is now 0x12
    BOOST_CHECK_EQUAL(b3, 0x12);

    //verify that b4 is now 0x34
    BOOST_CHECK_EQUAL(b4, 0x34);
}

BOOST_AUTO_TEST_CASE(Utils_Make_int16)
{
    int16 result;

    uint8 msb = 0x80;
    uint8 lsb = 0x02;

    //build the bytes into a word
    result = Utils::make_int16(msb, lsb);

    //verify that the word result is now 0x
    BOOST_CHECK_EQUAL(result, -32766);
}

BOOST_AUTO_TEST_CASE(Utils_Make_uint16)
{
    uint16 result;

    uint8 msb = 0x12;
    uint8 lsb = 0x34;

    //build the bytes into a word
    result = Utils::make_uint16(msb, lsb);

    //verify that the word result is now 0x1234
    BOOST_CHECK_EQUAL(result, 0x1234);

    msb = 0x00;
    lsb = 0x56;

    //build the bytes into a word
    result = Utils::make_uint16(msb, lsb);

    //verify that the word result is now 0x56
    BOOST_CHECK_EQUAL(result, 0x56);

    msb = 0x78;
    lsb = 0x00;

    //build the bytes into a word
    result = Utils::make_uint16(msb, lsb);

    //verify that the word result is now 0x7800
    BOOST_CHECK_EQUAL(result, 0x7800);
}

BOOST_AUTO_TEST_CASE(Utils_Make_uint32)
{
    uint32 result;

    uint8 b1 = 0x12;
    uint8 b2 = 0x34;
    uint8 b3 = 0x56;
    uint8 b4 = 0x78;


    //build the bytes into a dword
    result = Utils::make_uint32(b1, b2, b3, b4);

    //verify that the word result is now 0x12345678
    BOOST_CHECK_EQUAL(result, 0x12345678);

    b1 = 0x00;
    b2 = 0x00;
    b3 = 0x12;
    b4 = 0x34;

    //build the bytes into a dword
    result = Utils::make_uint32(b1, b2, b3, b4);

    //verify that the dword result is now 0x1234
    BOOST_CHECK_EQUAL(result, 0x1234);

    b1 = 0x56;
    b2 = 0x78;
    b3 = 0x00;
    b4 = 0x00;

    //build the bytes into a dword
    result = Utils::make_uint32(b1, b2, b3, b4);

    //verify that the word result is now 0x56780000
    BOOST_CHECK_EQUAL(result, 0x56780000);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(Utils_GetSystemTime)
{
    uint64 time1 = Utils::getCurrentSystemTime();
    Utils::threadSleep(200);
    uint64 sleepNano = 200000000;
    uint64 time2 = Utils::getCurrentSystemTime();

    //check that time 2 comes after time 1
    BOOST_CHECK( time1 < time2 );

    uint64 diff = time2 - time1;

    // check reported difference at least length of sleep time
    BOOST_CHECK(diff >= sleepNano);

    // check diff within 10% of sleep time
    BOOST_CHECK(diff < sleepNano * 1.1);
}

BOOST_AUTO_TEST_CASE(Utils_valueTypeSize)
{
    BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_double), 8);
    BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_float), 4);
    BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_int32), 4);
    BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_int16), 2);
    BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_uint16), 2);
    BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_uint32), 4);
    BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_uint8), 1);
    BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_bool), 1);
    BOOST_CHECK_THROW(Utils::valueTypeSize(valueType_Vector), Error);
}

BOOST_AUTO_TEST_CASE(Utils_round)
{
    BOOST_CHECK_CLOSE(Utils::round(4.50f), 5.0, 0.1);
    BOOST_CHECK_CLOSE(Utils::round(2.7f), 3.0, 0.1);
    BOOST_CHECK_CLOSE(Utils::round(4.49f), 4.0, 0.1);
    BOOST_CHECK_CLOSE(Utils::round(4.23f), 4.0, 0.1);
}

BOOST_AUTO_TEST_CASE(Utils_floorBase2)
{
    BOOST_CHECK_EQUAL(Utils::floorBase2(256), 256);
    BOOST_CHECK_EQUAL(Utils::floorBase2(251), 128);
    BOOST_CHECK_EQUAL(Utils::floorBase2(4000), 2048);
    BOOST_CHECK_EQUAL(Utils::floorBase2(32.0), 32);
}

BOOST_AUTO_TEST_CASE(Utils_ceilBase2)
{
    BOOST_CHECK_EQUAL(Utils::ceilBase2(256), 256);
    BOOST_CHECK_EQUAL(Utils::ceilBase2(251), 256);
    BOOST_CHECK_EQUAL(Utils::ceilBase2(4000), 4096);
    BOOST_CHECK_EQUAL(Utils::ceilBase2(32.0), 32);
}

BOOST_AUTO_TEST_CASE(Utils_bitIsSet)
{
    uint16 val = 82; //01010010

    BOOST_CHECK_EQUAL(Utils::bitIsSet(val, 0), false);
    BOOST_CHECK_EQUAL(Utils::bitIsSet(val, 1), true);
    BOOST_CHECK_EQUAL(Utils::bitIsSet(val, 2), false);
    BOOST_CHECK_EQUAL(Utils::bitIsSet(val, 3), false);
    BOOST_CHECK_EQUAL(Utils::bitIsSet(val, 4), true);
    BOOST_CHECK_EQUAL(Utils::bitIsSet(val, 5), false);
    BOOST_CHECK_EQUAL(Utils::bitIsSet(val, 6), true);
    BOOST_CHECK_EQUAL(Utils::bitIsSet(val, 7), false);
    BOOST_CHECK_EQUAL(Utils::bitIsSet(val, 8), false);
}

BOOST_AUTO_TEST_CASE(Utils_removeChar)
{
    //test removing all the 't' characters
    std::string test = "This is a test string";
    Utils::removeChar(test, 't');
    BOOST_CHECK_EQUAL(test, "This is a es sring");

    //test removing all the spaces
    Utils::removeChar(test, ' ');
    BOOST_CHECK_EQUAL(test, "Thisisaessring");

    //test removing a char that doesn't exist has no effect
    Utils::removeChar(test, 'z');
    BOOST_CHECK_EQUAL(test, "Thisisaessring");
}

BOOST_AUTO_TEST_CASE(Utils_removeStr)
{
    //test removing a single substring
    std::string test = "This is a test string";
    Utils::removeStr(test, "is a test ");
    BOOST_CHECK_EQUAL(test, "This string");

    //test removing a substring that shows up multiple times
    std::string test2 = "Hello World. How are you? Hello World.";
    Utils::removeStr(test2, "Hello World.");
    BOOST_CHECK_EQUAL(test2, " How are you? ");

    std::string test3 = "Hello World.";
    Utils::removeStr(test3, "Hellos");
    BOOST_CHECK_EQUAL(test3, "Hello World.");
}

BOOST_AUTO_TEST_CASE(Utils_containsStr)
{
    std::string full = "Hello world. How are you feeling today world?";

    BOOST_CHECK_EQUAL(Utils::containsStr(full, "world"), true);
    BOOST_CHECK_EQUAL(Utils::containsStr(full, "How are you doing"), false);
}

BOOST_AUTO_TEST_CASE(Utils_strTrimLeft)
{
    std::string test = "    \r\nThis is a string";

    Utils::strTrimLeft(test);
    BOOST_CHECK_EQUAL(test, "This is a string");

    Utils::strTrimLeft(test);
    BOOST_CHECK_EQUAL(test, "This is a string");

    test = "another string     \r\n";

    Utils::strTrimLeft(test);
    BOOST_CHECK_EQUAL(test, "another string     \r\n");
}

BOOST_AUTO_TEST_CASE(Utils_strTrimRight)
{
    std::string test = "This is a string    \r\n";

    Utils::strTrimRight(test);
    BOOST_CHECK_EQUAL(test, "This is a string");

    Utils::strTrimRight(test);
    BOOST_CHECK_EQUAL(test, "This is a string");

    test = "    \r\nanother string     \r\n";

    Utils::strTrimRight(test);
    BOOST_CHECK_EQUAL(test, "    \r\nanother string");
}

BOOST_AUTO_TEST_CASE(Utils_filterSensorcloudName)
{
    std::string test = "inertial-node-6500.1234";
    Utils::filterSensorcloudName(test);
    BOOST_CHECK_EQUAL(test, "inertial-node-6500.1234");

    test = "this is test?! Oh_My~*$%";
    Utils::filterSensorcloudName(test);
    BOOST_CHECK_EQUAL(test, "this-is-test---Oh_My----");
}

//TODO: Commented out the following because they give slightly different results on different machines (windows vs linux?)
/*
BOOST_AUTO_TEST_CASE(Utils_toStr)
{
    uint16 i = 64298;
    BOOST_CHECK_EQUAL(Utils::toStr(i), "64298");

    float f = 80045.942165472f;
    BOOST_CHECK_CLOSE(f, 80045.945313, 0.000001);
    BOOST_CHECK_EQUAL(Utils::toStr(f), "80045.945313");

    double d = 197321454.00942165472843;
    BOOST_CHECK_CLOSE(d, 197321454.00942165, 0.000000000000001);
    BOOST_CHECK_EQUAL(Utils::toStr(d), "197321454.009422");

    double d2 = 0.00942165472843;
    BOOST_CHECK_CLOSE(d2, 0.00942165472843, 0.000000000000001);
    BOOST_CHECK_EQUAL(Utils::toStr(d2), "0.009422");
}

BOOST_AUTO_TEST_CASE(Utils_toStrWithPrecision)
{
    uint16 i = 64298;
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(i), "64298");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(i, 20), "64298");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(i, 0), "64298");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(i, 1), "64298");

    float f = 80045.942165472f;
    BOOST_CHECK_CLOSE(f, 80045.945313, 0.000001);
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(f), "80045.9");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(f, 20), "80045.9453125");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(f, 0), "80045.9");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(f, 1), "8e+004");

    double d = 197321454.00942165472843;
    BOOST_CHECK_CLOSE(d, 197321454.00942165, 0.000000000000001);
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d), "1.97321e+008");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d, 20), "197321454.00942165");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d, 0), "1.97321e+008");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d, 1), "2e+008");

    double d2 = 0.00942165472843;
    BOOST_CHECK_CLOSE(d2, 0.00942165472843, 0.000000000000001);
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d2), "0.00942165");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d2, 20), "0.0094216547284300001");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d2, 0), "0.00942165");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d2, 1), "0.009");
}

BOOST_AUTO_TEST_CASE(Utils_toStrWithPrecision_fixed)
{
    uint16 i = 64298;
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(i), "64298");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(i, 5, true), "64298");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(i, 0, true), "64298");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(i, 1, true), "64298");

    float f = 80045.942165472f;
    BOOST_CHECK_CLOSE(f, 80045.945313, 0.000001);
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(f), "80045.9");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(f, 5, true), "80045.94531");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(f, 0, true), "80046");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(f, 1, true), "80045.9");

    double d = 197321454.00942165472843;
    BOOST_CHECK_CLOSE(d, 197321454.00942165, 0.000000000000001);
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d), "1.97321e+008");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d, 5, true), "197321454.00942");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d, 0, true), "197321454");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d, 1, true), "197321454.0");

    double d2 = 0.00942165472843;
    BOOST_CHECK_CLOSE(d2, 0.00942165472843, 0.000000000000001);
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d2), "0.00942165");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d2, 5, true), "0.00942");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d2, 0, true), "0");
    BOOST_CHECK_EQUAL(Utils::toStrWithPrecision(d2, 1, true), "0.0");
}
*/

BOOST_AUTO_TEST_SUITE_END()
