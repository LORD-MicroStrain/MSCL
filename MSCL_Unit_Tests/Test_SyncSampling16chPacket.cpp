/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Packets/SyncSamplingPacket_v2.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(Sync16chPacket_Test)

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_4ByteFloat)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x12);    //sample mode / data type - 4 byte float
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
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
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
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
    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 0);
    BOOST_CHECK_EQUAL(sweep.sampleRate().prettyStr(), "2Hz");
    BOOST_CHECK_EQUAL(sweep.nodeRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.baseRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_float);

    sweep = sweeps.at(1);
    
    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 2);    //check that the tick incremented (by MSCL, not by the packet)
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(sweep.samplingType(), DataSweep::samplingType_SyncSampling_Burst);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_2ByteUint)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //sample mode / data type - 2 byte uint
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(254);    //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
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
    BOOST_CHECK_EQUAL(sweep.samplingType(), DataSweep::samplingType_SyncSampling);
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(sweep.data()[0].as_uint16(), 254);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_uint24)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x29);    //sample mode / data type - 2 byte uint
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0xFD);   //channel data b1
    payloadBytes.push_back(0xDF);   //channel data b2
    payloadBytes.push_back(0x5E);   //channel data b3

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
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
    BOOST_CHECK_EQUAL(sweep.samplingType(), DataSweep::samplingType_SyncSampling);
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_uint32);
    BOOST_CHECK_EQUAL(sweep.data()[0].as_uint32(), 16637790);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_uint16_18bitTrun)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x2A);    //sample mode / data type - 2 byte uint
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);
    payloadBytes.push_back(0xB7);   //channel data b1
    payloadBytes.push_back(0xFF);   //channel data b2

    //188413 (sampled) -> 47103 (truncated sent) -> 188412 (changed back by software)

                                    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
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
    BOOST_CHECK_EQUAL(sweep.samplingType(), DataSweep::samplingType_SyncSampling);
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_uint32);
    BOOST_CHECK_EQUAL(sweep.data()[0].as_uint32(), 188412);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_2ByteUintShifted)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x21);    //data type - 2 byte uint shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(254);    //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
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

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_NoChannelMask)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(0);        //channel mask - NO CHANNELS
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //sample mode / data type - 2 byte uint
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
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
    BOOST_CHECK_EQUAL(sweep.samplingType(), DataSweep::samplingType_SyncSampling);
    BOOST_CHECK_EQUAL(sweep.data().size(), 0);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_Valid)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x22);    //app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(SyncSamplingPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_SmallPayload)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(SyncSamplingPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_BadAppID)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x32);    //BAD app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(SyncSamplingPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_BadStopFlags)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //app id / data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(15));    //INVALID DELIVERY STOP FLAGS
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(SyncSamplingPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_BadDataType)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x28);    //(INVALID DATA TYPE)
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(SyncSamplingPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_BadPacketType)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC); //INVALID packet type
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(SyncSamplingPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_NoChannelsActive)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);
    payloadBytes.push_back(0);        //channel mask (NO CHANNELS)
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(SyncSamplingPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_InvalidPayloadBytes)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);
    payloadBytes.push_back(3);        //channel mask - 2 channels but not enough data for 2 channels
    payloadBytes.push_back(112);    //sample rate
    payloadBytes.push_back(0x23);    //data type - 2 byte uint32 shifted
    payloadBytes.push_back(0);        //tick msb
    payloadBytes.push_back(1);        //tick lsb
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_SyncSampling_16ch);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(SyncSamplingPacket_v2::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_SUITE_END()