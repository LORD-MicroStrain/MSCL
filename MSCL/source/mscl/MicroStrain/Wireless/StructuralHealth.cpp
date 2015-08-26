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
#include "StructuralHealth.h"

namespace mscl
{
	StructuralHealth::StructuralHealth(float angle, uint32 uptime, float damage, const SampleRate& processingRate, const Histogram& histogram):
		m_angle(angle),
		m_uptime(uptime),
		m_damage(damage),
		m_processingRate(processingRate),
		m_histogram(histogram)
	{ }

	float StructuralHealth::angle() const
	{
		return m_angle;
	}

	uint32 StructuralHealth::uptime() const
	{
		return m_uptime;
	}

	float StructuralHealth::damage() const
	{
		return m_damage;
	}

	const SampleRate& StructuralHealth::processingRate() const
	{
		return m_processingRate;
	}

	const Histogram& StructuralHealth::histogram() const
	{
		return m_histogram;
	}
}