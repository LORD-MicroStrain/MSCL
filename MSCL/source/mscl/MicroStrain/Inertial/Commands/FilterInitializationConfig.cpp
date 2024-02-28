/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "FilterInitializationConfig.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    FilterInitializationConfig::FilterInitializationConfig(MipTypes::FunctionSelector function_selector, const FilterInitializationValues& dataToUse) :
        m_functionSelector(function_selector),
        m_data(dataToUse)
    { }

    FilterInitializationConfig::FilterInitializationConfig(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    std::string FilterInitializationConfig::commandName() const
    {
        return "FilterInitializationConfig";
    }

    FilterInitializationConfig FilterInitializationConfig::MakeSetCommand(const FilterInitializationValues& data)
    {
        return FilterInitializationConfig(MipTypes::USE_NEW_SETTINGS, data);
    }

    FilterInitializationConfig FilterInitializationConfig::MakeGetCommand()
    {
        return FilterInitializationConfig(MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    bool FilterInitializationConfig::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    FilterInitializationValues FilterInitializationConfig::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer buffer(response.data());
        FilterInitializationValues data;

		data.autoInitialize = !(buffer.read_uint8() > 0);
        data.initialValuesSource = static_cast<FilterInitialValuesSource>(buffer.read_uint8());
        data.autoHeadingAlignmentMethod = HeadingAlignmentMethod(buffer.read_uint8());

        float heading = buffer.read_float();
        float pitch = buffer.read_float();
        float roll = buffer.read_float();
        data.initialAttitude = EulerAngles(roll, pitch, heading);

        double posX = buffer.read_float();
        double posY = buffer.read_float();
        double posZ = buffer.read_float();

        float velX = buffer.read_float();
        float velY = buffer.read_float();
        float velZ = buffer.read_float();

        data.referenceFrame = static_cast<PositionVelocityReferenceFrame>(buffer.read_uint8());
        data.initialPosition = Position(posX, posY, posZ, data.referenceFrame);
        data.initialVelocity = GeometricVector(velX, velY, velZ, data.referenceFrame);

        return data;
    }

    FilterInitializationConfig::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
			byteCommand.append_uint8(!m_data.autoInitialize);
            byteCommand.append_uint8(static_cast<uint8>(m_data.initialValuesSource));
            byteCommand.append_uint8(m_data.autoHeadingAlignmentMethod.value);
            byteCommand.append_float(m_data.initialAttitude.heading());
            byteCommand.append_float(m_data.initialAttitude.pitch());
            byteCommand.append_float(m_data.initialAttitude.roll());
            byteCommand.append_float(static_cast<float>(m_data.initialPosition.latitude()));
            byteCommand.append_float(static_cast<float>(m_data.initialPosition.longitude()));
            byteCommand.append_float(static_cast<float>(m_data.initialPosition.altitude()));
            byteCommand.append_float(m_data.initialVelocity.north());
            byteCommand.append_float(m_data.initialVelocity.east());
            byteCommand.append_float(m_data.initialVelocity.down());
            byteCommand.append_uint8(static_cast<uint8>(m_data.referenceFrame));
        }

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
}
