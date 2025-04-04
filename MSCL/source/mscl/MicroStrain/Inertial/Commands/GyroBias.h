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
    //Class: GyroBias
    //    Contains the logic for the Inertial GyroBias command.
    class GyroBias : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "GyroBias"; }

        //Function: MakeSetCommand
        //
        //Parameter:
        //    vectorToSet -  The <GeometricVector> gyro bias vector to set.
        //
        //Returns:
        // GyroBias - object for the set command.
        static GyroBias MakeSetCommand(GeometricVector gyroBiasVector);

        //Function: MakeGetCommand
        //
        //Returns:
        // GyroBias - object for the get command.
        static GyroBias MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        // <GeometricVector> object with the data returned from the device.
        static GeometricVector getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        //Constructor: GyroBias
        //    Private constructor creates a GyroBias object.  Use Make___Command methods to create an object.
        GyroBias(MipTypes::FunctionSelector function_selector, GeometricVector gyroBiasVector);
        GyroBias(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_GYRO_BIAS; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0x9B; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_functionSelector
        //  <The MipTypes::FunctionSelector> type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_gyroBiasVector
        //  The gyro bias to send to the device.
        GeometricVector m_gyroBiasVector;

    public:
        // Destructor: ~GyroBias
        ~GyroBias() {}
    };
#endif // !SWIG
} // namespace mscl
