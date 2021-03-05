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
    //Class: Uint16Command
    //    A generic command class that contains the logic for any command that deals only with one or more uint16s.
    class Uint16Command : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for the command.
        virtual std::string commandName() const;

        //Function: MakeSetCommand
        //
        //Parameter: cmd
        //    The specific <MipTypes::Command> type to be constructed
        //
        //Parameter: dataToUse
        //    The list of uint16s to set.
        //
        //Returns:
        //    Uint16Command - object set up for sending a set command.
        static Uint16Command MakeSetCommand(MipTypes::Command cmd, const std::vector<uint16>& data);

        //Function: MakeGetCommand
        //
        //Parameter: cmd
        //    The specific <MipTypes::Command> type to be constructed
        //
        //Returns:
        //    Uint16Command - object set up for sending a get command.
        static Uint16Command MakeGetCommand(MipTypes::Command cmd);

        //Function: MakeGetCommand
        //
        //Parameter: cmd
        //    The specific <MipTypes::Command> type to be constructed
        //
        //Parameter: addlParams
        //    Any additional uint16 parameters that need to be sent to the node.
        //
        //Returns:
        //    Uint16Command - object set up for sending a get command.
        static Uint16Command MakeGetCommand(MipTypes::Command cmd, const std::vector<uint16>& addlParams);

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    vector of uint16s - An collection of uint16s with the data returned from the device.
        std::vector<uint16> getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor Uint16Command
        //    Private constructor creates a Uint16Command object.  Use Make___Command methods to create an object.
        Uint16Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector, const std::vector<uint16>& dataToUse);
        Uint16Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return m_cmd; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const;

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
        //    The uint16 data to send to the device.
        std::vector<uint16> m_data;

        //Variable: m_addlParams
        //    The uint16 parameters to send to the device in a get command.
        std::vector<uint16> m_addlParams;

    public:
        // Destructor
        ~Uint16Command() { }
    };
#endif
}