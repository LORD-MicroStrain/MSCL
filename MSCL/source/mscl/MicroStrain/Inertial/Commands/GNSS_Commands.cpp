/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "GNSS_Commands.h"

#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"
#include "mscl/Exceptions.h"
#include "mscl/Utils.h"

namespace mscl
{
    ByteStream GetGnssDataRateBase::buildCommand()
    {
        //return the result of the Generic buildCommand function
        return GenericMipCommand::buildCommand(CMD_ID);
    }

    GetGnssDataRateBase::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_GET_GNSS_RATE_BASE, collector, true, true, "Get GNSS Data Rate Base")
    {}

    uint16 GetGnssDataRateBase::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_DataRateBase(response);
    }

    //==========================================================================================
    //GNSS MESSAGE FORMAT
    ByteStream GnssMessageFormat::buildCommand_get()
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

    ByteStream GnssMessageFormat::buildCommand_set(const MipChannels& channels, uint16 sampleRateBase)
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
            if(ch.descriptorSet() != DescriptorSet::DESC_SET_DATA_GNSS)
            {
                throw Error("MipChannel (" + Utils::toStr(ch.channelField()) +") is not in the GNSS descriptor set");
            }

            //add the field descriptor and rate decimation
            fieldData.append_uint8(ch.fieldDescriptor());
            fieldData.append_uint16(ch.rateDecimation(sampleRateBase));
        }

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream GnssMessageFormat::buildCommand_save()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::SAVE_CURRENT_SETTINGS));

        //"get" has no channels, so add 0
        fieldData.append_uint8(0);

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    GnssMessageFormat::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericMipCommand::Response(MipTypes::CMD_GNSS_MESSAGE_FORMAT, collector, true, dataResponse, "GNSS Message Format")
    {}

    MipChannels GnssMessageFormat::Response::parseResponse(const GenericMipCmdResponse& response, uint16 sampleRateBase) const
    {
        return MIP_Commands::parseData_MessageFormat(response, fieldDataByte(), sampleRateBase);
    }
    //==========================================================================================
}
