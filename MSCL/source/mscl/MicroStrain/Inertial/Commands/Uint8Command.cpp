/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/Uint8Command.h"

namespace mscl
{
    Uint8Command::Uint8Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector, const std::vector<uint8>& dataToUse) :
        m_cmd(cmd),
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
        {
            m_data = dataToUse;
        }
        else
        {
            m_addlParams = dataToUse;
        }
    }

    Uint8Command::Uint8Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector) :
        m_cmd(cmd),
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    std::string Uint8Command::commandName() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_GPS_DYNAMICS_MODE:
            return "GPSDynamicsMode";
        case MipTypes::Command::CMD_DATA_STREAM_FORMAT:
            return "DeviceDataStreamFormat";
        case MipTypes::Command::CMD_POWER_STATES:
            return "DevicePowerStates";
        default:
            return "";
        }
    }

    uint8 Uint8Command::fieldDataByte() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_GPS_DYNAMICS_MODE:
            return 0x92;
        case MipTypes::Command::CMD_DATA_STREAM_FORMAT:
            return 0x88;
        case MipTypes::Command::CMD_POWER_STATES:
            return 0x89;
        default:
            return 0;
        }
    }

    Uint8Command Uint8Command::MakeSetCommand(MipTypes::Command cmd, const std::vector<uint8>& data)
    {
        return Uint8Command(cmd, MipTypes::USE_NEW_SETTINGS, data);
    }

    Uint8Command Uint8Command::MakeGetCommand(MipTypes::Command cmd)
    {
        return Uint8Command(cmd, MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    Uint8Command Uint8Command::MakeGetCommand(MipTypes::Command cmd, const std::vector<uint8>& addlParams)
    {
        return Uint8Command(cmd, MipTypes::READ_BACK_CURRENT_SETTINGS, addlParams);
    }

    bool Uint8Command::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    std::vector<uint8> Uint8Command::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer buffer(response.data());
        std::vector<uint8> data;

        int dataPointCount = 1;

        for (int i = 0; i < dataPointCount; i++)
        {
            uint8 point = buffer.read_uint8();
            data.push_back(point);
        }

        return data;
    }

    Uint8Command::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            for (size_t i = 0; i < m_data.size(); i++)
            {
                byteCommand.append_uint8(m_data[i]);
            }
        }
        else
        {
            for (size_t i = 0; i < m_addlParams.size(); i++)
            {
                byteCommand.append_uint8(m_addlParams[i]);
            }
        }

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
} // namespace mscl
