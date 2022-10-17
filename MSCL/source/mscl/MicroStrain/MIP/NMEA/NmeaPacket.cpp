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

    const std::vector<uint8> NmeaPacket::payload() const
    {
        return m_payload.data();
    }

    void NmeaPacket::payload(const Bytes& bytes)
    {
        m_payload.clear();

        m_payload.appendBytes(bytes);
    }
}