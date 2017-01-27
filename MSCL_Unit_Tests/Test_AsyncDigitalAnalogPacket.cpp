/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Packets/AsyncDigitalAnalogPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(AsyncDigitalAnalog_Test)

BOOST_AUTO_TEST_CASE(AsyncDigitalAnalogPacket_Constructor_4byteFloat)
{
    Bytes payloadBytes;
    payloadBytes.push_back(1);        //channel mask - channel 1 and 9 active
    payloadBytes.push_back(1);        //channel mask
    payloadBytes.push_back(2);        //data type - float
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
    payloadBytes.push_back(0);        //timestamp offset msb
    payloadBytes.push_back(1);        //timestamp offset lsb
    payloadBytes.push_back(0);        //digital data b1 (0000 0000)
    payloadBytes.push_back(1);        //digital data b2 (0000 0001)
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2
    payloadBytes.push_back(0);        //channel data b3
    payloadBytes.push_back(0);        //channel data b4
    payloadBytes.push_back(0);        //timestamp offset msb
    payloadBytes.push_back(2);        //timestamp offset lsb
    payloadBytes.push_back(1);        //digital data b1 (0000 0001)
    payloadBytes.push_back(1);        //digital data b2 (0000 0001)
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2
    payloadBytes.push_back(0);        //channel data b3
    payloadBytes.push_back(0);        //channel data b4
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2
    payloadBytes.push_back(0);        //channel data b3
    payloadBytes.push_back(0);        //channel data b4

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigitalAnalog);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.frequency(WirelessTypes::freq_14);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //call the addDataPacket() function to parse the packet
    WirelessPacketCollector collector;
    collector.addDataPacket(packet);

    DataSweeps sweeps;
    collector.getDataSweeps(sweeps);

    BOOST_CHECK_EQUAL(sweeps.size(), 2);

    DataSweep sweep = sweeps.at(0);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 1);
    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 30517);
    BOOST_CHECK_EQUAL(sweep.sampleRate().str(), "Event");
    BOOST_CHECK_EQUAL(sweep.nodeRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.baseRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.frequency(), WirelessTypes::freq_14);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);//1 analog channel
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_float);

    sweep = sweeps.at(1);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 2);    //check that the tick incremented (by MSCL, not by the packet)
    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 61035);
    BOOST_CHECK_EQUAL(sweep.sampleRate().str(), "Event");
    BOOST_CHECK_EQUAL(sweep.nodeRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.baseRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.frequency(), WirelessTypes::freq_14);
    BOOST_CHECK_EQUAL(sweep.data().size(), 2);//2 analog channels
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(sweep.data()[1].storedAs(), valueType_float);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalAnalogPacket_Constructor_2byteUint)
{
    Bytes payloadBytes;
    payloadBytes.push_back(1);        //channel mask - channel 1 and 9 active
    payloadBytes.push_back(1);        //channel mask
    payloadBytes.push_back(3);        //data type - uint16
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
    payloadBytes.push_back(0);        //timestamp offset msb
    payloadBytes.push_back(1);        //timestamp offset lsb
    payloadBytes.push_back(0);        //digital data b1 (0000 0000)
    payloadBytes.push_back(1);        //digital data b2 (0000 0001)
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigitalAnalog);
    packet.nodeRSSI(-50);
    packet.baseRSSI(-55);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //call the addDataPacket() function to parse the packet
    WirelessPacketCollector collector;
    collector.addDataPacket(packet);

    DataSweeps sweeps;
    collector.getDataSweeps(sweeps);

    BOOST_CHECK_EQUAL(sweeps.size(), 1);

    DataSweep sweep = sweeps.at(0);
    
    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 1);
    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 30517);
    BOOST_CHECK_EQUAL(sweep.sampleRate().str(), "Event");
    BOOST_CHECK_EQUAL(sweep.nodeRssi(), -50);
    BOOST_CHECK_EQUAL(sweep.baseRssi(), -55);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);//1 analog channel
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_uint16);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalAnalogPacket_IntegrityCheck_Good)
{
    Bytes payloadBytes;
    payloadBytes.push_back(1);        //channel mask - channel 1 and 9 active
    payloadBytes.push_back(1);        //channel mask
    payloadBytes.push_back(3);        //data type - uint16
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
    payloadBytes.push_back(0);        //timestamp offset msb
    payloadBytes.push_back(1);        //timestamp offset lsb
    payloadBytes.push_back(0);        //digital data b1 (0000 0000)
    payloadBytes.push_back(1);        //digital data b2 (0000 0001)
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigitalAnalog);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalAnalogPacket::integrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalAnalogPacket_IntegrityCheck_SmallPayload)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(2);        //datatype

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigitalAnalog);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalAnalogPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalAnalogPacket_IntegrityCheck_BadStopFlags)
{
    Bytes payloadBytes;
    payloadBytes.push_back(1);        //channel mask - channel 1 and 9 active
    payloadBytes.push_back(1);        //channel mask
    payloadBytes.push_back(3);        //data type - uint16
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
    payloadBytes.push_back(0);        //timestamp offset msb
    payloadBytes.push_back(1);        //timestamp offset lsb
    payloadBytes.push_back(0);        //digital data b1 (0000 0000)
    payloadBytes.push_back(1);        //digital data b2 (0000 0001)
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(15));    //INVALID DELIVERY STOP FLAGS
    packet.type(WirelessPacket::packetType_AsyncDigitalAnalog);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalAnalogPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalPacket_IntegrityCheck_BadPacketType)
{
    Bytes payloadBytes;
    payloadBytes.push_back(1);        //channel mask - channel 1 and 9 active
    payloadBytes.push_back(1);        //channel mask
    payloadBytes.push_back(3);        //data type - uint16
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
    payloadBytes.push_back(0);        //timestamp offset msb
    payloadBytes.push_back(1);        //timestamp offset lsb
    payloadBytes.push_back(0);        //digital data b1 (0000 0000)
    payloadBytes.push_back(1);        //digital data b2 (0000 0001)
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigital); //INVALID packet type
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalAnalogPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalAnalogPacket_IntegrityCheck_NoChannelsActive)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask - channel 1 and 9 active
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(3);        //data type - uint16
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
    packet.type(WirelessPacket::packetType_AsyncDigitalAnalog);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalAnalogPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalAnalogPacket_IntegrityCheck_BadDataType)
{
    Bytes payloadBytes;
    payloadBytes.push_back(1);        //channel mask - channel 1 and 9 active
    payloadBytes.push_back(1);        //channel mask
    payloadBytes.push_back(17);        //data type - BAD
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
    payloadBytes.push_back(0);        //timestamp offset msb
    payloadBytes.push_back(1);        //timestamp offset lsb
    payloadBytes.push_back(0);        //digital data b1 (0000 0000)
    payloadBytes.push_back(1);        //digital data b2 (0000 0001)
    payloadBytes.push_back(0);        //channel data b1
    payloadBytes.push_back(0);        //channel data b2

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigitalAnalog);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalAnalogPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_SUITE_END()