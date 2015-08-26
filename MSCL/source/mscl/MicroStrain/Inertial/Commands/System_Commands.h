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

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"

namespace mscl
{
	//Title: System_Commands

	//Class: CommunicationMode
	//	Contains the logic for the "Communication Mode" command
	//
	//See Also:
	//	<GenericInertialCommand>
	class CommunicationMode
	{
	public:
		//Constants: Packet Bytes
		//	CMD_ID				- CMD_GET_SENSOR_RATE_BASE	- The <InertialTypes::Command> for this command
		//  FIELD_DATA_BYTE		- 0x90						- The Data Field Descriptor byte
		static const InertialTypes::Command CMD_ID	= InertialTypes::CMD_COMMUNICATION_MODE;
		static const uint8 FIELD_DATA_BYTE			= 0x90;
		
	private:
		CommunicationMode();	//disabled default constructor

	public:
		//Function: buildCommand_get
		//	Builds the bytes for the "get" command
		//
		//Returns:
		//	A <ByteStream> that holds the bytes that make up the command
		static ByteStream buildCommand_get();

		//Function: buildCommand_set
		//	Builds the bytes for the "set" command. 
		//
		//Parameters:
		//	communicationMode - The communication mode to set. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
		//
		//Returns:
		//	A <ByteStream> that holds the bytes that make up the command
		//
		//Exceptions:
		//	- <Error>: An <InertialChannel> in the channels parameter is not part of the Sensor descriptor set
		static ByteStream buildCommand_set(uint8 communicationMode);

		class Response : public GenericInertialCommand::Response
		{
		protected:
			virtual InertialTypes::Command commandId() const override { return CMD_ID; }
			virtual uint8 fieldDataByte() const	{ return FIELD_DATA_BYTE; }

		public:
			Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
			uint8 parseData(const GenericInertialCommandResponse& response) const;
		};
	};
}