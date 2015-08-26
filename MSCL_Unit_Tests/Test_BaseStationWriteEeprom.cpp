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
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_WriteEeprom.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

Bytes buildBaseWriteEepromResponseV1()
{
	//build success response
	Bytes bytes;
	bytes.push_back(0x77);	

	return bytes;
}

Bytes buildBaseWriteEepromResponseV2(uint16 valueWritten)
{
	ChecksumBuilder checksum;
	checksum.append_uint16(valueWritten);

	//build success response
	Bytes bytes;
	bytes.push_back(0x78);	
	bytes.push_back(Utils::msb(valueWritten));
	bytes.push_back(Utils::lsb(valueWritten));
	bytes.push_back(Utils::msb(checksum.simpleChecksum()));
	bytes.push_back(Utils::lsb(checksum.simpleChecksum()));

	return bytes;
}

BOOST_AUTO_TEST_SUITE(BaseStationWriteEeprom_Test)

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_BuildCommand)
{
	//create a Write EEPROM command
	ByteStream b = BaseStation_WriteEeprom::buildCommand(112, 1234);

	//check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x78);
	BOOST_CHECK_EQUAL(b.read_uint16(1), 112);
	BOOST_CHECK_EQUAL(b.read_uint16(3), 1234);	
	BOOST_CHECK_EQUAL(b.read_uint16(5), 326);//verify the checksum
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_WriteEeprom::Response response(123, rc);

	DataBuffer buffer(buildBaseWriteEepromResponseV2(123));

	//check that match returns true
	BOOST_CHECK_EQUAL(response.match(buffer), true);

	//check that the result of the command is successful
	BOOST_CHECK_EQUAL(response.success(), true);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_IncorrectEepromValue)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_WriteEeprom::Response response(123, rc);

	DataBuffer buffer(buildBaseWriteEepromResponseV2(456));//build with incorrect eeprom value

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_FailNumBytes)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_WriteEeprom::Response response(123, rc);

	Bytes b;
	b.push_back(0x04);

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_FailByteMatch)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_WriteEeprom::Response response(23, rc);

	Bytes b = buildBaseWriteEepromResponseV2(23);
	b[0] = 0x01;	//incorrect command byte

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_FailChecksum)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_WriteEeprom::Response response(0, rc);

	Bytes b = buildBaseWriteEepromResponseV2(0);
	b[3] = 0x99;	//incorrect checksum

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchFailResponse_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_WriteEeprom::Response response(0, rc);

	Bytes b;
	b.push_back(0x21);

	DataBuffer buffer(b);

	//check that match returns true
	BOOST_CHECK_EQUAL(response.match(buffer), true);

	//check that the result of the command is failure
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchFailResponse_FailNumBytes)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_WriteEeprom::Response response(0, rc);

	Bytes b;//no bytes

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchFailResponse_InvalidByte)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	BaseStation_WriteEeprom::Response response(0, rc);

	Bytes b;
	b.push_back(0x22);

	DataBuffer buffer(b);

	//check that match returns false
	BOOST_CHECK_EQUAL(response.match(buffer), false);

	//check that the result of the command is failure
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_Wait_Timeout)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	//create the response for the BaseStation_ReadEeprom command
	BaseStation_WriteEeprom::Response response(0, rc);

	//wait for a quick timeout (no data has been sent/received)
	response.wait(1);

	//check that the result of the command is failure
	BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_SUITE_END()