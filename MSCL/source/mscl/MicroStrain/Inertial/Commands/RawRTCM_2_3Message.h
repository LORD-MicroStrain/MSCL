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
    //Class: RawRTCM_2_3Message
    //    Contains the logic for the Inertial RawRTCM_2_3Message command.
    class RawRTCM_2_3Message : public MipCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "RawRTCM_2_3Message"; }

        //Function: MakeCommand
		//
        //Parameter: theMessage
		//    The <RTCMMessage> object to send.
		//
        //Returns:
        //    RawRTCM_2_3Message - object set up for sending a set command.
        static RawRTCM_2_3Message MakeCommand(const RTCMMessage& theMessage);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        // Function: Constructor RawRTCM_2_3Message
        //    Private constructor creates a RawRTCM_2_3Message object.  Use Make___Command methods to create an object.
		RawRTCM_2_3Message(const RTCMMessage& theMessage);

        //Function: commandType
		//
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_RAW_RTCM_2_3_MESSAGE; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0xF1; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_data
        //    The RTCMMessage to send to the device.
        RTCMMessage m_message;

    public:
	// Destructor
        ~RawRTCM_2_3Message() {}
    };
#endif // !SWIG
} // namespace mscl
