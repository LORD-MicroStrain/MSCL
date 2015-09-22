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

	//Class: BaseStation_ReadEeprom_v2
	//	Contains logic for the base station read eeprom command (v2).
	class BaseStation_ReadEeprom_v2
	{
	private:
		BaseStation_ReadEeprom_v2();											//default constructor disabled
		BaseStation_ReadEeprom_v2(const BaseStation_ReadEeprom_v2&);			//copy constructor disabled
		BaseStation_ReadEeprom_v2& operator=(const BaseStation_ReadEeprom_v2&);	//assignement operator disabled

	public:
		//Function: buildCommand
		//	Builds the eeprom read command packet.
		//
		//Parameters:
		//	eepromAddress - The eeprom address to read from the base station.
		//
		//Returns:
		//	A <ByteStream> containing the base station read eeprom command
		static ByteStream buildCommand(uint16 eepromAddress);

		//Class: Response
		//	Handles the response to the base station read eeprom command.
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a read eeprom Response object.
			//
			//Parameters:
			//	eepromAddress - The eeprom address being read from.
			//	collector - The <ResponseCollector> used to register and unregister the response.
			Response(uint16 eepromAddress, std::weak_ptr<ResponseCollector> collector);

		private:
			//Variable: m_eepromAddress
			//	The eeprom address to match in the response.
			uint16 m_eepromAddress;

			//Variable: m_result
			//	The result value of the read eeprom command.
			uint16 m_result;

		public:
			//Function: match
			//	Checks if the packet passed in matches either the success or failure response.
			//
			//Parameters:
			//	packet - The <WirelessPacket> to try to match.
			//
			//Returns:
			//	true if the response pattern was found, false otherwise.
			virtual bool match(const WirelessPacket& packet) override;

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
			//	Checks if the packet passed in matches the success response.
			//
			//Parameters:
			//	packet - The <WirelessPacket> to try to match.
			//
			//Returns:
			//	true if the success response pattern was found, false otherwise
			bool matchSuccessResponse(const WirelessPacket& packet);

			//Function: matchFailResponse
			//	Checks if the packet passed in matches the failure response.
			//
			//Parameters:
			//	packet - The <WirelessPacket> to try to match.
			//
			//Returns:
			//	true if the failure response pattern was found, false otherwise
			bool matchFailResponse(const WirelessPacket& packet);
		};
	};

#endif

}