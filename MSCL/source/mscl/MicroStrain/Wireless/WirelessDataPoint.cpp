/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
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
		m_channelName("unknown")
	{
	}

	//WirelessDataPoint constructor
	WirelessDataPoint::WirelessDataPoint(WirelessChannel::ChannelId channelId, uint8 channelNumber, ValueType type, const anyType& value):
		DataPoint(type, value),
		m_channelId(channelId),
		m_channelNumber(channelNumber),
		m_channelName(WirelessChannel::channelName(m_channelId))
	{
	}

	//WirelessDataPoint constructor
	WirelessDataPoint::WirelessDataPoint(WirelessChannel::ChannelId channelId, uint8 channelNumber, const std::string& channelName, ValueType type, const anyType& value):
		DataPoint(type, value),
		m_channelId(channelId),
		m_channelNumber(channelNumber),
		m_channelName(channelName)
	{
	}

	//	Gets the WirelessChannel::ChannelId for the data point
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
		return m_channelName;
	}
}