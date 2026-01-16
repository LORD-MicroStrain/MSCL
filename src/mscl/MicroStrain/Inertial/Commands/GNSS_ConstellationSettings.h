/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
#ifndef SWIG
    //Class: GNSS_ConstellationSettings
    //    Contains the logic for the "GNSS Constellation Settings" command
    class GNSS_ConstellationSettings : public MipCommand
    {
    public:
        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_GNSS_CONSTELLATION_SETTINGS; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0xA0; }

        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "GNSS_ConstellationSettings"; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Function: MakeSetCommand
        //
        //Returns:
        //    GNSS_ConstellationSettings - object set up to send a set command.
        static GNSS_ConstellationSettings MakeSetCommand(ConstellationSettingsData);

        //Function: MakeGetCommand
        //
        //Returns:
        //    GNSS_ConstellationSettings - object set up to send a get command.
        static GNSS_ConstellationSettings MakeGetCommand();

        //Function: MakeResetToDefaultCommand
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        static GNSS_ConstellationSettings MakeResetToDefaultCommand();

        //Function: getResponseData
        //
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static ConstellationSettingsData getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        // Private Constructors.  Use static accessor classes to create an object.
        GNSS_ConstellationSettings(MipTypes::FunctionSelector function_selector, ConstellationSettingsData dataToUse);
        GNSS_ConstellationSettings(MipTypes::FunctionSelector function_selector);

        //Variable: m_functionSelector
        //    The <MipTypes::FunctionSelector> type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_data
        //    The <ConstellationSettingsData> to send to the device.
        ConstellationSettingsData m_data;

    public:
        // Destructor
        ~GNSS_ConstellationSettings() {}
    };
#endif // !SWIG
} // namespace mscl
