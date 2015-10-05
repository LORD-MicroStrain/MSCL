/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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