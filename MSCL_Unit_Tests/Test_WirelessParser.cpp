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
#include "mscl/MicroStrain/Wireless/WirelessParser.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Wireless/Commands/LongPing.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/Exceptions.h"

#include "mscl/MicroStrain/Wireless/Commands/StartSyncSampling.h"
#include "mscl/MicroStrain/Wireless/Commands/PageDownload.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(WirelessParser_Test)

BOOST_AUTO_TEST_SUITE(WirelessParser_parseAsPacket)

BOOST_AUTO_TEST_CASE(WirelessParser_parseAsPacket_NotEnoughData)
{
	//just not enough bytes to even be an ASPP packet
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x02);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_14), WirelessParser::parsePacketResult_notEnoughData);

	//not large enough to contain the rest of the packet's payload, etc.
	data.push_back(0x01);
	data.push_back(0x01);
	data.push_back(0x02);
	data.push_back(0x01);
	data.push_back(0xAB);	//payload length
	data.push_back(0x01);
	data.push_back(0x02);

	DataBuffer b2(data);

	BOOST_CHECK_EQUAL(parser.parseAsPacket(b2, packet, WirelessTypes::freq_14), WirelessParser::parsePacketResult_notEnoughData);
}


BOOST_AUTO_TEST_CASE(WirelessParser_parseAsPacket_InvalidPacket)
{
	//enough bytes to be ASPP, but not a valid ASPP packet
	Bytes data;
	data.push_back(0x01);
	data.push_back(0x02);
	data.push_back(0x01);
	data.push_back(0x02);
	data.push_back(0x01);
	data.push_back(0x02);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_14), WirelessParser::parsePacketResult_invalidPacket);
}

BOOST_AUTO_TEST_CASE(WirelessParser_parseAsPacket_IntegrityCheck_InvalidPacket)
{
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x03);
	data.push_back(0x01);	//Node Discovery Packet, but invalid radio frequency
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x05);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_14), WirelessParser::parsePacketResult_invalidPacket);
}

BOOST_AUTO_TEST_CASE(WirelessParser_parseAsPacket_InvalidChecksum)
{
	//ASPP packet with invalid checksum
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x03);
	data.push_back(0x0D);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x02);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_14), WirelessParser::parsePacketResult_badChecksum);
}

BOOST_AUTO_TEST_CASE(WirelessParser_parseAsPacket_CompletePacket)
{
	//a valid ASPP packet
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x03);
	data.push_back(0x0D);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x11);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_14), WirelessParser::parsePacketResult_completePacket);

	BOOST_CHECK_EQUAL(packet.deliveryStopFlags() == DeliveryStopFlags(true, true, true, true), true);
	BOOST_CHECK_EQUAL(packet.nodeAddress(), 1);
	BOOST_CHECK_EQUAL(packet.type(), WirelessPacket::packetType_nodeDiscovery);
	BOOST_CHECK_EQUAL(packet.nodeRSSI(), 0);
	BOOST_CHECK_EQUAL(packet.baseRSSI(), 0);
	BOOST_CHECK_EQUAL(packet.frequency(), WirelessTypes::freq_14);
}

