/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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