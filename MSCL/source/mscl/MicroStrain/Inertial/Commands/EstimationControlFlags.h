/*******************************************************************************
Copyright(c) 2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/Inertial/Commands/InertialCommand.h"

namespace mscl
{

#ifndef SWIG 

    //Class: EstimationControlFlags
    //    Contains the logic for the Inertial EstimationControlFlags command.
    class EstimationControlFlags : public InertialCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "EstimationControlFlags"; }

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
        //    response - The <GenericInertialCommandResponse> object from which to get formatted data.
		//
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static uint16 getResponseData(const GenericInertialCommandResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor EstimationControlFlags
        //    Private constructor creates an EstimationControlFlags object.  Use Make___Command methods to create an object.
        EstimationControlFlags(InertialTypes::FunctionSelector function_selector, const uint16& dataToUse);
		EstimationControlFlags(InertialTypes::FunctionSelector function_selector);

        //Function: commandType
		//
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_EF_BIAS_EST_CTRL; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x84; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_ControlFlags
        //    The uint16 to send to the device.
        uint16 m_ControlFlags;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        InertialTypes::FunctionSelector m_functionSelector;

    public:
	// Destructor
        ~EstimationControlFlags() { }
    };

#endif
}
