#include "stdafx.h"
#include "AdvancedLowPassFilterSettings.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    AdvancedLowPassFilterSettings::AdvancedLowPassFilterSettings(const InertialTypes::FunctionSelector&  function_selector,
                                                                 const AdvancedLowPassFilterData&        dataToUse) :
        m_functionSelector(function_selector),
        m_data(dataToUse)
    { }

    AdvancedLowPassFilterSettings::AdvancedLowPassFilterSettings(const InertialTypes::FunctionSelector& function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    AdvancedLowPassFilterSettings AdvancedLowPassFilterSettings::MakeSetCommand(const AdvancedLowPassFilterData& dataToUse)
    {
        return AdvancedLowPassFilterSettings(InertialTypes::USE_NEW_SETTINGS, dataToUse);
    }

    AdvancedLowPassFilterSettings AdvancedLowPassFilterSettings::MakeGetCommand(const AdvancedLowPassFilterData& dataToUse)
    {
        return AdvancedLowPassFilterSettings(InertialTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool AdvancedLowPassFilterSettings::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    AdvancedLowPassFilterData AdvancedLowPassFilterSettings::getResponseData(const GenericInertialCommandResponse& response)
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
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            InertialTypes::EnableSetting applyLowPassFilter = m_data.applyLowPassFilter ? InertialTypes::ENABLED : InertialTypes::DISABLED;
            byteCommand.append_uint8(static_cast<uint8>(applyLowPassFilter));
            byteCommand.append_uint8(static_cast<uint8>(m_data.manualFilterBandwidthConfig));
            byteCommand.append_uint16(static_cast<uint16>(m_data.cutoffFrequency));
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}