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

    //Class: SetReferencePosition
    //    Contains the logic for the Inertial Set Reference Position command.
    class SetReferencePosition : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "SetReferencePosition"; }

        //Function: MakeSetCommand
        //
        //Parameter: data
        //    The <FixedReferencePositionData> object to set.
        //
        //Returns:
        //    SetReferencePosition - object set up for sending a set command.
        static SetReferencePosition MakeSetCommand(FixedReferencePositionData data);

        //Function: MakeGetCommand
        //
        //Returns:
        //    SetReferencePosition - object set up for sending a get command.
        static SetReferencePosition MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    FixedReferencePositionData - An object with the data returned from the device.
        static FixedReferencePositionData getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor SetReferencePosition
        //    Private constructor creates a SetReferencePosition object.  Use Make___Command methods to create an object.
        SetReferencePosition(MipTypes::FunctionSelector function_selector, FixedReferencePositionData data);
        SetReferencePosition(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_EF_SET_REF_POSITION; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x90; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_data
        //    The <FixedReferencePositionData> for this node.
        FixedReferencePositionData m_data;

    public:
        // Destructor
        ~SetReferencePosition() { }
    };

#endif
}
