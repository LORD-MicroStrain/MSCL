#include "stdafx.h"
#include "GNSS_SBASSettings.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    SBASSettings SBASSettings::MakeSetCommand(SBASSettingsData dataToUse)
    {
        return SBASSettings(InertialTypes::USE_NEW_SETTINGS, dataToUse);
    }

    SBASSettings SBASSettings::MakeGetCommand()
    {
        SBASSettingsData dataToUse;  // The data won't get used for a get command.
        return SBASSettings(InertialTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool SBASSettings::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    SBASSettingsData SBASSettings::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        SBASSettingsData returnData;
        returnData.enableSBAS = (dataBuffer.read_uint8() == 0x01)? true : false;
        uint16 optionFlags = dataBuffer.read_uint16();
        returnData.enableRanging = Utils::bitIsSet(optionFlags, 7) ? true : false;
        returnData.enableCorrectionData = Utils::bitIsSet(optionFlags, 6) ? true : false;
        returnData.applyIntergityInfo = Utils::bitIsSet(optionFlags, 5) ? true : false;

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
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint8(InertialTypes::ENABLED);
            uint16 optionFlags = 0;
            if (m_data.enableRanging) optionFlags &= 0x1;
            if (m_data.enableSBAS) optionFlags &= 0x2;
            if (m_data.applyIntergityInfo) optionFlags &= 0x4;
            byteCommand.append_int16(optionFlags);

            uint8 vectorSize = checked_cast<uint8, size_t>(m_data.satellitePRNs.size(), "number of Satellite PRNs");
            byteCommand.append_uint8(vectorSize);

            for (std::vector<uint16>::const_iterator i = m_data.satellitePRNs.begin(); i != m_data.satellitePRNs.end(); ++i)
            {
                byteCommand.append_uint16(*i);
            }
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}