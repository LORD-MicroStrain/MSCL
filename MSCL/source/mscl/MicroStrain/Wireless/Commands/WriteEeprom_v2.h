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

	//Class: WriteEeprom_v2
	//	Contains logic for the WriteEeprom (version 2) Node command
	class WriteEeprom_v2
	{
	private:
		WriteEeprom_v2();									//default constructor disabled
		WriteEeprom_v2(const WriteEeprom_v2&);				//copy constructor disabled
		WriteEeprom_v2& operator=(const WriteEeprom_v2&);	//assignment operator disabled

	public:
		//Function: buildCommand
		//	Builds the WriteEeprom_v2 command packet
		//
		//Parameters:
		//	nodeAddress - the address of the Node to build the command for
		//	eepromAddress - the Eeprom address to write to
		//	valueToWrite - the value to write to the Eeprom
		//
		//Returns:
		//	A <ByteStream> containing the command packet
		static ByteStream buildCommand(NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueToWrite);

		//=====================================================================================================
		//Constants: Packet Bytes
		//	COMMAND_ID - 0x0008	- The Command ID for the WriteEeprom_v2 Command
		//=====================================================================================================
		static const short COMMAND_ID = 0x0008;

		//Class: Response
		//	Handles the response to the WriteEeprom_v2 Node command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a WriteEeprom_v2 Response object
			//
			//Parameters:
			//	nodeAddress - the node address to check for.
			//	eepromAddress - the eeprom address that was written to.
			//	valueWritten - the value that was written to eeprom.
			//	collector - The <ResponseCollector> used to register and unregister the response.
			Response(NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueWritten, std::weak_ptr<ResponseCollector> collector);

		private:
			//Variable: m_nodeAddress
			//	The node address to look for in the WriteEeprom_v2 response
			NodeAddress m_nodeAddress;

			//Variable: m_eepromAddress
			//	The eeprom address to look for in the WriteEeprom_v2 response.
			uint16 m_eepromAddress;

			//Variable: eepromValue
			//	The eeprom value to look for in the WriteEeprom_v2 response.
			uint16 m_eepromValue;

		public:
			//Function: match
			//	Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes
			//
			//Parameters:
			//	packet - The <WirelessPacket> in which to try to find the pattern
			//
			//Returns:
			//	true if the packet matches a response pattern, false otherwise
			virtual bool match(const WirelessPacket& packet) override;
		};
	};

#endif
}