/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "WirelessDataPoint.h"
#include "WirelessChannel.h"

namespace mscl
{
    //WirelessDataPoint default constructor
    WirelessDataPoint::WirelessDataPoint(): 
        DataPoint(valueType_float, anyType(0.0f)),
        m_channelId(WirelessChannel::channel_unknown),
        m_channelNumber(0),
        m_channelName([](){return "unknown";})
    {
    }

    //WirelessDataPoint constructor
    WirelessDataPoint::WirelessDataPoint(WirelessChannel::ChannelId channelId,
                                         uint8 channelNumber,
                                         ValueType type,
                                         const anyType& value,
                                         const ChannelProperties& channelProperties):
        DataPoint(type, value, channelProperties),
        m_channelId(channelId),
        m_channelNumber(channelNumber),
        m_channelName(std::bind(WirelessChannel::channelName, m_channelId))
    {
    }

    //WirelessDataPoint constructor
    WirelessDataPoint::WirelessDataPoint(WirelessChannel::ChannelId channelId,
                                         uint8 channelNumber,
                                         const Utils::Lazy<std::string>& channelName,
                                         ValueType type,
                                         const anyType& value,
                                         const ChannelProperties& channelProperties):
        DataPoint(type, value, channelProperties),
        m_channelId(channelId),
        m_channelNumber(channelNumber),
        m_channelName(channelName)
    {
    }

    //    Gets the WirelessChannel::ChannelId for the data point
    WirelessChannel::ChannelId WirelessDataPoint::channelId() const
    {
        return m_channelId;
    }

    uint8 WirelessDataPoint::channelNumber() const
    {
        return m_channelNumber;
    }

    const std::string& WirelessDataPoint::channelName() const
    {
        return *m_channelName;
    }
}
