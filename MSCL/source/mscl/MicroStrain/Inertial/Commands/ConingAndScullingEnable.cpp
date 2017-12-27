#include "stdafx.h"
#include "ConingAndScullingEnable.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    ConingAndScullingEnable::ConingAndScullingEnable(InertialTypes::FunctionSelector function_selector, bool enable) :
        m_functionSelector(function_selector),
        m_enabled(enable)
    { }

    ConingAndScullingEnable::ConingAndScullingEnable(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    ConingAndScullingEnable ConingAndScullingEnable::MakeSetCommand(bool enable)
    {
        return ConingAndScullingEnable(InertialTypes::USE_NEW_SETTINGS, enable);
    }

    ConingAndScullingEnable ConingAndScullingEnable::MakeGetCommand()
    {
        bool enabled = true;  // The data won't get used for a get command.
        return ConingAndScullingEnable(InertialTypes::READ_BACK_CURRENT_SETTINGS, enabled);
    }

    bool ConingAndScullingEnable::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    bool ConingAndScullingEnable::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        bool enabled;
        enabled = (dataBuffer.read_uint8() == InertialTypes::ENABLED)? true : false;

        return enabled;
    }

    ConingAndScullingEnable::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            InertialTypes::EnableSetting enableByte = m_enabled ? InertialTypes::ENABLED : InertialTypes::DISABLED;
            byteCommand.append_uint8(static_cast<uint8>(enableByte));
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data());
    }

}