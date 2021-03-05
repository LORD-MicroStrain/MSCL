/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "WirelessChannel.h"
#include "mscl/MicroStrain/DataPoint.h"
#include "mscl/Utils.h"

namespace mscl
{
    //API Class: WirelessDataPoint
    //    Represents a single channel's data point within a sweep
    //
    //See Also: 
    //    <DataPoint>, <Value>
    class WirelessDataPoint : public DataPoint
    {
    public:
        //Default Constructor: WirelessDataPoint
        //    Builds a WirelessDataPoint object
        WirelessDataPoint();

#ifndef SWIG
        //Constructor: WirelessDataPoint
        //    Builds a WirelessDataPoint object.
        //    The channel name will be automatically generated from the given channel id.
        //    
        //Parameters:
        //    channelId - The <WirelessChannel::ChannelId> of the the data point
        //    channelNumber - The channel number associated with the data point (ch1 = 1, ch8 = 8).
        //    type - The <ValueType> of the value to be stored
        //    value - The value to store
        //    channelProperties - Any <ChannelProperties> to store for later retrieval.
        WirelessDataPoint(
            WirelessChannel::ChannelId channelId,
            uint8 channelNumber,
            ValueType type,
            const anyType& value,
            const ChannelProperties& channelProperties = ChannelProperties());

        //Constructor: WirelessDataPoint
        //    Builds a WirelessDataPoint object.
        //    
        //Parameters:
        //    channelId - The <WirelessChannel::ChannelId> of the the data point
        //    channelNumber - The channel number associated with the data point (ch1 = 1, ch8 = 8).
        //    channelName - The channel name associated with the data point.
        //    type - The <ValueType> of the value to be stored
        //    value - The value to store
        //    channelProperties - Any <ChannelProperties> to store for later retrieval.
        WirelessDataPoint(
            WirelessChannel::ChannelId channelId,
            uint8 channelNumber,
            const Utils::Lazy<std::string>& channelName,
            ValueType type,
            const anyType& value,
            const ChannelProperties& channelProperties = ChannelProperties());
#endif
    
    private:
        //Variable: m_channelId
        //    The <WirelessChannel::ChannelId> representing information about the channel this data point is associated with
        WirelessChannel::ChannelId m_channelId;

        //Variable: m_channelNumber
        //    The channel number associated with the data point (ch1 = 1, ch8 = 8).
        uint8 m_channelNumber;

        //Variable: m_channelName
        //    The channel name associated with the data point (as a lazy load function).
        mutable Utils::Lazy<std::string> m_channelName;

    public:
        //API Function: channelId
        //    Gets the <WirelessChannel::ChannelId> associated with the data point.
        //
        //Returns:
        //    A <WirelessChannel::ChannelId> representing which channel this data corresponds with.
        WirelessChannel::ChannelId channelId() const;

        //API Function: channelNumber
        //    Gets the channel number associated with the data point (ch1 = 1, ch8 = 8), when applicable.
        //    Otherwise, this will return a 0 (for example, a Structural Health data point doesn't relate
        //    an actual channel on the Wireless Node, so this will be a 0).
        //    This number can be used to relate to the Node's <WirelessChannel> in the 
        //    map returned from calling <WirelessNode::channels>().
        //
        //Returns:
        //    The channel number associated with the data point.
        uint8 channelNumber() const;

        //API Function: channelName
        //    Gets the name of the channel. 
        //    This is the universal channel name that should be used for uploading to SensorCloud.
        //
        //Returns:
        //    The name of the channel.
        const std::string& channelName() const;
    };

    //API Typedef: ChannelData
    //    A typedef for a collection (vector) of <WirelessDataPoint>s
    typedef std::vector<WirelessDataPoint> ChannelData;
}
