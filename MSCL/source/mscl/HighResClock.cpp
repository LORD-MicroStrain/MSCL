/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "HighResClock.h"
#include <chrono>

namespace mscl
{

    HighResClock::HighResClock() :
        m_startHighResNanos(std::chrono::nanoseconds(std::chrono::high_resolution_clock::now().time_since_epoch()).count()),
        m_startSysTimeNanos(std::chrono::nanoseconds(std::chrono::system_clock::now().time_since_epoch()).count())
    {
    }

    uint64 HighResClock::getCurrentSystemTime() const
    {
        //get the current time from the high_res clock, in nanoseconds since epoch
        uint64 nanoseconds = std::chrono::nanoseconds(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

        //calculate the difference between this current time and the start high_res clock time
        uint64 diff = nanoseconds - m_startHighResNanos;

        //add the difference from the high_res clock to the start system clock time to get the nanoseconds in system time
        return m_startSysTimeNanos + diff;
    }

}
