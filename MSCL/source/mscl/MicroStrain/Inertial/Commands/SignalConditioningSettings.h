/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
#ifndef SWIG
    //Class: SignalConditioningSettings
    //    A class to handle the Signal Conditioning Settings command
    class SignalConditioningSettings : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for the command.
        virtual std::string commandName() const { return "AHRSSignalConditioningSettings"; };

        //Function: MakeSetCommand
        //
        //Parameter: data
        //    The <SignalConditioningValues> to set.
        //
        //Returns:
        //    SignalConditioningSettings - object set up for sending a set command.
        static SignalConditioningSettings MakeSetCommand(const SignalConditioningValues& data);

        //Function: MakeGetCommand
        //
        //Returns:
        //    SignalConditioningSettings - object set up for sending a get command.
        static SignalConditioningSettings MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    <SignalConditioningValues> that are currently set on the device.
        SignalConditioningValues getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor Uint8Command
        //    Private constructor creates a Uint8Command object.  Use Make___Command methods to create an object.
        SignalConditioningSettings(MipTypes::FunctionSelector function_selector, const SignalConditioningValues& dataToUse);
        SignalConditioningSettings(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::Command::CMD_SENSOR_SIG_COND_SETTINGS; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x86; };

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_cmd
        //    The specific <MipTypes::Command> type of this object
        MipTypes::Command m_cmd;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_data
        //    The <SignalConditioningValues> to send to the device.
        SignalConditioningValues m_data;

    public:
        // Destructor
        ~SignalConditioningSettings() { }
    };
#endif
}