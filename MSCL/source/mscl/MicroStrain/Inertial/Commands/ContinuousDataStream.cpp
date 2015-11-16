/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "ContinuousDataStream.h"
#include "Inertial_Commands.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/Utils.h"
#include "mscl/Exceptions.h"

namespace mscl
{
    uint8 ContinuousDataStream::getDeviceSelector(InertialTypes::InertialCategory type)
    {
        switch(type)
        {
            case InertialTypes::CATEGORY_SENSOR:
                return 0x01;

            case InertialTypes::CATEGORY_GPS:
                return 0x02;

            case InertialTypes::CATEGORY_ESTFILTER:
                return 0x03;

            default:
                return 0x00;
        }
    }

    ByteStream ContinuousDataStream::buildCommand_get(InertialTypes::InertialCategory type)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_getCurrent));

        //add the device selector
        fieldData.append_uint8(getDeviceSelector(type));

        //"get" ignores the enable flag
        fieldData.append_uint8(0);

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream ContinuousDataStream::buildCommand_set(InertialTypes::InertialCategory type, bool enable)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_setCurrent));

        //add the device selector
        fieldData.append_uint8(getDeviceSelector(type));

        //add the enable flag
        fieldData.append_uint8(static_cast<uint8>(enable));

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ContinuousDataStream::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse, InertialTypes::InertialCategory type):
        GenericInertialCommand::Response(collector, true, dataResponse, "Continuous Data Stream"),
        m_deviceSelector(getDeviceSelector(type))
    {}

    bool ContinuousDataStream::Response::match_data(const InertialDataField& field)
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
        return GenericInertialCommand::Response::match_data(field);
    }

    bool ContinuousDataStream::Response::parseResponse(const GenericInertialCommandResponse& response) const
    {
        return Inertial_Commands::parseData_ContinuousDataStream(response);
    }
}