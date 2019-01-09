/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

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

    //Class: MagnetometerHardIronOffset
    //    Contains the logic for the Inertial MagnetometerHardIronOffset command.
    class MagnetometerHardIronOffset : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "MagnetometerHardIronOffset"; }

        //Function: MakeSetCommand
        //
        //Parameter: offsetVector
        //    The <GeometricVector> object to set.
        //
        //Returns:
        //    MagnetometerHardIronOffset - object set up for sending a set command.
        static MagnetometerHardIronOffset MakeSetCommand(GeometricVector offsetVector);

        //Function: MakeGetCommand
        //
        //Returns:
        //    MagnetometerHardIronOffset - object set up for sending a get command.
        static MagnetometerHardIronOffset MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static GeometricVector getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor MagnetometerHardIronOffset
        //    Private constructor creates a MagnetometerHardIronOffset object.  Use Make___Command methods to create an object.
        MagnetometerHardIronOffset(MipTypes::FunctionSelector function_selector, GeometricVector dataToUse);
        MagnetometerHardIronOffset(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_MAG_HARD_IRON_OFFSET; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x9C; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_offsetVector
        //    The MagnetometerHardIronOffsetData to send to the device.
        GeometricVector m_offsetVector;

    public:
        // Destructor
        ~MagnetometerHardIronOffset() { }
    };

#endif
}
