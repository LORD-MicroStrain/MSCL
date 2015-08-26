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

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

	//Class: BaseStation_ReadEeprom
	//	Contains logic for the base station read eeprom command
	class BaseStation_ReadEeprom
	{
	private:
		BaseStation_ReadEeprom();											//default constructor disabled
		BaseStation_ReadEeprom(const BaseStation_ReadEeprom&);				//copy constructor disabled
		BaseStation_ReadEeprom& operator=(const BaseStation_ReadEeprom&);	//assignement operator disabled

	public:
		//=====================================================================================================
		//Constants: Packet Bytes
		//	COMMAND_BYTE	- 0x73	- The Command ID byte for the read eeprom command
		//	FAIL_BYTE		- 0x21	- The Fail Response ID byte for the read eeprom command
		//=====================================================================================================
		static const short COMMAND_BYTE = 0x73;
		static const short FAIL_BYTE	= 0x21;

		//Function: buildCommand
		//	Builds the eeprom read command packet
		//
		//Parameters:
		//	eepromAddress - The eeprom address to read from the base station
		//
		//Returns:
		//	A <ByteStream> containing the base station read eeprom command
		static ByteStream buildCommand(uint16 eepromAddress);

		//Class: Response
		//	Handles the response to the base station read eeprom command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a read eeprom Response object
			//
			//Parameters:
			//	collector - The <ResponseCollector> used to register and unregister the response 
			Response(std::weak_ptr<ResponseCollector> collector);

		private:
			//Variable: m_result
			//	The result value of the read eeprom command.
			uint16 m_result;

		public:
			//Function: match
			//	Checks if the bytes passed in match the response pattern from their current read position
			//
			//Parameters:
			//	data - The <DataBuffer> containing the bytes in which to try to find the pattern
			//
			//Returns:
			//	true if the response pattern was found, false otherwise
			virtual bool match(DataBuffer& data) override;

			//Function: result
			//	Gets the result value of the response.
			//
			//Returns:
			//	The result value of the response.
			//
			//Exceptions:
			//	- <Error>: failed to read the base station's eeprom.
			uint16 result() const;

		private:
			//Function: matchSuccessResponse
			//	Checks if the bytes passed in match the success response pattern from their current read position
			//
			//Parameters:
			//	data - The <DataBuffer> containing the bytes in which to try to find the pattern
			//
			//Returns:
			//	true if the success response pattern was found, false otherwise
			bool matchSuccessResponse(DataBuffer& data);

			//Function: matchFailResponse
			//	Checks if the bytes passed in match the failure response pattern from their current read position
			//
			//Parameters:
			//	data - The <DataBuffer> containing the bytes in which to try to find the pattern
			//
			//Returns:
			//	true if the failure response pattern was found, false otherwise
			bool matchFailResponse(DataBuffer& data);
		};
	};

#endif

}