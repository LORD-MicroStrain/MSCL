/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/DataSweep.h"
#include "mscl/MicroStrain/Wireless/Packets/ShmPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(ShmPacket_Test)

BOOST_AUTO_TEST_CASE(ShmPacket_Constructor)
{
    ByteStream payloadBytes;
    payloadBytes.append_uint8(0xA0);    //app id
    payloadBytes.append_uint8(0);        //angle id
    payloadBytes.append_uint8(0);        //mode
    payloadBytes.append_uint16(5);        //bin size
    payloadBytes.append_uint16(10);        //bin lower bound
    payloadBytes.append_uint16(16);        //dataset id
    payloadBytes.append_uint32(25);        //uptime
    payloadBytes.append_float(0.622558944f);    //angle    (in radians)
    payloadBytes.append_float(20.6f);    //life

    //there are 21 bins in each packet
    for(int i = 0; i < 21; i++)
    {
        payloadBytes.append_uint32(13);    //bin data
    }

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SHM);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes.data());    //give the packet the payload bytes we created

    //call the addDataPacket() function to parse the packet as an LDC Packet
    WirelessPacketCollector collector;
    collector.addDataPacket(packet);

    DataSweeps sweeps;
    collector.getDataSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps.size(), 1);

    DataSweep sweep = sweeps.at(0);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 16);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);    //1 point in the packet
    BOOST_CHECK_EQUAL(sweep.data().at(0).channelId(), WirelessChannel::channel_structuralHealth);
    BOOST_CHECK_EQUAL(sweep.data().at(0).channelNumber(), 0);
    BOOST_CHECK_EQUAL(sweep.data().at(0).channelName(), "structuralHealth_angle35.67");

    BOOST_CHECK_EQUAL(sweep.data().at(0).storedAs(), valueType_StructuralHealth);

    StructuralHealth sh = sweep.data().at(0).as_StructuralHealth();

    BOOST_CHECK_EQUAL(sh.uptime(), 25);
    BOOST_CHECK_CLOSE(sh.angle(), 35.67, 0.0001);
    BOOST_CHECK_CLOSE(sh.damage(), 20.6, 0.0001);

    Bins bins = sh.histogram().bins();
    Bin bin = bins.at(0);
    BOOST_CHECK_EQUAL(sh.histogram().binsStart().as_uint32(), 10);
    BOOST_CHECK_EQUAL(sh.histogram().binsSize().as_uint32(), 5);
    BOOST_CHECK_EQUAL(bins.size(), 21);
    BOOST_CHECK_EQUAL(bin.start().as_uint32(), 10);
    BOOST_CHECK_EQUAL(bin.end().as_uint32(), 15);
    BOOST_CHECK_EQUAL(bin.count().as_uint32(), 13);
    bin = bins.at(1);
    BOOST_CHECK_EQUAL(bin.start().as_uint32(), 15);
    BOOST_CHECK_EQUAL(bin.end().as_uint32(), 20);
}

