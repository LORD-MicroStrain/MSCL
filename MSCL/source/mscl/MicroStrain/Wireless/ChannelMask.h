/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/BitMask.h"
#include "mscl/Types.h"

namespace mscl
{
    //API Class: ChannelMask
    //    Represents the channel mask (active and inactive channels) for a WirelessNode. 
    class ChannelMask
    {
    private:
        BitMask m_bitMask;

    public:
        //API Constant: MAX_CHANNELS = 16
        //    The maximum number of channels currently available on any WirelessNode
        static const uint8 MAX_CHANNELS = 16;

    public:
        //API Constructor: ChannelMask
        //    Creates an ChannelMask object given a channel mask that was stored on a WirelessNode
        //
        //Parameters:
        //    channelMask - A channel mask value from a WirelessNode representing the active and inactive channels
        explicit ChannelMask(uint16 channelMask);

        //API Constructor: ChannelMask
        //    The default constructor for creating an ChannelMask object, which sets all the channels to inactive
        ChannelMask();

        virtual ~ChannelMask() {};

        //API Operator: ==
        //  Equal operator for comparing ChannelMasks.
        virtual bool operator==(const ChannelMask& other) const;

        //API Operator: !=
        //  Not Equal operator for comparing ChannelMasks.
        virtual bool operator!=(const ChannelMask& other) const;

        //API Operator: <
        //  Less Than operator for comparing ChannelMasks.
        virtual bool operator<(const ChannelMask& other) const;

        //API Operator: >
        //  Greater Than operator for comparing ChannelMasks.
        virtual bool operator>(const ChannelMask& other) const;

        //API Function: fromMask
        //    Initializes the ChannelMask object from a channel mask
        //
        //Parameters:
        //    channelMask - A channel mask value from a WirelessNode representing the active and inactive channels
        void fromMask(uint16 channelMask);

        //API Function: toMask
        //    Gets the channel mask value of the current ChannelMask object
        //
        //Returns:
        //    The ChannelMask object represented as a channel mask
        uint16 toMask() const;

        //API Function: count
        //    Gets the total number of active channels in the current ChannelMask object
        //
        //Returns:
        //    The total number of active channels
        uint8 count() const;

        //API Function: enabled
        //    Checks whether a certain channel is enabled or disabled
        //
        //Parameters:
        //    channel - The channel to check if enabled or disabled, based on index 1 (channel1 = 1, channel8 = 8)
        //
        //Returns:
        //    true if the channel is enabled, false if the channel is disabled
        bool enabled(uint8 channel) const;

        //API Function: enable
        //    Enables or disables a specified channel
        //
        //Parameters:
        //    channel - The channel to enable or disable, based on index 1 (channel1 = 1, channel8 = 8)
        //    enable - Set to true to enable the channel, false to disable the channel
        void enable(uint8 channel, bool enable = true);

        //API Function: lastChEnabled
        //    Finds the last channel (highest channel number) that is enabled in the mask.
        //    This is useful when looping over the ChannelMask object and performing an action on all enabled channels.
        //
        //Returns:
        //    The channel number (ch1 = 1, ch16 = 16) of the last channel enabled. 0 if no channels are enabled.
        uint8 lastChEnabled() const;
    };
}