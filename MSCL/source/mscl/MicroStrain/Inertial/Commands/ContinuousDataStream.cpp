/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "ContinuousDataStream.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/Utils.h"
#include "mscl/Exceptions.h"

namespace mscl
{
    uint8 ContinuousDataStream::getDeviceSelector(MipTypes::DataClass type)
    {
        switch(type)
        {
            case MipTypes::CLASS_AHRS_IMU:
                return 0x01;

            case MipTypes::CLASS_GNSS:
                return 0x02;

            case MipTypes::CLASS_ESTFILTER:
                return 0x03;

            default:
                return 0x00;
        }
    }

    ByteStream ContinuousDataStream::buildCommand_get(MipTypes::DataClass type)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //add the device selector
        fieldData.append_uint8(getDeviceSelector(type));

        //"get" ignores the enable flag
        fieldData.append_uint8(0);

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream ContinuousDataStream::buildCommand_set(MipTypes::DataClass type, bool enable)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the device selector
        fieldData.append_uint8(getDeviceSelector(type));

        //add the enable flag
        fieldData.append_uint8(static_cast<uint8>(enable));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ContinuousDataStream::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse, MipTypes::DataClass type):
        GenericMipCommand::Response(MipTypes::CMD_CONTINUOUS_DATA_STREAM, collector, true, dataResponse, "Continuous Data Stream"),
        m_deviceSelector(getDeviceSelector(type))
    {}

    bool ContinuousDataStream::Response::match_data(const MipDataField& field)
    {
        ByteStream data = field.fieldData();

        //verify that the full field data is there
        if(data.size() < 2)
        {
            return false;
        }

        //verify that the device selector is the one we are looking for
        if(data.read_uint8(0) != m_deviceSelector)
        {
            return false;
        }
        
        //call match from the super class as well
        return GenericMipCommand::Response::match_data(field);
    }

    bool ContinuousDataStream::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_ContinuousDataStream(response);
    }
}