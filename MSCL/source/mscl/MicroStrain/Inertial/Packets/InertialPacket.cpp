/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "InertialPacket.h"

namespace mscl
{
    //default constructor for InertialPacket
    InertialPacket::InertialPacket() :
        m_descriptorSet(0)
    {}

    bool InertialPacket::isDataPacket() const
    {
        switch(m_descriptorSet)
        {
        //actual Data packets
        case DescriptorSet::DESC_SET_DATA_SENSOR:
        case DescriptorSet::DESC_SET_DATA_GNSS:
        case DescriptorSet::DESC_SET_DATA_EST_FILTER:
            return true;

        //any other packet type is not a data packet
        default:
            return false;
        }
    }

    //type getter
    uint8 InertialPacket::descriptorSet() const
    {
        return m_descriptorSet;
    }

    //type setter
    void InertialPacket::descriptorSet(uint8 set)
    {
        m_descriptorSet = set;
    }

    const std::vector<uint8> InertialPacket::payload() const
    {
        return m_payload.data();
    }

    void InertialPacket::payload(const Bytes& bytes)
    {
        m_payload.clear();

        m_payload.appendBytes(bytes);
    }
}