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

    //Class: AccelBias
    //    Contains the logic for the Inertial GPSTimeUpdate command.
    class AccelBias : public MipCommand
    {
    public:
        //Function: commandName
        //Returns:
        // std::string - the string name for this class.
        virtual std::string commandName() const { return "AccelBias"; }

        //Function: MakeSetCommand
        //
        //Parameter:
        //    vectorToSet -  The <GeometricVector> accelerometer bias vector to set.
        //
        //Returns:
        // AccelBias - object for the set command.
        static AccelBias MakeSetCommand(const GeometricVector& vectorToSet);

        //Function: MakeGetCommand
        //
        //Returns:
        // AccelBias - object for the get command.
        static AccelBias MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        // <GeometricVector> object with the data returned from the device.
        static GeometricVector getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        // Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Constructor: AccelBias
        //  Private constructor creates a GyroBias object.  Use Make___Command methods to create an object.
        AccelBias(MipTypes::FunctionSelector function_selector, const GeometricVector& dataToUse);
        AccelBias(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        // MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_ACCEL_BIAS; }

        //Function: fieldDataByte
        //
        //Returns:
        // uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x9A; }

        //Function: responseExpected
        //
        //Returns:
        // bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_functionSelector
        //    The <MipTypes::FunctionSelector> type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_accelerometerBiasVector
        //   The <ConstellationSettingsData> to send to the device.
        GeometricVector m_accelerometerBiasVector;

    public:
        // Destructor: ~AccelBias
        ~AccelBias() { }
    };

#endif
}
