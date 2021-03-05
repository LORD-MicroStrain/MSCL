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

    //Class: CaptureGyroBias
    //    Contains the logic for the Inertial CaptureGyroBias command.
    class CaptureGyroBias : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "CaptureGyroBias"; }

        //Function: MakeCommand
        //
        //Returns:
        //    CaptureGyroBias - object for the set command.
        static CaptureGyroBias MakeCommand(uint16 dataToUse);

        //Function: getResponseData
        //
        //Returns:
        //    A <GeometricVector> object with the data returned from the device.
        static GeometricVector getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        //Constructor: CaptureGyroBias
        //    Private constructor creates a CaptureGyroBias object.  Use MakeCommand methods to create an object.
        CaptureGyroBias(uint16 samplingTimeInMS);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_CAP_GYRO_BIAS; }

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

        //Variable: samplingTimeInMS
        //    The <uint16> CaptureGyroBiasData to send to the device.
        uint16 m_samplingTimeInMS;

    public:
	// Destructor
        ~CaptureGyroBias() { }
    };

#endif
}
