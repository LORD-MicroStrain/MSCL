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
    //Class: MagnetometerCaptureAutoCalibration
    //    Contains the logic for the Inertial MagnetometerCaptureAutoCalibration command.
    class MagnetometerCaptureAutoCalibration : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "MagnetometerCaptureAutoCalibration"; }

        //Function: MakeCommand
        //
        //Returns:
        //    MagnetometerCaptureAutoCalibration - object for the command.
        static MagnetometerCaptureAutoCalibration MakeCommand();

        //Function: MakeSaveCommand
        //
        //Returns:
        //    MagnetometerCaptureAutoCalibration - object for the command to save as startup values.
        static MagnetometerCaptureAutoCalibration MakeSaveCommand();

        //Function: getResponseData
        //
        //Returns:
        //    A <GeometricVector> object with the data returned from the device.
        static bool getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        //Constructor: MagnetometerCaptureAutoCalibration
        //    Private constructor creates a MagnetometerCaptureAutoCalibration object.  Use MakeCommand methods to create an object.
        MagnetometerCaptureAutoCalibration(MipTypes::FunctionSelector functionSelector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_EF_MAG_CAPTURE_AUTO_CAL; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0xF1; }

    public:
        // Destructor
        ~MagnetometerCaptureAutoCalibration() {}
    };
#endif // !SWIG
} // namespace mscl
