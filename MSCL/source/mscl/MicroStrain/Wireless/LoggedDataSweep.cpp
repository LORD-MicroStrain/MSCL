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
#include "LoggedDataSweep.h"

namespace mscl
{
	LoggedDataSweep::LoggedDataSweep() :
		m_timestamp(0),
		m_tick(0)
	{
	}

	LoggedDataSweep::LoggedDataSweep(const Timestamp& timestamp, uint64 tick, const ChannelData& data) :
		m_timestamp(timestamp),
		m_tick(tick),
		m_data(data)
	{
	}

	Timestamp LoggedDataSweep::timestamp() const
	{
		return m_timestamp;
	}

	void LoggedDataSweep::timestamp(const Timestamp& time)
	{
		m_timestamp = time;
	}

	uint64 LoggedDataSweep::nanoseconds() const
	{
		return m_timestamp.nanoseconds();
	}

	uint64 LoggedDataSweep::tick() const
	{
		return m_tick;
	}

	void LoggedDataSweep::tick(uint64 tick)
	{
		m_tick = tick;
	}

	const ChannelData& LoggedDataSweep::data() const
	{
		return m_data;
	}

	void LoggedDataSweep::data(ChannelData data)
	{
		m_data = data;
	}
}