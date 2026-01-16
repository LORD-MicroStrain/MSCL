/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/DataSweep.h"
#include "mscl/MicroStrain/Wireless/Packets/LdcPacket_v2.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(Ldc16chPacket_Test)

BOOST_AUTO_TEST_CASE(Ldc16chPacket_Constructor_4ByteFloat)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x22);    //app id / data type - 4 byte float
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2
    payloadBytes.push_back(0);        //channel data b3
    payloadBytes.push_back(0);        //channel data b4

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //call the addDataPacket() function to parse the packet as an LDC Packet
    WirelessPacketCollector collector;
    collector.addDataPacket(packet);

    DataSweeps sweeps;
    collector.getDataSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps.size(), 1);

    DataSweep sweep = sweeps.at(0);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 1);
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_float);
}

BOOST_AUTO_TEST_CASE(Ldc16chPacket_Constructor_2byteUint_Shifted)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x21);    //app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //call the addDataPacket() function to parse the packet as an LDC Packet
    WirelessPacketCollector collector;
    collector.addDataPacket(packet);

    DataSweeps sweeps;
    collector.getDataSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps.size(), 1);

    DataSweep sweep = sweeps.at(0);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 1);
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_uint16);
}

BOOST_AUTO_TEST_CASE(Ldc16chPacket_Constructor_2byteUint)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //call the addDataPacket() function to parse the packet as an LDC Packet
    WirelessPacketCollector collector;
    collector.addDataPacket(packet);

    DataSweeps sweeps;
    collector.getDataSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps.size(), 1);

    DataSweep sweep = sweeps.at(0);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 1);
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_uint16);
}

BOOST_AUTO_TEST_CASE(Ldc16chPacket_IntegrityCheck_Good)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0x01);    //channel mask - channel 9
    payloadBytes.push_back(0x01);    //channel mask - channel 1
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x22);    //app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(1);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(LdcPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Ldc16chPacket_IntegrityCheck_SmallPayload)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(LdcPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Ldc16chPacket_IntegrityCheck_BadAppID)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x12);    //BAD app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(LdcPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Ldc16chPacket_IntegrityCheck_BadStopFlags)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(15));    //INVALID DELIVERY STOP FLAGS
    packet.type(WirelessPacket::packetType_LDC_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(LdcPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Ldc16chPacket_IntegrityCheck_BadPacketType)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC);        //INVALID PACKET TYPE
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(LdcPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Ldc16chPacket_IntegrityCheck_InvalidPayloadSize)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(3);        //channel mask - 2 channels active
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1    (ONLY 1 CHANNEL OF DATA WHEN SHOULD BE 2)
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(LdcPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Ldc16chPacket_IntegrityCheck_BadDataType)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 2 channels active
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x20);    //app id / BAD data type
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(LdcPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_SUITE_END()
