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
    //Class: EstimationControlFlags
    //    Contains the logic for the Inertial EstimationControlFlags command.
    class EstimationControlFlags : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "EstimationControlFlags"; }

        //Function: MakeSetCommand
        //
        //Parameter: dataToUse
        //    The <uint16> control flags to set.
        //
        //Returns:
        //    EstimationControlFlags - object set up for sending a set command.
        static EstimationControlFlags MakeSetCommand(const uint16& controlFlags);

        //Function: MakeGetCommand
        //
        //Returns:
        //    EstimationControlFlags - object set up for sending a get command.
        static EstimationControlFlags MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    EstimationControlOptions - the object containing the flags returned from the device.
        static EstimationControlOptions getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        // Function: Constructor EstimationControlFlags
        //    Private constructor creates an EstimationControlFlags object.  Use Make___Command methods to create an object.
        EstimationControlFlags(MipTypes::FunctionSelector function_selector, const uint16& dataToUse);
        EstimationControlFlags(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_EF_BIAS_EST_CTRL; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0x84; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_ControlFlags
        //    The uint16 to send to the device.
        uint16 m_ControlFlags;

    public:
        // Destructor
        ~EstimationControlFlags() {}
    };
#endif // !SWIG
} // namespace mscl
