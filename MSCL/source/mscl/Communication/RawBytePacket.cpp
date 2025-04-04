/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Communication/RawBytePacket.h"

namespace mscl
{
    //default constructor for RawBytePacket
    RawBytePacket::RawBytePacket() :
        m_packetType(NO_PACKET_FOUND),
        m_source(FROM_READ)
    {}

    //type getter
    RawBytePacket::PacketType RawBytePacket::type() const
    {
        return m_packetType;
    }

    //type setter
    void RawBytePacket::type(PacketType type)
    {
        m_packetType = type;
    }

    //source getter
    RawBytePacket::PacketSource RawBytePacket::source() const
    {
        return m_source;
    }

    //source setter
    void RawBytePacket::source(PacketSource source)
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
} // namespace mscl
