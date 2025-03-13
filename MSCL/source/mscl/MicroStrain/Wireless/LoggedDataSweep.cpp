/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "LoggedDataSweep.h"

namespace mscl
{
    LoggedDataSweep::LoggedDataSweep() :
        m_timestamp(0),
        m_tick(0),
        m_calsApplied(false)
    {
    }

    LoggedDataSweep::LoggedDataSweep(const Timestamp& timestamp, uint64 tick, const ChannelData& data, bool calsApplied) :
        m_timestamp(timestamp),
        m_tick(tick),
        m_data(data),
        m_calsApplied(calsApplied)
    {
    }

    Timestamp LoggedDataSweep::timestamp() const
    {
        return m_timestamp;
    }

    uint64 LoggedDataSweep::tick() const
    {
        return m_tick;
    }

    const ChannelData& LoggedDataSweep::data() const
    {
        return m_data;
    }

    bool LoggedDataSweep::calApplied() const
    {
        return m_calsApplied;
    }
}
