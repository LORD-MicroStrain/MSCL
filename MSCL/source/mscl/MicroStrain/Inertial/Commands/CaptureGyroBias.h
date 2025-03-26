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
    //Class: CaptureGyroBias
    //    Contains the logic for the Inertial CaptureGyroBias command.
    class CaptureGyroBias : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "CaptureGyroBias"; }

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
        operator ByteStream() const override;

    private:
        //Constructor: CaptureGyroBias
        //    Private constructor creates a CaptureGyroBias object.  Use MakeCommand methods to create an object.
        CaptureGyroBias(uint16 samplingTimeInMS);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_CAP_GYRO_BIAS; }

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

        //Variable: samplingTimeInMS
        //    The <uint16> CaptureGyroBiasData to send to the device.
        uint16 m_samplingTimeInMS;

    public:
	// Destructor
        ~CaptureGyroBias() {}
    };
#endif // !SWIG
} // namespace mscl
