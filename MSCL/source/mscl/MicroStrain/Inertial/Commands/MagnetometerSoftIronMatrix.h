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

    //Class: MagnetometerSoftIronMatrix
    //    Contains the logic for the Inertial MagnetometerSoftIronMatrix command.
    class MagnetometerSoftIronMatrix : public InertialCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "MagnetometerSoftIronMatrix"; }

        //Function: MakeSetCommand
		//
        //Parameter: dataToUse
		//    The <Matrix_3x3> object to set.
		//
        //Returns:
        //    MagnetometerSoftIronMatrix - object set up for sending a set command.
        static MagnetometerSoftIronMatrix MakeSetCommand(Matrix_3x3 dataToUse);

        //Function: MakeGetCommand
		//
        //Returns:
        //    MagnetometerSoftIronMatrix - object set up for sending a get command.
        static MagnetometerSoftIronMatrix MakeGetCommand();

        //Function: getResponseData
		//
        //Parameter:
        //    response - The <GenericInertialCommandResponse> object from which to get formatted data.
		//
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static Matrix_3x3 getResponseData(const GenericInertialCommandResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor MagnetometerSoftIronMatrix
        //    Private constructor creates a MagnetometerSoftIronMatrix object.  Use Make___Command methods to create an object.
        MagnetometerSoftIronMatrix(InertialTypes::FunctionSelector function_selector, Matrix_3x3 matrix);
		MagnetometerSoftIronMatrix(InertialTypes::FunctionSelector function_selector);

        //Function: commandType
		//
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_MAG_SOFT_IRON_MATRIX; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x9D; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_matrix
        //    The Matrix_3x3 to send to the device.
        Matrix_3x3 m_matrix;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        InertialTypes::FunctionSelector m_functionSelector;

    public:
	// Destructor
        ~MagnetometerSoftIronMatrix() { }
    };

#endif
}
