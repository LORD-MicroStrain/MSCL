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
#include "stdafx.h"

#include "NodeDiscoveryPacket_v3.h"

namespace mscl
{
	const DeliveryStopFlags NodeDiscoveryPacket_v3::stopFlags_nodeDiscovery(true, false, false, false);

	bool NodeDiscoveryPacket_v3::integrityCheck(const WirelessPacket& packet)
	{
		const uint8 RADIO_CHANNEL_MIN = 11;
		const uint8 RADIO_CHANNEL_MAX = 26;

		//verify the payload size is correct
		if(packet.payload().size() != 17)
		{
			return false;
		}

		//read what should be the radio channel byte
		uint8 radioChannel = packet.payload().read_uint8(PAYLOAD_OFFSET_RADIO_CHANNEL);

		//verify that the radio channel byte is valid
		if(radioChannel < RADIO_CHANNEL_MIN || radioChannel > RADIO_CHANNEL_MAX)
		{
			return false;
		}

		//verify the delivery stop flags are what we expected
		if(packet.deliveryStopFlags() != stopFlags_nodeDiscovery)
		{
			//packet not intended for the PC
			return false;
		}

		//verify the packet type is correct
		if(packet.type() != packetType_nodeDiscovery_v3)
		{
			//packet is not a node discovery packet
			return false;
		}

		//packet looks valid
		return true;
	}
}