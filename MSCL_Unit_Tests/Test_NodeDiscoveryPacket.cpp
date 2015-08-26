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
#include "mscl/MicroStrain/Wireless/Packets/NodeDiscoveryPacket.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(NodeDiscoveryPacket_Test)

BOOST_AUTO_TEST_CASE(NodeDiscovery_IntegrityCheck_Fail_PayloadSize)
{
	Bytes payloadBytes;
	payloadBytes.push_back(12);		

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_nodeDiscovery);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_IntegrityCheck_Fail_LowFrequency)
{
	Bytes payloadBytes;
	payloadBytes.push_back(1);		//invalid frequency
	payloadBytes.push_back(0x09);	
	payloadBytes.push_back(0x7A);	

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_nodeDiscovery);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_IntegrityCheck_Fail_HighFrequency)
{
	Bytes payloadBytes;
	payloadBytes.push_back(50);		//invalid frequency
	payloadBytes.push_back(0x09);	
	payloadBytes.push_back(0x7A);	

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_nodeDiscovery);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_IntegrityCheck_Fail_DSF)
{
	Bytes payloadBytes;
	payloadBytes.push_back(13);		
	payloadBytes.push_back(0x09);	
	payloadBytes.push_back(0x7A);	

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags(false, true, false, true));	//invalid DSF
	packet.type(WirelessPacket::packetType_nodeDiscovery);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_IntegrityCheck_Fail_PacketType)
{
	Bytes payloadBytes;
	payloadBytes.push_back(13);		
	payloadBytes.push_back(0x09);	
	payloadBytes.push_back(0x7A);	

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags(true, true, true, true));
	packet.type(WirelessPacket::packetType_BufferedLDC);				//invalid packet type
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_IntegrityCheck_Success)
{
	Bytes payloadBytes;
	payloadBytes.push_back(13);		
	payloadBytes.push_back(0x09);	
	payloadBytes.push_back(0x7A);	

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags(true, true, true, true));
	packet.type(WirelessPacket::packetType_nodeDiscovery);				
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(NodeDiscoveryPacket::integrityCheck(packet), true);
}

BOOST_AUTO_TEST_SUITE_END()