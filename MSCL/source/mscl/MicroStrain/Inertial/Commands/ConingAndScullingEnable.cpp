#include "stdafx.h"
#include "ConingAndScullingEnable.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    ConingAndScullingEnable::ConingAndScullingEnable(MipTypes::FunctionSelector function_selector, bool enable) :
        m_functionSelector(function_selector),
        m_enabled(enable)
    { }

    ConingAndScullingEnable::ConingAndScullingEnable(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    ConingAndScullingEnable ConingAndScullingEnable::MakeSetCommand(bool enable)
    {
        return ConingAndScullingEnable(MipTypes::USE_NEW_SETTINGS, enable);
    }

    ConingAndScullingEnable ConingAndScullingEnable::MakeGetCommand()
    {
        bool enabled = true;  // The data won't get used for a get command.
        return ConingAndScullingEnable(MipTypes::READ_BACK_CURRENT_SETTINGS, enabled);
    }

    bool ConingAndScullingEnable::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    bool ConingAndScullingEnable::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        bool enabled;
        enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED)? true : false;

        return enabled;
    }

    ConingAndScullingEnable::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            MipTypes::EnableSetting enableByte = m_enabled ? MipTypes::ENABLED : MipTypes::DISABLED;
            byteCommand.append_uint8(static_cast<uint8>(enableByte));
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}