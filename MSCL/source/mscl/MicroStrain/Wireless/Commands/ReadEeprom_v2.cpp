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
#include "ReadEeprom_v2.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
	ByteStream ReadEeprom_v2::buildCommand(NodeAddress nodeAddress, uint16 eepromAddress)
	{
		//build the command ByteStream
		ByteStream cmd;
		cmd.append_uint8(0xAA);				//Start of Packet
		cmd.append_uint8(0x05);				//Delivery Stop Flag
		cmd.append_uint8(0x00);				//App Data Type
		cmd.append_uint16(nodeAddress);		//Node address	(2 bytes)
		cmd.append_uint8(0x04);				//Payload length
		cmd.append_uint16(0x0007);			//Command ID	(2 bytes)
		cmd.append_uint16(eepromAddress);	//EEPROM Address (2 bytes)

		//calculate the checksum of bytes 2-10
		uint16 checksum = cmd.calculateSimpleChecksum(1, 9);

		cmd.append_uint16(checksum);		//Checksum		(2 bytes)

		return cmd;
	}

	ReadEeprom_v2::Response::Response(NodeAddress nodeAddress, uint16 eepromAddress, std::weak_ptr<ResponseCollector> collector):
		ResponsePattern(collector),
		m_nodeAddress(nodeAddress),
		m_eepromAddress(eepromAddress),
		m_eepromValue(0)
	{
	}

	bool ReadEeprom_v2::Response::match(const WirelessPacket& packet)
	{
		WirelessPacket::Payload payload = packet.payload();

		uint8 dsf = packet.deliveryStopFlags().toByte();

		//check the main bytes of the packet
		if( (dsf != 0x07 && dsf != 0x00) ||					//delivery stop flag (Unfortunately some nodes report 0x00 and some report 0x07)
			packet.type() != 0x00 ||						//app data type
			packet.nodeAddress() != m_nodeAddress ||		//node address
			payload.size() != 0x06 ||						//payload length
			payload.read_uint16(0) != 0x0007 ||				//command ID
			payload.read_uint16(2) != m_eepromAddress		//eeprom address
			)
		{
			//failed to match some of the bytes
			return false;
		}

		//if we made it here, the packet matches the response pattern

		//get the eeprom value from the response
		m_success = true;
		m_eepromValue = packet.payload().read_uint16(4);

		//we have fully matched the response
		m_fullyMatched = true;

		//notify that the response was matched
		m_matchCondition.notify();

		return true;
	}

	uint16 ReadEeprom_v2::Response::eepromValue() const
	{
		//throw an exception if the command failed
		throwIfFailed("Read Node EEPROM");

		return m_eepromValue;
	}
}