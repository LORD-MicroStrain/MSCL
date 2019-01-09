/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "ChannelMask.h"

namespace mscl
{
    ChannelMask::ChannelMask(uint16 channelMask):
        m_bitMask(channelMask)
    {
    }

    ChannelMask::ChannelMask():
        m_bitMask(0)
    {
    }

    bool ChannelMask::operator==(const ChannelMask& other) const
    {
        return m_bitMask == other.m_bitMask;
    }

    bool ChannelMask::operator!=(const ChannelMask& other) const
    {
        return m_bitMask != other.m_bitMask;
    }

    bool ChannelMask::operator<(const ChannelMask& other) const
    {
        return m_bitMask < other.m_bitMask;
    }

    bool ChannelMask::operator>(const ChannelMask& other) const
    {
        return m_bitMask > other.m_bitMask;
    }

    void ChannelMask::fromMask(uint16 channelMask)
    {
        m_bitMask.fromMask(channelMask);
    }

    uint16 ChannelMask::toMask() const
    {
        return m_bitMask.toMask();
    }

    uint8 ChannelMask::count() const
    {
        return m_bitMask.enabledCount();
    }

    bool ChannelMask::enabled(uint8 channel) const
    {
        return m_bitMask.enabled(channel - 1);
    }

    void ChannelMask::enable(uint8 channel, bool enable)
    {
        m_bitMask.enable(channel - 1, enable);
    }

    uint8 ChannelMask::lastChEnabled() const
    {
        int16 result = m_bitMask.lastBitEnabled();

        if(result == -1)
        {
            return 0;
        }

        return static_cast<uint8>(result + 1);
    }
}