#include "stdafx.h"
#include "HeadingUpdateControl.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    HeadingUpdateControl::HeadingUpdateControl(InertialTypes::FunctionSelector function_selector, const HeadingUpdateOptions& headingUpdateOptions) :
        m_functionSelector(function_selector),
        m_HeadingUpdateOptions(headingUpdateOptions)
    { }

    HeadingUpdateControl::HeadingUpdateControl(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    HeadingUpdateControl HeadingUpdateControl::MakeSetCommand(const HeadingUpdateOptions& dataToUse)
    {
        return HeadingUpdateControl(InertialTypes::USE_NEW_SETTINGS, dataToUse);
    }

    HeadingUpdateControl HeadingUpdateControl::MakeGetCommand()
    {
        HeadingUpdateOptions headingUpdateOptions;  // The data won't get used for a get command.
        return HeadingUpdateControl(InertialTypes::READ_BACK_CURRENT_SETTINGS, headingUpdateOptions);
    }

    bool HeadingUpdateControl::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    HeadingUpdateOptions HeadingUpdateControl::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        HeadingUpdateOptions headingUpdateOptions (dataBuffer.read_uint8());

        return headingUpdateOptions;
    }

    HeadingUpdateControl::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint8(m_HeadingUpdateOptions.AsUint8());
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data());
    }

}