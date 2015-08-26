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
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_ReadEeprom.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

Bytes buildBaseReadEepromResponseV1(uint16 valueRead)
{
	ChecksumBuilder checksum;
	checksum.append_uint16(valueRead);

	//build success response
	Bytes bytes;
	bytes.push_back(0x72);	
	bytes.push_back(Utils::msb(valueRead));
	bytes.push_back(Utils::lsb(valueRead));

	return bytes;
}

Bytes buildBaseReadEepromResponseV2(uint16 valueRead)
{
	ChecksumBuilder checksum;
	checksum.append_uint16(valueRead);

	//build success response
	Bytes bytes;
	bytes.push_back(0x73);	
	bytes.push_back(Utils::msb(valueRead));
	bytes.push_back(Utils::lsb(valueRead));
	bytes.push_back(Utils::msb(checksum.simpleChecksum()));
	bytes.push_back(Utils::lsb(checksum.simpleChecksum()));

	return bytes;
}

BOOST_AUTO_TEST_SUITE(BaseStationReadEeprom_Test)

BOOST_AUTO_TEST_CASE(BaseStationReadEeprom_BuildCommand)
{
	//create a Read EEPROM command
	ByteStream b = BaseStation_ReadEeprom::buildCommand(46);

	//check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x73);
	BOOST_CHECK_EQUAL(b.read_uint16(1), 46);
	BOOST_CHECK_EQUAL(b.read_uint16(3), 46);	//verify the checksum
}

BOOST_AUTO_TEST_CASE(BaseStationReadEeprom_MatchSuccessResponse_Success_V2)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_ReadEeprom::Response response(rc);

	DataBuffer buffer(buildBaseReadEepromResponseV2(123));

	//check that match returns true
	BOOST_CHECK_EQUAL(response.match(buffer), true);

	//check that the result of the command is successful
	BOOST_CHECK_EQUAL(response.success(), true);
}

BOOST_AUTO_TEST_CASE(BaseStationReadEeprom_MatchSuccessResponse_FailNumBytes)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_ReadEeprom::Response response(rc);

	Bytes b;
	b.push_back(0x04);

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure (throws an exception)
	BOOST_CHECK_THROW(response.result(), Error);
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationReadEeprom_MatchSuccessResponse_FailByteMatch_V2)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_ReadEeprom::Response response(rc);

	Bytes b = buildBaseReadEepromResponseV2(23);
	b[0] = 0x01;	//incorrect command byte

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure (throws an exception)
	BOOST_CHECK_THROW(response.result(), Error);
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationReadEeprom_MatchSuccessResponse_FailChecksum)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_ReadEeprom::Response response(rc);

	Bytes b = buildBaseReadEepromResponseV2(0);
	b[3] = 0x99;	//incorrect checksum

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure (throws an exception)
	BOOST_CHECK_THROW(response.result(), Error);
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationReadEeprom_MatchFailResponse_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_ReadEeprom::Response response(rc);

	Bytes b;
	b.push_back(0x21);

	DataBuffer buffer(b);

	//check that match returns true
	BOOST_CHECK_EQUAL(response.match(buffer), true);

	//check that the result of the command is failure
	BOOST_CHECK_THROW(response.result(), Error);
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationReadEeprom_MatchFailResponse_FailNumBytes)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_ReadEeprom::Response response(rc);

	Bytes b;//no bytes

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure (throws an exception)
	BOOST_CHECK_THROW(response.result(), Error);
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationReadEeprom_MatchFailResponse_InvalidByte)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_ReadEeprom::Response response(rc);

	Bytes b;
	b.push_back(0x22);

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure (throws an exception)
	BOOST_CHECK_THROW(response.result(), Error);
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationReadEeprom_Wait_Timeout)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	//create the response for the BaseStation_ReadEeprom command
	BaseStation_ReadEeprom::Response response(rc);

	//wait for a quick timeout (no data has been sent/received)
	response.wait(1);

	//verify the failed result of the response
	BOOST_CHECK_THROW(response.result(), Error);
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_SUITE_END()