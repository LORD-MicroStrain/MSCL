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
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/Commands/Inertial_SetToIdle.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace std;
using namespace mscl;

BOOST_AUTO_TEST_SUITE(Inertial_SetToIdle_Test)

BOOST_AUTO_TEST_CASE(Inertial_SetToIdle_BuildCommand)
{
	ByteStream b = Inertial_SetToIdle::buildCommand();
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x01);
	BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(6), 0xE1);
	BOOST_CHECK_EQUAL(b.read_uint8(7), 0xC7);
}

BOOST_AUTO_TEST_CASE(Inertial_SetToIdle_Match_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	Inertial_SetToIdle::Response response(rc);
	
	Bytes ackField;
	ackField.push_back(0x02);
	ackField.push_back(0x00);
	InertialDataField field1(0x01F1, ackField); //good ack field

	//check that the match fails
	BOOST_CHECK_EQUAL(response.match(field1), true);
	BOOST_CHECK_EQUAL(response.fullyMatched(), true);	
	BOOST_CHECK_EQUAL(response.result().success(), true);
}

BOOST_AUTO_TEST_SUITE_END()