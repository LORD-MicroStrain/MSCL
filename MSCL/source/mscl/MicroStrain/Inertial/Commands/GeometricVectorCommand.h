/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
#ifndef SWIG
    //Class: GeometricVectorCommand
    //    A generic command class that contains the logic for any command that deals only with one or more <GeometricVector>.
    class GeometricVectorCommand : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for the command.
        std::string commandName() const override;

        //Function: MakeSetCommand
        //
        //Parameter: cmd
        //    The specific <MipTypes::Command> type to be constructed
        //
        //Parameter: dataToUse
        //    The list of <GeometricVector> objects to set.
        //
        //Returns:
        //    GeometricVectorCommand - object set up for sending a set command.
        static GeometricVectorCommand MakeSetCommand(MipTypes::Command cmd, const GeometricVectors& data);

        //Function: MakeGetCommand
        //
        //Parameter: cmd
        //    The specific <MipTypes::Command> type to be constructed
        //
        //Returns:
        //    GeometricVectorCommand - object set up for sending a get command.
        static GeometricVectorCommand MakeGetCommand(MipTypes::Command cmd);

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    GeometricVector - An collection of GeometricVectors with the data returned from the device.
        GeometricVectors getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        // Function: Constructor GeometricVectorCommand
        //    Private constructor creates a GeometricVectorCommand object.  Use Make___Command methods to create an object.
        GeometricVectorCommand(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector, const GeometricVectors& dataToUse);
        GeometricVectorCommand(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return m_cmd; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override;

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_cmd
        //    The specific <MipTypes::Command> type of this object
        MipTypes::Command m_cmd;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_data
        //    The <GeometricVector> data to send to the device.
        GeometricVectors m_data;

    public:
        // Destructor
        ~GeometricVectorCommand() {}
    };
#endif // !SWIG
} // namespace mscl
