/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/SignalConditioningSettings.h"

namespace mscl
{
    SignalConditioningSettings::SignalConditioningSettings(MipTypes::FunctionSelector function_selector, const SignalConditioningValues& dataToUse) :
        m_functionSelector(function_selector),
        m_data(dataToUse)
    {}

    SignalConditioningSettings::SignalConditioningSettings(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    SignalConditioningSettings SignalConditioningSettings::MakeSetCommand(const SignalConditioningValues& data)
    {
        return SignalConditioningSettings(MipTypes::USE_NEW_SETTINGS, data);
    }

    SignalConditioningSettings SignalConditioningSettings::MakeGetCommand()
    {
        return SignalConditioningSettings(MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    bool SignalConditioningSettings::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    SignalConditioningValues SignalConditioningSettings::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer buffer(response.data());
        SignalConditioningValues data;

        data.orientationCalcDecimation = buffer.read_uint16();
        data.dataConditioningFlags = buffer.read_uint16();
        data.accelGyroFilterWidth = buffer.read_uint8();
        data.magFilterWidth = buffer.read_uint8();
        data.upCompensation = buffer.read_uint16();
        data.northCompensation = buffer.read_uint16();
        data.magBandwidthPower = static_cast<SignalConditioningValues::MagPowerBandwidthSettings>(buffer.read_uint8());

        return data;
    }

    SignalConditioningSettings::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint16(m_data.orientationCalcDecimation);
            byteCommand.append_uint16(m_data.dataConditioningFlags);
            byteCommand.append_uint8(m_data.accelGyroFilterWidth);
            byteCommand.append_uint8(m_data.magFilterWidth);
            byteCommand.append_uint16(m_data.upCompensation);
            byteCommand.append_uint16(m_data.northCompensation);
            byteCommand.append_uint8(static_cast<uint8>(m_data.magBandwidthPower));
            byteCommand.append_uint16(0x0000); //reserved
        }

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
} // namespace mscl
