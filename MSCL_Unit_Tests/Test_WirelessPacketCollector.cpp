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
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(WirelessPacketCollector_Test)

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_AddDataPacket_SyncSampling)
{
	//a valid buffered ldc packet payload
	Bytes payload;
	payload.push_back(0x02);		//first byte in payload of 0x02 signifies Sync Sampling packet type
	payload.push_back(0x01);		//channel mask
	payload.push_back(0x70);
	payload.push_back(0x03);		//data type
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);

	WirelessPacket packet;
	packet.type(WirelessPacket::packetType_SyncSampling);
	packet.nodeAddress(567);
	packet.payload(payload);

	WirelessPacketCollector collector;
	collector.addDataPacket(packet);

	DataSweep sweep;
	collector.getNextDataSweep(sweep, 1);

	//check that the sweep contains the data we setup
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 567);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_GetNextDataSweep_AddDataPacket_LDC)
{
	//a valid LDC packet payload
	Bytes data;
	data.push_back(0x02);		//first byte in payload of 0x02 signifies Sync Sampling packet type
	data.push_back(0x01);		//channel mask
	data.push_back(0x70);		//sample rate
	data.push_back(0x03);		//data type
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);

	WirelessPacket packet;
	packet.type(WirelessPacket::packetType_LDC);
	packet.nodeAddress(678);
	packet.payload(data);

	WirelessPacketCollector collector;
	collector.addDataPacket(packet);

	DataSweep sweep;
	collector.getNextDataSweep(sweep, 1);

	//check that the sweep contains the data we setup
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 678);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_AddDataPacket_BufferedLdc)
{
	//a valid buffered ldc packet payload
	Bytes payload;
	payload.push_back(0x02);		//App Id
	payload.push_back(0x01);		//channel mask
	payload.push_back(0x70);
	payload.push_back(0x03);		//data type
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);

	WirelessPacket packet;
	packet.type(WirelessPacket::packetType_BufferedLDC);
	packet.nodeAddress(567);
	packet.payload(payload);

	WirelessPacketCollector collector;
	collector.addDataPacket(packet);

	DataSweep sweep;
	collector.getNextDataSweep(sweep, 1);

	//check that the sweep contains the data we setup
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 567);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_GetNextDataPacket_Timeout)
{
	WirelessPacketCollector collector;

	DataSweep sweep;
	//we don't have any data, so make sure calling getNextDataSweep with a timeout of 1 millisecond throws an exception
	BOOST_CHECK_THROW(collector.getNextDataSweep(sweep, 1), Error_NoData);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_GetNextDataSweep_MulitipleSweeps)
{
	//a valid sync sampling packet payload with 2 sweeps
	Bytes payload;
	payload.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	payload.push_back(0x01);		//channel mask
	payload.push_back(0x70);
	payload.push_back(0x03);		//data type
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);		//sweep 1
	payload.push_back(0x00);		//sweep 1
	payload.push_back(0x01);		//sweep 2
	payload.push_back(0x01);		//sweep 2

	WirelessPacket packet;
	packet.type(WirelessPacket::packetType_SyncSampling);
	packet.nodeAddress(234);
	packet.payload(payload);

	WirelessPacketCollector collector;
	collector.addDataPacket(packet);

	DataSweep sweep;
	collector.getNextDataSweep(sweep, 0);

	//check that the sweep contains the data we setup
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 234);

	//we should have multiple sweeps in this same packet, so this should be ok
	DataSweep sweep2;
	collector.getNextDataSweep(sweep2, 0);

	//check that the sweep contains the data we setup
	BOOST_CHECK_EQUAL(sweep2.nodeAddress(), 234);
}


