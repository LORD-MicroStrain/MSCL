/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "MipChannel.h"
#include "mscl/MicroStrain/Inertial/InertialNode.h"
#include "mscl/Utils.h"

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
        if (m_sampleRate.rateType() == SampleRate::rateType_decimation)
        {
            return static_cast<uint16>(m_sampleRate.samples());
        }

        return static_cast<uint16>(sampleRateBase / m_sampleRate.samplesPerSecond());
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