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
#include "mscl/MicroStrain/Wireless/Packets/NodeDiscoveryPacket_v2.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(NodeDiscoveryPacket_v2_Test)

BOOST_AUTO_TEST_CASE(NodeDiscovery_v2_IntegrityCheck_Fail_PayloadSize)
{
	Bytes payloadBytes;
	payloadBytes.push_back(12);		

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
	packet.type(WirelessPacket::packetType_nodeDiscovery_v2);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_v2_IntegrityCheck_Fail_Frequency)
{
	Bytes payloadBytes;
	payloadBytes.push_back(99);		//INVALID freq
	payloadBytes.push_back(0xBA);	//pan id (0xBABE)
	payloadBytes.push_back(0xBE);
	payloadBytes.push_back(0x03);	//model (node_gLink_10g)
	payloadBytes.push_back(0xC2);
	payloadBytes.push_back(0x1C);
	payloadBytes.push_back(0xC8);
	payloadBytes.push_back(0x00);	//serial (31849)
	payloadBytes.push_back(0x00);
	payloadBytes.push_back(0x7C);
	payloadBytes.push_back(0x69);
	payloadBytes.push_back(0x07);	//firmware version (7.15.0)
	payloadBytes.push_back(0x0F);
	payloadBytes.push_back(0x00);	//boot mode (defaultMode_sleep)
	payloadBytes.push_back(0x05);

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
	packet.type(WirelessPacket::packetType_nodeDiscovery_v2);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_v2_IntegrityCheck_Fail_DSF)
{
	Bytes payloadBytes;
	payloadBytes.push_back(13);		//freq
	payloadBytes.push_back(0xBA);	//pan id (0xBABE)
	payloadBytes.push_back(0xBE);
	payloadBytes.push_back(0x03);	//model (node_gLink_10g)
	payloadBytes.push_back(0xC2);
	payloadBytes.push_back(0x1C);
	payloadBytes.push_back(0xC8);
	payloadBytes.push_back(0x00);	//serial (31849)
	payloadBytes.push_back(0x00);
	payloadBytes.push_back(0x7C);
	payloadBytes.push_back(0x69);
	payloadBytes.push_back(0x07);	//firmware version (7.15.0)
	payloadBytes.push_back(0x0F);
	payloadBytes.push_back(0x00);	//boot mode (defaultMode_sleep)
	payloadBytes.push_back(0x05);

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags(false, true, false, true));	//invalid DSF
	packet.type(WirelessPacket::packetType_nodeDiscovery_v2);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_v2_IntegrityCheck_Fail_PacketType)
{
	Bytes payloadBytes;
	payloadBytes.push_back(13);		//freq
	payloadBytes.push_back(0xBA);	//pan id (0xBABE)
	payloadBytes.push_back(0xBE);
	payloadBytes.push_back(0x03);	//model (node_gLink_10g)
	payloadBytes.push_back(0xC2);
	payloadBytes.push_back(0x1C);
	payloadBytes.push_back(0xC8);
	payloadBytes.push_back(0x00);	//serial (31849)
	payloadBytes.push_back(0x00);
	payloadBytes.push_back(0x7C);
	payloadBytes.push_back(0x69);
	payloadBytes.push_back(0x07);	//firmware version (7.15.0)
	payloadBytes.push_back(0x0F);
	payloadBytes.push_back(0x00);	//boot mode (defaultMode_sleep)
	payloadBytes.push_back(0x05);

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
	packet.type(WirelessPacket::packetType_nodeDiscovery);				//invalid packet type
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_v2_IntegrityCheck_Success)
{
	Bytes payloadBytes;
	payloadBytes.push_back(13);		//freq
	payloadBytes.push_back(0xBA);	//pan id (0xBABE)
	payloadBytes.push_back(0xBE);
	payloadBytes.push_back(0x03);	//model (node_gLink_10g)
	payloadBytes.push_back(0xC2);
	payloadBytes.push_back(0x1C);
	payloadBytes.push_back(0xC8);
	payloadBytes.push_back(0x00);	//serial (31849)
	payloadBytes.push_back(0x00);
	payloadBytes.push_back(0x7C);
	payloadBytes.push_back(0x69);
	payloadBytes.push_back(0x07);	//firmware version (7.15.0)
	payloadBytes.push_back(0x0F);
	payloadBytes.push_back(0x00);	//boot mode (defaultMode_sleep)
	payloadBytes.push_back(0x05);

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
	packet.type(WirelessPacket::packetType_nodeDiscovery_v2);				
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket_v2::integrityCheck(packet), true);
}

BOOST_AUTO_TEST_SUITE_END()