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
	//Class: NodeDiscoveryPacket
	//	A class representing a MicroStrain "node discovery" packet
	class NodeDiscoveryPacket : public WirelessPacket
	{
	public:
		//=====================================================================================================
		//Constants: Node Discovery Packet Information
		//	PAYLOAD_OFFSET_RADIO_CHANNEL - 0		- The offset into the payload to get the radio channel
		//	PAYLOAD_OFFSET_MODEL_NUMBER	 - 1		- The offset into the payload to get the model number (2 bytes)
		//=====================================================================================================
		static const int PAYLOAD_OFFSET_RADIO_CHANNEL	= 0;
		static const int PAYLOAD_OFFSET_MODEL_NUMBER	= 1;

	private:
		NodeDiscoveryPacket();	//default constructor disabled

	public:
		//Constant: stopFlags_nodeDiscovery
		//	The delivery stop flags that are expected in the node discovery command
		static const DeliveryStopFlags stopFlags_nodeDiscovery;

		//Function: integrityCheck
		//	Verifies that the packet is a well formed Node Discovery packet
		//
		//Parameters:
		//	packet - The fully formed Wireless Packet to check the integrity of
		//
		//Returns:
		//	true is the packet is a well-formed Node Discovery Packet, false otherwise
		static bool integrityCheck(const WirelessPacket& packet);
	};
}