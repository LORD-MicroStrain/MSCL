/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStation_ReadEeprom_v2.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"

namespace mscl
{
	ByteStream BaseStation_ReadEeprom_v2::buildCommand(uint16 eepromAddress)
	{
		//build the command ByteStream
		ByteStream cmd;

		cmd.append_uint8(0xAA);				//Start of packet
		cmd.append_uint8(0x0E);				//Delivery Stop Flag
		cmd.append_uint8(0x30);				//App Data Type
		cmd.append_uint16(WirelessProtocol::BASE_STATION_ADDRESS);	//Base Station Address
		cmd.append_uint8(0x04);				//Payload length
		cmd.append_uint16(0x0073);			//Command ID
		cmd.append_uint16(eepromAddress);	//eeprom address to read
		cmd.append_uint16(cmd.calculateSimpleChecksum(1, 9));	//checksum
		
		//return the built command bytes
		return cmd;
	}


	BaseStation_ReadEeprom_v2::Response::Response(uint16 eepromAddress, std::weak_ptr<ResponseCollector> collector):
		ResponsePattern(collector),
		m_eepromAddress(eepromAddress),
		m_errorCode(WirelessPacket::error_none)
	{
	}

	bool BaseStation_ReadEeprom_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
	{
		WirelessPacket::Payload payload = packet.payload();

		//check the main bytes of the packet
		if(packet.deliveryStopFlags().toByte() != 0x07 ||						//delivery stop flag
		   packet.type() != WirelessPacket::packetType_baseSuccessReply ||		//app data type
		   packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||	//node address
		   payload.size() != 0x06 ||											//payload length
		   payload.read_uint16(0) != 0x0073 ||									//command ID
		   payload.read_uint16(2) != m_eepromAddress							//eeprom address
		   )
		{
			//failed to match some of the bytes
			return false;
		}

		//get the eeprom value
		m_result = payload.read_uint16(4);
		m_errorCode = WirelessPacket::error_none;

		//set the result to success
		m_success = true;

		return true;
	}

	bool BaseStation_ReadEeprom_v2::Response::matchFailResponse(const WirelessPacket& packet)
	{
		WirelessPacket::Payload payload = packet.payload();

		//check the main bytes of the packet
		if(packet.deliveryStopFlags().toByte() != 0x07 ||						//delivery stop flag
		   packet.type() != WirelessPacket::packetType_baseErrorReply ||		//app data type
		   packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||	//node address
		   payload.size() != 0x05 ||											//payload length
		   payload.read_uint16(0) != 0x0073 ||									//command ID
		   payload.read_uint16(2) != m_eepromAddress							//eeprom address
		   )
		{
			//failed to match some of the bytes
			return false;
		}

		//read the error code from the response
		m_errorCode = static_cast<WirelessPacket::ResponseErrorCode>(payload.read_uint8(4));

		//set the result to failure
		m_success = false;

		return true;
	}

	bool BaseStation_ReadEeprom_v2::Response::match(const WirelessPacket& packet)
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

	uint16 BaseStation_ReadEeprom_v2::Response::result() const
	{
		//throw an exception if the command failed
		throwIfFailed("Read BaseStation EEPROM");

		return m_result;
	}

	WirelessPacket::ResponseErrorCode BaseStation_ReadEeprom_v2::Response::errorCode() const
	{
		return m_errorCode;
	}
}