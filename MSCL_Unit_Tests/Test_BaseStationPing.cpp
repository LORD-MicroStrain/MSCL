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
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_Ping.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(BaseStationPing_Test)

BOOST_AUTO_TEST_CASE(BaseStationPing_BuildCommand)
{
	//create a LongPing command
	ByteStream b = BaseStation_Ping::buildCommand();

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x01);
}

BOOST_AUTO_TEST_CASE(BaseStationPing_Match_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_Ping::Response response(rc);

	Bytes bytes;
	bytes.push_back(0x01);	//success response

	DataBuffer buffer(bytes);

	//check that match returns true
	BOOST_CHECK_EQUAL(response.match(buffer), true);

	//check that the result of the ping is true
	BOOST_CHECK_EQUAL(response.success(), true);
}

BOOST_AUTO_TEST_CASE(BaseStationPing_Match_Fail)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_Ping::Response response(rc);

	Bytes bytes;
	bytes.push_back(0x45);	//fail response

	DataBuffer buffer(bytes);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the ping is false
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationPing_Match_Fail_ByteSize)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_Ping::Response response(rc);

	Bytes bytes;	//empty bytes		

	DataBuffer buffer(bytes);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the ping is false
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_SUITE_END()