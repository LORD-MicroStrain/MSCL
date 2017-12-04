#include "stdafx.h"
#include "GNSS_SourceControl.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    GNSS_SourceControl::GNSS_SourceControl(InertialTypes::FunctionSelector function_selector, const GNSS_Source& gnssSource) :
        m_functionSelector(function_selector),
        m_gnssSource(gnssSource)
    { }

    GNSS_SourceControl::GNSS_SourceControl(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    GNSS_SourceControl GNSS_SourceControl::MakeSetCommand(const GNSS_Source& gnssSource)
    {
        return GNSS_SourceControl(InertialTypes::USE_NEW_SETTINGS, gnssSource);
    }

    GNSS_SourceControl GNSS_SourceControl::MakeGetCommand()
    {
        GNSS_Source gnssSource;  // The data won't get used for a get command.
        return GNSS_SourceControl(InertialTypes::READ_BACK_CURRENT_SETTINGS, gnssSource);
    }

    bool GNSS_SourceControl::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    GNSS_Source GNSS_SourceControl::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        GNSS_Source returnData;
        returnData = static_cast<GNSS_Source>(dataBuffer.read_uint8());

        return returnData;
    }

    GNSS_SourceControl::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint8(static_cast<uint8>(m_gnssSource));
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data());
    }

}