BOOST_AUTO_TEST_CASE(WirelessParser_parseAsPacket_Duplicate)
{
	//a valid LDC packet
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x04);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x08);
	data.push_back(0x02);
	data.push_back(0x01);
	data.push_back(0x70);
	data.push_back(0x03);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x8A);

	DataBuffer b(data);
	DataBuffer b2(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_14), WirelessParser::parsePacketResult_completePacket);

	BOOST_CHECK_EQUAL(packet.nodeAddress(), 1);
	BOOST_CHECK_EQUAL(packet.type(), WirelessPacket::packetType_LDC);
	BOOST_CHECK_EQUAL(packet.frequency(), WirelessTypes::freq_14);

	//parse the same packet again, which will be thrown out as a duplicate
	BOOST_CHECK_EQUAL(parser.parseAsPacket(b2, packet, WirelessTypes::freq_14), WirelessParser::parsePacketResult_duplicate);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(WirelessParser_ParseSuite)

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_DataPacket)
{
	//a valid ASPP packet that has an LDC packet type
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x04);		//LDC Packet Type
	data.push_back(0x01);		//Node 456 (0x01C8)
	data.push_back(0xC8);
	data.push_back(0x08);		//payload length
	data.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	data.push_back(0x01);		//channel mask
	data.push_back(0x70);		//sample rate
	data.push_back(0x03);		//data type
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x52);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	WirelessPacketCollector packetCollector;
	WirelessParser parser(packetCollector, responseCollector);

	DataSweep sweep;
	//check that calling getNextDataSweep currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(b, WirelessTypes::freq_15);

	//calling getNextDataSweep now should return a legitimate DataSweep
	packetCollector.getNextDataSweep(sweep, 0);

	//check that the sweep is what we stored there
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 456);
	BOOST_CHECK_EQUAL(sweep.frequency(), WirelessTypes::freq_15);

	//check that calling getNextDataSweep again throws an Error_NoData exception
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);
}

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_Duplicate)
{
	//a valid ASPP packet that has an LDC packet type
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x04);		//LDC Packet Type
	data.push_back(0x01);		//Node 456 (0x01C8)
	data.push_back(0xC8);
	data.push_back(0x08);		//payload length
	data.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	data.push_back(0x01);		//channel mask
	data.push_back(0x70);		//sample rate
	data.push_back(0x03);		//data type
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x52);

	DataBuffer b(data);
	DataBuffer bDuplicate(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	WirelessPacketCollector packetCollector;
	WirelessParser parser(packetCollector, responseCollector);

	DataSweep sweep;

	//check that calling getNextDataSweep currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(b, WirelessTypes::freq_18);

	//calling getNextDataSweep now should return a legitimate DataSweep
	packetCollector.getNextDataSweep(sweep, 0);

	//check that the sweep is what we stored there
	BOOST_CHECK_EQUAL(sweep.tick(), 0);
	BOOST_CHECK_EQUAL(sweep.frequency(), WirelessTypes::freq_18);

	//parse the same packet again
	parser.parse(bDuplicate, WirelessTypes::freq_18);

	//check that the packet was thrown out as being a duplicate
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);

	data[11] = 0x01;	//increment the tick
	data[17] = 0x53;	//checksum

	DataBuffer b3(data);

	parser.parse(b3, WirelessTypes::freq_15);

	DataSweep sweep2;
	packetCollector.getNextDataSweep(sweep2, 0);

	BOOST_CHECK_EQUAL(sweep2.tick(), 1);
	BOOST_CHECK_EQUAL(sweep2.frequency(), WirelessTypes::freq_15);
}

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_ResponsePacket_NoMatch)
{
	//a valid ASPP packet that isn't a command packet
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x03);
	data.push_back(0x0D);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x11);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);

	//create the response for the LongPing command that we will NOT be matching
	LongPing::Response response(123, rc);

	//build the long ping command to send
	ByteStream pingCommand = LongPing::buildCommand(123);

	WirelessPacketCollector packetCollector;
	WirelessParser parser(packetCollector, rc);

	DataSweep sweep;
	//check that calling getNextDataSweep currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(b, WirelessTypes::freq_15);

	//check that calling getNextDataSweep still throws an Error_NoData exception (no data was added)
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);
}

