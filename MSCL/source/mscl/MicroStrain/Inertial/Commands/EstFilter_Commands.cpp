/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "EstFilter_Commands.h"
#include "Inertial_Commands.h"
#include "mscl/Utils.h"
#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Inertial/EulerAngles.h"
#include "mscl/MicroStrain/Inertial/PositionOffset.h"

namespace mscl
{
    //==========================================================================================
    //GET ESTIMATION FILTER DATA RATE BASE
    ByteStream GetEstFilterDataRateBase::buildCommand()
    {
        //return the result of the Generic buildCommand function
        return GenericInertialCommand::buildCommand(CMD_ID);
    }

    GetEstFilterDataRateBase::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericInertialCommand::Response(collector, true, true, "Get Estimation Filter Data Rate Base")
    {}

    uint16 GetEstFilterDataRateBase::Response::parseResponse(const GenericInertialCommandResponse& response) const
    {
        return Inertial_Commands::parseData_DataRateBase(response);
    }
    //==========================================================================================

    //==========================================================================================
    //ESTIMATION FILTER MESSAGE FORMAT
    ByteStream EstFilterMessageFormat::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_getCurrent));

        //"get" has no channels, so add 0 
        fieldData.append_uint8(0);

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream EstFilterMessageFormat::buildCommand_set(const InertialChannels& channels, uint16 sampleRateBase)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_setCurrent));

        //add the number of channels
        fieldData.append_uint8(static_cast<uint8>(channels.size()));

        //loop through each channel in the vector of channels
        for(InertialChannel ch : channels)
        {
            //if we find a channel not in the descriptor set
            if(ch.descriptorSet() != DescriptorSet::DESC_SET_DATA_EST_FILTER)
            {
                throw Error("InertialChannel (" + Utils::toStr(ch.channelField()) + ") is not in the Estimation Filter descriptor set");
            }

            //validate the sample rate for the channel
            ch.validateSampleRate(sampleRateBase);

            //add the field descriptor and rate decimation
            fieldData.append_uint8(ch.fieldDescriptor());
            fieldData.append_uint16(ch.rateDecimation(sampleRateBase));
        }

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    EstFilterMessageFormat::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericInertialCommand::Response(collector, true, dataResponse, "Estimation Filter Message Format")
    {}

    InertialChannels EstFilterMessageFormat::Response::parseResponse(const GenericInertialCommandResponse& response, uint16 sampleRateBase) const
    {
        return Inertial_Commands::parseData_MessageFormat(response, fieldDataByte(), sampleRateBase);
    }
    //==========================================================================================

    //==========================================================================================
    //Sensor to Vehicle Frame Transformation
    ByteStream SensorToVehicFrameTrans::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_getCurrent));

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream SensorToVehicFrameTrans::buildCommand_set(const EulerAngles& angles)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_setCurrent));

        //add the roll, pitch, yaw data
        fieldData.append_float(angles.roll());
        fieldData.append_float(angles.pitch());
        fieldData.append_float(angles.yaw());

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    SensorToVehicFrameTrans::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericInertialCommand::Response(collector, true, dataResponse, "Sensor to Vehicle Frame Transformation")
    {
    }

    EulerAngles SensorToVehicFrameTrans::Response::parseResponse(const GenericInertialCommandResponse& response) const
    {
        return Inertial_Commands::parseData_EulerAngles(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Sensor to Vehicle Frame Offset
    ByteStream SensorToVehicFrameOffset::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_getCurrent));

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream SensorToVehicFrameOffset::buildCommand_set(const PositionOffset& offset)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_setCurrent));

        //add the x, y, z data
        fieldData.append_float(offset.x());
        fieldData.append_float(offset.y());
        fieldData.append_float(offset.z());

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    SensorToVehicFrameOffset::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericInertialCommand::Response(collector, true, dataResponse, "Sensor to Vehicle Frame Offset")
    {
    }

    PositionOffset SensorToVehicFrameOffset::Response::parseResponse(const GenericInertialCommandResponse& response) const
    {
        return Inertial_Commands::parseData_PositionOffset(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Antenna Offset
    ByteStream AntennaOffset::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_getCurrent));

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream AntennaOffset::buildCommand_set(const PositionOffset& offset)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_setCurrent));

        //add the x, y, z data
        fieldData.append_float(offset.x());
        fieldData.append_float(offset.y());
        fieldData.append_float(offset.z());

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    AntennaOffset::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericInertialCommand::Response(collector, true, dataResponse, "Antenna Offset")
    {
    }

    PositionOffset AntennaOffset::Response::parseResponse(const GenericInertialCommandResponse& response) const
    {
        return Inertial_Commands::parseData_PositionOffset(response);
    }
    //==========================================================================================
}