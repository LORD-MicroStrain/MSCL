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

#include "BaseStation_WriteEeprom_v2.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "WirelessProtocol.h"

namespace mscl
{
	ByteStream BaseStation_WriteEeprom_v2::buildCommand(uint16 eepromAddress, uint16 valueToWrite)
	{
		//build the command ByteStream
		ByteStream cmd;

		cmd.append_uint8(0xAA);				//Start of packet
		cmd.append_uint8(0x0E);				//Delivery Stop Flag
		cmd.append_uint8(0x30);				//App Data Type
		cmd.append_uint16(WirelessProtocol::BASE_STATION_ADDRESS);	//Base Station Address
		cmd.append_uint8(0x06);				//Payload length
		cmd.append_uint16(0x0078);			//Command ID
		cmd.append_uint16(eepromAddress);	//eeprom address to write to
		cmd.append_uint16(valueToWrite);	//value to write
		cmd.append_uint16(cmd.calculateSimpleChecksum(1, 11));	//checksum

		//return the built command bytes
		return cmd;
	}


	BaseStation_WriteEeprom_v2::Response::Response(uint16 valueToWrite, uint16 eepromAddress, std::weak_ptr<ResponseCollector> collector):
		ResponsePattern(collector),
		m_valueWritten(valueToWrite),
		m_eepromAddress(eepromAddress)
	{
	}

	bool BaseStation_WriteEeprom_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
	{
		WirelessPacket::Payload payload = packet.payload();

		//check the main bytes of the packet
		if(packet.deliveryStopFlags().toByte() != 0x07 ||						//delivery stop flag
		   packet.type() != WirelessPacket::packetType_baseReply ||				//app data type
		   packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||	//node address
		   payload.size() != 0x06 ||											//payload length
		   payload.read_uint16(0) != 0x0078 ||									//command ID
		   payload.read_uint16(2) != m_eepromAddress ||							//eeprom address
		   payload.read_uint16(4) != m_valueWritten								//value written
		   )
		{
			//failed to match some of the bytes
			return false;
		}

		m_success = true;

		return true;
	}

	bool BaseStation_WriteEeprom_v2::Response::matchFailResponse(const WirelessPacket& packet)
	{
		WirelessPacket::Payload payload = packet.payload();

		//check the main bytes of the packet
		if(packet.deliveryStopFlags().toByte() != 0x07 ||						//delivery stop flag
		   packet.type() != WirelessPacket::packetType_baseErrorReply ||		//app data type
		   packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||	//node address
		   payload.size() != 0x07 ||											//payload length
		   payload.read_uint16(0) != 0x0078 ||									//command ID
		   payload.read_uint16(2) != m_eepromAddress ||							//eeprom address
		   payload.read_uint16(4) != m_valueWritten								//value written
		   )
		{
			//failed to match some of the bytes
			return false;
		}

		//Not doing anything with the error code as of now
		//uint8 errorCode = payload.read_uint8(6);

		//set the result to failure
		m_success = false;

		return true;
	}

	bool BaseStation_WriteEeprom_v2::Response::match(const WirelessPacket& packet)
	{
		//if the bytes match the success response
		if(matchSuccessResponse(packet))
		{
			//we have fully matched the response
			m_fullyMatched = true;

			//notify that the response was matched
			m_matchCondition.notify();
			return true;
		}
		//if the bytes match the fail response
		else if(matchFailResponse(packet))
		{
			//we have fully matched the response
			m_fullyMatched = true;

			//notify that the response was matched
			m_matchCondition.notify();
			return true;
		}

		//the bytes don't match any response
		return false;
	}
}