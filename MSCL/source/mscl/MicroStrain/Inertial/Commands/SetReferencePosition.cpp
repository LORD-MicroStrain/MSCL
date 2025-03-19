/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/SetReferencePosition.h"

namespace mscl
{
    SetReferencePosition::SetReferencePosition(MipTypes::FunctionSelector function_selector, FixedReferencePositionData data) :
        m_functionSelector(function_selector),
        m_data(data)
    {}

    SetReferencePosition::SetReferencePosition(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    SetReferencePosition SetReferencePosition::MakeSetCommand(FixedReferencePositionData data)
    {
        return SetReferencePosition(MipTypes::USE_NEW_SETTINGS, data);
    }

    SetReferencePosition SetReferencePosition::MakeGetCommand()
    {
        return SetReferencePosition(MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    bool SetReferencePosition::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    FixedReferencePositionData SetReferencePosition::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        bool enabled;
        enabled = dataBuffer.read_uint8() == MipTypes::ENABLED;
        Position reference;
        reference.latitude(dataBuffer.read_double());
        reference.longitude(dataBuffer.read_double());
        reference.altitude(dataBuffer.read_double());

        FixedReferencePositionData data(enabled, reference);

        return data;
    }

    SetReferencePosition::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            MipTypes::EnableSetting enableByte = m_data.enable ? MipTypes::ENABLED : MipTypes::DISABLED;
            byteCommand.append_uint8(static_cast<uint8>(enableByte));
            byteCommand.append_double(m_data.referencePosition.latitude());
            byteCommand.append_double(m_data.referencePosition.longitude());
            byteCommand.append_double(m_data.referencePosition.altitude());
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
} // namespace mscl
