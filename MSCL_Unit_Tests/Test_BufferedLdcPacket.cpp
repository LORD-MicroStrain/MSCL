/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/DataSweep.h"
#include "mscl/MicroStrain/Wireless/Packets/BufferedLdcPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(BufferedLdcPacket_Test)

BOOST_AUTO_TEST_CASE(BufferedLdc_Constructor_4ByteFloat)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);        //app id
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_float32);    //data type - 4 byte float
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2
    payloadBytes.push_back(0);        //channel data b3
    payloadBytes.push_back(0);        //channel data b4
    payloadBytes.push_back(1);        //channel data b1
    payloadBytes.push_back(1);        //channel data b2
    payloadBytes.push_back(1);        //channel data b3
    payloadBytes.push_back(1);        //channel data b4

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //call the addDataPacket() function to parse the packet as an LDC Packet
    WirelessPacketCollector collector;
    collector.addDataPacket(packet);

    DataSweeps sweeps;
    collector.getDataSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps.size(), 2);

    DataSweep sweep = sweeps.at(0);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 1);
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_float);

    sweep = sweeps.at(1);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 2);    //check that the tick incremented (by MSCL, not by the packet)
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_float);
}

BOOST_AUTO_TEST_CASE(BufferedLdc_Constructor_2ByteUint)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);        //app id
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_uint16_12bitRes);    //data type - 2 byte uint
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(254);    //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
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
    BOOST_CHECK_EQUAL(sweep.data()[0].as_uint16(), 254);    //check that the data was shifted (divided by 2)
}

BOOST_AUTO_TEST_CASE(BufferedLdc_Constructor_2ByteUintShifted)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);        //app id
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_uint16_shifted);    //data type - 2 byte uint shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(254);    //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
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
    BOOST_CHECK_EQUAL(sweep.data()[0].as_uint16(), 127);    //check that the data was shifted (divided by 2)
}

BOOST_AUTO_TEST_CASE(BufferedLdc_Constructor_NoChannelMask)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);        //app id
    payloadBytes.push_back(0);        //channel mask - NO CHANNELS
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_uint16_12bitRes);    //data type - 2 byte uint
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
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
    BOOST_CHECK_EQUAL(sweep.data().size(), 0);
}

BOOST_AUTO_TEST_CASE(BufferedLdc_IntegrityCheck_Good)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);        //app id
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_uint16_12bitRes);    //data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(BufferedLdcPacket::integrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(BufferedLdc_IntegrityCheck_SmallPayload)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);        //app id
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(BufferedLdcPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(BufferedLdc_IntegrityCheck_BadAppID)
{
    Bytes payloadBytes;
    payloadBytes.push_back(3);        //app id (INVALID)
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_uint16_12bitRes);    //data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(BufferedLdcPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(BufferedLdc_IntegrityCheck_BadStopFlags)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);        //app id
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_uint16_12bitRes);    //data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(15));    //INVALID DELIVERY STOP FLAGS
    packet.type(WirelessPacket::packetType_BufferedLDC);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(BufferedLdcPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(BufferedLdc_IntegrityCheck_BadDataType)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(8);        //(INVALID DATA TYPE)
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(BufferedLdcPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(BufferedLdc_IntegrityCheck_BadPacketType)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_uint16_12bitRes);    //data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling); //INVALID packet type
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(BufferedLdcPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(BufferedLdc_IntegrityCheck_NoChannelsActive)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);
    payloadBytes.push_back(0);        //channel mask (NO CHANNELS)
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_uint16_12bitRes);    //data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(BufferedLdcPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(BufferedLdc_IntegrityCheck_InvalidPayloadBytes)
{
    Bytes payloadBytes;
    payloadBytes.push_back(2);
    payloadBytes.push_back(3);        //channel mask - 2 channels but not enough data for 2 channels
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(WirelessTypes::dataType_uint16_12bitRes);    //data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_BufferedLDC);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(BufferedLdcPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_SUITE_END()
