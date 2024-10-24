/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "GNSS_ConstellationSettings.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    GNSS_ConstellationSettings::GNSS_ConstellationSettings(MipTypes::FunctionSelector function_selector, ConstellationSettingsData dataToUse) :
        m_functionSelector(function_selector),
        m_data(dataToUse)
    { }

    GNSS_ConstellationSettings::GNSS_ConstellationSettings(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    GNSS_ConstellationSettings GNSS_ConstellationSettings::MakeSetCommand(ConstellationSettingsData dataToUse)
    {
        return GNSS_ConstellationSettings(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    GNSS_ConstellationSettings GNSS_ConstellationSettings::MakeGetCommand()
    {
        return GNSS_ConstellationSettings(MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    GNSS_ConstellationSettings GNSS_ConstellationSettings::MakeResetToDefaultCommand()
    {
        return GNSS_ConstellationSettings(MipTypes::RESET_TO_DEFAULT);
    }

    bool GNSS_ConstellationSettings::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    ConstellationSettingsData GNSS_ConstellationSettings::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        ConstellationSettingsData returnData;
        returnData.maxChannelsAvailable = dataBuffer.read_uint16();
        returnData.maxChannelsToUse = dataBuffer.read_uint16();
        uint8 numberOfConstellations = dataBuffer.read_uint8();
        for (uint8 constellationNum = 0; constellationNum < numberOfConstellations; ++constellationNum)
        {
            Constellation constellationToAdd;
            constellationToAdd.constellationID = static_cast<InertialTypes::ConstellationId>(dataBuffer.read_uint8());
            constellationToAdd.enabled = (dataBuffer.read_uint8() == 0x00) ? false : true;
            constellationToAdd.reservedChannelCount = dataBuffer.read_uint8();
            constellationToAdd.maxChannels = dataBuffer.read_uint8();
            uint16 constellationOptionFlags = dataBuffer.read_uint16();
            constellationToAdd.enableL1SAIF = Utils::bitIsSet(constellationOptionFlags, 0) ? true : false;

            returnData.constellations.push_back(constellationToAdd);
        }
        return returnData;
    }

    GNSS_ConstellationSettings::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint16(static_cast<uint8>(m_data.maxChannelsToUse));
            byteCommand.append_uint8(static_cast<uint8>(m_data.constellations.size()));
            for (Constellations::const_iterator constellation = m_data.constellations.begin(); constellation != m_data.constellations.end(); ++constellation)
            {
                byteCommand.append_uint8(static_cast<uint8>(constellation->constellationID));
                byteCommand.append_uint8(constellation->enabled);
                byteCommand.append_uint8(constellation->reservedChannelCount);
                byteCommand.append_uint8(constellation->maxChannels);
                uint16 constellationOptionFlags = (constellation->enableL1SAIF == true)? 0x01 : 0x00;
                byteCommand.append_uint16(constellationOptionFlags);
            }
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}
