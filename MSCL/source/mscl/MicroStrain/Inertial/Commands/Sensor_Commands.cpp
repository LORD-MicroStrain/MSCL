/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Sensor_Commands.h"

#include "mscl/Exceptions.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    //==========================================================================================
    //GET SENSOR DATA RATE BASE
    ByteStream GetSensorDataRateBase::buildCommand()
    {
        //return the result of the Generic buildCommand function
        return GenericMipCommand::buildCommand(CMD_ID);
    }

    GetSensorDataRateBase::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_GET_SENSOR_RATE_BASE, collector, true, true, "Get Sensor Data Rate Base")
    {}

    uint16 GetSensorDataRateBase::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_DataRateBase(response);
    }
    //==========================================================================================

    //==========================================================================================
    //SENSOR MESSAGE FORMAT
    ByteStream SensorMessageFormat::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //"get" has no channels, so add 0 
        fieldData.append_uint8(0);

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream SensorMessageFormat::buildCommand_set(const MipChannels& channels, uint16 sampleRateBase)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the number of channels
        fieldData.append_uint8(static_cast<uint8>(channels.size()));

        //loop through each channel in the vector of channels
        for(MipChannel ch : channels)
        {
            //if we find a channel not in the Sensor descriptor set
            if(ch.descriptorSet() != DescriptorSet::DESC_SET_DATA_SENSOR)
            {
                throw Error("MipChannel (" + Utils::toStr(ch.channelField()) +") is not in the Sensor descriptor set");
            }

            //add the field descriptor and rate decimation
            fieldData.append_uint8(ch.fieldDescriptor());
            fieldData.append_uint16(ch.rateDecimation(sampleRateBase));
        }

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream SensorMessageFormat::buildCommand_save()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::SAVE_CURRENT_SETTINGS));

        // no channels, so add 0 
        fieldData.append_uint8(0);

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    SensorMessageFormat::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericMipCommand::Response(MipTypes::CMD_SENSOR_MESSAGE_FORMAT, collector, true, dataResponse, "Sensor Message Format")
    {}

    MipChannels SensorMessageFormat::Response::parseResponse(const GenericMipCmdResponse& response, uint16 sampleRateBase) const
    {
        return MIP_Commands::parseData_MessageFormat(response, fieldDataByte(), sampleRateBase);
    }
    //==========================================================================================

}