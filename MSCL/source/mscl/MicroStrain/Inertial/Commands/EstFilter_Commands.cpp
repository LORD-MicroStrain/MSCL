/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "EstFilter_Commands.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"
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
        return GenericMipCommand::buildCommand(CMD_ID);
    }

    GetEstFilterDataRateBase::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_GET_EF_RATE_BASE, collector, true, true, "Get Estimation Filter Data Rate Base")
    {}

    uint16 GetEstFilterDataRateBase::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_DataRateBase(response);
    }
    //==========================================================================================

    //==========================================================================================
    //ESTIMATION FILTER MESSAGE FORMAT
    ByteStream EstFilterMessageFormat::buildCommand_get()
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

    ByteStream EstFilterMessageFormat::buildCommand_set(const MipChannels& channels, uint16 sampleRateBase)
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
            //if we find a channel not in the descriptor set
            if(ch.descriptorSet() != DescriptorSet::DESC_SET_DATA_EST_FILTER)
            {
                throw Error("MipChannel (" + Utils::toStr(ch.channelField()) + ") is not in the Estimation Filter descriptor set");
            }

            //add the field descriptor and rate decimation
            fieldData.append_uint8(ch.fieldDescriptor());
            fieldData.append_uint16(ch.rateDecimation(sampleRateBase));
        }

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream EstFilterMessageFormat::buildCommand_save()
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


    EstFilterMessageFormat::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericMipCommand::Response(MipTypes::CMD_EF_MESSAGE_FORMAT, collector, true, dataResponse, "Estimation Filter Message Format")
    {}

    MipChannels EstFilterMessageFormat::Response::parseResponse(const GenericMipCmdResponse& response, uint16 sampleRateBase) const
    {
        return MIP_Commands::parseData_MessageFormat(response, fieldDataByte(), sampleRateBase);
    }
    //==========================================================================================

    //==========================================================================================
    //Reset Filter
    ByteStream ResetFilter::buildCommand()
    {
        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID);
    }

    ResetFilter::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_EF_RESET_FILTER, collector, true, false, "Reset Filter")
    {
    }
    //==========================================================================================

    //==========================================================================================
    //Set Initial Attitude
    ByteStream SetInitialAttitude::buildCommand(const EulerAngles& attitude)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the roll, pitch, yaw data
        fieldData.append_float(attitude.roll());
        fieldData.append_float(attitude.pitch());
        fieldData.append_float(attitude.yaw());

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    SetInitialAttitude::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_EF_INIT_ATTITUDE, collector, true, false, "Set Initial Attitude")
    {
    }
    //==========================================================================================

    //==========================================================================================
    //Set Initial Attitude
    ByteStream SetInitialHeading::buildCommand(float heading)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the roll, pitch, yaw data
        fieldData.append_float(heading);

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    SetInitialHeading::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_EF_INIT_HEADING, collector, true, false, "Set Initial Heading")
    {
    }
    //==========================================================================================

    //==========================================================================================
    //Auto-Initialization Control
    ByteStream AutoInitializeControl::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream AutoInitializeControl::buildCommand_set(bool enable)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the enable/disable flag
        fieldData.append_uint8(static_cast<uint8>(enable));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    AutoInitializeControl::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericMipCommand::Response(MipTypes::CMD_EF_AUTO_INIT_CTRL, collector, true, dataResponse, "Auto-Initialization Control")
    {
    }

    bool AutoInitializeControl::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_singleBool(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Altitude Aid Control
    ByteStream AltitudeAidControl::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream AltitudeAidControl::buildCommand_set(bool enable)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the enable/disable flag
        fieldData.append_uint8(static_cast<uint8>(enable));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    AltitudeAidControl::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse) :
        GenericMipCommand::Response(MipTypes::CMD_EF_ALTITUDE_AID_CTRL, collector, true, dataResponse, "Altitude Aid Control")
    {
    }

    bool AltitudeAidControl::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_singleBool(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Pitch/Roll Aid Control
    ByteStream PitchRollAidControl::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream PitchRollAidControl::buildCommand_set(bool enable)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the enable/disable flag
        fieldData.append_uint8(static_cast<uint8>(enable));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    PitchRollAidControl::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse) :
        GenericMipCommand::Response(MipTypes::CMD_EF_PITCH_ROLL_AID_CTRL, collector, true, dataResponse, "Pitch/Roll Aid Control")
    {
    }

    bool PitchRollAidControl::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_singleBool(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Velocity ZUPT Control
    ByteStream VelocityZUPTControl::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream VelocityZUPTControl::buildCommand_set(const ZUPTSettingsData& settingsData)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the enable/disable flag
        fieldData.append_uint8(static_cast<uint8>(settingsData.enabled));

        //add the threshold value
        fieldData.append_float(static_cast<float>(settingsData.threshold));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    VelocityZUPTControl::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse) :
        GenericMipCommand::Response(MipTypes::CMD_EF_ZERO_VEL_UPDATE_CTRL, collector, true, dataResponse, "Velocity ZUPT Control")
    {
    }

    ZUPTSettingsData VelocityZUPTControl::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_ZUPTControl(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Angular Rate ZUPT Control
    ByteStream AngularRateZUPTControl::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream AngularRateZUPTControl::buildCommand_set(const ZUPTSettingsData& settingsData)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the enable/disable flag
        fieldData.append_uint8(static_cast<uint8>(settingsData.enabled));

        //add the threshold value
        fieldData.append_float(static_cast<float>(settingsData.threshold));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    AngularRateZUPTControl::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse) :
        GenericMipCommand::Response(MipTypes::CMD_EF_ZERO_ANG_RATE_UPDATE_CTRL, collector, true, dataResponse, "Angular Rate ZUPT Control")
    {
    }

    ZUPTSettingsData AngularRateZUPTControl::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_ZUPTControl(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Tare Orientation

    ByteStream TareOrientation::buildCommand_set(const TareAxisValues& axisValue)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        fieldData.append_uint8(static_cast<uint8>(axisValue.asUint8()));

        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    TareOrientation::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse) :
        GenericMipCommand::Response(MipTypes::CMD_EF_TARE_ORIENT, collector, true, dataResponse, "Tare Orientation")
    {
    }

    bool TareOrientation::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_singleBool(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Commanded Velocity Zupt
    ByteStream CmdedVelZupt::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    CmdedVelZupt::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericMipCommand::Response(MipTypes::CMD_EF_CMDED_ZERO_VEL_UPDATE, collector, true, false, "Commanded Zero Velocity Update")
    {
    }
    //==========================================================================================

    //==========================================================================================
    //Commanded Angular Zupt
    ByteStream CmdedAngularZupt::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    CmdedAngularZupt::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse) :
        GenericMipCommand::Response(MipTypes::CMD_EF_CMDED_ZERO_ANG_RATE_UPDATE, collector, true, false, "Commanded Zero Angular Rate Update")
    {
    }
    //==========================================================================================

    //==========================================================================================
    //Sensor to Vehicle Frame Transformation
    ByteStream SensorToVehicFrameTrans::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream SensorToVehicFrameTrans::buildCommand_set(const EulerAngles& angles)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the roll, pitch, yaw data
        fieldData.append_float(angles.roll());
        fieldData.append_float(angles.pitch());
        fieldData.append_float(angles.yaw());

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    SensorToVehicFrameTrans::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericMipCommand::Response(MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_EULER, collector, true, dataResponse, "Sensor to Vehicle Frame Transformation")
    {
    }

    EulerAngles SensorToVehicFrameTrans::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_EulerAngles(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Sensor to Vehicle Frame Offset
    ByteStream SensorToVehicFrameOffset::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(MipTypes::CMD_EF_SENS_VEHIC_FRAME_OFFSET, fieldData.data());
    }

    ByteStream SensorToVehicFrameOffset::buildCommand_set(const PositionOffset& offset)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the x, y, z data
        fieldData.append_float(offset.x());
        fieldData.append_float(offset.y());
        fieldData.append_float(offset.z());

        //build and return the command bytes
        return GenericMipCommand::buildCommand(MipTypes::CMD_EF_SENS_VEHIC_FRAME_OFFSET, fieldData.data());
    }

    SensorToVehicFrameOffset::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericMipCommand::Response(MipTypes::CMD_EF_SENS_VEHIC_FRAME_OFFSET, collector, true, dataResponse, "Sensor to Vehicle Frame Offset")
    {
    }

    PositionOffset SensorToVehicFrameOffset::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_PositionOffset(response);
    }
    //==========================================================================================

    //==========================================================================================
    //Antenna Offset
    ByteStream AntennaOffset::buildCommand_get()
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::READ_BACK_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream AntennaOffset::buildCommand_set(const PositionOffset& offset)
    {
        //container to hold the command's field data
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::USE_NEW_SETTINGS));

        //add the x, y, z data
        fieldData.append_float(offset.x());
        fieldData.append_float(offset.y());
        fieldData.append_float(offset.z());

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    AntennaOffset::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
        GenericMipCommand::Response(MipTypes::CMD_EF_ANTENNA_OFFSET, collector, true, dataResponse, "Antenna Offset")
    {
    }

    PositionOffset AntennaOffset::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return MIP_Commands::parseData_PositionOffset(response);
    }
    //==========================================================================================
}