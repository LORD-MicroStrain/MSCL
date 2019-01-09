/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/NodeDiscovery.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/Timestamp.h"

#include <boost/test/unit_test.hpp>
#include "mock_BaseStation.h"
#include "mock_WirelessNode.h"

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
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
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
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x07));
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
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x07));
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

BOOST_AUTO_TEST_CASE(NodeDiscovery_v1_updateEepromCache)
{
    Bytes payloadBytes;
    payloadBytes.push_back(18);
    payloadBytes.push_back(Utils::msb(2433));
    payloadBytes.push_back(Utils::lsb(2433));

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_nodeDiscovery);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);

    packet.payload(payloadBytes);

    //create a NodeDiscovery object with the packet
    NodeDiscovery nd(packet);

    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
    BaseStation base(impl);

    std::unique_ptr<BaseStationFeatures> baseFeatures;
    expectBaseFeatures(baseFeatures, impl);
    MOCK_EXPECT(impl->communicationProtocol).returns(WirelessTypes::commProtocol_lxrs);
    MOCK_EXPECT(impl->node_pageDownload).returns(false);
    MOCK_EXPECT(impl->node_readEeprom).once().with(mock::any, mock::any, 124, mock::assign(0x0105)).returns(true);  //aspp ver lxrs
    MOCK_EXPECT(impl->node_readEeprom).once().with(mock::any, mock::any, 126, mock::assign(0x0105)).returns(true);  //aspp ver lxrs+
    MOCK_EXPECT(impl->node_readEeprom).once().with(mock::any, mock::any, 46, mock::assign(0)).returns(true);        //new model number eeprom (act like not supported)

    WirelessNode node(100, base);

    node.updateEepromCacheFromNodeDiscovery(nd);

    BOOST_CHECK_EQUAL(node.frequency(), WirelessTypes::freq_18);
    BOOST_CHECK_EQUAL(node.model(), WirelessModels::node_vLink);
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_v2_updateEepromCache)
{
    Bytes payloadBytes;
    payloadBytes.push_back(14);      //freq
    payloadBytes.push_back(0xBA);    //pan id (0xBABE)
    payloadBytes.push_back(0xBE);
    payloadBytes.push_back(0x18);    //model (shm-link)
    payloadBytes.push_back(0xA4);
    payloadBytes.push_back(0x17);
    payloadBytes.push_back(0x70);
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
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x07));
    packet.type(WirelessPacket::packetType_nodeDiscovery_v2);
    packet.nodeRSSI(-45);
    packet.baseRSSI(-5);
    packet.payload(payloadBytes);

    //create a NodeDiscovery object with the packet
    NodeDiscovery nd(packet);

    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
    BaseStation base(impl);

    std::unique_ptr<BaseStationFeatures> baseFeatures;
    expectBaseFeatures(baseFeatures, impl);
    MOCK_EXPECT(impl->communicationProtocol).returns(WirelessTypes::commProtocol_lxrs);

    WirelessNode node(100, base);

    node.updateEepromCacheFromNodeDiscovery(nd);

    BOOST_CHECK_EQUAL(node.frequency(), WirelessTypes::freq_14);
    BOOST_CHECK_EQUAL(node.model(), WirelessModels::node_shmLink);
    BOOST_CHECK_EQUAL(node.serial(), "6308-6000-31849");
    BOOST_CHECK_EQUAL(node.firmwareVersion().str(), "7.15.0");
}

BOOST_AUTO_TEST_CASE(NodeDiscovery_v3_updateEepromCache)
{
    Bytes payloadBytes;
    payloadBytes.push_back(20);      //freq
    payloadBytes.push_back(0xBA);    //pan id (0xBABE)
    payloadBytes.push_back(0xBE);
    payloadBytes.push_back(0x18);    //model (node_gLink_10g)
    payloadBytes.push_back(0xA1);
    payloadBytes.push_back(0x0B);
    payloadBytes.push_back(0xB8);
    payloadBytes.push_back(0x00);    //serial (87125)
    payloadBytes.push_back(0x01);
    payloadBytes.push_back(0x54);
    payloadBytes.push_back(0x55);
    payloadBytes.push_back(0x3E);    //firmware version (62.13)
    payloadBytes.push_back(0x00);
    payloadBytes.push_back(0x00);
    payloadBytes.push_back(0x0D);
    payloadBytes.push_back(0x00);    //boot mode (defaultMode_sleep)
    payloadBytes.push_back(0x05);

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x07));
    packet.type(WirelessPacket::packetType_nodeDiscovery_v3);
    packet.nodeRSSI(-45);
    packet.baseRSSI(-5);
    packet.payload(payloadBytes);

    //create a NodeDiscovery object with the packet
    NodeDiscovery nd(packet);

    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
    BaseStation base(impl);

    std::unique_ptr<BaseStationFeatures> baseFeatures;
    expectBaseFeatures(baseFeatures, impl);
    MOCK_EXPECT(impl->communicationProtocol).returns(WirelessTypes::commProtocol_lxrs);

    WirelessNode node(100, base);

    node.updateEepromCacheFromNodeDiscovery(nd);

    BOOST_CHECK_EQUAL(node.frequency(), WirelessTypes::freq_20);
    BOOST_CHECK_EQUAL(node.model(), WirelessModels::node_gLink_10g);
    BOOST_CHECK_EQUAL(node.serial(), "6305-3000-87125");
    BOOST_CHECK_EQUAL(node.firmwareVersion().str(), "62.13.0");
    BOOST_CHECK_EQUAL(node.getDefaultMode(), WirelessTypes::defaultMode_sleep);
}

BOOST_AUTO_TEST_SUITE_END()