/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "ChannelMask.h"

namespace mscl
{
    ChannelMask::ChannelMask(uint16 channelMask):
        BitMask(channelMask)
    {
    }

    ChannelMask::ChannelMask():
        BitMask(0)
    {
    }

    bool ChannelMask::operator==(const ChannelMask& other) const
    {
        return BitMask::operator==(other);
    }

    bool ChannelMask::operator!=(const ChannelMask& other) const
    {
        return BitMask::operator!=(other);
    }

    bool ChannelMask::operator<(const ChannelMask& other) const
    {
        return BitMask::operator<(other);
    }

    bool ChannelMask::operator>(const ChannelMask& other) const
    {
        return BitMask::operator>(other);
    }

    void ChannelMask::fromMask(uint16 channelMask)
    {
        BitMask::fromMask(channelMask);
    }

    uint16 ChannelMask::toMask() const
    {
        return BitMask::toMask();
    }

    uint8 ChannelMask::count() const
    {
        return BitMask::enabledCount();
    }

    bool ChannelMask::enabled(uint8 channel) const
    {
        return BitMask::enabled(channel - 1);
    }

    void ChannelMask::enable(uint8 channel, bool enable)
    {
        BitMask::enable(channel - 1, enable);
    }

    uint8 ChannelMask::lastChEnabled() const
    {
        int16 result = BitMask::lastBitEnabled();

        if(result == -1)
        {
            return 0;
        }

        return static_cast<uint8>(result + 1);
    }
}