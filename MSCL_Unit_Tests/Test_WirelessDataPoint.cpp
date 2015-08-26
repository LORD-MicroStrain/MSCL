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
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(WirelessDataPoint_Test)

BOOST_AUTO_TEST_CASE(WirelessDataPoint_DefaultConstructor)
{
	WirelessDataPoint p;
	
	//check the default channelId
	BOOST_CHECK_EQUAL(p.channelId(), WirelessChannel::channel_unknown);

	//check the default channelNumber
	BOOST_CHECK_EQUAL(p.channelNumber(), 0);

	//check the default dataType
	BOOST_CHECK_EQUAL(p.storedAs(), valueType_float);

	//check the default value
	BOOST_CHECK_EQUAL(p.as_float(), 0.0);

	BOOST_CHECK_EQUAL(p.channelName(), "unknown");
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_channelName)
{
	WirelessDataPoint p(WirelessChannel::channel_1, 1, valueType_float, anyType((float)123.456f));
	WirelessDataPoint p2(WirelessChannel::channel_6, 6, valueType_uint16, anyType((uint16)12));
	WirelessDataPoint p3(WirelessChannel::channel_digital_12, 12, valueType_uint16, anyType((uint16)12));

	BOOST_CHECK_EQUAL(p.channelName(), "ch1");
	BOOST_CHECK_EQUAL(p2.channelName(), "ch6");
	BOOST_CHECK_EQUAL(p3.channelName(), "digital12");
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_as_float)
{
	WirelessDataPoint p(WirelessChannel::channel_1, 1, valueType_float, anyType((float)123.456f));
	WirelessDataPoint p1(WirelessChannel::channel_1, 1, valueType_bool, anyType(false));
	WirelessDataPoint p2(WirelessChannel::channel_1, 1, valueType_uint16, anyType((uint16)12));
	WirelessDataPoint p3(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)-34));
	WirelessDataPoint p4(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)1234567890));
	WirelessDataPoint p5(WirelessChannel::channel_1, 1, valueType_double, anyType((double)1.7E50));
	WirelessDataPoint p6(WirelessChannel::channel_1, 1, valueType_int16, anyType((int16)-48));
	WirelessDataPoint p7(WirelessChannel::channel_1, 1, valueType_string, anyType((std::string)"789.123"));

	//check the value of each WirelessDataPoint when calling as_float()
	BOOST_CHECK_CLOSE(p.as_float(), 123.456, 0.1);
	BOOST_CHECK_EQUAL(p1.as_float(), 0.0);
	BOOST_CHECK_EQUAL(p2.as_float(), 12.0);
	BOOST_CHECK_EQUAL(p3.as_float(), -34.0);
	BOOST_CHECK_CLOSE(p4.as_float(), 1234567890.0, 0.1);
	BOOST_CHECK_THROW(p5.as_float(), Error_BadDataType);	//out of range of a float
	BOOST_CHECK_EQUAL(p6.as_float(), -48.0);
	BOOST_CHECK_CLOSE(p7.as_float(), 789.123, 0.001);

	WirelessDataPoint p8(WirelessChannel::channel_1, 1, valueType_uint16, anyType(-20));	//invalid valueType / value combination
	BOOST_CHECK_THROW(p8.as_float(), Error_BadDataType);

	WirelessDataPoint p9(WirelessChannel::channel_1, 1, valueType_string, anyType((std::string)"ABC"));
	BOOST_CHECK_THROW(p9.as_float(), Error_BadDataType);
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_as_double)
{
	WirelessDataPoint p(WirelessChannel::channel_1, 1, valueType_double, anyType((double)1.23));
	WirelessDataPoint p1(WirelessChannel::channel_1, 1, valueType_float, anyType((float)123.456f));
	WirelessDataPoint p2(WirelessChannel::channel_1, 1, valueType_bool, anyType(false));
	WirelessDataPoint p3(WirelessChannel::channel_1, 1, valueType_uint16, anyType((uint16)12));
	WirelessDataPoint p4(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)-34));
	WirelessDataPoint p5(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)1234567890));
	WirelessDataPoint p6(WirelessChannel::channel_1, 1, valueType_int16, anyType((int16)-34));
	WirelessDataPoint p7(WirelessChannel::channel_1, 1, valueType_string, anyType((std::string)"789.123"));

	//check the value of each WirelessDataPoint when calling as_float()
	BOOST_CHECK_CLOSE(p.as_double(), 1.23, 0.1);
	BOOST_CHECK_CLOSE(p1.as_double(), 123.456, 0.1);
	BOOST_CHECK_EQUAL(p2.as_double(), 0.0);
	BOOST_CHECK_EQUAL(p3.as_double(), 12.0);
	BOOST_CHECK_EQUAL(p4.as_double(), -34.0);
	BOOST_CHECK_CLOSE(p5.as_double(), 1234567890.0, 0.1);
	BOOST_CHECK_EQUAL(p6.as_double(), -34.0);
	BOOST_CHECK_CLOSE(p7.as_float(), 789.123, 0.001);

	WirelessDataPoint p8(WirelessChannel::channel_1, 1, valueType_uint16, anyType(-20));	//invalid valueType / value combination
	BOOST_CHECK_THROW(p8.as_double(), Error_BadDataType);

	WirelessDataPoint p9(WirelessChannel::channel_1, 1, valueType_Matrix, anyType(0));	//bad type
	BOOST_CHECK_THROW(p9.as_double(), Error_BadDataType);
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_as_uint8)
{
	WirelessDataPoint p(WirelessChannel::channel_1, 1, valueType_float, anyType((float)123.456f));
	WirelessDataPoint p1(WirelessChannel::channel_1, 1, valueType_bool, anyType(true));
	WirelessDataPoint p2(WirelessChannel::channel_1, 1, valueType_uint16, anyType((uint16)12));
	WirelessDataPoint p3(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)34));
	WirelessDataPoint p4(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)56));
	WirelessDataPoint p5(WirelessChannel::channel_1, 1, valueType_int16, anyType((int16)34));
	WirelessDataPoint p6(WirelessChannel::channel_1, 1, valueType_string, anyType((std::string)"78"));

	//check the value of each WirelessDataPoint when calling as_uint8()
	BOOST_CHECK_EQUAL(p.as_uint8(), 123);
	BOOST_CHECK_EQUAL(p1.as_uint8(), 1);
	BOOST_CHECK_EQUAL(p2.as_uint8(), 12);
	BOOST_CHECK_EQUAL(p3.as_uint8(), 34);
	BOOST_CHECK_EQUAL(p4.as_uint8(), 56);
	BOOST_CHECK_EQUAL(p5.as_uint8(), 34);
	BOOST_CHECK_EQUAL(p6.as_uint8(), 78);

	WirelessDataPoint p7(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)-34));
	BOOST_CHECK_THROW(p7.as_uint8(), Error_BadDataType);	//trying to access a signed value as an unsigned value

	WirelessDataPoint p8(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)258));
	BOOST_CHECK_THROW(p8.as_uint8(), Error_BadDataType);	//trying to access an unsigned value that is out of range of the signed value

	WirelessDataPoint p9(WirelessChannel::channel_1, 1, valueType_Matrix, anyType(0));
	BOOST_CHECK_THROW(p9.as_uint8(), Error_BadDataType);	//trying to access an unsigned value that is out of range of the signed value
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_as_uint16)
{
	WirelessDataPoint p(WirelessChannel::channel_1, 1, valueType_float, anyType((float)123.456f));
	WirelessDataPoint p1(WirelessChannel::channel_1, 1, valueType_bool, anyType(true));
	WirelessDataPoint p2(WirelessChannel::channel_1, 1, valueType_uint16, anyType((uint16)12));
	WirelessDataPoint p3(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)34));
	WirelessDataPoint p4(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)56));
	WirelessDataPoint p5(WirelessChannel::channel_1, 1, valueType_int16, anyType((int16)34));
	WirelessDataPoint p6(WirelessChannel::channel_1, 1, valueType_string, anyType((std::string)"65432"));

	//check the value of each WirelessDataPoint when calling as_uint16()
	BOOST_CHECK_EQUAL(p.as_uint16(), 123);
	BOOST_CHECK_EQUAL(p1.as_uint16(), 1);
	BOOST_CHECK_EQUAL(p2.as_uint16(), 12);
	BOOST_CHECK_EQUAL(p3.as_uint16(), 34);
	BOOST_CHECK_EQUAL(p4.as_uint16(), 56);
	BOOST_CHECK_EQUAL(p5.as_uint16(), 34);
	BOOST_CHECK_EQUAL(p6.as_uint16(), 65432);

	WirelessDataPoint p7(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)-34));
	BOOST_CHECK_THROW(p7.as_uint16(), Error_BadDataType);	//trying to access a signed value as an unsigned value

	WirelessDataPoint p8(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)3123456789));
	BOOST_CHECK_THROW(p8.as_uint16(), Error_BadDataType);	//trying to access an unsigned value that is out of range of the signed value
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_as_uint32)
{
	WirelessDataPoint p(WirelessChannel::channel_1, 1, valueType_float, anyType((float)123.456f));
	WirelessDataPoint p1(WirelessChannel::channel_1, 1, valueType_bool, anyType(false));
	WirelessDataPoint p2(WirelessChannel::channel_1, 1, valueType_uint16, anyType((uint16)12));
	WirelessDataPoint p3(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)34));
	WirelessDataPoint p4(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)56));
	WirelessDataPoint p5(WirelessChannel::channel_1, 1, valueType_int16, anyType((int16)34));
	WirelessDataPoint p6(WirelessChannel::channel_1, 1, valueType_string, anyType((std::string)"6553545"));

	//check the value of each WirelessDataPoint when calling as_uint32()
	BOOST_CHECK_EQUAL(p.as_uint32(), 123);
	BOOST_CHECK_EQUAL(p1.as_uint32(), 0);
	BOOST_CHECK_EQUAL(p2.as_uint32(), 12);
	BOOST_CHECK_EQUAL(p3.as_uint32(), 34);
	BOOST_CHECK_EQUAL(p4.as_uint32(), 56);
	BOOST_CHECK_EQUAL(p5.as_uint32(), 34);
	BOOST_CHECK_EQUAL(p6.as_uint32(), 6553545);

	WirelessDataPoint p7(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)-34));
	BOOST_CHECK_THROW(p7.as_uint32(), Error_BadDataType);	//trying to access a signed value as an unsigned value

	ByteStream temp;
	temp.append_uint16(0);

	WirelessDataPoint p8(WirelessChannel::channel_1, 1, valueType_Vector, anyType(Vector(valueType_uint16, temp)));
	BOOST_CHECK_THROW(p8.as_uint32(), Error_BadDataType);	//invalid type
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_as_int16)
{
	WirelessDataPoint p(WirelessChannel::channel_1, 1, valueType_float, anyType((float)123.456f));
	WirelessDataPoint p1(WirelessChannel::channel_1, 1, valueType_bool, anyType(false));
	WirelessDataPoint p2(WirelessChannel::channel_1, 1, valueType_uint16, anyType((uint16)12));
	WirelessDataPoint p3(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)34));
	WirelessDataPoint p4(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)56));
	WirelessDataPoint p5(WirelessChannel::channel_1, 1, valueType_int16, anyType((int16)-1500));
	WirelessDataPoint p6(WirelessChannel::channel_1, 1, valueType_string, anyType((std::string)"-756"));


	//check the value of each WirelessDataPoint when calling asInt32()
	BOOST_CHECK_EQUAL(p.as_int16(), 123);
	BOOST_CHECK_EQUAL(p1.as_int16(), 0);
	BOOST_CHECK_EQUAL(p2.as_int16(), 12);
	BOOST_CHECK_EQUAL(p3.as_int16(), 34);
	BOOST_CHECK_EQUAL(p4.as_int16(), 56);
	BOOST_CHECK_EQUAL(p5.as_int16(), -1500);
	BOOST_CHECK_EQUAL(p6.as_int16(), -756);

	WirelessDataPoint p7(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)2147483650));
	BOOST_CHECK_THROW(p7.as_int16(), Error_BadDataType);	//overflow error

	WirelessDataPoint p8(WirelessChannel::channel_1, 1, valueType_Matrix, anyType(0));
	BOOST_CHECK_THROW(p8.as_int16(), Error_BadDataType);	//bad type
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_as_int32)
{
	WirelessDataPoint p(WirelessChannel::channel_1, 1, valueType_float, anyType((float)123.456f));
	WirelessDataPoint p1(WirelessChannel::channel_1, 1, valueType_bool, anyType(false));
	WirelessDataPoint p2(WirelessChannel::channel_1, 1, valueType_uint16, anyType((uint16)12));
	WirelessDataPoint p3(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)34));
	WirelessDataPoint p4(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)56));
	WirelessDataPoint p5(WirelessChannel::channel_1, 1, valueType_int16, anyType((int16)34));
	WirelessDataPoint p6(WirelessChannel::channel_1, 1, valueType_string, anyType((std::string)"-6553547"));

	//check the value of each WirelessDataPoint when calling asInt32()
	BOOST_CHECK_EQUAL(p.as_int32(), 123);
	BOOST_CHECK_EQUAL(p1.as_int32(), 0);
	BOOST_CHECK_EQUAL(p2.as_int32(), 12);
	BOOST_CHECK_EQUAL(p3.as_int32(), 34);
	BOOST_CHECK_EQUAL(p4.as_int32(), 56);
	BOOST_CHECK_EQUAL(p5.as_int32(), 34);
	BOOST_CHECK_EQUAL(p6.as_int32(), -6553547);

	WirelessDataPoint p7(WirelessChannel::channel_1, 1, valueType_uint32, anyType((uint32)2147483650));
	BOOST_CHECK_THROW(p7.as_int32(), Error_BadDataType);	//overflow error

	WirelessDataPoint p8(WirelessChannel::channel_1, 1, valueType_Matrix, anyType(0));
	BOOST_CHECK_THROW(p8.as_int32(), Error_BadDataType);	//bad type
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_as_bool)
{
	WirelessDataPoint p(WirelessChannel::channel_digital_1, 1, valueType_bool, anyType(true));
	WirelessDataPoint p2(WirelessChannel::channel_digital_3, 1, valueType_bool, anyType(false));
	WirelessDataPoint p3(WirelessChannel::channel_1, 1, valueType_int32, anyType((int32)-12));

	//check the value of each WirelessDataPoint
	BOOST_CHECK_EQUAL(p.as_bool(), true);
	BOOST_CHECK_EQUAL(p2.as_bool(), false);
	BOOST_CHECK_THROW(p3.as_bool(), Error_BadDataType);
}

BOOST_AUTO_TEST_CASE(WirelessDataPoint_as_string)
{
	WirelessDataPoint p(WirelessChannel::channel_digital_1, 1, valueType_bool, anyType(true));
	WirelessDataPoint p2(WirelessChannel::channel_digital_2, 1, valueType_bool, anyType(false));
	WirelessDataPoint p3(WirelessChannel::channel_1, 1, valueType_string, anyType((std::string)"3DM-GX3-35"));

	BOOST_CHECK_EQUAL(p.as_string(), "1");
	BOOST_CHECK_EQUAL(p2.as_string(), "0");
	BOOST_CHECK_EQUAL(p3.as_string(), "3DM-GX3-35");
}


BOOST_AUTO_TEST_SUITE_END()