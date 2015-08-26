/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#include "mscl/Types.h"
#include "mscl/Utils.h"
#include "mscl/Exceptions.h"

#include <boost/detail/endian.hpp>
#include <boost/test/unit_test.hpp>
#include <turtle/mock.hpp>

using namespace mscl;
using namespace mscl::Utils;

BOOST_AUTO_TEST_SUITE(Utils_Test)

//===================================================================================================================
//												Utils Byte Conversions
//===================================================================================================================
BOOST_AUTO_TEST_SUITE(Utils_ByteOperations)

//Test the msb() and lsb() functions
BOOST_AUTO_TEST_CASE(Utils_MSB_LSB)
{
	//check that the msb of 0x12 is 0x00
	BOOST_CHECK_EQUAL( msb(0x12), 0x00 );

	//check that the msb of 0x3456 is 0x34
	BOOST_CHECK_EQUAL( msb(0x3456), 0x34 );

	//check that the lsb of 0x12 is 0x12
	BOOST_CHECK_EQUAL( lsb(0x12), 0x12 );

	//check that the lsb of 0x3456 is 0x56
	BOOST_CHECK_EQUAL( lsb(0x3456), 0x56 );
}

BOOST_AUTO_TEST_CASE(Utils_splitFloatBigEndian)
{
	uint8 b1, b2, b3, b4;

	Utils::split_float_big_endian(123.456789f, b1, b2, b3, b4);

#if defined (BOOST_LITTLE_ENDIAN)

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

	Utils::split_float_little_endian(123.456789f, b1, b2, b3, b4);

#if defined (BOOST_LITTLE_ENDIAN)

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

#if defined (BOOST_LITTLE_ENDIAN)
	
	float val = Utils::make_float_big_endian(0x42, 0xF6, 0xE9, 0xE0);

	BOOST_CHECK_CLOSE(val, 123.456789, 0.00001);

#else

	float val = Utils::make_float_big_endian(0xE0, 0xE9, 0xF6, 0x42);

	BOOST_CHECK_CLOSE(val, 123.456789, 0.00001);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_makeFloatLittleEndian)
{

#if defined (BOOST_LITTLE_ENDIAN)
	
	float val = Utils::make_float_little_endian(0xE0, 0xE9, 0xF6, 0x42);

	BOOST_CHECK_CLOSE(val, 123.456789, 0.00001);

#else

	float val = Utils::make_float_little_endian(0x42, 0xF6, 0xE9, 0xE0);

	BOOST_CHECK_CLOSE(val, 123.456789, 0.00001);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_splitDoubleBigEndian)
{
	uint8 b1, b2, b3, b4, b5, b6, b7, b8;

	Utils::split_double_big_endian(12.34567, b1, b2, b3, b4, b5, b6, b7, b8);

#if defined (BOOST_LITTLE_ENDIAN)

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

	Utils::split_double_little_endian(12.34567, b1, b2, b3, b4, b5, b6, b7, b8);

#if defined (BOOST_LITTLE_ENDIAN)

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

#if defined (BOOST_LITTLE_ENDIAN)
	
	double val = Utils::make_double_big_endian(0x40, 0x28, 0xb0, 0xfb, 0xa8, 0x82, 0x6a, 0xa9);

	BOOST_CHECK_CLOSE(val, 12.34567, 0.00001);

#else

	double val = Utils::make_double_big_endian(0xa9, 0x6a, 0x82, 0xa8, 0xfb, 0xb0, 0x28, 0x40);

	BOOST_CHECK_CLOSE(val, 12.34567, 0.00001);

#endif
}

BOOST_AUTO_TEST_CASE(Utils_makeDoubleLittleEndian)
{

#if defined (BOOST_LITTLE_ENDIAN)
	
	double val = Utils::make_double_little_endian(0xa9, 0x6a, 0x82, 0xa8, 0xfb, 0xb0, 0x28, 0x40);

	BOOST_CHECK_CLOSE(val, 12.34567, 0.00001);

#else

	double val = Utils::make_double_little_endian(0x40, 0x28, 0xb0, 0xfb, 0xa8, 0x82, 0x6a, 0xa9);

	BOOST_CHECK_CLOSE(val, 12.34567, 0.00001);

#endif
}

