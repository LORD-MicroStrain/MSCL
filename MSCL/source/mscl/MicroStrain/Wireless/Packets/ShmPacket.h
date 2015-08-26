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

	//Class: ShmPacket
	//	A <WirelessDataPacket> derived class representing a Structural Health Monitoring Packet
	class ShmPacket : public WirelessDataPacket
	{
	public:
		//Constructor: ShmPacket
		//	Creates an ShmPacket from the passed in <WirelessPacket>.
		//
		//Parameters:
		//	packet - A <WirelessPacket> determined to be a SyncSamplingPacket.
		explicit ShmPacket(const WirelessPacket& packet);

	private:
		//Variable: m_binCount
		//	The number of bins in the packet.
		size_t m_binCount;

	private:
		ShmPacket();	//default constructor disabled

		//Function: parseSweeps
		//	Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container.
		void parseSweeps();

		//Function: parseSweeps_v1
		//	Parses the packet for version 1 of the SHM-Link packet.
		void parseSweeps_v1();

		//Function: parseSweeps_v2
		//	Parses the packet for version 2 of the SHM-Link packet.
		void parseSweeps_v2();

	public:
		//Function: integrityCheck
		//	Verifies that the packet is a well formed Shm-Link packet.
		//
		//Parameters:
		//	packet - The fully formed Wireless Packet to check the integrity of.
		//
		//Returns:
		//	true if the packet is a well formed SHM packet, false otherwise.
		static bool integrityCheck(const WirelessPacket& packet);
	};

}