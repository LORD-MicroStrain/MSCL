/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/GeometricVectorCommand.h"

namespace mscl
{
    GeometricVectorCommand::GeometricVectorCommand(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector, const GeometricVectors& dataToUse) :
        m_cmd(cmd),
        m_functionSelector(function_selector),
        m_data(dataToUse)
    {}

    GeometricVectorCommand::GeometricVectorCommand(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector) :
        m_cmd(cmd),
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    std::string GeometricVectorCommand::commandName() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_MAG_NOISE_STD_DEV:
            return "MagnetometerNoiseStandardDeviation";
        case MipTypes::Command::CMD_EF_GRAVITY_NOISE_STD_DEV:
            return "GravityNoiseStandardDeviation";
        case MipTypes::Command::CMD_EF_ACCEL_WHT_NSE_STD_DEV:
            return "AccelerometerNoiseStandardDeviation";
        case MipTypes::Command::CMD_EF_GYRO_WHT_NSE_STD_DEV:
            return "GyroscopeNoiseStandardDeviation";
        case MipTypes::Command::CMD_EF_HARD_IRON_OFFSET_PROCESS_NOISE:
            return "HardIronOffsetProcessNoise";
        case MipTypes::Command::CMD_EF_ACCEL_BIAS_MODEL_PARAMS:
            return "AccelerometerBiasModelParameters";
        case MipTypes::Command::CMD_EF_GYRO_BIAS_MODEL_PARAMS:
            return "GyroscopeBiasModelParameters";
        case MipTypes::Command::CMD_EF_GRAVITY_NOISE_MINIMUM:
            return "GravityNoiseMinimum";
        default:
            return "";
        }
    }

    uint8 GeometricVectorCommand::fieldDataByte() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_MAG_NOISE_STD_DEV:
            return 0xB1;
        case MipTypes::Command::CMD_EF_GRAVITY_NOISE_STD_DEV:
            return 0x93;
        case MipTypes::Command::CMD_EF_ACCEL_WHT_NSE_STD_DEV:
            return 0x89;
        case MipTypes::Command::CMD_EF_GYRO_WHT_NSE_STD_DEV:
            return 0x8A;
        case MipTypes::Command::CMD_EF_HARD_IRON_OFFSET_PROCESS_NOISE:
            return 0x96;
        case MipTypes::Command::CMD_EF_ACCEL_BIAS_MODEL_PARAMS:
            return 0x8B;
        case MipTypes::Command::CMD_EF_GYRO_BIAS_MODEL_PARAMS:
            return 0x8C;
        case MipTypes::Command::CMD_EF_GRAVITY_NOISE_MINIMUM:
            return 0x95;
        default:
            return 0;
        }
    }

    GeometricVectorCommand GeometricVectorCommand::MakeSetCommand(MipTypes::Command cmd, const GeometricVectors& data)
    {
        return GeometricVectorCommand(cmd, MipTypes::USE_NEW_SETTINGS, data);
    }

    GeometricVectorCommand GeometricVectorCommand::MakeGetCommand(MipTypes::Command cmd)
    {
        return GeometricVectorCommand(cmd, MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    bool GeometricVectorCommand::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    GeometricVectors GeometricVectorCommand::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer buffer(response.data());
        GeometricVectors data;

        int dataPointCount = 1;
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_ACCEL_BIAS_MODEL_PARAMS:
        case MipTypes::Command::CMD_EF_GYRO_BIAS_MODEL_PARAMS:
            dataPointCount = 2;
            break;
        default:
            break;
        }

        for (int i = 0; i < dataPointCount; i++)
        {
            GeometricVector point;
            point.x(buffer.read_float());
            point.y(buffer.read_float());
            point.z(buffer.read_float());
            data.push_back(point);
        }

        return data;
    }

    GeometricVectorCommand::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            for (size_t i = 0; i < m_data.size(); i++)
            {
                byteCommand.append_float(m_data[i].x());
                byteCommand.append_float(m_data[i].y());
                byteCommand.append_float(m_data[i].z());
            }
        }

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
} // namespace mscl
