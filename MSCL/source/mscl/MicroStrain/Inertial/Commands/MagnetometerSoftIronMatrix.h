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

    //Class: MagnetometerSoftIronMatrix
    //    Contains the logic for the Inertial MagnetometerSoftIronMatrix command.
    class MagnetometerSoftIronMatrix : public MipCommand
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
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static Matrix_3x3 getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor MagnetometerSoftIronMatrix
        //    Private constructor creates a MagnetometerSoftIronMatrix object.  Use Make___Command methods to create an object.
        MagnetometerSoftIronMatrix(MipTypes::FunctionSelector function_selector, Matrix_3x3 matrix);
        MagnetometerSoftIronMatrix(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_MAG_SOFT_IRON_MATRIX; }

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

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_matrix
        //    The Matrix_3x3 to send to the device.
        Matrix_3x3 m_matrix;

    public:
        // Destructor
        ~MagnetometerSoftIronMatrix() { }
    };

#endif
}
