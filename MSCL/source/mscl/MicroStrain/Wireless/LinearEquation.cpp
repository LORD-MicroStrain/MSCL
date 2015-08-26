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
#include "LinearEquation.h"

namespace mscl
{
	LinearEquation::LinearEquation():
		m_slope(1.0f),
		m_offset(0.0f)
	{ }

	LinearEquation::LinearEquation(float slope, float offset):
		m_slope(slope),
		m_offset(offset)
	{ }

	void LinearEquation::slope(float slope)
	{
		m_slope = slope;
	}

	float LinearEquation::slope() const
	{
		return m_slope;
	}

	void LinearEquation::offset(float offset)
	{
		m_offset = offset;
	}

	float LinearEquation::offset() const
	{
		return m_offset;
	}
}