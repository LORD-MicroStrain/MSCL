/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/MipChannel.h"

namespace mscl
{
    MipChannel::MipChannel():
        m_channelField(static_cast<MipTypes::ChannelField>(0))
    {}

    MipChannel::MipChannel(MipTypes::ChannelField channelId, const SampleRate& sampleRate) :
        m_channelField(channelId),
        m_sampleRate(sampleRate)
    {}

    MipTypes::ChannelField MipChannel::channelField() const
    {
        return m_channelField;
    }

    const SampleRate& MipChannel::sampleRate() const
    {
        return m_sampleRate;
    }

    uint16 MipChannel::rateDecimation(uint16 sampleRateBase) const
    {
        return m_sampleRate.toDecimation(sampleRateBase);
    }

    uint8 MipChannel::fieldDescriptor() const
    {
        return Utils::lsb(static_cast<uint16>(m_channelField));
    }

    uint8 MipChannel::descriptorSet() const
    {
        return Utils::msb(static_cast<uint16>(m_channelField));
    }
}
