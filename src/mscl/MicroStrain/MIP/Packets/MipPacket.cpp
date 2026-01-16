/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"

namespace mscl
{
    //default constructor for MipPacket
    MipPacket::MipPacket() :
        m_descriptorSet(0)
    {}

    bool MipPacket::isDataPacket(uint8 descriptorSet)
    {
        switch(descriptorSet)
        {
        //actual Data packets
        case DescriptorSet::DESC_SET_DATA_SENSOR:
        case DescriptorSet::DESC_SET_DATA_GNSS:
        case DescriptorSet::DESC_SET_DATA_EST_FILTER:
        case DescriptorSet::DESC_SET_DATA_DISPLACEMENT:
        case DescriptorSet::DESC_SET_DATA_GNSS_1:
        case DescriptorSet::DESC_SET_DATA_GNSS_2:
        case DescriptorSet::DESC_SET_DATA_GNSS_3:
        case DescriptorSet::DESC_SET_DATA_GNSS_4:
        case DescriptorSet::DESC_SET_DATA_GNSS_5:
        case DescriptorSet::DESC_SET_DATA_SYSTEM:
            return true;

        //any other packet type is not a data packet
        default:
            return false;
        }
    }

    //type getter
    uint8 MipPacket::descriptorSet() const
    {
        return m_descriptorSet;
    }

    //type setter
    void MipPacket::descriptorSet(uint8 set)
    {
        m_descriptorSet = set;
    }

    const std::vector<uint8> MipPacket::payload() const
    {
        return m_payload.data();
    }

    void MipPacket::payload(const Bytes& bytes)
    {
        m_payload.clear();

        m_payload.appendBytes(bytes);
    }
} // namespace mscl
