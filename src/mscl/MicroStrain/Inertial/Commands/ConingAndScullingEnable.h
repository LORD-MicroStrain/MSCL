/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
#ifndef SWIG
    //Class: ConingAndScullingEnable
    //    Contains the logic for the Inertial ConingAndScullingEnable command.
    class ConingAndScullingEnable : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "ConingAndScullingEnable"; }

        //Function: MakeSetCommand
        //
        //Parameter: dataToUse
        //    The <ConingAndScullingEnableData> object to set.
        //
        //Returns:
        //    ConingAndScullingEnable - object set up for sending a set command.
        static ConingAndScullingEnable MakeSetCommand(bool enable);

        //Function: MakeGetCommand
        //
        //Returns:
        //    ConingAndScullingEnable - object set up for sending a get command.
        static ConingAndScullingEnable MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static bool getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        // Function: Constructor ConingAndScullingEnable
        //    Private constructor creates a ConingAndScullingEnable object.  Use Make___Command methods to create an object.
        ConingAndScullingEnable(MipTypes::FunctionSelector function_selector, bool enable);
        ConingAndScullingEnable(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_CONING_SCULLING; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0x9E; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_enabled
        //    Whether to enable or disable coning and sculling.
        bool m_enabled;

    public:
        // Destructor
        ~ConingAndScullingEnable() {}
    };
#endif // !SWIG
} // namespace mscl
