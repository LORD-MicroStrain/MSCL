/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/HeadingUpdateControl.h"

namespace mscl
{
    HeadingUpdateControl::HeadingUpdateControl(MipTypes::FunctionSelector function_selector, const HeadingUpdateOptions& headingUpdateOptions) :
        m_functionSelector(function_selector),
        m_HeadingUpdateOptions(headingUpdateOptions)
    {}

    HeadingUpdateControl::HeadingUpdateControl(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    HeadingUpdateControl HeadingUpdateControl::MakeSetCommand(const HeadingUpdateOptions& dataToUse)
    {
        return HeadingUpdateControl(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    HeadingUpdateControl HeadingUpdateControl::MakeGetCommand()
    {
        HeadingUpdateOptions headingUpdateOptions;  // The data won't get used for a get command.
        return HeadingUpdateControl(MipTypes::READ_BACK_CURRENT_SETTINGS, headingUpdateOptions);
    }

    bool HeadingUpdateControl::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    HeadingUpdateOptions HeadingUpdateControl::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        HeadingUpdateOptions headingUpdateOptions (static_cast<InertialTypes::HeadingUpdateEnableOption>(dataBuffer.read_uint8()));

        return headingUpdateOptions;
    }

    HeadingUpdateControl::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint8(static_cast<uint8>(m_HeadingUpdateOptions.AsOptionId()));
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
} // namespace mscl
