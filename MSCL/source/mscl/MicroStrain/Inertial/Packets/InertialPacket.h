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
//PUBLIC_HEADER
#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
	//API Class: InertialPacket
	//	A class that contains packet information about an Inertial packet
	class InertialPacket
	{
	public:
		//=====================================================================================================
		//API Enums: Response State
		//	MIP_ACK_NACK_ERROR_NONE						- 0	- No Error
		//	MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND			- 1	- Error: Unknown command was sent to the device
		//	MIP_ACK_NACK_ERROR_CHECKSUM_INVALID			- 2	- Error: Invalid checksum was recieved by the device
		//	MIP_ACK_NACK_ERROR_PARAMETER_INVALID		- 3	- Error: Invalid parameter was received by the device
		//	MIP_ACK_NACK_ERROR_COMMAND_FAILED			- 4	- Error: The command has failed
		//	MIP_ACK_NACK_ERROR_COMMAND_TIMEOUT			- 5	- Error: The command has timed out
		//	MIP_ACK_NACK_ERROR_UNKNOWN_DESCRIPTOR_SET	- 6	- Error: Unknown descriptor set was recieved by the device
		//=====================================================================================================
		enum MipAckNack
		{
			MIP_ACK_NACK_ERROR_NONE = 0,

			MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND = 1,
			MIP_ACK_NACK_ERROR_CHECKSUM_INVALID = 2,
			MIP_ACK_NACK_ERROR_PARAMETER_INVALID = 3,
			MIP_ACK_NACK_ERROR_COMMAND_FAILED = 4,
			MIP_ACK_NACK_ERROR_COMMAND_TIMEOUT = 5,
			MIP_ACK_NACK_ERROR_UNKNOWN_DESCRIPTOR_SET = 6
		};

	public:
		//Default Constructor: InertialPacket
		//	The default constructor for an InertialPacket object
		InertialPacket();

#ifndef SWIG
	public:
		//Typedef: Payload
		//	typedef for the bytes that make up a payload in a packet
		typedef ByteStream Payload;

	protected:
		//Variable: m_descriptorSet
		//	The descriptor set (packet type) of the InertialPacket
		uint8 m_descriptorSet;

		//Variable: m_payload
		//	The payload bytes in the packet
		Payload m_payload;

	public:
		//Function: payload
		//	Sets the payload bytes of the packet
		//
		//Parameters:
		//	bytes - The payload of the packet, as a vector of bytes
		void payload(const Bytes& bytes);

		//Function: type
		//	Sets the descriptor set of the InertialPacket
		//
		//Parameters:
		//	set - The descriptor set value to set
		void descriptorSet(uint8 set);
#endif
		//API Function: isDataPacket
		//	Gets whether or not the packet is a data packet
		//
		//Returns:
		//	true if the packet is a data packet, false otherwise
		bool isDataPacket() const;

		//API Function: descriptorSet
		//	Gets the descriptor set of the InertialPacket
		//
		//Returns:
		//	The descriptor set value of the packet
		uint8 descriptorSet() const;

		//API Function: payload
		//	Gets the payload bytes of the packet
		//
		//Returns:
		//	The payload of the packet, as a vector of bytes
		const std::vector<uint8> payload() const;
	};

