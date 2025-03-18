/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/GNSS_SBASSettings.h"

namespace mscl
{
    SBASSettings SBASSettings::MakeSetCommand(SBASSettingsData dataToUse)
    {
        return SBASSettings(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    SBASSettings SBASSettings::MakeGetCommand()
    {
        SBASSettingsData dataToUse;  // The data won't get used for a get command.
        return SBASSettings(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool SBASSettings::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    SBASSettingsData SBASSettings::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        SBASSettingsData returnData;
        returnData.enableSBAS = (dataBuffer.read_uint8() == MipTypes::ENABLED)? true : false;
        uint16 optionFlags = dataBuffer.read_uint16();
        returnData.enableRanging = Utils::bitIsSet(optionFlags, 0) ? true : false;
        returnData.enableCorrectionData = Utils::bitIsSet(optionFlags, 1) ? true : false;
        returnData.applyIntegrityInfo = Utils::bitIsSet(optionFlags, 2) ? true : false;

        uint8 numberOfSatellites = dataBuffer.read_uint8();
        for (uint8 satelliteNum = 0; satelliteNum < numberOfSatellites; ++satelliteNum)
        {
            uint16 satellitePRN = dataBuffer.read_uint16();
            returnData.satellitePRNs.push_back(satellitePRN);
        }
        return returnData;
    }

    SBASSettings::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            uint8 sbasEnabled = static_cast<uint8>(m_data.enableSBAS ? MipTypes::ENABLED : MipTypes::DISABLED);
            byteCommand.append_uint8(sbasEnabled);
            uint16 optionFlags = 0;
            if (m_data.enableRanging) optionFlags |= 0x1;
            if (m_data.enableCorrectionData) optionFlags |= 0x2;
            if (m_data.applyIntegrityInfo) optionFlags |= 0x4;
            byteCommand.append_uint16(optionFlags);

            uint8 vectorSize = checked_cast<uint8, size_t>(m_data.satellitePRNs.size(), "number of Satellite PRNs");
            byteCommand.append_uint8(vectorSize);

            for (std::vector<uint16>::const_iterator i = m_data.satellitePRNs.begin(); i != m_data.satellitePRNs.end(); ++i)
            {
                byteCommand.append_uint16(*i);
            }
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}
