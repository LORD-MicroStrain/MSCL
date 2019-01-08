#include "stdafx.h"
#include "FloatCommand.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    FloatCommand::FloatCommand(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector, const std::vector<float>& dataToUse) :
        m_cmd(cmd),
        m_functionSelector(function_selector),
        m_data(dataToUse)
    { }

    FloatCommand::FloatCommand(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector) :
        m_cmd(cmd),
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    std::string FloatCommand::commandName() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_PRESS_ALT_NOISE_STD_DEV:
            return "PressureAltitudeNoiseStandardDeviation";
        default:
            return "";
        }
    }

    uint8 FloatCommand::fieldDataByte() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_PRESS_ALT_NOISE_STD_DEV:
            return 0x94;
        default:
            return 0;
        }
    }

    FloatCommand FloatCommand::MakeSetCommand(MipTypes::Command cmd, const std::vector<float>& data)
    {
        return FloatCommand(cmd, MipTypes::USE_NEW_SETTINGS, data);
    }

    FloatCommand FloatCommand::MakeGetCommand(MipTypes::Command cmd)
    {
        return FloatCommand(cmd, MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    bool FloatCommand::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    std::vector<float> FloatCommand::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer buffer(response.data());
        std::vector<float> data;

        int dataPointCount = 1;

        for (int i = 0; i < dataPointCount; i++)
        {
            float point = buffer.read_float();
            data.push_back(point);
        }

        return data;
    }

    FloatCommand::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            for (size_t i = 0; i < m_data.size(); i++)
            {
                byteCommand.append_float(m_data[i]);
            }
        }

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
}