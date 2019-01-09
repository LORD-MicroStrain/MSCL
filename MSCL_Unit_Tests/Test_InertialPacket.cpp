/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialPacket_Test)

BOOST_AUTO_TEST_CASE(InertialPacket_isDataPacket)
{
    MipPacket p;

    //initially, the packet is set to an unknown descriptor set, so isn't a data packet
    BOOST_CHECK_EQUAL(p.descriptorSet(), 0);
    BOOST_CHECK_EQUAL(p.isDataPacket(), false);

    //set the descriptor set to a command set, still isn't a data packet
    p.descriptorSet(DescriptorSet::DESC_SET_CMD_3DM);
    BOOST_CHECK_EQUAL(p.isDataPacket(), false);

    //set the descriptor set to a data set, check that isDataPacket returns true
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_SENSOR);
    BOOST_CHECK_EQUAL(p.isDataPacket(), true);

    //set the descriptor set to a data set, check that isDataPacket returns true
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_GNSS);
    BOOST_CHECK_EQUAL(p.isDataPacket(), true);

    //set the descriptor set to a data set, check that isDataPacket returns true
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_EST_FILTER);
    BOOST_CHECK_EQUAL(p.isDataPacket(), true);
}

BOOST_AUTO_TEST_CASE(InertialPacket_Payload)
{
    MipPacket p;

    Bytes b;
    b.push_back(0x01);
    b.push_back(0x02);

    //set the payload of the packet
    p.payload(b);

    //check that the payload bytes are correct
    BOOST_CHECK_EQUAL(p.payload().at(0), 0x01);
    BOOST_CHECK_EQUAL(p.payload().at(1), 0x02);

    Bytes b2;
    b2.push_back(0x03);
    b2.push_back(0x04);

    //update the payload to the new bytes, which should overwrite all the bytes
    p.payload(b2);

    //check that the payload bytes are correct
    BOOST_CHECK_EQUAL(p.payload().at(0), 0x03);
    BOOST_CHECK_EQUAL(p.payload().at(1), 0x04);
}

BOOST_AUTO_TEST_SUITE_END()