//Test the splitWord() function
BOOST_AUTO_TEST_CASE(Utils_splitWord)
{
	uint8 msb, lsb;

	uint16 value = 0x1234;

	//convert the word value into 2 bytes
	split_uint16(value, msb, lsb);

	//verify that the msb is now 0x12
	BOOST_CHECK_EQUAL(msb, 0x12);

	//verify that the lsb is now 0x34
	BOOST_CHECK_EQUAL(lsb, 0x34);

	
	value = 0x56;

	//convert the word value into 2 bytes
	split_uint16(value, msb, lsb);

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
	split_uint32(value, b1, b2, b3, b4);

	//verify that b1 is now 0x12
	BOOST_CHECK_EQUAL(b1, 0x12);

	//verify that b2 is now 0x34
	BOOST_CHECK_EQUAL(b2, 0x34);

	//verify that b3 is now 0x56
	BOOST_CHECK_EQUAL(b3, 0x56);

	//verify that b4 is now 0x78
	BOOST_CHECK_EQUAL(b4, 0x78);

	uint16 w1, w2;
	split_uint32(value, w1, w2);
	BOOST_CHECK_EQUAL(w1, 0x1234);
	BOOST_CHECK_EQUAL(w2, 0x5678);


	uint16 wordVal = 0x1234;

	//convert the word value to 4 bytes
	split_uint32(wordVal, b1, b2, b3, b4);

	//verify that b1 is now 0x00
	BOOST_CHECK_EQUAL(b1, 0x00);

	//verify that b2 is now 0x00
	BOOST_CHECK_EQUAL(b2, 0x00);

	//verify that b3 is now 0x12
	BOOST_CHECK_EQUAL(b3, 0x12);

	//verify that b4 is now 0x34
	BOOST_CHECK_EQUAL(b4, 0x34);

	split_uint32(wordVal, w1, w2);
	BOOST_CHECK_EQUAL(w1, 0x0000);
	BOOST_CHECK_EQUAL(w2, 0x1234);

	uint16 model, modelClass;
	uint32 fullModel = 0x18A107D0;
	split_uint32(fullModel, model, modelClass);
	BOOST_CHECK_EQUAL(model, 6305);
	BOOST_CHECK_EQUAL(modelClass, 2000);

}

BOOST_AUTO_TEST_CASE(Utils_Make_int16)
{
	int16 result;

	uint8 msb = 0x80;
	uint8 lsb = 0x02;

	//build the bytes into a word
	result = make_int16(msb, lsb);

	//verify that the word result is now 0x
	BOOST_CHECK_EQUAL(result, -32766);
}

