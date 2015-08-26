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
#include "mscl/MicroStrain/Wireless/Commands/SetToIdle.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>
#include "mock_BaseStation.h"

using namespace mscl;

BOOST_AUTO_TEST_SUITE(SetToIdle_Test)

BOOST_AUTO_TEST_CASE(SetToIdle_BuildCommand)
{
	ByteStream b = SetToIdle::buildCommand(6045);

	BOOST_CHECK_EQUAL(b.read_uint8(0), 0xAA);	//sop
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0xFE);	//dsf
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x00);	//app data type
	BOOST_CHECK_EQUAL(b.read_uint16(3), 6045);	//node address
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x02);	//payload len
	BOOST_CHECK_EQUAL(b.read_uint16(6), 0x0090);	//command id
	BOOST_CHECK_EQUAL(b.read_uint16(8), 0x244);	//checksum
}

BOOST_AUTO_TEST_CASE(SetToIdle_Match_Success_stopped_withAA)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl);
	BaseStation base(baseImpl);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	SetToIdle::Response response(100, rc, base);

	//a successful stop node response, with the initial 0xAA in the response
	Bytes bytes;
	bytes.push_back(0xAA);
	bytes.push_back(0x90);
	bytes.push_back(0x01);

	DataBuffer buffer(bytes);

	//check that match returns true
	BOOST_CHECK_EQUAL(response.result(), SetToIdleStatus::setToIdleResult_notCompleted);
	BOOST_CHECK_EQUAL(response.match(buffer), true);
	BOOST_CHECK_EQUAL(response.result(), SetToIdleStatus::setToIdleResult_success);
}

BOOST_AUTO_TEST_CASE(SetToIdle_Match_Success_stopped)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl);
	BaseStation base(baseImpl);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	SetToIdle::Response response(100, rc, base);

	//a successful stop node response, without the initial 0xAA in the response
	Bytes bytes;
	bytes.push_back(0x90);
	bytes.push_back(0x01);

	DataBuffer buffer(bytes);

	//check that match returns true
	BOOST_CHECK_EQUAL(response.match(buffer), true);
	BOOST_CHECK_EQUAL(response.result(), SetToIdleStatus::setToIdleResult_success);
}

BOOST_AUTO_TEST_CASE(SetToIdle_Match_Success_canceled_withAA)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl);
	BaseStation base(baseImpl);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	SetToIdle::Response response(100, rc, base);

	//a canceled stop node response, with the initial 0xAA in the response
	Bytes bytes;
	bytes.push_back(0xAA);
	bytes.push_back(0x21);
	bytes.push_back(0x01);

	DataBuffer buffer(bytes);

	//check that match returns true
	BOOST_CHECK_EQUAL(response.match(buffer), true);
	BOOST_CHECK_EQUAL(response.result(), SetToIdleStatus::setToIdleResult_canceled);
}

BOOST_AUTO_TEST_CASE(SetToIdle_Match_Success_canceled)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl);
	BaseStation base(baseImpl);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	SetToIdle::Response response(100, rc, base);

	//a canceled stop node response, without the initial 0xAA in the response
	Bytes bytes;
	bytes.push_back(0x21);
	bytes.push_back(0x01);

	DataBuffer buffer(bytes);

	//check that match returns true
	BOOST_CHECK_EQUAL(response.match(buffer), true);
	BOOST_CHECK_EQUAL(response.result(), SetToIdleStatus::setToIdleResult_canceled);
}

BOOST_AUTO_TEST_CASE(SetToIdle_Cancel)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl);
	BaseStation base(baseImpl);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	SetToIdle::Response response(100, rc, base);

	MOCK_EXPECT(baseImpl->ping).returns(true);		//expect to ping the base station

	base.baseCommandsTimeout(5);

	BOOST_CHECK_THROW(response.cancel(), Error_Communication);	//throws an error because we didn't get the final canceled response

	//a canceled stop node response, without the initial 0xAA in the response
	Bytes bytes;
	bytes.push_back(0x21);
	bytes.push_back(0x01);

	DataBuffer buffer(bytes);

	//check that match returns true
	BOOST_CHECK_EQUAL(response.match(buffer), true);
}

BOOST_AUTO_TEST_SUITE_END()