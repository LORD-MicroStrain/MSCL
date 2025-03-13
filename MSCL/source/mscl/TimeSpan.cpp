/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"

#include "TimeSpan.h"
#include "Timestamp.h"

namespace mscl
{
    TimeSpan::TimeSpan(uint64 nanoseconds) :
        m_nanoseconds(nanoseconds)
    {
    }

    bool TimeSpan::operator == (const TimeSpan& other) const { return compare(other) == 0; }
    bool TimeSpan::operator != (const TimeSpan& other) const { return compare(other) != 0; }
    bool TimeSpan::operator < (const TimeSpan& other) const { return compare(other) < 0; }
    bool TimeSpan::operator <= (const TimeSpan& other) const { return compare(other) <= 0; }
    bool TimeSpan::operator > (const TimeSpan& other) const { return compare(other) > 0; }
    bool TimeSpan::operator >= (const TimeSpan& other) const { return compare(other) >= 0; }

    int64 TimeSpan::compare(const TimeSpan& other) const
    {
        //get the difference between the nanoseconds of the TimeSpan
        int64 difference = m_nanoseconds - other.m_nanoseconds;

        //return the difference
        return difference;
    }

    uint64 TimeSpan::getNanoseconds() const
    {
        return m_nanoseconds;
    }

    uint64 TimeSpan::getMicroseconds() const
    {
        return m_nanoseconds / NANOSECONDS_PER_MICROSECOND;
    }

    uint64 TimeSpan::getMilliseconds() const
    {
        return m_nanoseconds / NANOSECONDS_PER_MILLISECOND;
    }

    uint64 TimeSpan::getSeconds() const
    {
        return m_nanoseconds / NANOSECONDS_PER_SECOND;
    }

    TimeSpan TimeSpan::NanoSeconds(uint64 nanoseconds)    { return TimeSpan(static_cast<uint64>(nanoseconds)    * 1); }
    TimeSpan TimeSpan::MicroSeconds(uint64 microseconds){ return TimeSpan(static_cast<uint64>(microseconds) * 1000); }
    TimeSpan TimeSpan::MilliSeconds(uint64 milliseconds){ return TimeSpan(static_cast<uint64>(milliseconds) * 1000000); }
    TimeSpan TimeSpan::Seconds(uint64 seconds)            { return TimeSpan(static_cast<uint64>(seconds)        * 1000000000); }
    TimeSpan TimeSpan::Minutes(int minutes)                { return TimeSpan(static_cast<uint64>(minutes)        * 1000000000 * 60); }
    TimeSpan TimeSpan::Hours(int hours)                    { return TimeSpan(static_cast<uint64>(hours)        * 1000000000 * 60 * 60); }
    TimeSpan TimeSpan::Days(int days)                    { return TimeSpan(static_cast<uint64>(days)            * 1000000000 * 60 * 60 * 24); }

    TimeSpan operator*(TimeSpan timeSpan, uint32 factor)
    {
        timeSpan.m_nanoseconds *= factor;
        return timeSpan;
    }

    TimeSpan operator*(uint32 factor, TimeSpan timeSpan)
    {
        timeSpan.m_nanoseconds *= factor;
        return timeSpan;
    }

    TimeSpan operator/(TimeSpan timeSpan, uint32 divisor)
    {
        timeSpan.m_nanoseconds /= divisor;
        return timeSpan;
    }

    TimeSpan operator/(uint32 divisor, TimeSpan timeSpan)
    {
        timeSpan.m_nanoseconds /= divisor;
        return timeSpan;
    }
}
