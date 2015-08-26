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
#include "mscl/MicroStrain/Inertial/Commands/EstFilter_Commands.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(EstFilterCommands_Test)

BOOST_AUTO_TEST_SUITE(EstFilterCommands_GetEstFilterDataRateBase)

BOOST_AUTO_TEST_CASE(GetEstFilterDataRateBase_buildCommand)
{
	ByteStream b = GetEstFilterDataRateBase::buildCommand();

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
	BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x0B);
	BOOST_CHECK_EQUAL(b.read_uint8(6), 0xF5);
	BOOST_CHECK_EQUAL(b.read_uint8(7), 0xFC);
}

BOOST_AUTO_TEST_CASE(GetEstFilterDataRateBase_parseData)
{
	ByteStream data;
	data.append_uint16(500);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetEstFilterDataRateBase::Response response(rc);

	BOOST_CHECK_EQUAL(response.parseData(GenericInertialCommandResponse::ResponseSuccess("", data)), 500);
}

BOOST_AUTO_TEST_CASE(GetEstFilterDataRateBase_Match_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetEstFilterDataRateBase::Response response(rc);

	Bytes ackData;
	ackData.push_back(0x0B);
	ackData.push_back(0x00);
	InertialDataField ackField(0x0CF1, ackData); //ack/nack field

	Bytes data;
	data.push_back(0x00);
	data.push_back(0x02);
	InertialDataField dataField(0x0C8A, data); //data field

	//check that the match succeeds
	BOOST_CHECK_EQUAL(response.match(ackField), true);
	BOOST_CHECK_EQUAL(response.fullyMatched(), false);
	BOOST_CHECK_EQUAL(response.match(dataField), true);
	BOOST_CHECK_EQUAL(response.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response.result().success(), true);
	BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::InertialPacket::MIP_ACK_NACK_ERROR_NONE);
}

BOOST_AUTO_TEST_SUITE_END()	//End GetEstFilterDataRateBase


BOOST_AUTO_TEST_SUITE(EstFilterCommands_EstFilterMessageFormat)

BOOST_AUTO_TEST_CASE(EstFilterMessageFormat_buildCommand_get)
{
	ByteStream b = EstFilterMessageFormat::buildCommand_get();

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
	BOOST_CHECK_EQUAL(b.read_uint8(3), 0x04);
	BOOST_CHECK_EQUAL(b.read_uint8(4), 0x04);
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x0A);
	BOOST_CHECK_EQUAL(b.read_uint8(6), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(7), 0x00);
	BOOST_CHECK_EQUAL(b.read_uint8(8), 0xFA);
	BOOST_CHECK_EQUAL(b.read_uint8(9), 0xF9);
}

BOOST_AUTO_TEST_CASE(EstFilterMessageFormat_buildCommand_set)
{
	SampleRate hz1 = SampleRate::Hertz(1);

	InertialChannels chs;
	chs.push_back(InertialChannel(InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS, hz1));
	chs.push_back(InertialChannel(InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY, hz1));

	ByteStream b = EstFilterMessageFormat::buildCommand_set(chs, 1);

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
	BOOST_CHECK_EQUAL(b.read_uint8(3), 0x0A);
	BOOST_CHECK_EQUAL(b.read_uint8(4), 0x0A);
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x0A);
	BOOST_CHECK_EQUAL(b.read_uint8(6), 0x01);
	BOOST_CHECK_EQUAL(b.read_uint8(7), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(8), 0x01);
	BOOST_CHECK_EQUAL(b.read_uint8(9), 0x00);
	BOOST_CHECK_EQUAL(b.read_uint8(10), 0x01);
	BOOST_CHECK_EQUAL(b.read_uint8(11), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(12), 0x00);
	BOOST_CHECK_EQUAL(b.read_uint8(13), 0x01);
	BOOST_CHECK_EQUAL(b.read_uint8(14), 0x0C);
	BOOST_CHECK_EQUAL(b.read_uint8(15), 0x6A);
}

BOOST_AUTO_TEST_CASE(EstFilterMessageFormat_parseData)
{
	ByteStream data;
	data.append_uint8(0x01);
	data.append_uint8(0x06);	//CH_NAV_ESTIMATED_GYRO_BIAS
	data.append_uint16(2);		//rate decimation

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	EstFilterMessageFormat::Response response(rc, true);

	uint16 sampleRateBase = 100;

	InertialChannels chs = response.parseData(GenericInertialCommandResponse::ResponseSuccess("", data), sampleRateBase);

	BOOST_CHECK_EQUAL(chs.size(), 1);
	BOOST_CHECK_EQUAL(chs.at(0).channelField(), InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS);
	BOOST_CHECK_EQUAL(chs.at(0).rateDecimation(sampleRateBase), 2);
	BOOST_CHECK_EQUAL(chs.at(0).sampleRate().samplesPerSecond(), SampleRate::Hertz(50).samplesPerSecond());

}

BOOST_AUTO_TEST_SUITE_END()	//End EstFilterMessageFormat


BOOST_AUTO_TEST_SUITE_END()