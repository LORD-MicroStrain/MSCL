/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/StructuralHealth.h"

namespace mscl
{
    StructuralHealth::StructuralHealth(float angle, uint32 uptime, float damage, const SampleRate& processingRate, const Histogram& histogram) :
        m_angle(angle),
        m_uptime(uptime),
        m_damage(damage),
        m_processingRate(processingRate),
        m_histogram(histogram)
    {}

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
} // namespace mscl
