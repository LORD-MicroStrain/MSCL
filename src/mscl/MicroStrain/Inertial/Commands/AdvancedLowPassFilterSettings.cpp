/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/AdvancedLowPassFilterSettings.h"

namespace mscl
{
    AdvancedLowPassFilterSettings::AdvancedLowPassFilterSettings(const MipTypes::FunctionSelector&  function_selector,
                                                                 const LowPassFilterData&        dataToUse) :
        m_functionSelector(function_selector),
        m_data(dataToUse)
    {}

    AdvancedLowPassFilterSettings::AdvancedLowPassFilterSettings(const MipTypes::FunctionSelector& function_selector,
                                                                 const MipTypes::ChannelField& descriptor) :
        m_functionSelector(function_selector),
        m_data(LowPassFilterData(descriptor))
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    AdvancedLowPassFilterSettings AdvancedLowPassFilterSettings::MakeSetCommand(const LowPassFilterData& dataToUse)
    {
        return AdvancedLowPassFilterSettings(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    AdvancedLowPassFilterSettings AdvancedLowPassFilterSettings::MakeGetCommand(const MipTypes::ChannelField& descriptor)
    {
        return AdvancedLowPassFilterSettings(MipTypes::READ_BACK_CURRENT_SETTINGS, descriptor);
    }

    bool AdvancedLowPassFilterSettings::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    LowPassFilterData AdvancedLowPassFilterSettings::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        LowPassFilterData returnData;
        returnData.dataDescriptor = LowPassFilterData::getDataDescriptorFromUint8(dataBuffer.read_uint8());
        returnData.applyLowPassFilter = dataBuffer.read_uint8() == 0x01;
        returnData.manualFilterBandwidthConfig = static_cast<LowPassFilterData::ManualFilterBandwidthConfig>(dataBuffer.read_uint8());
        returnData.cutoffFrequency = dataBuffer.read_uint16();
        return returnData;
    }

    AdvancedLowPassFilterSettings::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));
        byteCommand.append_uint8(LowPassFilterData::getDataDescriptorForCommand(m_data.dataDescriptor));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            MipTypes::EnableSetting applyLowPassFilter = m_data.applyLowPassFilter ? MipTypes::ENABLED : MipTypes::DISABLED;
            uint16 freq = m_data.manualFilterBandwidthConfig == LowPassFilterData::USER_SPECIFIED_CUTOFF_FREQ ? static_cast<uint16>(m_data.cutoffFrequency) : 0x0000;

            byteCommand.append_uint8(static_cast<uint8>(applyLowPassFilter));
            byteCommand.append_uint8(static_cast<uint8>(m_data.manualFilterBandwidthConfig));
            byteCommand.append_uint16(static_cast<uint16>(freq));
            byteCommand.append_uint8(0x00);
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
} // namespace mscl
