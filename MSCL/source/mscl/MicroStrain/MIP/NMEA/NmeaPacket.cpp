/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "NmeaPacket.h"

namespace mscl
{
    //default constructor for NmeaPacket
    NmeaPacket::NmeaPacket()
    {}

    const std::string NmeaPacket::message() const
    {
        return m_message.read_string(0, m_message.size());
    }

    const Bytes NmeaPacket::message_asBytes() const
    {
        return m_message.data();
    }

    void NmeaPacket::message(const Bytes& bytes)
    {
        m_message.clear();

        m_message.appendBytes(bytes);
    }
}