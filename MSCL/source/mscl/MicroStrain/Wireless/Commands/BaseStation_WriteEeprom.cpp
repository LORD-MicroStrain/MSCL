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

#include "BaseStation_WriteEeprom.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"

namespace mscl
{
	ByteStream BaseStation_WriteEeprom::buildCommand(uint16 eepromAddress, uint16 valueToWrite)
	{
		//build the command ByteStream
		ByteStream cmd;

		cmd.append_uint8(COMMAND_BYTE);
		cmd.append_uint16(eepromAddress);						//eeprom address to write to
		cmd.append_uint16(valueToWrite);						//value to write to eeprom
		cmd.append_uint16(cmd.calculateSimpleChecksum(1, 4));	//checksum

		return cmd;
	}


	BaseStation_WriteEeprom::Response::Response(uint16 valueToWrite, std::weak_ptr<ResponseCollector> collector):
		ResponsePattern(collector),
		m_valueWritten(valueToWrite)
	{
	}

	bool BaseStation_WriteEeprom::Response::matchSuccessResponse(DataBuffer& data)
	{
		const uint16 TOTAL_SUCCESS_BYTES = 5;

		//create a save point with the data
		ReadBufferSavePoint savePoint(&data);

		//if there aren't enough bytes in the buffer to match the response
		if(data.bytesRemaining() < TOTAL_SUCCESS_BYTES) 
		{ 
			return false; 
		}

		//if the first byte isn't the command byte
		if(data.read_uint8() != COMMAND_BYTE) 
		{ 
			return false; 
		}

		//the next two bytes should be the eeprom value we wrote in the command
		uint16 eepromVal = data.read_uint16();

		//if the eeprom value isn't the one we tried to write, then this packet is not correct
		if(eepromVal != m_valueWritten)
		{
			return false;
		}


		//build the ChecksumBuilder with the necessary bytes
		ChecksumBuilder checksum;
		checksum.append_uint16(eepromVal);	//eeprom value

		//if the checksum doesn't match
		if(data.read_uint16() != checksum.simpleChecksum()) 
		{ 
			return false; 
		}


		//if we made it this far, we successfully matched everything

		//commit the current read position
		savePoint.commit();

		//set the result to success
		m_success = true;

		return true;
	}

	bool BaseStation_WriteEeprom::Response::matchFailResponse(DataBuffer& data)
	{
		const uint16 TOTAL_FAILURE_BYTES = 1;

		//create a save point with the data
		ReadBufferSavePoint savePoint(&data);

		//if there aren't enough bytes in the buffer to match the response
		if(data.bytesRemaining() < TOTAL_FAILURE_BYTES) 
		{
			return false; 
		}

		//if the first byte isn't the fail byte
		if(data.read_uint8() != FAIL_BYTE) 
		{ 
			return false; 
		}

		//if we made it this far, we successfully matched everything

		//commit the current read position
		savePoint.commit();

		//set the result to a failure
		m_success = false;

		return true;
	}

	bool BaseStation_WriteEeprom::Response::match(DataBuffer& data)
	{
		//if the bytes match the success response
		if(matchSuccessResponse(data))
		{
			//we have fully matched the response
			m_fullyMatched = true;

			//notify that the response was matched
			m_matchCondition.notify();
			return true;
		}
		//if the bytes match the fail response
		else if(matchFailResponse(data))
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