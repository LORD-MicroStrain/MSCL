/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "HighResClock.h"
#include <boost/chrono/chrono.hpp>

namespace mscl
{

    HighResClock::HighResClock() :
        m_startHighResNanos(boost::chrono::nanoseconds(boost::chrono::high_resolution_clock::now().time_since_epoch()).count()),    //Note: this could use a std::chrono::high_resolution_clock except there is a bug in VS2013 where this always compiles as a system_clock.
        m_startSysTimeNanos(boost::chrono::nanoseconds(boost::chrono::system_clock::now().time_since_epoch()).count())
    {
    }

    uint64 HighResClock::getCurrentSystemTime() const
    {
        //get the current time from the high_res clock, in nanoseconds since epoch
        uint64 nanoseconds = boost::chrono::nanoseconds(boost::chrono::high_resolution_clock::now().time_since_epoch()).count();

        //calculate the difference between this current time and the start high_res clock time
        uint64 diff = nanoseconds - m_startHighResNanos;

        //add the difference from the high_res clock to the start system clock time to get the nanoseconds in system time
        return m_startSysTimeNanos + diff;
    }

}