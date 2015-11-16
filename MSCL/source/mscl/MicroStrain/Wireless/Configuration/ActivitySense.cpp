/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "ActivitySense.h"

namespace mscl
{
    ActivitySense::ActivitySense():
        m_enabled(false),
        m_activityThreshold(0.0),
        m_inactivityThreshold(0.0),
        m_activityTime(0.0),
        m_inactivityTimeout(0.0)
    {
    }

    bool ActivitySense::enabled() const
    {
        return m_enabled;
    }

    void ActivitySense::enabled(bool enable)
    {
        m_enabled = enable;
    }

    float ActivitySense::activityThreshold() const
    {
        return m_activityThreshold;
    }

    void ActivitySense::activityThreshold(float threshold)
    {
        m_activityThreshold = threshold;
    }

    float ActivitySense::inactivityThreshold() const
    {
        return m_inactivityThreshold;
    }

    void ActivitySense::inactivityThreshold(float threshold)
    {
        m_inactivityThreshold = threshold;
    }

    float ActivitySense::activityTime() const
    {
        return m_activityTime;
    }

    void ActivitySense::activityTime(float time)
    {
        m_activityTime = time;
    }

    float ActivitySense::inactivityTimeout() const
    {
        return m_inactivityTimeout;
    }

    void ActivitySense::inactivityTimeout(float timeout)
    {
        m_inactivityTimeout = timeout;
    }
}