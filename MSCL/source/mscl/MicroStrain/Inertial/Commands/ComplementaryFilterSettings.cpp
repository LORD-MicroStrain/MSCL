/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "ComplementaryFilterSettings.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    ComplementaryFilterSettings::ComplementaryFilterSettings(MipTypes::FunctionSelector function_selector, ComplementaryFilterData dataToUse) :
        m_functionSelector(function_selector),
        m_data(dataToUse)
    { }

    ComplementaryFilterSettings::ComplementaryFilterSettings(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    ComplementaryFilterSettings ComplementaryFilterSettings::MakeSetCommand(const ComplementaryFilterData& dataToUse)
    {
        return ComplementaryFilterSettings(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    ComplementaryFilterSettings ComplementaryFilterSettings::MakeGetCommand()
    {
        ComplementaryFilterData dataToUse;  // The data won't get used for a get command.
        return ComplementaryFilterSettings(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool ComplementaryFilterSettings::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    ComplementaryFilterData ComplementaryFilterSettings::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        ComplementaryFilterData returnData;
        returnData.upCompensationEnabled = (dataBuffer.read_uint8() == MipTypes::ENABLED) ? true : false;
        returnData.northCompensationEnabled = (dataBuffer.read_uint8() == MipTypes::ENABLED) ? true : false;
        returnData.upCompensationTimeInSeconds = dataBuffer.read_float();
        returnData.northCompensationTimeInSeconds = dataBuffer.read_float();

        return returnData;
    }

    ComplementaryFilterSettings::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            MipTypes::EnableSetting upCompEnabled = m_data.upCompensationEnabled ? MipTypes::ENABLED : MipTypes::DISABLED;
            byteCommand.append_uint8(static_cast<uint8>(upCompEnabled));
            MipTypes::EnableSetting northCompEnabled = m_data.northCompensationEnabled ? MipTypes::ENABLED : MipTypes::DISABLED;
            byteCommand.append_uint8(static_cast<uint8>(northCompEnabled));
            byteCommand.append_float(m_data.upCompensationTimeInSeconds);
            byteCommand.append_float(m_data.northCompensationTimeInSeconds);
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}
