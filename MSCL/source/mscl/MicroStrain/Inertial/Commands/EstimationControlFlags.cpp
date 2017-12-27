#include "stdafx.h"
#include "EstimationControlFlags.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    EstimationControlFlags::EstimationControlFlags(InertialTypes::FunctionSelector function_selector, const uint16& dataToUse) :
        m_functionSelector(function_selector),
        m_ControlFlags(dataToUse)
    { }

    EstimationControlFlags::EstimationControlFlags(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    EstimationControlFlags EstimationControlFlags::MakeSetCommand(const uint16& controlFlags)
    {
        return EstimationControlFlags(InertialTypes::USE_NEW_SETTINGS, controlFlags);
    }

    EstimationControlFlags EstimationControlFlags::MakeGetCommand()
    {
        uint16 controlFlags;  // The data won't get used for a get command.
        return EstimationControlFlags(InertialTypes::READ_BACK_CURRENT_SETTINGS, controlFlags);
    }

    bool EstimationControlFlags::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    uint16 EstimationControlFlags::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        uint16 returnData;
        returnData = dataBuffer.read_uint16();

        return returnData;
    }

    EstimationControlFlags::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint16(m_ControlFlags);
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data());
    }

}