/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"
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
        virtual std::string commandName() const { return "HeadingUpdateControl"; }

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
        operator ByteStream() const;

    private:
        // Function: Constructor HeadingUpdateControl
        //    Private constructor creates a HeadingUpdateControl object.  Use Make___Command methods to create an object.
        HeadingUpdateControl(MipTypes::FunctionSelector function_selector, const HeadingUpdateOptions& dataToUse);
        HeadingUpdateControl(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_EF_HEADING_UPDATE_CTRL; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x87; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_HeadingUpdateOptions
        //    The uint8 to send to the device.
        HeadingUpdateOptions m_HeadingUpdateOptions;

    public:
        // Destructor
        ~HeadingUpdateControl() { }
    };

#endif
}
