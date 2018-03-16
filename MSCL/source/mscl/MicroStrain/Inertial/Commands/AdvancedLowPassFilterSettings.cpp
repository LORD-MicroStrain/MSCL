#include "stdafx.h"
#include "AdvancedLowPassFilterSettings.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    AdvancedLowPassFilterSettings::AdvancedLowPassFilterSettings(const MipTypes::FunctionSelector&  function_selector,
                                                                 const AdvancedLowPassFilterData&        dataToUse) :
        m_functionSelector(function_selector),
        m_data(dataToUse)
    { }

    AdvancedLowPassFilterSettings::AdvancedLowPassFilterSettings(const MipTypes::FunctionSelector& function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    AdvancedLowPassFilterSettings AdvancedLowPassFilterSettings::MakeSetCommand(const AdvancedLowPassFilterData& dataToUse)
    {
        return AdvancedLowPassFilterSettings(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    AdvancedLowPassFilterSettings AdvancedLowPassFilterSettings::MakeGetCommand(const AdvancedLowPassFilterData& dataToUse)
    {
        return AdvancedLowPassFilterSettings(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool AdvancedLowPassFilterSettings::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    AdvancedLowPassFilterData AdvancedLowPassFilterSettings::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        AdvancedLowPassFilterData returnData;
        returnData.dataDescriptor = static_cast<AdvancedLowPassFilterData::DataDescriptor>(dataBuffer.read_uint8());
        returnData.applyLowPassFilter = (dataBuffer.read_uint8() == 0x01)? true : false;
        returnData.manualFilterBandwidthConfig = static_cast<AdvancedLowPassFilterData::ManualFilterBandwidthConfig>(dataBuffer.read_uint8());
        returnData.cutoffFrequency = dataBuffer.read_uint16();
        return returnData;
    }

    AdvancedLowPassFilterSettings::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));
        byteCommand.append_uint8(static_cast<uint8>(m_data.dataDescriptor));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            MipTypes::EnableSetting applyLowPassFilter = m_data.applyLowPassFilter ? MipTypes::ENABLED : MipTypes::DISABLED;
            byteCommand.append_uint8(static_cast<uint8>(applyLowPassFilter));
            byteCommand.append_uint8(static_cast<uint8>(m_data.manualFilterBandwidthConfig));
            byteCommand.append_uint16(static_cast<uint16>(m_data.cutoffFrequency));
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}