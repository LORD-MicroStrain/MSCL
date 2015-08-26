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

namespace mscl
{
	//Class: GetDeviceDescriptorSets
	//	Contains the logic for the Inertial "Get Device Descriptor Sets" command
	class GetDeviceDescriptorSets
	{
	public:
		//Constants: Packet Bytes
		//	CMD_ID				= CMD_GET_DESCRIPTOR_SETS	- The <InertialTypes::Command> for this command
		//  FIELD_DATA_BYTE		= 0x82						- The Data Field Descriptor byte
		static const InertialTypes::Command CMD_ID = InertialTypes::CMD_GET_DESCRIPTOR_SETS;
		static const uint8 FIELD_DATA_BYTE			= 0x82;

	private:
		GetDeviceDescriptorSets();		//default constructor disabled

	public:
		//Function: buildCommand
		//	Builds the command packet
		//
		//Returns:
		//	A <ByteStream> containing the Inertial GetDeviceDescriptorSets command packet
		static ByteStream buildCommand();

		//Class: Response
		//	Handles the response to the GetDeviceDescriptorSets command
		class Response : public GenericInertialCommand::Response
		{
		protected:
			virtual InertialTypes::Command commandId() const override { return CMD_ID; }
			virtual uint8 fieldDataByte() const override { return FIELD_DATA_BYTE; }

		public:
			//Constructor: Response
			//	Creates a Response object
			//
			//Parameters:
			//	collector - The <ResponseCollector> used to register and unregister the response
			Response(std::weak_ptr<ResponseCollector> collector);

		public:
			//Function: match_data
			//	Attempts to match an <InertialDataField> to the expected data field response.
			//
			//Returns:
			//	true if the field matches the expected data, false if it does not.
			virtual bool match_data(const InertialDataField& field) override;

			//Function: parseData
			//	Parses a successfully matched response for the GetDeviceDescriptorSets command.
			//
			//Parameters:
			//	response - The <GenericInertialCommandResponse> that matches the data field for this response.
			//
			//Returns:
			//	The descriptor sets parsed from the response.
			std::vector<uint16> parseData(const GenericInertialCommandResponse& response) const;
		};
	};
}