/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "GNSS_SourceControl.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    GNSS_SourceControl::GNSS_SourceControl(MipTypes::FunctionSelector function_selector, const InertialTypes::GNSS_Source& gnssSource) :
        m_functionSelector(function_selector),
        m_gnssSource(gnssSource)
    { }

    GNSS_SourceControl::GNSS_SourceControl(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    GNSS_SourceControl GNSS_SourceControl::MakeSetCommand(const InertialTypes::GNSS_Source& gnssSource)
    {
        return GNSS_SourceControl(MipTypes::USE_NEW_SETTINGS, gnssSource);
    }

    GNSS_SourceControl GNSS_SourceControl::MakeGetCommand()
    {
        InertialTypes::GNSS_Source gnssSource;  // The data won't get used for a get command.
        return GNSS_SourceControl(MipTypes::READ_BACK_CURRENT_SETTINGS, gnssSource);
    }

    bool GNSS_SourceControl::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    InertialTypes::GNSS_Source GNSS_SourceControl::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        InertialTypes::GNSS_Source returnData;
        returnData = static_cast<InertialTypes::GNSS_Source>(dataBuffer.read_uint8());

        return returnData;
    }

    GNSS_SourceControl::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint8(static_cast<uint8>(m_gnssSource));
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}