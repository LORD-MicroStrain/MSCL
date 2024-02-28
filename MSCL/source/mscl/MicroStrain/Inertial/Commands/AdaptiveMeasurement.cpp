/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "AdaptiveMeasurement.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    AdaptiveMeasurement::AdaptiveMeasurement(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector, const AdaptiveMeasurementData& dataToUse) :
        m_cmd(cmd),
        m_functionSelector(function_selector),
        m_data(dataToUse)
    { }

    AdaptiveMeasurement::AdaptiveMeasurement(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector) :
        m_cmd(cmd),
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    std::string AdaptiveMeasurement::commandName() const
    {
        switch (m_cmd)
        {
            case MipTypes::Command::CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE:
                return "GravityMagnitudeErrorAdaptiveMeasurement";
            case MipTypes::Command::CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE:
                return "MagnetometerMagnitudeErrorAdaptiveMeasurement";
            case MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE:
                return "MagnetometerDipAngleErrorAdaptiveMeasurement";
            default:
                return "";
        }
    }

    uint8 AdaptiveMeasurement::fieldDataByte() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE:
            return 0xB3;
        case MipTypes::Command::CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE:
            return 0xB4;
        case MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE:
            return 0xB5;
        default:
            return 0;
        }
    }

    AdaptiveMeasurement AdaptiveMeasurement::MakeSetCommand(MipTypes::Command cmd, const AdaptiveMeasurementData& data)
    {
        return AdaptiveMeasurement(cmd, MipTypes::USE_NEW_SETTINGS, data);
    }

    AdaptiveMeasurement AdaptiveMeasurement::MakeGetCommand(MipTypes::Command cmd)
    {
        return AdaptiveMeasurement(cmd, MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    bool AdaptiveMeasurement::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    AdaptiveMeasurementData AdaptiveMeasurement::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer buffer(response.data());
        AdaptiveMeasurementData data;
        data.mode = static_cast<InertialTypes::AdaptiveMeasurementMode>(buffer.read_uint8());
        data.lowPassFilterCutoff = buffer.read_float();
        if (m_cmd != MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE)
        {
            data.lowLimit = buffer.read_float();
        }

        data.highLimit = buffer.read_float();
        if (m_cmd != MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE)
        {
            data.lowLimitUncertainty = buffer.read_float();
        }

        data.highLimitUncertainty = buffer.read_float();
        data.minUncertainty = buffer.read_float();

        return data;
    }

    AdaptiveMeasurement::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint8(static_cast<uint8>(m_data.mode));
            if (m_data.mode == InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_ENABLE_FIXED)
            {
                byteCommand.append_float(m_data.lowPassFilterCutoff);
                if (m_cmd != MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE)
                {
                    byteCommand.append_float(m_data.lowLimit);
                }

                byteCommand.append_float(m_data.highLimit);
                if (m_cmd != MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE)
                {
                    byteCommand.append_float(m_data.lowLimitUncertainty);
                }

                byteCommand.append_float(m_data.highLimitUncertainty);
                byteCommand.append_float(m_data.minUncertainty);
            }
        }

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
}
