/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/System_Commands.h"

#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    //==========================================================================================
    //GET PORT INTERFACE CONTROL
    ByteStream InterfaceControl::buildCommand_get(uint8 interfaceId)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //add the interface ID byte
        fieldData.append_uint8(interfaceId);

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream InterfaceControl::buildCommand_set(uint8 interfaceId, DeviceCommPort::Protocol inputProtocols, DeviceCommPort::Protocol outputProtocols)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the interface ID
        fieldData.append_uint8(interfaceId);

        //add the input protocols
        fieldData.append_uint32(static_cast<uint32>(inputProtocols));

        //add the output protocols
        fieldData.append_uint32(static_cast<uint32>(outputProtocols));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    InterfaceControl::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse) :
        GenericMipCommand::Response(MipTypes::CMD_INTERFACE_CONTROL, collector, true, dataResponse, "Interface Control")
    {}

    DeviceCommPort InterfaceControl::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_InterfaceControl(response);
    }
    //==========================================================================================

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

    CommunicationMode::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse) :
        GenericMipCommand::Response(MipTypes::CMD_COMMUNICATION_MODE, collector, true, dataResponse, "Communication Mode")
    {}

    uint8 CommunicationMode::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_CommunicationMode(response);
    }
    //==========================================================================================
}
