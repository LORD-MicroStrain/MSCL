/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "RawBytePacket.h"

namespace mscl
{
    //default constructor for RawBytePacket
    RawBytePacket::RawBytePacket() :
        m_packetType(PacketType::NO_PACKET_FOUND),
        m_source(PacketSource::FROM_READ)
    {}

    //type getter
    RawBytePacket::PacketType RawBytePacket::type() const
    {
        return m_packetType;
    }

    //type setter
    void RawBytePacket::type(RawBytePacket::PacketType type)
    {
        m_packetType = type;
    }

    //source getter
    RawBytePacket::PacketSource RawBytePacket::source() const
    {
        return m_source;
    }

    //source setter
    void RawBytePacket::source(RawBytePacket::PacketSource source)
    {
        m_source = source;
    }

    const std::vector<uint8> RawBytePacket::payload() const
    {
        return m_payload.data();
    }

    void RawBytePacket::payload(const Bytes& bytes)
    {
        m_payload.clear();

        m_payload.appendBytes(bytes);
    }
}