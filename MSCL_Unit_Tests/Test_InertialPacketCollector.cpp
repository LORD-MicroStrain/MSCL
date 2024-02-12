/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Packets/MipPacketCollector.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialPacketCollector_Test)

BOOST_AUTO_TEST_CASE(InertialPacketCollector_getDataPackets_noData)
{
    MipPacketCollector collector;

    //check that totalPackets is 0
    BOOST_CHECK_EQUAL(collector.totalPackets(), 0);

    //check that the size of the packets is 0
    std::vector<MipDataPacket> packets;
    collector.getDataPackets(packets);
    BOOST_CHECK_EQUAL(packets.size(), 0);
}

BOOST_AUTO_TEST_CASE(InertialPacketCollector_getDataPackets_multiplePackets_all)
{
    MipPacketCollector collector;

    MipPacket p;
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_GNSS);

    MipPacket p2;
    p2.descriptorSet(DescriptorSet::DESC_SET_DATA_EST_FILTER);

    //add the packets to the collector
    collector.addDataPacket(p);
    collector.addDataPacket(p2);

    //check that the number of packets is 2
    BOOST_CHECK_EQUAL(collector.totalPackets(), 2);

    //check that calling getDataPackets returns 2 packets
    std::vector<MipDataPacket> packets;
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
    MipPacketCollector collector;

    MipPacket p;
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_GNSS);

    MipPacket p2;
    p2.descriptorSet(DescriptorSet::DESC_SET_DATA_EST_FILTER);

    //add the packets to the collector
    collector.addDataPacket(p);
    collector.addDataPacket(p2);

    //check that the number of packets is 2
    BOOST_CHECK_EQUAL(collector.totalPackets(), 2);

    //check that calling getDataPackets returns 1 packet
    std::vector<MipDataPacket> packets;
    collector.getDataPackets(packets, 0, 1);
    BOOST_CHECK_EQUAL(packets.size(), 1);
    BOOST_CHECK_EQUAL(packets.at(0).descriptorSet(), DescriptorSet::DESC_SET_DATA_GNSS);

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