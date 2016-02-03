/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/NodeDiscovery.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/Timestamp.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(NodeDiscovery_Test)

BOOST_AUTO_TEST_CASE(NodeDiscovery_DefaultConstructor)
{
    NodeDiscovery nd;

    int unknownRssi = WirelessTypes::UNKNOWN_RSSI;

    BOOST_CHECK_EQUAL(nd.nodeAddress(), 0);
    BOOST_CHECK_EQUAL(nd.frequency(), WirelessTypes::freq_unknown);
    BOOST_CHECK_EQUAL(nd.model(), 0);
    BOOST_CHECK_EQUAL(nd.baseRssi(), unknownRssi);
    BOOST_CHECK_EQUAL(nd.timestamp().nanoseconds(), 0);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_Constructor)
{
    Bytes payloadBytes;
    payloadBytes.push_back(12);    
    payloadBytes.push_back(0x04);    
    payloadBytes.push_back(0xD2);    

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
    packet.type(WirelessPacket::packetType_nodeDiscovery);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);

    //create a NodeDiscovery object with the packet
    NodeDiscovery nd(packet);
    Timestamp timeNow = Timestamp::timeNow();

    NodeDiscoveries nds;
    nds.push_back(nd);

    BOOST_CHECK_EQUAL(nds.at(0).nodeAddress(), 345);
    BOOST_CHECK_EQUAL(nds.at(0).frequency(), 12);
    BOOST_CHECK_EQUAL(nds.at(0).model(), 1234);
    BOOST_CHECK_EQUAL(nds.at(0).baseRssi(), 1);
    BOOST_CHECK_LE(nds.at(0).timestamp().nanoseconds(), timeNow.nanoseconds());
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_Constructor_v2)
{
    Bytes payloadBytes;
    payloadBytes.push_back(13);        //freq
    payloadBytes.push_back(0xBA);    //pan id (0xBABE)
    payloadBytes.push_back(0xBE);
    payloadBytes.push_back(0x18);    //model (node_gLink_10g)
    payloadBytes.push_back(0xA1);
    payloadBytes.push_back(0x0B);
    payloadBytes.push_back(0xB8);
    payloadBytes.push_back(0x00);    //serial (31849)
    payloadBytes.push_back(0x00);
    payloadBytes.push_back(0x7C);
    payloadBytes.push_back(0x69);
    payloadBytes.push_back(0x07);    //firmware version (7.15.0)
    payloadBytes.push_back(0x0F);
    payloadBytes.push_back(0x00);    //boot mode (defaultMode_sleep)
    payloadBytes.push_back(0x05);

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
    packet.type(WirelessPacket::packetType_nodeDiscovery_v2);
    packet.nodeRSSI(-45);
    packet.baseRSSI(-5);
    packet.payload(payloadBytes);

    //create a NodeDiscovery object with the packet
    NodeDiscovery nd(packet);
    Timestamp timeNow = Timestamp::timeNow();

    BOOST_CHECK_EQUAL(nd.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(nd.frequency(), 13);
    BOOST_CHECK_EQUAL(nd.model(), WirelessModels::node_gLink_10g);
    BOOST_CHECK_EQUAL(nd.baseRssi(), -5);
    BOOST_CHECK_EQUAL(nd.panId(), 0xBABE);
    BOOST_CHECK_EQUAL(nd.serialNumber(), 31849);
    BOOST_CHECK_EQUAL(nd.firmwareVersion().str(), "7.15.0");
    BOOST_CHECK_EQUAL(nd.defaultMode(), 999);
    BOOST_CHECK_LE(nd.timestamp().nanoseconds(), timeNow.nanoseconds());
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_Constructor_v3)
{
    Bytes payloadBytes;
    payloadBytes.push_back(13);        //freq
    payloadBytes.push_back(0xBA);    //pan id (0xBABE)
    payloadBytes.push_back(0xBE);
    payloadBytes.push_back(0x18);    //model (node_gLink_10g)
    payloadBytes.push_back(0xA1);
    payloadBytes.push_back(0x0B);
    payloadBytes.push_back(0xB8);
    payloadBytes.push_back(0x00);    //serial (31849)
    payloadBytes.push_back(0x00);
    payloadBytes.push_back(0x7C);
    payloadBytes.push_back(0x69);
    payloadBytes.push_back(0x3E);    //firmware version (62.13)
    payloadBytes.push_back(0x00);
    payloadBytes.push_back(0x00);
    payloadBytes.push_back(0x0D);
    payloadBytes.push_back(0x00);    //boot mode (defaultMode_sleep)
    payloadBytes.push_back(0x05);

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
    packet.type(WirelessPacket::packetType_nodeDiscovery_v3);
    packet.nodeRSSI(-45);
    packet.baseRSSI(-5);
    packet.payload(payloadBytes);

    //create a NodeDiscovery object with the packet
    NodeDiscovery nd(packet);
    Timestamp timeNow = Timestamp::timeNow();

    BOOST_CHECK_EQUAL(nd.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(nd.frequency(), 13);
    BOOST_CHECK_EQUAL(nd.model(), WirelessModels::node_gLink_10g);
    BOOST_CHECK_EQUAL(nd.baseRssi(), -5);
    BOOST_CHECK_EQUAL(nd.panId(), 0xBABE);
    BOOST_CHECK_EQUAL(nd.serialNumber(), 31849);
    BOOST_CHECK_EQUAL(nd.firmwareVersion().str(), "62.13.0");
    BOOST_CHECK_EQUAL(nd.defaultMode(), WirelessTypes::defaultMode_sleep);
    BOOST_CHECK_LE(nd.timestamp().nanoseconds(), timeNow.nanoseconds());
}

BOOST_AUTO_TEST_SUITE_END()