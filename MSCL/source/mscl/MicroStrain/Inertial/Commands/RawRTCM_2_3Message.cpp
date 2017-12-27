#include "stdafx.h"
#include "RawRTCM_2_3Message.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    RawRTCM_2_3Message::RawRTCM_2_3Message(const RTCMMessage& theMessage) :
        m_message(theMessage)
    { }

    RawRTCM_2_3Message RawRTCM_2_3Message::MakeCommand(const RTCMMessage& theMessage)
    {
        return RawRTCM_2_3Message(theMessage);
    }

    bool RawRTCM_2_3Message::responseExpected() const
    {
        return false;
    }

    RawRTCM_2_3Message::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_string(m_message);
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data());
    }

}