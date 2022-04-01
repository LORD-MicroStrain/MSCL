/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "PositionOffset.h"

namespace mscl
{
    PositionOffset::PositionOffset():
        m_x(0.0f),
        m_y(0.0f),
        m_z(0.0f)
    {
    }

    PositionOffset::PositionOffset(float x, float y, float z):
        m_x(x),
        m_y(y),
        m_z(z)
    {
    }

    float PositionOffset::x() const
    {
        return m_x;
    }

    float PositionOffset::y() const
    {
        return m_y;
    }

    float PositionOffset::z() const
    {
        return m_z;
    }
}