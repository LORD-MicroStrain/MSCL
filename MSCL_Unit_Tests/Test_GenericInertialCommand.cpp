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
#include "mscl/MicroStrain/Inertial/Commands/GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(GenericInertialCommand_Test)

BOOST_AUTO_TEST_CASE(GenericInertialCommandResponse_ResponseSuccess)
{
	//check a success response with no data
	GenericInertialCommandResponse res = GenericInertialCommandResponse::ResponseSuccess("Hello World");
	BOOST_CHECK_EQUAL(res.errorCode(), InertialPacket::MIP_ACK_NACK_ERROR_NONE);
	BOOST_CHECK_EQUAL(res.success(), true);
	BOOST_CHECK_EQUAL(res.data().size(), 0);

	//check a success response with data
	ByteStream bytes;
	bytes.append_uint16(0x1234);
	GenericInertialCommandResponse res2 = GenericInertialCommandResponse::ResponseSuccess("Hello World", bytes);
	BOOST_CHECK_EQUAL(res2.errorCode(), InertialPacket::MIP_ACK_NACK_ERROR_NONE);
	BOOST_CHECK_EQUAL(res2.success(), true);
	BOOST_CHECK_EQUAL(res2.data().size(), 2);
}

BOOST_AUTO_TEST_CASE(GenericInertialCommandResponse_ResponseFail)
{
	//check a fail response
	GenericInertialCommandResponse res = GenericInertialCommandResponse::ResponseFail(ResponsePattern::STATE_FAIL, InertialPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND, "");
	BOOST_CHECK_EQUAL(res.errorCode(), InertialPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
	BOOST_CHECK_EQUAL(res.success(), false);
}

BOOST_AUTO_TEST_CASE(GenericInertialCommand_buildCommand_withBytes)
{
	ByteStream cmdNoData = GenericInertialCommand::buildCommand(0x0C, 0x06);

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(cmdNoData.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(cmdNoData.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(cmdNoData.read_uint8(2), 0x0C);
	BOOST_CHECK_EQUAL(cmdNoData.read_uint8(3), 0x02);
	BOOST_CHECK_EQUAL(cmdNoData.read_uint8(4), 0x02);
	BOOST_CHECK_EQUAL(cmdNoData.read_uint8(5), 0x06);
	BOOST_CHECK_EQUAL(cmdNoData.read_uint8(6), 0xF0);
	BOOST_CHECK_EQUAL(cmdNoData.read_uint8(7), 0xF7);

	Bytes data;
	data.push_back(0x02);
	data.push_back(0x00);
	ByteStream cmd = GenericInertialCommand::buildCommand(0x0C, 0x08, data);

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(cmd.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(cmd.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(cmd.read_uint8(2), 0x0C);
	BOOST_CHECK_EQUAL(cmd.read_uint8(3), 0x04);
	BOOST_CHECK_EQUAL(cmd.read_uint8(4), 0x04);
	BOOST_CHECK_EQUAL(cmd.read_uint8(5), 0x08);
	BOOST_CHECK_EQUAL(cmd.read_uint8(6), 0x02);
	BOOST_CHECK_EQUAL(cmd.read_uint8(7), 0x00);
	BOOST_CHECK_EQUAL(cmd.read_uint8(8), 0xF8);
	BOOST_CHECK_EQUAL(cmd.read_uint8(9), 0xF3);
}

BOOST_AUTO_TEST_SUITE_END()