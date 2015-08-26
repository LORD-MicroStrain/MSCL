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

#include "WirelessPacket.h"

namespace mscl
{
	//Class: WirelessPacketUtils
	//	Contains useful utility functions for interfacing with MicroStrain's Wireless packets 
	class WirelessPacketUtils
	{

	public:
		//Function: correctPacketType
		//	Some packets are not properly identified. 
		//	This function looks for special cases of misidentified packets and corrects them.
		//
		//Parameters:
		//	packet - A reference to a <WirelessPacket> which contains all the wireless packet data and info
		static void correctPacketType(WirelessPacket& packet);

		//Function: packetIntegrityCheck
		//	Verifies that the packet matches the packet type that it is currently set to
		//
		//Parameters:
		//	packet - A reference to the <WirelessPacket> to check the integrity of
		//
		//Returns:
		//	true if the packet's bytes are what they should be for its current type, false otherwise
		static bool packetIntegrityCheck(const WirelessPacket& packet);
	};

}