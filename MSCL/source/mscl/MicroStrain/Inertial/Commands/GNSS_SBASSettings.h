/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
#ifndef SWIG
    class SBASSettings : public MipCommand
    {
    public:
        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_GNSS_SBAS_SETTINGS; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0xA1; }

        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "SBASSettings"; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Function: MakeSetCommand
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        static SBASSettings MakeSetCommand(SBASSettingsData);

        //Function: MakeGetCommand
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        static SBASSettings MakeGetCommand();

        //Function: getResponseData
        //
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static SBASSettingsData getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        //Constructor: SBASSettings
        SBASSettings(MipTypes::FunctionSelector function_selector, SBASSettingsData dataToUse) :
            m_functionSelector(function_selector),
            m_data(dataToUse)
        {}

        //Variable: m_functionSelector
        //  The MipTypes::FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_data
        //  The ConstellationSettingsData to send to the device.
        SBASSettingsData m_data;

    public:
        //  Destructor
        ~SBASSettings() {}
    };
#endif // !SWIG
} // namespace mscl
