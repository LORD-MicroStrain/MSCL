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

#include "HistogramOptions.h"

namespace mscl
{
	HistogramOptions::HistogramOptions():
		m_transmitRate(WirelessTypes::sampleRate_30Sec),
		m_binStart(0),
		m_binSize(5)
	{
	}

	WirelessTypes::WirelessSampleRate HistogramOptions::transmitRate() const
	{
		return m_transmitRate;
	}

	void HistogramOptions::transmitRate(WirelessTypes::WirelessSampleRate rate)
	{
		m_transmitRate = rate;
	}

	uint16 HistogramOptions::binsStart() const
	{
		return m_binStart;
	}

	void HistogramOptions::binsStart(uint16 start)
	{
		m_binStart = start;
	}

	uint16 HistogramOptions::binsSize() const
	{
		return m_binSize;
	}

	void HistogramOptions::binsSize(uint16 size)
	{
		m_binSize = size;
	}
}