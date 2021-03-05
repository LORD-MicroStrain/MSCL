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

    //Class: VehicleDynamicsMode
    //    Contains the logic for the Inertial VehicleDynamicsMode command.
    class VehicleDynamicsMode : public MipCommand
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
        static VehicleDynamicsMode MakeSetCommand(const InertialTypes::VehicleModeType& vehicleType);

        //Function: MakeGetCommand
        //
        //Returns:
        //    VehicleDynamicsMode - object set up for sending a get command.
        static VehicleDynamicsMode MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    VehicleModeType - An object with the data returned from the device.
        static InertialTypes::VehicleModeType getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor VehicleDynamicsMode
        //    Private constructor creates a VehicleDynamicsMode object.  Use Make___Command methods to create an object.
        VehicleDynamicsMode(MipTypes::FunctionSelector function_selector, const InertialTypes::VehicleModeType& dataToUse);
        VehicleDynamicsMode(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_EF_VEHIC_DYNAMICS_MODE; }

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

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_VehicleType
        //    The uint8 to send to the device.
        InertialTypes::VehicleModeType m_VehicleType;

    public:
        // Destructor
        ~VehicleDynamicsMode() { }
    };

#endif
}