/*
BOOST_AUTO_TEST_CASE(WirelessParser_Parse_ResponsePacket_MatchCmd)
{
	Bytes data;
	data.push_back(0xBC);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x03);
	data.push_back(0x0D);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x11);

	DataBuffer b(data);

	//create the response for the LongPing command that we will be matching
	LongPing::Response response(123);

	//register the response with the response collector
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	RegisterTracker tracker = rc.registerResponse(response);

	//build the long ping command to send
	ByteStream pingCommand = LongPing::buildCommand(123);

	WirelessPacketCollector packetCollector;
	WirelessParser parser(&packetCollector, rc);

	//check that calling getNextDataSweep currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(b);

	//check that calling getNextDataSweep still throws an Error_NoData exception (no data was added)
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(0), Error_NoData);
}
*/

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_ResponsePacket_Match_Packet)
{
	//a valid ASPP packet that is a command response
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x02);
	data.push_back(0x01);
	data.push_back(0x6F);
	data.push_back(0x02);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x7B);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	//create the response for the LongPing command that we will be matching
	LongPing::Response response(367, rc);

	//build the long ping command to send
	ByteStream pingCommand = LongPing::buildCommand(367);

	WirelessPacketCollector packetCollector;
	WirelessParser parser(packetCollector, rc);

	DataSweep sweep;

	//check that calling getNextDataSweep currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(b, WirelessTypes::freq_15);

	//check that waiting for the response succeeds (found the response)
	BOOST_CHECK_EQUAL(response.wait(100), true);
}

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_Bad_Checksum)
{
	//looks like an ASPP packet but with an invalid checksum
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x04);		//LDC Packet Type
	data.push_back(0x01);		//Node 456 (0x01C8)
	data.push_back(0xC8);
	data.push_back(0x08);		//payload length
	data.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	data.push_back(0x01);		//channel mask
	data.push_back(0x70);		//sample rate
	data.push_back(0x03);		//data type
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x56);
	data.push_back(0x52);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	WirelessPacketCollector packetCollector;
	WirelessParser parser(packetCollector, rc);

	DataSweep sweep;

	//check that calling getNextDataSweep currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(b, WirelessTypes::freq_15);

	//check that calling getNextDataSweep again throws an Error_NoData exception
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);
}

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_Bad_Followed_By_Good)
{
	//random data that looks like an ASPP packet but with an invalid checksum
	//followed by a valid ASPP packet that has an LDC packet type
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x04);		//LDC Packet Type
	data.push_back(0x01);		//Node 456 (0x01C8)
	data.push_back(0xC8);
	data.push_back(0x08);		//payload length
	data.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	data.push_back(0x01);		//channel mask
	data.push_back(0x70);		//sample rate
	data.push_back(0x03);		//data type
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x52);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	WirelessPacketCollector packetCollector;
	WirelessParser parser(packetCollector, rc);

	DataSweep sweep;

	//check that calling getNextDataSweep currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(b, WirelessTypes::freq_15);

	//calling getNextDataSweep now should return a legitimate DataSweep
	packetCollector.getNextDataSweep(sweep, 0);

	//check that the sweep is what we stored there
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 456);

	//check that calling getNextDataSweep again throws an Error_NoData exception
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);
}


