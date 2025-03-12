/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/Uint16Command.h"

namespace mscl
{
    Uint16Command::Uint16Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector, const std::vector<uint16>& dataToUse) :
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

    Uint16Command::Uint16Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector) :
        m_cmd(cmd),
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    std::string Uint16Command::commandName() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_ENABLE_DISABLE_MEASUREMENTS:
            return "EnableDisableMeasurements";
        default:
            return "";
        }
    }

    uint8 Uint16Command::fieldDataByte() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_ENABLE_DISABLE_MEASUREMENTS:
            return 0xB0;
        default:
            return 0;
        }
    }

    Uint16Command Uint16Command::MakeSetCommand(MipTypes::Command cmd, const std::vector<uint16>& data)
    {
        return Uint16Command(cmd, MipTypes::USE_NEW_SETTINGS, data);
    }

    Uint16Command Uint16Command::MakeGetCommand(MipTypes::Command cmd)
    {
        return Uint16Command(cmd, MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    Uint16Command Uint16Command::MakeGetCommand(MipTypes::Command cmd, const std::vector<uint16>& addlParams)
    {
        return Uint16Command(cmd, MipTypes::READ_BACK_CURRENT_SETTINGS, addlParams);
    }

    bool Uint16Command::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    std::vector<uint16> Uint16Command::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer buffer(response.data());
        std::vector<uint16> data;

        int dataPointCount = 1;

        for (int i = 0; i < dataPointCount; i++)
        {
            uint16 point = buffer.read_uint16();
            data.push_back(point);
        }

        return data;
    }

    Uint16Command::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            for (size_t i = 0; i < m_data.size(); i++)
            {
                byteCommand.append_uint16(m_data[i]);
            }
        }
        else
        {
            for (size_t i = 0; i < m_addlParams.size(); i++)
            {
                byteCommand.append_uint16(m_addlParams[i]);
            }
        }

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
}
