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
#include "mscl/MicroStrain/Inertial/Commands/GPS_Commands.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(GpsCommands_Test)

BOOST_AUTO_TEST_SUITE(GpsCommands_GetGpsDataRateBase)

BOOST_AUTO_TEST_CASE(GetGpsDataRateBase_buildCommand)
{
	ByteStream b = GetGpsDataRateBase::buildCommand();

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
	BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x07);
	BOOST_CHECK_EQUAL(b.read_uint8(6), 0xF1);
	BOOST_CHECK_EQUAL(b.read_uint8(7), 0xF8);
}

BOOST_AUTO_TEST_CASE(GetGpsDataRateBase_parseData)
{
	ByteStream data;
	data.append_uint16(1000);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetGpsDataRateBase::Response response(rc);

	BOOST_CHECK_EQUAL(response.parseData(GenericInertialCommandResponse::ResponseSuccess("", data)), 1000);
}

BOOST_AUTO_TEST_CASE(GetGpsDataRateBase_Match_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetGpsDataRateBase::Response response(rc);

	Bytes ackData;
	ackData.push_back(0x07);
	ackData.push_back(0x00);
	InertialDataField ackField(0x0CF1, ackData); //ack/nack field

	Bytes data;
	data.push_back(0x00);
	data.push_back(0x04);
	InertialDataField dataField(0x0C84, data); //data field

	//check that the match succeeds
	BOOST_CHECK_EQUAL(response.match(ackField), true);
	BOOST_CHECK_EQUAL(response.fullyMatched(), false);
	BOOST_CHECK_EQUAL(response.match(dataField), true);
	BOOST_CHECK_EQUAL(response.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response.result().success(), true);
	BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::InertialPacket::MIP_ACK_NACK_ERROR_NONE);
}

BOOST_AUTO_TEST_SUITE_END()	//End GetGpsDataRateBase


BOOST_AUTO_TEST_SUITE(GpsCommands_GpsMessageFormat)

BOOST_AUTO_TEST_CASE(GpsMessageFormat_buildCommand_get)
{
	ByteStream b = GpsMessageFormat::buildCommand_get();

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
	BOOST_CHECK_EQUAL(b.read_uint8(3), 0x04);
	BOOST_CHECK_EQUAL(b.read_uint8(4), 0x04);
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x09);
	BOOST_CHECK_EQUAL(b.read_uint8(6), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(7), 0x00);
	BOOST_CHECK_EQUAL(b.read_uint8(8), 0xF9);
	BOOST_CHECK_EQUAL(b.read_uint8(9), 0xF6);
}

BOOST_AUTO_TEST_CASE(GpsMessageFormat_buildCommand_set)
{
	InertialChannels chs;
	chs.push_back(InertialChannel(InertialTypes::CH_FIELD_GPS_LLH_POSITION, SampleRate::Hertz(2)));
	chs.push_back(InertialChannel(InertialTypes::CH_FIELD_GPS_NED_VELOCITY, SampleRate::Hertz(4)));

	ByteStream b = GpsMessageFormat::buildCommand_set(chs, 4);

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
	BOOST_CHECK_EQUAL(b.read_uint8(3), 0x0A);
	BOOST_CHECK_EQUAL(b.read_uint8(4), 0x0A);
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x09);
	BOOST_CHECK_EQUAL(b.read_uint8(6), 0x01);
	BOOST_CHECK_EQUAL(b.read_uint8(7), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(8), 0x03);
	BOOST_CHECK_EQUAL(b.read_uint8(9), 0x00);
	BOOST_CHECK_EQUAL(b.read_uint8(10), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(11), 0x05);
	BOOST_CHECK_EQUAL(b.read_uint8(12), 0x00);
	BOOST_CHECK_EQUAL(b.read_uint8(13), 0x01);
	BOOST_CHECK_EQUAL(b.read_uint8(14), 0x11);
	BOOST_CHECK_EQUAL(b.read_uint8(15), 0x7A);
}

BOOST_AUTO_TEST_CASE(GpsMessageFormat_parseData)
{
	ByteStream data;
	data.append_uint8(0x01);
	data.append_uint8(0x08);	//CH_GPS_UTC_TIME
	data.append_uint16(4);		//rate decimation

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GpsMessageFormat::Response response(rc, true);

	uint16 sampleRateBase = 1000;

	InertialChannels chs = response.parseData(GenericInertialCommandResponse::ResponseSuccess("", data), sampleRateBase);

	BOOST_CHECK_EQUAL(chs.size(), 1);
	BOOST_CHECK_EQUAL(chs.at(0).channelField(), InertialTypes::CH_FIELD_GPS_UTC_TIME);
	BOOST_CHECK_EQUAL(chs.at(0).rateDecimation(sampleRateBase), 4);
	BOOST_CHECK_EQUAL(chs.at(0).sampleRate().samplesPerSecond(), SampleRate::Hertz(250).samplesPerSecond());
}

BOOST_AUTO_TEST_SUITE_END()	//End GpsMessageFormat


BOOST_AUTO_TEST_SUITE_END()