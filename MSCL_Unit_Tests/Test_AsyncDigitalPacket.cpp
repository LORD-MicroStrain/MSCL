/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Packets/AsyncDigitalPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(AsyncDigital_Test)

BOOST_AUTO_TEST_CASE(AsyncDigitalPacket_Constructor)
{
    Bytes payloadBytes;
    payloadBytes.push_back(1);        //channel mask - channel 1 and 9 active
    payloadBytes.push_back(1);        //channel mask
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
    payloadBytes.push_back(0);        //channel data msb
    payloadBytes.push_back(5);        //channel data lsb
    payloadBytes.push_back(0);        //timestamp offset msb
    payloadBytes.push_back(2);        //timestamp offset lsb
    payloadBytes.push_back(0);        //channel data msb
    payloadBytes.push_back(12);        //channel data lsb

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigital);
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
    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 30517);
    BOOST_CHECK_EQUAL(sweep.sampleRate().str(), "Event");
    BOOST_CHECK_EQUAL(sweep.nodeRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.baseRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.data().size(), 2);//2 digital channels
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_bool);

    sweep = sweeps.at(1);

    //check that the sweep data matches the packet we added
    BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
    BOOST_CHECK_EQUAL(sweep.tick(), 2);    //check that the tick incremented (by MSCL, not by the packet)
    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 61035);
    BOOST_CHECK_EQUAL(sweep.sampleRate().str(), "Event");
    BOOST_CHECK_EQUAL(sweep.nodeRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.baseRssi(), 1);
    BOOST_CHECK_EQUAL(sweep.data().size(), 2);//2 digital channels
    BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_bool);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalPacket_IntegrityCheck_Good)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask - channel 1 active
    payloadBytes.push_back(1);        //channel mask
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
    payloadBytes.push_back(0);        //channel data msb
    payloadBytes.push_back(5);        //channel data lsb

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigital);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalPacket::integrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalPacket_IntegrityCheck_SmallPayload)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask
    payloadBytes.push_back(1);        //channel mask - 1 channel
    payloadBytes.push_back(0);        //tick

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigital);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalPacket_IntegrityCheck_BadStopFlags)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask - channel 1 active
    payloadBytes.push_back(1);        //channel mask
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
    payloadBytes.push_back(0);        //channel data msb
    payloadBytes.push_back(5);        //channel data lsb

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(15));    //INVALID DELIVERY STOP FLAGS
    packet.type(WirelessPacket::packetType_AsyncDigital);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalPacket_IntegrityCheck_BadPacketType)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask - channel 1 active
    payloadBytes.push_back(1);        //channel mask
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
    payloadBytes.push_back(0);        //channel data msb
    payloadBytes.push_back(5);        //channel data lsb

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_LDC); //INVALID packet type
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(AsyncDigitalPacket_IntegrityCheck_InvalidPayloadBytes)
{
    Bytes payloadBytes;
    payloadBytes.push_back(0);        //channel mask - channel 1 active
    payloadBytes.push_back(1);        //channel mask
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
    payloadBytes.push_back(0);        //channel data msb
    payloadBytes.push_back(5);        //channel data lsb
    payloadBytes.push_back(1);        //EXTRA RANDOM BYTE

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(345);
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0));
    packet.type(WirelessPacket::packetType_AsyncDigital);
    packet.nodeRSSI(1);
    packet.baseRSSI(1);
    packet.payload(payloadBytes);    //give the packet the payload bytes we created

    //check that the integrity check failed
    BOOST_CHECK_EQUAL(AsyncDigitalPacket::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_SUITE_END()