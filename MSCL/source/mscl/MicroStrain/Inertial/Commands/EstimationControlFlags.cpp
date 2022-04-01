/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "EstimationControlFlags.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    EstimationControlFlags::EstimationControlFlags(MipTypes::FunctionSelector function_selector, const uint16& dataToUse) :
        m_functionSelector(function_selector),
        m_ControlFlags(dataToUse)
    { }

    EstimationControlFlags::EstimationControlFlags(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    EstimationControlFlags EstimationControlFlags::MakeSetCommand(const uint16& controlFlags)
    {
        return EstimationControlFlags(MipTypes::USE_NEW_SETTINGS, controlFlags);
    }

    EstimationControlFlags EstimationControlFlags::MakeGetCommand()
    {
        uint16 controlFlags;  // The data won't get used for a get command.
        return EstimationControlFlags(MipTypes::READ_BACK_CURRENT_SETTINGS, controlFlags);
    }

    bool EstimationControlFlags::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    EstimationControlOptions EstimationControlFlags::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        uint16 returnData;
        returnData = dataBuffer.read_uint16();

        return EstimationControlOptions(returnData);
    }

    EstimationControlFlags::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint16(m_ControlFlags);
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}