BOOST_AUTO_TEST_CASE(WirelessPacketCollector_GetNextDataSweep_MulitiplePackets)
{
	//a valid LDC packet payload
	Bytes data;
	data.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	data.push_back(0x01);		//channel mask
	data.push_back(0x70);		//sample rate
	data.push_back(0x03);		//data type
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);

	WirelessPacket packet;
	packet.type(WirelessPacket::packetType_LDC);
	packet.nodeAddress(678);
	packet.payload(data);

	WirelessPacket packet2;
	packet2.type(WirelessPacket::packetType_LDC);
	packet2.nodeAddress(154);
	packet2.payload(data);

	WirelessPacketCollector collector;
	collector.addDataPacket(packet);
	collector.addDataPacket(packet2);

	DataSweep sweep;
	collector.getNextDataSweep(sweep, 0);

	//check that the sweep contains the data we setup
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 678);

	DataSweep sweep2;
	collector.getNextDataSweep(sweep2, 0);

	//check that the sweep contains the data we setup
	BOOST_CHECK_EQUAL(sweep2.nodeAddress(), 154);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_GetDataSweeps_NoData)
{
	WirelessPacketCollector collector;

	//verify that the total sweeps is 0
	BOOST_CHECK_EQUAL(collector.totalSweeps(), 0);

	//verify that calling getDataSweeps with no max gives an empty vector back
	std::vector<mscl::DataSweep> sweeps;
	collector.getDataSweeps(sweeps);
	BOOST_CHECK_EQUAL(sweeps.size(), 0);

	//verify that calling getDataSweeps with a max gives an empty vector back
	collector.getDataSweeps(sweeps, 0, 100);
	BOOST_CHECK_EQUAL(sweeps.size(), 0);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_GetDataSweeps_MultiplePackets_All)
{
	//a valid LDC packet payload
	Bytes data;
	data.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	data.push_back(0x01);		//channel mask
	data.push_back(0x70);		//sample rate
	data.push_back(0x03);		//data type
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);

	WirelessPacket packet;
	packet.type(WirelessPacket::packetType_LDC);
	packet.nodeAddress(678);
	packet.payload(data);

	WirelessPacket packet2;
	packet2.type(WirelessPacket::packetType_LDC);
	packet2.nodeAddress(154);
	packet2.payload(data);

	WirelessPacketCollector collector;
	collector.addDataPacket(packet);
	collector.addDataPacket(packet2);

	//check that the number of sweeps is 2 (1 in each packet)
	BOOST_CHECK_EQUAL(collector.totalSweeps(), 2);

	//check that calling getDataSweeps returns 2 sweeps
	std::vector<DataSweep> sweeps;
	collector.getDataSweeps(sweeps);
	BOOST_CHECK_EQUAL(sweeps.size(), 2);

	//check that there are no more sweeps to get
	BOOST_CHECK_EQUAL(collector.totalSweeps(), 0);
	sweeps.clear();
	collector.getDataSweeps(sweeps);
	BOOST_CHECK_EQUAL(sweeps.size(), 0);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_GetDataSweeps_MultiplePackets_Limited)
{
	//a valid LDC packet payload
	Bytes data;
	data.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	data.push_back(0x01);		//channel mask
	data.push_back(0x70);		//sample rate
	data.push_back(0x03);		//data type
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);
	data.push_back(0x00);

	WirelessPacket packet;
	packet.type(WirelessPacket::packetType_LDC);
	packet.nodeAddress(678);
	packet.payload(data);

	WirelessPacket packet2;
	packet2.type(WirelessPacket::packetType_LDC);
	packet2.nodeAddress(154);
	packet2.payload(data);

	WirelessPacketCollector collector;
	collector.addDataPacket(packet);
	collector.addDataPacket(packet2);

	//check that the number of sweeps is 2 (1 in each packet)
	BOOST_CHECK_EQUAL(collector.totalSweeps(), 2);

	//check that calling getDataSweeps with a max of 1 returns 1 sweep
	std::vector<DataSweep> sweeps;
	collector.getDataSweeps(sweeps, 0, 1);
	BOOST_CHECK_EQUAL(sweeps.size(), 1);
	BOOST_CHECK_EQUAL(sweeps.at(0).nodeAddress(), 678);

	//check that calling it again, gives us the next sweep
	sweeps.clear();
	collector.getDataSweeps(sweeps, 0, 1);
	BOOST_CHECK_EQUAL(sweeps.size(), 1);
	BOOST_CHECK_EQUAL(sweeps.at(0).nodeAddress(), 154);

	//check that there are no more sweeps to get
	BOOST_CHECK_EQUAL(collector.totalSweeps(), 0);
	sweeps.clear();
	collector.getDataSweeps(sweeps);
	BOOST_CHECK_EQUAL(sweeps.size(), 0);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_GetDataSweeps_MultipleSweeps)
{
	//a valid sync sampling packet payload with 2 sweeps
	Bytes payload;
	payload.push_back(0x02);		//first byte in payload of 0x02 signifies sync sampling packet type
	payload.push_back(0x01);		//channel mask
	payload.push_back(0x70);
	payload.push_back(0x03);		//data type
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);
	payload.push_back(0x00);		//sweep 1
	payload.push_back(0x00);		//sweep 1
	payload.push_back(0x01);		//sweep 2
	payload.push_back(0x01);		//sweep 2

	WirelessPacket packet;
	packet.type(WirelessPacket::packetType_SyncSampling);
	packet.nodeAddress(234);
	packet.payload(payload);

	WirelessPacketCollector collector;
	collector.addDataPacket(packet);

	//check that the number of sweeps is 2 (1 in each packet)
	BOOST_CHECK_EQUAL(collector.totalSweeps(), 2);

	//check that calling getDataSweeps returns 2 sweeps
	std::vector<DataSweep> sweeps;
	collector.getDataSweeps(sweeps);
	BOOST_CHECK_EQUAL(sweeps.size(), 2);

	//check that there are no more sweeps to get
	BOOST_CHECK_EQUAL(collector.totalSweeps(), 0);
	sweeps.clear();
	collector.getDataSweeps(sweeps);
	BOOST_CHECK_EQUAL(sweeps.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()