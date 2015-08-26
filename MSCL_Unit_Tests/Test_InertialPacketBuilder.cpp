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
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/ByteStream.h"
#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialPacketBuilder_Test)

BOOST_AUTO_TEST_CASE(InertialPacketBuilder_Constructor)
{
	//create a field to add
	InertialDataField field(0x01);

	//create the builder
	InertialPacketBuilder builder(0x01, field);
	
	//build the packet
	ByteStream bytes = builder.buildPacket();

	BOOST_CHECK_EQUAL(bytes.read_uint8(0), 0x75);	//sync 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(1), 0x65);	//sync 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(2), 0x01);	//desc set
	BOOST_CHECK_EQUAL(bytes.read_uint8(3), 0x02);	//payload length
	BOOST_CHECK_EQUAL(bytes.read_uint8(4), 0x02);	//field length
	BOOST_CHECK_EQUAL(bytes.read_uint8(5), 0x01);	//field desc
	BOOST_CHECK_EQUAL(bytes.read_uint8(6), 0xE0);	//checksum MSB
	BOOST_CHECK_EQUAL(bytes.read_uint8(7), 0xC6);	//checksum LSB
}

BOOST_AUTO_TEST_CASE(InertialPacketBuilder_WithFieldData)
{
	//add the field data bytes
	Bytes data;
	data.push_back(0x00);
	data.push_back(0x00);

	//create a field to add
	InertialDataField field(0x01, data);

	//create the builder
	InertialPacketBuilder builder(0x0C, field);
	
	//build the packet
	ByteStream bytes = builder.buildPacket();

	BOOST_CHECK_EQUAL(bytes.read_uint8(0), 0x75);	//sync 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(1), 0x65);	//sync 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(2), 0x0C);	//desc set
	BOOST_CHECK_EQUAL(bytes.read_uint8(3), 0x04);	//payload length
	BOOST_CHECK_EQUAL(bytes.read_uint8(4), 0x04);	//field length
	BOOST_CHECK_EQUAL(bytes.read_uint8(5), 0x01);	//field desc
	BOOST_CHECK_EQUAL(bytes.read_uint8(6), 0x00);	//field data 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(7), 0x00);	//field data 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(8), 0xEF);	//checksum MSB
	BOOST_CHECK_EQUAL(bytes.read_uint8(9), 0xDA);	//checksum LSB
}

BOOST_AUTO_TEST_CASE(InertialPacketBuilder_MultipleFields)
{
	//add the field data bytes
	Bytes data;
	data.push_back(0x00);
	data.push_back(0x02);
	data.push_back(0x03);
	data.push_back(0x00);
	data.push_back(0x0A);
	data.push_back(0x04);
	data.push_back(0x00);
	data.push_back(0x0A);

	//create a field to add
	InertialDataField field1(0x08, data);

	//create the builder
	InertialPacketBuilder builder(0x0C, field1);

	Bytes data2;
	data2.push_back(0x00);
	data2.push_back(0x02);
	data2.push_back(0x04);
	data2.push_back(0x00);
	data2.push_back(0x04);
	data2.push_back(0x06);
	data2.push_back(0x00);
	data2.push_back(0x04);

	//create another field to add
	InertialDataField field2(0x09, data2);

	builder.addField(field2);

	
	//build the packet
	ByteStream bytes = builder.buildPacket();

	BOOST_CHECK_EQUAL(bytes.read_uint8(0), 0x75);	//sync 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(1), 0x65);	//sync 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(2), 0x0C);	//desc set
	BOOST_CHECK_EQUAL(bytes.read_uint8(3), 0x14);	//payload length
	BOOST_CHECK_EQUAL(bytes.read_uint8(4), 0x0A);	//field length
	BOOST_CHECK_EQUAL(bytes.read_uint8(5), 0x08);	//field desc
	BOOST_CHECK_EQUAL(bytes.read_uint8(6), 0x00);	//field data 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(7), 0x02);	//field data 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(8), 0x03);	//field data 3
	BOOST_CHECK_EQUAL(bytes.read_uint8(9), 0x00);	//field data 4
	BOOST_CHECK_EQUAL(bytes.read_uint8(10), 0x0A);	//field data 5
	BOOST_CHECK_EQUAL(bytes.read_uint8(11), 0x04);	//field data 6
	BOOST_CHECK_EQUAL(bytes.read_uint8(12), 0x00);	//field data 7
	BOOST_CHECK_EQUAL(bytes.read_uint8(13), 0x0A);	//field data 8
	BOOST_CHECK_EQUAL(bytes.read_uint8(14), 0x0A);	//field length
	BOOST_CHECK_EQUAL(bytes.read_uint8(15), 0x09);	//field desc
	BOOST_CHECK_EQUAL(bytes.read_uint8(16), 0x00);	//field data 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(17), 0x02);	//field data 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(18), 0x04);	//field data 3
	BOOST_CHECK_EQUAL(bytes.read_uint8(19), 0x00);	//field data 4
	BOOST_CHECK_EQUAL(bytes.read_uint8(20), 0x04);	//field data 5
	BOOST_CHECK_EQUAL(bytes.read_uint8(21), 0x06);	//field data 6
	BOOST_CHECK_EQUAL(bytes.read_uint8(22), 0x00);	//field data 7
	BOOST_CHECK_EQUAL(bytes.read_uint8(23), 0x04);	//field data 8
	BOOST_CHECK_EQUAL(bytes.read_uint8(24), 0x50);	//checksum MSB
	BOOST_CHECK_EQUAL(bytes.read_uint8(25), 0x98);	//checksum LSB
}

