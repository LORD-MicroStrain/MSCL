/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketCollector.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacket.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialPacketCollector_Test)

BOOST_AUTO_TEST_CASE(InertialPacketCollector_getNextDataPacket_success)
{
    InertialPacketCollector collector;

    InertialPacket p;
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_GPS);

    //add the packet to the collector
    collector.addDataPacket(p);

    //call getNextDataPacket on the collector
    InertialDataPacket result;
    collector.getNextDataPacket(result, 1);

    //check that we got a valid packet
    BOOST_CHECK_EQUAL(result.isDataPacket(), true);
    BOOST_CHECK_EQUAL(result.descriptorSet(), DescriptorSet::DESC_SET_DATA_GPS);

    //check that calling getNextDataPacket again throws an exception
    BOOST_CHECK_THROW(collector.getNextDataPacket(result, 1), Error_NoData);
}

BOOST_AUTO_TEST_CASE(InertialPacketCollector_getNextDataPacket_noData)
{
    InertialPacketCollector collector;

    InertialDataPacket packet;

    //check that calling getNextDataPacket throws an exception
    BOOST_CHECK_THROW(collector.getNextDataPacket(packet, 1), Error_NoData);
}

BOOST_AUTO_TEST_CASE(InertialPacketCollector_getDataPackets_noData)
{
    InertialPacketCollector collector;

    //check that totalPackets is 0
    BOOST_CHECK_EQUAL(collector.totalPackets(), 0);

    //check that the size of the packets is 0
    std::vector<InertialDataPacket> packets;
    collector.getDataPackets(packets);
    BOOST_CHECK_EQUAL(packets.size(), 0);
}

BOOST_AUTO_TEST_CASE(InertialPacketCollector_getDataPackets_multiplePackets_all)
{
    InertialPacketCollector collector;

    InertialPacket p;
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_GPS);

    InertialPacket p2;
    p2.descriptorSet(DescriptorSet::DESC_SET_DATA_EST_FILTER);

    //add the packets to the collector
    collector.addDataPacket(p);
    collector.addDataPacket(p2);

    //check that the number of packets is 2
    BOOST_CHECK_EQUAL(collector.totalPackets(), 2);

    //check that calling getDataPackets returns 2 packets
    std::vector<InertialDataPacket> packets;
    collector.getDataPackets(packets);
    BOOST_CHECK_EQUAL(packets.size(), 2);

    //check that there are no more packets to get
    BOOST_CHECK_EQUAL(collector.totalPackets(), 0);
    packets.clear();
    collector.getDataPackets(packets);
    BOOST_CHECK_EQUAL(packets.size(), 0);
}

BOOST_AUTO_TEST_CASE(InertialPacketCollector_getDataPackets_multiplePackets_limited)
{
    InertialPacketCollector collector;

    InertialPacket p;
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_GPS);

    InertialPacket p2;
    p2.descriptorSet(DescriptorSet::DESC_SET_DATA_EST_FILTER);

    //add the packets to the collector
    collector.addDataPacket(p);
    collector.addDataPacket(p2);

    //check that the number of packets is 2
    BOOST_CHECK_EQUAL(collector.totalPackets(), 2);

    //check that calling getDataPackets returns 1 packet
    std::vector<InertialDataPacket> packets;
    collector.getDataPackets(packets, 0, 1);
    BOOST_CHECK_EQUAL(packets.size(), 1);
    BOOST_CHECK_EQUAL(packets.at(0).descriptorSet(), DescriptorSet::DESC_SET_DATA_GPS);

    //check that calling getDataPackets returns 1 packet
    packets.clear();
    collector.getDataPackets(packets, 0, 1);
    BOOST_CHECK_EQUAL(packets.size(), 1);
    BOOST_CHECK_EQUAL(packets.at(0).descriptorSet(), DescriptorSet::DESC_SET_DATA_EST_FILTER);

    //check that there are no more packets to get
    BOOST_CHECK_EQUAL(collector.totalPackets(), 0);
    packets.clear();
    collector.getDataPackets(packets, 1);
    BOOST_CHECK_EQUAL(packets.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()