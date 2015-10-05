/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStation_ReadEeprom.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"

namespace mscl
{
	ByteStream BaseStation_ReadEeprom::buildCommand(uint16 eepromAddress)
	{
		//build the command ByteStream
		ByteStream cmd;

		cmd.append_uint8(COMMAND_BYTE);
		cmd.append_uint16(eepromAddress);						//eeprom address to read
		cmd.append_uint16(cmd.calculateSimpleChecksum(1, 2));	//checksum
		
		//return the built command bytes
		return cmd;
	}


	BaseStation_ReadEeprom::Response::Response(std::weak_ptr<ResponseCollector> collector):
		ResponsePattern(collector)
	{
	}

	bool BaseStation_ReadEeprom::Response::matchSuccessResponse(DataBuffer& data)
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


		//the next two bytes should be the eeprom value
		uint16 eepromVal = data.read_uint16();

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
		m_result = eepromVal;

		return true;
	}

	bool BaseStation_ReadEeprom::Response::matchFailResponse(DataBuffer& data)
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

	bool BaseStation_ReadEeprom::Response::match(DataBuffer& data)
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

	uint16 BaseStation_ReadEeprom::Response::result() const
	{
		//throw an exception if the command failed
		throwIfFailed("Read BaseStation EEPROM");

		return m_result;
	}
}