BOOST_AUTO_TEST_CASE(WirelessParser_Parse_Bad)
{
	//random data that looks like an ASPP packet but with an invalid checksum
	//followed by part of an ASPP packet, but not complete
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x04);		//LDC Packet Type
	data.push_back(0x01);		//Node 456 (0x01C8)
	data.push_back(0xC8);
	data.push_back(0x08);		//payload length
	data.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	data.push_back(0x01);		//channel mask
	data.push_back(0x70);		//sample rate
	data.push_back(0x03);		//data type

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	WirelessPacketCollector packetCollector;
	WirelessParser parser(packetCollector, rc);

	DataSweep sweep;

	//check that calling getNextDataSweep currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(b, WirelessTypes::freq_15);

	//check that calling getNextDataSweep again throws an Error_NoData exception
	BOOST_CHECK_THROW(packetCollector.getNextDataSweep(sweep, 0), Error_NoData);
}

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_StartSyncSampling_1node)
{
	//a valid ASPP packet
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x75);
	data.push_back(0x03);
	data.push_back(0x00);
	data.push_back(0x3B);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0xD2);
	data.push_back(0x00);
	data.push_back(0xBB);

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);

	//create the response for the StartSyncSampling command
	StartSyncSampling::Response response1(373, responseCollector);

	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	parser.parse(b, WirelessTypes::freq_14);

	BOOST_CHECK_EQUAL(response1.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response1.success(), true);
}

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_StartSyncSampling_2nodes_sequentially)
{
	//a valid ASPP packet
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x75);
	data.push_back(0x03);
	data.push_back(0x00);
	data.push_back(0x3B);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0xD2);
	data.push_back(0x00);
	data.push_back(0xBB);
	DataBuffer b(data);

	Bytes data2;
	data2.push_back(0xAA);
	data2.push_back(0xAA);
	data2.push_back(0x07);
	data2.push_back(0x00);
	data2.push_back(0x00);
	data2.push_back(0x3A);
	data2.push_back(0x03);
	data2.push_back(0x00);
	data2.push_back(0x3B);
	data2.push_back(0x00);
	data2.push_back(0x00);
	data2.push_back(0xE2);
	data2.push_back(0x00);
	data2.push_back(0x7F);
	DataBuffer b2(data2);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);

	//create the response for the StartSyncSampling command
	StartSyncSampling::Response response1(373, responseCollector);

	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	parser.parse(b, WirelessTypes::freq_14);

	BOOST_CHECK_EQUAL(response1.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response1.success(), true);

	StartSyncSampling::Response response2(58, responseCollector);
	parser.parse(b2, WirelessTypes::freq_14);

	BOOST_CHECK_EQUAL(response2.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response2.success(), true);
}

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_StartSyncSampling_2nodes_sameTime)
{
	//a valid ASPP packet
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x75);
	data.push_back(0x03);
	data.push_back(0x00);
	data.push_back(0x3B);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0xD2);
	data.push_back(0x00);
	data.push_back(0xBB);
	DataBuffer b(data);

	Bytes data2;
	data2.push_back(0xAA);
	data2.push_back(0xAA);
	data2.push_back(0x07);
	data2.push_back(0x00);
	data2.push_back(0x00);
	data2.push_back(0x3A);
	data2.push_back(0x03);
	data2.push_back(0x00);
	data2.push_back(0x3B);
	data2.push_back(0x00);
	data2.push_back(0x00);
	data2.push_back(0xE2);
	data2.push_back(0x00);
	data2.push_back(0x7F);
	DataBuffer b2(data2);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);

	//create the response for the StartSyncSampling command
	StartSyncSampling::Response response1(373, responseCollector);
	StartSyncSampling::Response response2(58, responseCollector);

	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	parser.parse(b, WirelessTypes::freq_14);
	parser.parse(b2, WirelessTypes::freq_14);

	BOOST_CHECK_EQUAL(response1.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response1.success(), true);

	BOOST_CHECK_EQUAL(response2.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response2.success(), true);
}

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_StartSyncSampling_2nodes_extraBytes)
{
	Bytes extra1;
	extra1.push_back(0xAA);
	DataBuffer eb(extra1);

	Bytes extra2;
	extra2.push_back(0xAA);
	extra2.push_back(0xBE);
	extra2.push_back(0xAC);
	DataBuffer eb2(extra2);

	//a valid ASPP packet
	Bytes data;
	data.push_back(0xAA);
	data.push_back(0x07);
	data.push_back(0x00);
	data.push_back(0x01);
	data.push_back(0x75);
	data.push_back(0x03);
	data.push_back(0x00);
	data.push_back(0x3B);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0xD2);
	data.push_back(0x00);
	data.push_back(0xBB);
	DataBuffer b(data);

	Bytes data2;
	data2.push_back(0xAA);
	data2.push_back(0xAA);
	data2.push_back(0x07);
	data2.push_back(0x00);
	data2.push_back(0x00);
	data2.push_back(0x3A);
	data2.push_back(0x03);
	data2.push_back(0x00);
	data2.push_back(0x3B);
	data2.push_back(0x00);
	data2.push_back(0x00);
	data2.push_back(0xE2);
	data2.push_back(0x00);
	data2.push_back(0x7F);
	DataBuffer b2(data2);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);

	//create the response for the StartSyncSampling command
	StartSyncSampling::Response response1(373, responseCollector);
	StartSyncSampling::Response response2(58, responseCollector);

	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	parser.parse(eb, WirelessTypes::freq_14);
	parser.parse(b, WirelessTypes::freq_14);
	parser.parse(eb2, WirelessTypes::freq_14);
	parser.parse(b2, WirelessTypes::freq_14);

	BOOST_CHECK_EQUAL(response1.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response1.success(), true);

	BOOST_CHECK_EQUAL(response2.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response2.success(), true);
}

BOOST_AUTO_TEST_CASE(WirelessParser_Parse_PageDownload)
{
	//build the page download response
	Bytes data;
	data.push_back(0x05);
	for(int i = 0; i < 260; i++)
	{
		data.push_back(0x00);//data points
	}
	//add the last 4 bytes manually for data purposes
	data.push_back(0x01);
	data.push_back(0x02);
	data.push_back(0x01);
	data.push_back(0x04);
	data.push_back(0x00);	//checksum msb
	data.push_back(0x08);	//checksum lsb

	DataBuffer b(data);

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);

	//create the response for the StartSyncSampling command
	PageDownload::Response response(responseCollector);

	WirelessPacketCollector m_packetCollector;
	WirelessParser parser(m_packetCollector, responseCollector);
	WirelessPacket packet;

	parser.parse(b, WirelessTypes::freq_14);

	BOOST_CHECK_EQUAL(response.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response.success(), true);
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()