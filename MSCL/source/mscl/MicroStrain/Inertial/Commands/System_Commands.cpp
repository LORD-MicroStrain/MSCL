/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "System_Commands.h"
#include "Inertial_Commands.h"

namespace mscl
{
	//==========================================================================================
	//GET SENSOR DATA RATE BASE
	ByteStream CommunicationMode::buildCommand_get()
	{
		//container to hold the command's field data
		ByteStream fieldData;

		//add the command selector byte
		fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_getCurrent));

		//"get" has no data, so add 0 
		fieldData.append_uint8(0);

		//build and return the command bytes
		return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
	}

	ByteStream CommunicationMode::buildCommand_set(uint8 communicationMode)
	{
		//container to hold the command's field data
		ByteStream fieldData;

		//add the command selector byte
		fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_setCurrent));

		//add the communication mode
		fieldData.append_uint8(communicationMode);

		//build and return the command bytes
		return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
	}

	CommunicationMode::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
		GenericInertialCommand::Response(collector, true, dataResponse, "Communication Mode")
	{}

	uint8 CommunicationMode::Response::parseData(const GenericInertialCommandResponse& response) const
	{
		return Inertial_Commands::parseData_CommunicationMode(response);
	}
	//==========================================================================================
}