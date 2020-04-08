/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "System_Commands.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    //==========================================================================================
    //GET SENSOR DATA RATE BASE
    ByteStream CommunicationMode::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //"get" has no data, so add 0 
        fieldData.append_uint8(0);

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream CommunicationMode::buildCommand_set(uint8 communicationMode)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the communication mode
        fieldData.append_uint8(communicationMode);

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    CommunicationMode::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericMipCommand::Response(MipTypes::CMD_COMMUNICATION_MODE, collector, true, dataResponse, "Communication Mode")
    {}

    uint8 CommunicationMode::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_CommunicationMode(response);
    }
    //==========================================================================================
}