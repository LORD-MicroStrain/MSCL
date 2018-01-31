/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "EulerAngles.h"

namespace mscl
{
    EulerAngles::EulerAngles():
        m_roll(0.0f),
        m_pitch(0.0f),
        m_yaw(0.0f)
    {
    }

    EulerAngles::EulerAngles(float roll, float pitch, float yaw):
        m_roll(roll),
        m_pitch(pitch),
        m_yaw(yaw)
    {
    }

    float EulerAngles::roll() const
    {
        return m_roll;
    }

    float EulerAngles::pitch() const
    {
        return m_pitch;
    }

    float EulerAngles::yaw() const
    {
        return m_yaw;
    }
}