BOOST_AUTO_TEST_CASE(Utils_Make_uint16)
{
	uint16 result;

	uint8 msb = 0x12;
	uint8 lsb = 0x34;

	//build the bytes into a word
	result = make_uint16(msb, lsb);

	//verify that the word result is now 0x1234
	BOOST_CHECK_EQUAL(result, 0x1234);

	msb = 0x00;
	lsb = 0x56;

	//build the bytes into a word
	result = make_uint16(msb, lsb);

	//verify that the word result is now 0x56
	BOOST_CHECK_EQUAL(result, 0x56);

	msb = 0x78;
	lsb = 0x00;

	//build the bytes into a word
	result = make_uint16(msb, lsb);

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
	result = make_uint32(b1, b2, b3, b4);

	//verify that the word result is now 0x12345678
	BOOST_CHECK_EQUAL(result, 0x12345678);

	b1 = 0x00;
	b2 = 0x00;
	b3 = 0x12;
	b4 = 0x34;

	//build the bytes into a dword
	result = make_uint32(b1, b2, b3, b4);

	//verify that the dword result is now 0x1234
	BOOST_CHECK_EQUAL(result, 0x1234);

	b1 = 0x56;
	b2 = 0x78;
	b3 = 0x00;
	b4 = 0x00;

	//build the bytes into a dword
	result = make_uint32(b1, b2, b3, b4);

	//verify that the word result is now 0x56780000
	BOOST_CHECK_EQUAL(result, 0x56780000);


	uint16 word1 = 0x1234;
	uint16 word2 = 0x5678;

	result = make_uint32(word1, word2);
	BOOST_CHECK_EQUAL(result, 0x12345678);

	uint16 model = 6305;
	uint16 modelClass = 2000;

	result = make_uint32(model, modelClass);
	BOOST_CHECK_EQUAL(result, 0x18A107D0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(Utils_GetSystemTime)
{
	uint64 time1 = Utils::getCurrentSystemTime();
	Utils::threadSleep(200);
	uint64 time2 = Utils::getCurrentSystemTime();

	//check that time 2 comes after time 1
	BOOST_CHECK( time1 < time2 );

	const uint64 TIME_2012 = 1349207816000000000;	// 10-02-2012
	const uint64 TIME_2017 = 1506974216000000000;	// 10-02-2017

	//check that the time is between a certain range of time
	BOOST_CHECK(time1 > TIME_2012);
	BOOST_CHECK(time1 < TIME_2017);		//this will break on October 2nd, 2017. If you are fixing this in 2017...Hello future Software Engineer! This is Ricky from 5 years ago. How are the flying cars?
}

BOOST_AUTO_TEST_CASE(Utils_valueTypeSize)
{
	BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_double), 8);
	BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_float), 4);
	BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_int32), 4);
	BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_int16), 2);
	BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_uint16), 2);
	BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_uint32), 2);
	BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_uint8), 1);
	BOOST_CHECK_EQUAL(Utils::valueTypeSize(valueType_bool), 1);
	BOOST_CHECK_THROW(Utils::valueTypeSize(valueType_Vector), Error);
}

BOOST_AUTO_TEST_CASE(Utils_logBase2)
{
	BOOST_CHECK_CLOSE(Utils::logBase2(256), 8, 0.1);
	BOOST_CHECK_CLOSE(Utils::logBase2(2), 1, 0.1);
	BOOST_CHECK_CLOSE(Utils::logBase2(4000), 11.965784, 0.001);
}

BOOST_AUTO_TEST_CASE(Utils_round)
{
	BOOST_CHECK_CLOSE(Utils::round(4.50f), 5.0, 0.1);
	BOOST_CHECK_CLOSE(Utils::round(2.7f), 3.0, 0.1);
	BOOST_CHECK_CLOSE(Utils::round(4.49f), 4.0, 0.1);
	BOOST_CHECK_CLOSE(Utils::round(4.23f), 4.0, 0.1);
}

BOOST_AUTO_TEST_CASE(Utils_roundDownToNearestBase2)
{
	BOOST_CHECK_EQUAL(Utils::roundDownToNearestBase2(256), 256);
	BOOST_CHECK_EQUAL(Utils::roundDownToNearestBase2(251), 128);
	BOOST_CHECK_EQUAL(Utils::roundDownToNearestBase2(4000), 2048);
	BOOST_CHECK_EQUAL(Utils::roundDownToNearestBase2(32.0), 32);
}

BOOST_AUTO_TEST_CASE(Utils_roundUpToNearestBase2)
{
	BOOST_CHECK_EQUAL(Utils::roundUpToNearestBase2(256), 256);
	BOOST_CHECK_EQUAL(Utils::roundUpToNearestBase2(251), 256);
	BOOST_CHECK_EQUAL(Utils::roundUpToNearestBase2(4000), 4096);
	BOOST_CHECK_EQUAL(Utils::roundUpToNearestBase2(32.0), 32);
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