#ifndef SWIG
	//Struct: InertialPacketInfo
	//	Contains constants representing information on Inertial MIP Packets
	struct InertialPacketInfo
	{
		//=====================================================================================================
		//Enums: Inertial Packet Bytes
		//	INERTIAL_PACKET_START_OF_PACKET	- 0x7565	- The full start of packet value of any inertial packet
		//	INERTIAL_PACKET_SOP1			- 0x75		- The first (start of packet) byte of any inertial packet
		//	INERTIAL_PACKET_SOP2			- 0x65		- The second (start of packet) byte of any inertial packet
		//	COMMAND_SET_BASE				- 0x01		- The Base command set is common to many MicroStrain devices.  With the Base command set it is possible to
		//												  identify many properties and do basic functions on a device even if you do not recognize its specialized 
		//												  functionality or data.  The commands work the same way on all devices that implement this set.
		//	COMMAND_SET_3DM					- 0x0C		- The 3DM command set is common to the MicroStrain Inertial sensors that support the MIP packet protocol.  
		//												  Because of the unified set of commands, it is easy to migrate code from one inertial sensor to another.
		//	COMMAND_SET_NAV_FILTER			- 0x0D		- The Navigation Filter command set is specific to MicroStrain Inertial Navigation sensors.
		//	COMMAND_SET_SYSTEM				- 0x7F		- The System Command set provides a set of advanced commands that are specific to devices such as the 3DMGX3-35
		//												  that have multiple intelligent internal sensor blocks.  These commands allow special mode such as talking
		//												  directly to the native protocols of the embedded sensor blocks.  For example, with the 3DM-GX3-35, you 
		//												  may switch into a mode that talks directly to the internal u-blox chip or directly to the embedded 3DM-GX3-25 
		//												  AHRS.  This allows you to use code or utilities written specifically for the native u-blox protocols (NMEA or UBX) 
		//												  and 3DM-GX3-25 protocols (original single byte commands or ASPP packet protocol).
		//=====================================================================================================
		enum
		{
			INERTIAL_PACKET_START_OF_PACKET = 0x7565,
			INERTIAL_PACKET_SOP1			= 0x75,
			INERTIAL_PACKET_SOP2			= 0x65,
			COMMAND_SET_BASE				= 0x01,
			COMMAND_SET_3DM					= 0x0C,
			COMMAND_SET_NAV_FILTER			= 0x0D,
			COMMAND_SET_SYSTEM				= 0x7F
		};

		//=====================================================================================================
		//Enums: Inertial Packet Information
		//  MIP_MIN_PACKET_SIZE				- 8		- The minimum number of bytes to make a valid MIP packet (0x75, 0x65, Descriptor Set, Payload Len, Payload, Checksum)
		//	MIP_NUM_BYTES_BEFORE_PAYLOAD	- 4		- The number of bytes in the MIP packets before the payload
		//	MIP_NUM_BYTES_AFTER_PAYLOAD		- 2		- The number of bytes in the MIP packets after the payload
		//=====================================================================================================
		enum
		{
			MIP_MIN_PACKET_SIZE				= 8,
			MIP_NUM_BYTES_BEFORE_PAYLOAD	= 4,
			MIP_NUM_BYTES_AFTER_PAYLOAD		= 2
		};
	};

	//Struct: DescriptorSet
	//	Contains enums representing Descriptor sets for Inertial Packets
	struct DescriptorSet
	{
	public:
		//=====================================================================================================
		//Enums: Inertial Packet Descriptor Sets
		//	DESC_SET_CMD_BASE			- 0x01	- Command Packet, Base Set
		//	DESC_SET_CMD_3DM			- 0x0C	- Command Packet, 3DM Set
		//	DESC_SET_CMD_NAV			- 0x0D	- Command Packet, Navigation Filter Set
		//	DESC_SET_CMD_SYS			- 0x7F	- Command Packet, System Set
		//	DESC_SET_DATA_SENSOR		- 0x80	- Data Packet, Sensor Set
		//	DESC_SET_DATA_GPS			- 0x81	- Data Packet, GPS Set
		//	DESC_SET_DATA_EST_FILTER	- 0x82	- Data Packet, Estimation Filter Set
		//=====================================================================================================
		enum
		{
			DESC_SET_CMD_BASE			= InertialPacketInfo::COMMAND_SET_BASE,
			DESC_SET_CMD_3DM			= InertialPacketInfo::COMMAND_SET_3DM,
			DESC_SET_CMD_NAV			= InertialPacketInfo::COMMAND_SET_NAV_FILTER,
			DESC_SET_CMD_SYS			= InertialPacketInfo::COMMAND_SET_SYSTEM,
			DESC_SET_DATA_SENSOR		= 0x80,
			DESC_SET_DATA_GPS			= 0x81,
			DESC_SET_DATA_EST_FILTER	= 0x82
		};
	};
#endif
}