BOOST_AUTO_TEST_CASE(ShmPacket2_Constructor)
{
    ByteStream payloadBytes;
    payloadBytes.append_uint8(0x00);    //app id (v2)
    payloadBytes.append_uint8(108);        //transmit rate
    payloadBytes.append_uint8(112);        //processing rate
    payloadBytes.append_uint32(4000000000);        //persistant tick
    payloadBytes.append_float(42.17663f);    //angle (in degrees)
    payloadBytes.append_float(20.36f);    //damage
    payloadBytes.append_uint16(10);        //bin start
    payloadBytes.append_uint16(5);        //bin size

    //there are 21 bins in each packet
    for(int i = 0; i < 21; i++)
    {
        payloadBytes.append_uint32(3000000000);    //bin data
    }

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SHM);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes.data());    //give the packet the payload bytes we created

    //call the addDataPacket() function to parse the packet as an LDC Packet
    WirelessPacketCollector collector;
    collector.addDataPacket(packet);

    DataSweeps sweeps;
    collector.getDataSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps.size(), 1);

    DataSweep sweep = sweeps.at(0);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 4000000000);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);    //1 point in the packet
    BOOST_CHECK_EQUAL(sweep.data().at(0).channelId(), WirelessChannel::channel_structuralHealth);
    BOOST_CHECK_EQUAL(sweep.data().at(0).channelNumber(), 0);
    BOOST_CHECK_EQUAL(sweep.data().at(0).channelName(), "structuralHealth_angle42.18");

    BOOST_CHECK_EQUAL(sweep.data().at(0).storedAs(), valueType_StructuralHealth);

    StructuralHealth sh = sweep.data().at(0).as_StructuralHealth();

    BOOST_CHECK_EQUAL(sh.uptime(), 4000000000);
    BOOST_CHECK_CLOSE(sh.angle(), 42.17663, 0.0001);
    BOOST_CHECK_CLOSE(sh.damage(), 20.36, 0.0001);

    Bins bins = sh.histogram().bins();
    Bin bin = bins.at(0);
    BOOST_CHECK_EQUAL(sh.histogram().binsStart().as_uint32(), 10);
    BOOST_CHECK_EQUAL(sh.histogram().binsSize().as_uint32(), 5);
    BOOST_CHECK_EQUAL(bins.size(), 21);
    BOOST_CHECK_EQUAL(bin.start().as_uint32(), 10);
    BOOST_CHECK_EQUAL(bin.end().as_uint32(), 15);
    BOOST_CHECK_EQUAL(bin.count().as_uint32(), 3000000000);
    bin = bins.at(1);
    BOOST_CHECK_EQUAL(bin.start().as_uint32(), 15);
    BOOST_CHECK_EQUAL(bin.end().as_uint32(), 20);
}

BOOST_AUTO_TEST_CASE(ShmPacket_IntegrityCheck_SmallPayload)
{
    ByteStream payloadBytes;
    payloadBytes.append_uint8(0xA0);    //app id
    payloadBytes.append_uint8(0);        //angle id
    payloadBytes.append_uint8(0);        //mode
    payloadBytes.append_uint16(5);        //bin size
    payloadBytes.append_uint16(10);        //bin lower bound
    payloadBytes.append_uint16(16);        //dataset id
    payloadBytes.append_uint32(25);        //uptime
    payloadBytes.append_float(35.67f);    //angle
    payloadBytes.append_float(20.6f);    //life
                                        //no bins

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SHM);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes.data());    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(ShmPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(ShmPacket_IntegrityCheck_BadStopFlags)
{
    ByteStream payloadBytes;
    payloadBytes.append_uint8(0xA0);    //app id
    payloadBytes.append_uint8(0);        //angle id
    payloadBytes.append_uint8(0);        //mode
    payloadBytes.append_uint16(5);        //bin size
    payloadBytes.append_uint16(10);        //bin lower bound
    payloadBytes.append_uint16(16);        //dataset id
    payloadBytes.append_uint32(25);        //uptime
    payloadBytes.append_float(35.67f);    //angle
    payloadBytes.append_float(20.6f);    //life

    //there are 21 bins in each packet
    for(int i = 0; i < 21; i++)
    {
        payloadBytes.append_uint32(13);    //bin data
    }

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(15));    //INVALID DELIVERY STOP FLAGS
    packet.type(WirelessPacket::packetType_SHM);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes.data());    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(ShmPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(ShmPacket_IntegrityCheck_BadPacketType)
{
    ByteStream payloadBytes;
    payloadBytes.append_uint8(0xA0);    //app id
    payloadBytes.append_uint8(0);        //angle id
    payloadBytes.append_uint8(0);        //mode
    payloadBytes.append_uint16(5);        //bin size
    payloadBytes.append_uint16(10);        //bin lower bound
    payloadBytes.append_uint16(16);        //dataset id
    payloadBytes.append_uint32(25);        //uptime
    payloadBytes.append_float(35.67f);    //angle
    payloadBytes.append_float(20.6f);    //life

    //there are 21 bins in each packet
    for(int i = 0; i < 21; i++)
    {
        payloadBytes.append_uint32(13);    //bin data
    }

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling);        //INVALID PACKET TYPE
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes.data());    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(ShmPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_SUITE_END()
