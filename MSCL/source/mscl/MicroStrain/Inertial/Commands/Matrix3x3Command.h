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
    //Class: Matrix3x3Command
    //    A generic command class that contains the logic for any command that deals only with one or more <Matrix_3x3>.
    class Matrix3x3Command : public MipCommand
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
        //    The list of <Matrix_3x3> objects to set.
        //
        //Returns:
        //    Matrix3x3Command - object set up for sending a set command.
        static Matrix3x3Command MakeSetCommand(MipTypes::Command cmd, const Matrix_3x3s& data);

        //Function: MakeGetCommand
        //
        //Parameter: cmd
        //    The specific <MipTypes::Command> type to be constructed
        //
        //Returns:
        //    Matrix3x3Command - object set up for sending a get command.
        static Matrix3x3Command MakeGetCommand(MipTypes::Command cmd);

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    Matrix_3x3 - An collection of Matrix_3x3s with the data returned from the device.
        Matrix_3x3s getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor Matrix3x3Command
        //    Private constructor creates a Matrix3x3Command object.  Use Make___Command methods to create an object.
        Matrix3x3Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector, const Matrix_3x3s& dataToUse);
        Matrix3x3Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector);

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
        //    The <Matrix_3x3> data to send to the device.
        Matrix_3x3s m_data;

    public:
        // Destructor
        ~Matrix3x3Command() { }
    };
#endif
}