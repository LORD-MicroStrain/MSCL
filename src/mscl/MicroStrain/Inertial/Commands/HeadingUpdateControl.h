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
    //Class: HeadingUpdateControl
    //    Contains the logic for the Inertial HeadingUpdateControl command.
    class HeadingUpdateControl : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "HeadingUpdateControl"; }

        //Function: MakeSetCommand
        //
        //Parameter: dataToUse
        //    The <HeadingUpdateOptions> object to set.
        //
        //Returns:
        //    HeadingUpdateControl - object set up for sending a set command.
        static HeadingUpdateControl MakeSetCommand(const HeadingUpdateOptions& headingUpdateOptions);

        //Function: MakeGetCommand
        //
        //Returns:
        //    HeadingUpdateControl - object set up for sending a get command.
        static HeadingUpdateControl MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static HeadingUpdateOptions getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        // Function: Constructor HeadingUpdateControl
        //    Private constructor creates a HeadingUpdateControl object.  Use Make___Command methods to create an object.
        HeadingUpdateControl(MipTypes::FunctionSelector function_selector, const HeadingUpdateOptions& dataToUse);
        HeadingUpdateControl(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_EF_HEADING_UPDATE_CTRL; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0x87; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_HeadingUpdateOptions
        //    The uint8 to send to the device.
        HeadingUpdateOptions m_HeadingUpdateOptions;

    public:
        // Destructor
        ~HeadingUpdateControl() {}
    };
#endif // !SWIG
} // namespace mscl
