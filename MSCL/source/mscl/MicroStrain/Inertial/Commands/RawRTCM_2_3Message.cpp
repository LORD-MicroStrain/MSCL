/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "RawRTCM_2_3Message.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

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
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}
