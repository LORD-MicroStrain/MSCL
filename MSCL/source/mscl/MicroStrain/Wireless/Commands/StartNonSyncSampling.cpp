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
#include "StartNonSyncSampling.h"

namespace mscl
{
	ByteStream StartNonSyncSampling::buildCommand(NodeAddress nodeAddress)
	{
		//build the command ByteStream
		ByteStream cmd;
		cmd.append_uint8(0xAA);				//Start of Packet
		cmd.append_uint8(0x05);				//Delivery Stop Flag
		cmd.append_uint8(0x00);				//App Data Type
		cmd.append_uint16(nodeAddress);		//Node address	(2 bytes)
		cmd.append_uint8(0x02);				//Payload length
		cmd.append_uint16(0x38);			//Command ID	(2 bytes)

		//calculate the checksum of bytes 2-10
		uint16 checksum = cmd.calculateSimpleChecksum(1, 7);

		cmd.append_uint16(checksum);		//Checksum		(2 bytes)

		return cmd;
	}
}