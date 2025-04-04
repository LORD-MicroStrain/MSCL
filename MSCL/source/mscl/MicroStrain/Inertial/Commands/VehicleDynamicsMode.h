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
    //Class: VehicleDynamicsMode
    //    Contains the logic for the Inertial VehicleDynamicsMode command.
    class VehicleDynamicsMode : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "VehicleDynamicsMode"; }

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
        operator ByteStream() const override;

    private:
        // Function: Constructor VehicleDynamicsMode
        //    Private constructor creates a VehicleDynamicsMode object.  Use Make___Command methods to create an object.
        VehicleDynamicsMode(MipTypes::FunctionSelector function_selector, const InertialTypes::VehicleModeType& dataToUse);
        VehicleDynamicsMode(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_EF_VEHIC_DYNAMICS_MODE; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0x80; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_VehicleType
        //    The uint8 to send to the device.
        InertialTypes::VehicleModeType m_VehicleType;

    public:
        // Destructor
        ~VehicleDynamicsMode() {}
    };
#endif // !SWIG
} // namespace mscl
