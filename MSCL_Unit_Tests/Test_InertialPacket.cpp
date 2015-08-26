/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#include "mscl/MicroStrain/Inertial/Packets/InertialPacket.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialPacket_Test)

BOOST_AUTO_TEST_CASE(InertialPacket_isDataPacket)
{
	InertialPacket p;

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
	p.descriptorSet(DescriptorSet::DESC_SET_DATA_GPS);
	BOOST_CHECK_EQUAL(p.isDataPacket(), true);

	//set the descriptor set to a data set, check that isDataPacket returns true
	p.descriptorSet(DescriptorSet::DESC_SET_DATA_EST_FILTER);
	BOOST_CHECK_EQUAL(p.isDataPacket(), true);
}

BOOST_AUTO_TEST_CASE(InertialPacket_Payload)
{
	InertialPacket p;

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