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
//PUBLIC_HEADER
#pragma once

#include <memory>

#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/Timestamp.h"
#include "WirelessDataPoint.h"
#include "WirelessTypes.h"

namespace mscl
{
	//API Class: LoggedDataSweep
	//	Represents 1 data sweep that was logged to a <WirelessNode>.
	class LoggedDataSweep
	{
	public:
		//Function: LoggedDataSweep
		//	Creates a LoggedDataSweep object with a tick and timestamp of 0.
		LoggedDataSweep();
		
		//Function: LoggedDataSweep
		//	Creates a LoggedDataSweep object.
		//
		//Parameters:
		//	timestamp - The <Timestamp> of the sweep.
		//	tick - The tick of the sweep.
		//	data - The <ChannelData> containing the actual data points.
		LoggedDataSweep(const Timestamp& timestamp, uint64 tick, const ChannelData& data);

	private:
		//Variable: m_timestamp
		//	The <Timestamp> of the data sweep.
		Timestamp m_timestamp;

		//Variable: m_tick
		//	The tick value representing the count of each sweep in a datalogging session (increments with each sweep).
		uint64 m_tick;

		//Variable: m_data
		//	Contains one or more <WirelessDataPoint>s, corresponding to each channel's data for this sweep.
		ChannelData m_data;

	public:
		//API Function: timestamp
		//	Gets the timestamp of the sweep as a <Timestamp>
		//
		//Returns:
		//	A <Timestamp> representing the timestamp of the sweep
		Timestamp timestamp() const;

		//API Function: nanoseconds
		//	Gets the timestamp of the sweep in nanoseconds since UTC
		//
		//Returns:
		//	The timestamp of the sweep in nanoseconds since UTC
		uint64 nanoseconds() const;

		//API Function: tick
		//	Gets the tick value of the sweep
		//
		//Returns:
		//	The tick value of the sweep
		uint64 tick() const;

		//API Function: data
		//	Gets the channel data in this sweep as a <WirelessDataPoint::ChannelData> container.
		//
		//Returns:
		//	A <WirelessDataPoint::ChannelData> container holding the data for the sweep.
		const ChannelData& data() const;

#ifndef SWIG
		//Function: timestamp
		//	Sets the timestamp of the sweep
		//
		//Parameters:
		//	time - The <Timestamp> to set
		void timestamp(const Timestamp& time);

		//Function: tick
		//	Sets the tick of the sweep
		//
		//Parameters:
		//	tick - The tick to set
		void tick(uint64 tick);

		//Function: data
		//	Sets the data of the sweep
		//
		//Parameters:
		//	data - The <ChannelData> to set
		void data(ChannelData data);
#endif
	};

	//API Typedef: LoggedDataSweeps
	//	Typedef for a vector of <LoggedDataSweep> objects.
	typedef std::vector<LoggedDataSweep> LoggedDataSweeps;

}