/*******************************************************************************
Copyright(c) 2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/InertialReturnTypes.h"
#include "mscl/MicroStrain/Inertial/Commands/InertialCommand.h"

namespace mscl
{

#ifndef SWIG 

    //Class: GyroBias
    //    Contains the logic for the Inertial GyroBias command.
    class GyroBias : public InertialCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "GyroBias"; }

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
        //    response - The <GenericInertialCommandResponse> object from which to get formatted data.
        //
        //Returns:
        // <GeometricVector> object with the data returned from the device.
        static GeometricVector getResponseData(const GenericInertialCommandResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        //Constructor: GyroBias
        //    Private constructor creates a GyroBias object.  Use Make___Command methods to create an object.
        GyroBias(InertialTypes::FunctionSelector function_selector, GeometricVector gyroBiasVector);
        GyroBias(InertialTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_GYRO_BIAS; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x9B; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_gyroBiasVector
        //  The gyro bias to send to the device.
        GeometricVector m_gyroBiasVector;

        //Variable: m_functionSelector
        //  <The InertialTypes::FunctionSelector> type of command to send, get/set, reset to factory defaults, et al.
        InertialTypes::FunctionSelector m_functionSelector;

    public:
	    // Destructor: ~GyroBias
        ~GyroBias() { }
    };

#endif
}
