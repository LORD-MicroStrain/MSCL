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
#include "Histogram.h"

namespace mscl
{
	Bin::Bin(const Value& start, const Value& end, uint32 count):
		m_start(start),
		m_end(end),
		m_count(count)
	{
	}

	Value Bin::start() const
	{
		return m_start;
	}

	Value Bin::end() const
	{
		return m_end;
	}

	uint32 Bin::count() const
	{
		return m_count;
	}



	Histogram::Histogram(const Value& binsStart, const Value& binsSize):
		m_binsStart(binsStart),
		m_binsSize(binsSize)
	{
	}

	Value Histogram::binsStart() const
	{
		return m_binsStart;
	}

	Value Histogram::binsSize() const
	{
		return m_binsSize;
	}

	Bins Histogram::bins() const
	{
		return m_bins;
	}

	void Histogram::addBin(const Bin& bin)
	{
		m_bins.push_back(bin);
	}
}