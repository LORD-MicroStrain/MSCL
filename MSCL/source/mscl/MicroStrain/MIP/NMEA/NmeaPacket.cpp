/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "NmeaPacket.h"

namespace mscl
{
    const std::string NmeaPacketInfo::TALKER_ID_PROPRIETARY   = "P";
    const std::string NmeaPacketInfo::TALKER_ID_GNSS          = "GN";
    const std::string NmeaPacketInfo::TALKER_ID_GPS           = "GP";
    const std::string NmeaPacketInfo::TALKER_ID_GALILEO       = "GA";
    const std::string NmeaPacketInfo::TALKER_ID_GLONASS       = "GL";

    const std::string NmeaPacketInfo::SENTENCE_GGA    = "GGA";
    const std::string NmeaPacketInfo::SENTENCE_GLL    = "GLL";
    const std::string NmeaPacketInfo::SENTENCE_GSV    = "GSV";
    const std::string NmeaPacketInfo::SENTENCE_RMC    = "RMC";
    const std::string NmeaPacketInfo::SENTENCE_VTG    = "VTG";
    const std::string NmeaPacketInfo::SENTENCE_HDT    = "HDT";
    const std::string NmeaPacketInfo::SENTENCE_ZDA    = "ZDA";
    const std::string NmeaPacketInfo::SENTENCE_PKRA   = "PKRA";
    const std::string NmeaPacketInfo::SENTENCE_PKRR   = "PKRR";

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