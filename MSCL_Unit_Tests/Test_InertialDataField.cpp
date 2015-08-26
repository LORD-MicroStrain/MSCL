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
#include "mscl/MicroStrain/Inertial/Packets/InertialDataPacket.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialDataField_Test)

BOOST_AUTO_TEST_CASE(InertialDataField_Constructor)
{
	InertialDataField f;

	//check that the default field type of 0 is assigned
	BOOST_CHECK_EQUAL(f.fieldId(), 0);

	Bytes b;
	b.push_back(0x01);
	b.push_back(0x02);

	//build an InertialDataField from the bytes
	InertialDataField f1(InertialTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC, b);

	BOOST_CHECK_EQUAL(f1.fieldId(), InertialTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC);
	BOOST_CHECK_EQUAL(f1.fieldData().read_uint8(0), 0x01);
	BOOST_CHECK_EQUAL(f1.fieldData().read_uint8(1), 0x02);
}

BOOST_AUTO_TEST_SUITE_END()