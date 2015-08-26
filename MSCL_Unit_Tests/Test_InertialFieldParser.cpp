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
#include "mscl/MicroStrain/Inertial/Packets/InertialFieldParser.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialDataPacket.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialFieldParser_Test)

BOOST_AUTO_TEST_CASE(InertialFieldParser_parseField)
{
	ByteStream bytes;

	//add bytes to the ByteStream
	bytes.append_float(1.234f);	//Accel 1 float
	bytes.append_float(0.0f);	//Accel 2 float
	bytes.append_float(0.0f);	//Accel 3 float

	InertialDataField field(InertialTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC, bytes.data()); 

	InertialDataPoints data;

	InertialFieldParser::parseField(field, data);

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
	bytes.append_uint32(0x3F9DF3B6);	//Accel 1 float
	bytes.append_uint32(0x00000000);	//Accel 2 float
	bytes.append_uint32(0x00000000);	//Accel 3 float

	InertialDataField field(0, bytes.data()); 

	InertialDataPoints data;

	InertialFieldParser::parseField(field, data);

	//verify the field was parsed correctly
	BOOST_CHECK_EQUAL(data.size(), 1);
	BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Bytes);
}

BOOST_AUTO_TEST_SUITE_END()