BOOST_AUTO_TEST_CASE(InertialPacketBuilder_InertialFieldCopyConstructor)
{
	//add the field data bytes
	Bytes data;
	data.push_back(0x00);
	data.push_back(0x00);

	//create a field to add
	InertialDataField field(0x01, data);

	//create another field with the copy constructor
	InertialDataField field2(field);

	//create the builder
	InertialPacketBuilder builder(0x0C, field2);
	
	//build the packet
	ByteStream bytes = builder.buildPacket();

	BOOST_CHECK_EQUAL(bytes.read_uint8(0), 0x75);	//sync 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(1), 0x65);	//sync 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(2), 0x0C);	//desc set
	BOOST_CHECK_EQUAL(bytes.read_uint8(3), 0x04);	//payload length
	BOOST_CHECK_EQUAL(bytes.read_uint8(4), 0x04);	//field length
	BOOST_CHECK_EQUAL(bytes.read_uint8(5), 0x01);	//field desc
	BOOST_CHECK_EQUAL(bytes.read_uint8(6), 0x00);	//field data 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(7), 0x00);	//field data 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(8), 0xEF);	//checksum MSB
	BOOST_CHECK_EQUAL(bytes.read_uint8(9), 0xDA);	//checksum LSB
}

BOOST_AUTO_TEST_CASE(InertialPacketBuilder_InertialFieldAssignmentOperator)
{
	//add the field data bytes
	Bytes data;
	data.push_back(0x00);
	data.push_back(0x00);

	//create a field to add
	InertialDataField field(0x01, data);

	//create another field with the assignment operator
	InertialDataField field2 = field;

	//create the builder
	InertialPacketBuilder builder(0x0C, field2);
	
	//build the packet
	ByteStream bytes = builder.buildPacket();

	BOOST_CHECK_EQUAL(bytes.read_uint8(0), 0x75);	//sync 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(1), 0x65);	//sync 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(2), 0x0C);	//desc set
	BOOST_CHECK_EQUAL(bytes.read_uint8(3), 0x04);	//payload length
	BOOST_CHECK_EQUAL(bytes.read_uint8(4), 0x04);	//field length
	BOOST_CHECK_EQUAL(bytes.read_uint8(5), 0x01);	//field desc
	BOOST_CHECK_EQUAL(bytes.read_uint8(6), 0x00);	//field data 1
	BOOST_CHECK_EQUAL(bytes.read_uint8(7), 0x00);	//field data 2
	BOOST_CHECK_EQUAL(bytes.read_uint8(8), 0xEF);	//checksum MSB
	BOOST_CHECK_EQUAL(bytes.read_uint8(9), 0xDA);	//checksum LSB
}

BOOST_AUTO_TEST_SUITE_END()