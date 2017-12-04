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

    //Class: VehicleDynamicsMode
    //    Contains the logic for the Inertial VehicleDynamicsMode command.
    class VehicleDynamicsMode : public InertialCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "VehicleDynamicsMode"; }

        //Function: MakeSetCommand
		//
        //Parameter: dataToUse
		//    The <VehicleModeType> object to set.
		//
        //Returns:
        //    VehicleDynamicsMode - object set up for sending a set command.
        static VehicleDynamicsMode MakeSetCommand(const VehicleModeType& vehicleType);

        //Function: MakeGetCommand
		//
        //Returns:
        //    VehicleDynamicsMode - object set up for sending a get command.
        static VehicleDynamicsMode MakeGetCommand();

        //Function: getResponseData
		//
        //Parameter:
        //    response - The <GenericInertialCommandResponse> object from which to get formatted data.
		//
        //Returns:
        //    VehicleModeType - An object with the data returned from the device.
        static VehicleModeType getResponseData(const GenericInertialCommandResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor VehicleDynamicsMode
        //    Private constructor creates a VehicleDynamicsMode object.  Use Make___Command methods to create an object.
        VehicleDynamicsMode(InertialTypes::FunctionSelector function_selector, const VehicleModeType& dataToUse);
		VehicleDynamicsMode(InertialTypes::FunctionSelector function_selector);

        //Function: commandType
		//
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_EF_VEHIC_DYNAMICS_MODE; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x80; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_VehicleType
        //    The uint8 to send to the device.
        VehicleModeType m_VehicleType;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        InertialTypes::FunctionSelector m_functionSelector;

    public:
	// Destructor
        ~VehicleDynamicsMode() { }
    };

#endif
}
