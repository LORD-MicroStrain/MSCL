/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "ChannelMask.h"

namespace mscl
{
    ChannelMask::ChannelMask(uint16 channelMask)
    {
        fromMask(channelMask);
    }

    ChannelMask::ChannelMask()
    {
        //initialize all the channels to inactive (channel mask of 0)
        fromMask(0);
    }

    bool ChannelMask::operator==(const ChannelMask& other) const
    {
        //loop through all the channels possible
        for(uint8 chItr = 0; chItr < MAX_CHANNELS; chItr++)
        {
            //if we find any differences for active/inactive chs
            if(m_channels[chItr] != other.m_channels[chItr])
            {
                return false;
            }
        }

        return true;
    }

    bool ChannelMask::operator!=(const ChannelMask& other) const
    {
        //loop through all the channels possible
        for(uint8 chItr = 0; chItr < MAX_CHANNELS; chItr++)
        {
            //if we find any differences for active/inactive chs
            if(m_channels[chItr] != other.m_channels[chItr])
            {
                return true;
            }
        }

        return false;
    }
    
    bool ChannelMask::operator<(const ChannelMask& other) const
    {
        return toMask() < other.toMask();
    }

    bool ChannelMask::operator>(const ChannelMask& other) const
    {
        return toMask() > other.toMask();
    }

    void ChannelMask::fromMask(uint16 channelMask)
    {
        //loop through all the channels possible
        for(uint8 chItr = 0; chItr < MAX_CHANNELS; chItr++)
        {
            //check each channels bit value to see if it is active (1)
            m_channels[chItr] = (channelMask & (1 << chItr)) != 0;
        }
    }

    uint16 ChannelMask::toMask() const
    {
        uint16 channelMask = 0;

        //loop through all the channels possible
        for(uint8 chItr = 0; chItr < MAX_CHANNELS; chItr++)
        {
            //if the channel is active
            if(m_channels[chItr])
            {
                channelMask |= (1 << chItr);    
            }
        }

        return channelMask;
    }

    uint8 ChannelMask::count() const
    {
        uint8 count = 0;

        //loop through all the channels possible
        for(uint8 chItr = 0; chItr < MAX_CHANNELS; chItr++)
        {
            //if the channel is active
            if(m_channels[chItr])
            {
                //increment the count
                count++;    
            }
        }

        return count;
    }

    bool ChannelMask::enabled(uint8 channel) const
    {
        //if the channel is out of range
        if(channel > MAX_CHANNELS || channel == 0)
        {
            return false;
        }

        return m_channels[channel - 1];
    }

    void ChannelMask::enable(uint8 channel, bool enable)
    {
        //verify the channel is within range
        if(channel <= MAX_CHANNELS && channel != 0)
        {
            m_channels[channel - 1] = enable;
        }
    }

    uint8 ChannelMask::lastChEnabled() const
    {
        uint8 itr = MAX_CHANNELS;

        //loop over the channels backwards
        for(; itr >= 1; --itr)
        {
            //if we find a channel that is enabled
            if(m_channels[itr - 1])
            {
                //we can stop looking and return the channel number
                return itr;
            }
        }

        //no channels were found to be enabled
        return 0;
    }
}