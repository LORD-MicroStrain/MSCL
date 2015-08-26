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
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

	//Class: HclSmartBearing_RawPacket
	//	A <WirelessDataPacket> derived class representing a HclSmartBearing Raw data packet.
	class HclSmartBearing_RawPacket: public WirelessDataPacket
	{
	private:
		//=====================================================================================================
		//Constants: HclSmartBearing_RawPacket Information
		//	PAYLOAD_OFFSET_APP_ID			- 0		- The offset into the payload to get the application ID
		//	PAYLOAD_OFFSET_ERROR_MASK		- 1		- The offset into the payload to get the sensor board error mask.
		//	PAYLOAD_OFFSET_SAMPLE_RATE		- 2		- The offset into the payload to get the sample rate
		//	PAYLOAD_OFFSET_TICK				- 3		- The offset into the payload to get the tick (2 bytes)
		//	PAYLOAD_OFFSET_TS_SEC			- 5		- The offset into the payload to get the timestamp seconds (4 bytes)
		//	PAYLOAD_OFFSET_TS_NANOSEC		- 9		- The offset into the payload to get the timestamp nanoseconds (4 bytes)
		//=====================================================================================================
		static const uint16 PAYLOAD_OFFSET_APP_ID		= 0;
		static const uint16 PAYLOAD_OFFSET_ERROR_MASK	= 1;
		static const uint16 PAYLOAD_OFFSET_SAMPLE_RATE	= 2;
		static const uint16 PAYLOAD_OFFSET_TICK			= 3;
		static const uint16 PAYLOAD_OFFSET_TS_SEC		= 5;
		static const uint16 PAYLOAD_OFFSET_TS_NANOSEC	= 9;

		//Enums: RawPacketId
		//	The possible raw packet types.
		//
		//	rawPacket_baseBoard		- 0 - HclSmartBearing Raw Base Board data packet
		//	rawPacket_strainBoard	- 1 - HclSmartBearing Raw Strain Board data packet
		//	rawPacket_inertialBoard - 2 - HclSmartBearing Raw Inertial Board data packet
		enum RawPacketId
		{
			rawPacket_baseBoard		= 0,
			rawPacket_strainBoard	= 1,
			rawPacket_inertialBoard = 2
		};

	public:
		//Constructor: HclSmartBearing_RawPacket
		//	Creates a HclSmartBearing_RawPacket from the passed in <WirelessPacket>.
		//
		//Parameters:
		//	packet - A <WirelessPacket> determined to be a HclSmartBearing_RawPacket.
		explicit HclSmartBearing_RawPacket(const WirelessPacket& packet);

	private:
		float m_magConversionVal;

	private:
		HclSmartBearing_RawPacket();	//default constructor disabled

		//Function: parseSweeps
		//	Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
		//
		//Exceptions:
		//	- <Error_UnknownSampleRate>: failed to find the sample rate in the list
		void parseSweeps();

		void parseSweeps_baseBoard();

		anyType getMagChValue(uint16 packetVal);

		//Function: integrityCheck_baseBoard
		//	Verifies that the packet is a well formed HclSmartBearing_RawPacket Base Board packet.
		//
		//Parameters:
		//	packet - The fully formed Wireless Packet to check the integrity of.
		//
		//Returns:
		//	true if the packet is a well formed HclSmartBearing_RawPacket Base Board packet, false otherwise.
		static bool integrityCheck_baseBoard(const WirelessPacket::Payload& payload);

	public:
		//Function: integrityCheck
		//	Verifies that the packet is a well formed HclSmartBearing_RawPacket packet.
		//
		//Parameters:
		//	packet - The fully formed Wireless Packet to check the integrity of.
		//
		//Returns:
		//	true if the packet is a well formed HclSmartBearing_RawPacket packet, false otherwise.
		static bool integrityCheck(const WirelessPacket& packet);

		//Function: getUniqueId
		//	Gets the unique Id of the <WirelessPacket> passed in
		//
		//Parameters:
		//	packet - The <WirelessPacket> to get the unique id of
		//
		//Returns:
		//	The <UniqueWirelessPacketId> of the passed in packet
		static UniqueWirelessPacketId getUniqueId(const WirelessPacket& packet);
	};

}