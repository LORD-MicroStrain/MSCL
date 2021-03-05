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

    //Class: RawRTCM_2_3Message
    //    Contains the logic for the Inertial RawRTCM_2_3Message command.
    class RawRTCM_2_3Message : public MipCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "RawRTCM_2_3Message"; }

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
        operator ByteStream() const;

    private:
        // Function: Constructor RawRTCM_2_3Message
        //    Private constructor creates a RawRTCM_2_3Message object.  Use Make___Command methods to create an object.
		RawRTCM_2_3Message(const RTCMMessage& theMessage);

        //Function: commandType
		//
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_RAW_RTCM_2_3_MESSAGE; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0xF1; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_data
        //    The RTCMMessage to send to the device.
        RTCMMessage m_message;

    public:
	// Destructor
        ~RawRTCM_2_3Message() { }
    };

#endif
}
