#include "stdafx.h"
#include "ComplementaryFilterSettings.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    ComplementaryFilterSettings::ComplementaryFilterSettings(InertialTypes::FunctionSelector function_selector, ComplementaryFilterData dataToUse) :
        m_functionSelector(function_selector),
        m_data(dataToUse)
    { }

    ComplementaryFilterSettings::ComplementaryFilterSettings(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    ComplementaryFilterSettings ComplementaryFilterSettings::MakeSetCommand(const ComplementaryFilterData& dataToUse)
    {
        return ComplementaryFilterSettings(InertialTypes::USE_NEW_SETTINGS, dataToUse);
    }

    ComplementaryFilterSettings ComplementaryFilterSettings::MakeGetCommand()
    {
        ComplementaryFilterData dataToUse;  // The data won't get used for a get command.
        return ComplementaryFilterSettings(InertialTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool ComplementaryFilterSettings::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    ComplementaryFilterData ComplementaryFilterSettings::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        ComplementaryFilterData returnData;
        returnData.upCompensationEnabled = (dataBuffer.read_uint8() == InertialTypes::ENABLED) ? true : false;
        returnData.northCompensationEnabled = (dataBuffer.read_uint8() == InertialTypes::ENABLED) ? true : false;
        returnData.upCompensationTimeInSeconds = dataBuffer.read_float();
        returnData.northCompensationTimeInSeconds = dataBuffer.read_float();

        return returnData;
    }

    ComplementaryFilterSettings::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            InertialTypes::EnableSetting upCompEnabled = m_data.upCompensationEnabled ? InertialTypes::ENABLED : InertialTypes::DISABLED;
            byteCommand.append_uint8(static_cast<uint8>(upCompEnabled));
            InertialTypes::EnableSetting northCompEnabled = m_data.northCompensationEnabled ? InertialTypes::ENABLED : InertialTypes::DISABLED;
            byteCommand.append_uint8(static_cast<uint8>(northCompEnabled));
            byteCommand.append_float(m_data.upCompensationTimeInSeconds);
            byteCommand.append_float(m_data.northCompensationTimeInSeconds);
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data());
    }

}