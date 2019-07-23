/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "boost/date_time.hpp"                                    //for boost::posix_time::time_facet
#include "boost/date_time/posix_time/posix_time_duration.hpp"    //for boost::posix_time durations

#include "Timestamp.h"
#include "TimeSpan.h"
#include "Types.h"
#include "Utils.h"

#include <chrono>
#include <time.h>


namespace mscl
{
    uint8 Timestamp::s_gpsLeapSeconds = 18;

    //constructor
    Timestamp::Timestamp(uint64 nanoseconds/*=0*/) :
        m_nanoseconds(nanoseconds)
    {
    }

    Timestamp::Timestamp(uint16 year, uint16 month, uint16 day, uint16 hour, uint16 minute, uint16 second, uint32 milli)
    {
        boost::posix_time::ptime dateTime(boost::gregorian::date(year, month, day),
                                          boost::posix_time::hours(hour) + boost::posix_time::minutes(minute) + boost::posix_time::seconds(second) + boost::posix_time::milliseconds(milli));
        m_nanoseconds = (dateTime - boost::posix_time::from_time_t(0)).total_nanoseconds();
    }

    TimeSpan Timestamp::operator-(const Timestamp& other) const
    {
        uint64 diff;

        //if the current timestamp comes before the other timestamp
        if(m_nanoseconds < other.m_nanoseconds)
        {
            //subtract the current timestamp from the other timestamp
            diff = other.m_nanoseconds - m_nanoseconds;
        }
        //if the current timestamp comes after the other timestamp
        else
        {
            //subtract the other timestamp from the current timestamp
            diff = m_nanoseconds - other.m_nanoseconds;
        }

        //return a TimeSpan with the difference
        return TimeSpan::NanoSeconds(diff);
    }

    bool Timestamp::operator==(const Timestamp& other) const
    {
        return m_nanoseconds == other.m_nanoseconds;
    }

    bool Timestamp::operator!=(const Timestamp& other) const
    {
        return m_nanoseconds != other.m_nanoseconds;
    }

    bool Timestamp::operator<(const Timestamp& other) const
    {
        return m_nanoseconds < other.m_nanoseconds;
    }

    bool Timestamp::operator<=(const Timestamp& other) const
    {
        return m_nanoseconds <= other.m_nanoseconds;
    }

    bool Timestamp::operator>(const Timestamp& other) const
    {
        return m_nanoseconds > other.m_nanoseconds;
    }

    bool Timestamp::operator>=(const Timestamp& other) const
    {
        return m_nanoseconds >= other.m_nanoseconds;
    }

    //get the number of nanoseconds since epoch
    uint64 Timestamp::nanoseconds() const
    {
        return m_nanoseconds;
    }

    //get the number of seconds since epoch
    uint64 Timestamp::seconds() const
    {
        return m_nanoseconds / TimeSpan::NANOSECONDS_PER_SECOND;
    }

    //set the number of nanoseconds since epoch
    void Timestamp::setTime(uint64 nanosSinceEpoch)
    {
        m_nanoseconds = nanosSinceEpoch;
    }

    //Sets the nanoseconds value to the current system time in UTC
    void Timestamp::setTimeNow()
    {
        setTime(Utils::getCurrentSystemTime());
    }

    Timestamp Timestamp::timeNow()
    {
        //build a Timestamp object
        Timestamp result;

        //set the time to the current system time
        result.setTimeNow();

        //return the Timestamp object
        return result;
    }

    void Timestamp::setLeapSeconds(uint8 gpsLeapSeconds)
    {
        Timestamp::s_gpsLeapSeconds = gpsLeapSeconds;
    }

    uint8 Timestamp::getLeapSeconds()
    {
        return s_gpsLeapSeconds;
    }

    std::string Timestamp::str() const
    {
        std::stringstream result;

        //convert the nanoseconds to seconds
        time_t timeInSec = m_nanoseconds / TimeSpan::NANOSECONDS_PER_SECOND;

        //convert the time_t value to a tm structure
        tm myTm;

#ifdef _WIN32
        gmtime_s(&myTm, &timeInSec);
#else
        gmtime_r(&timeInSec, &myTm);
#endif

        //format the time into a string (in locale format)
        char out[100];
        strftime(out, 100, "%Y-%m-%d %H:%M:%S", &myTm);

        //add the subseconds onto the end of the string
        result << out << "." << std::setfill('0') << std::setw(9) << m_nanoseconds % TimeSpan::NANOSECONDS_PER_SECOND;

        return result.str();
    }

    uint64 Timestamp::gpsTimeToUtcTime(double timeOfWeek, uint16 weekNumber)
    {
        //split the seconds and subseconds out to get around the double resolution issue
        double seconds;
        double subseconds = modf(timeOfWeek, &seconds);

        // seconds since start of Unix time = seconds between 1970 and 1980 + number of weeks since 1980 * number of seconds in a week + number of complete seconds past in current week - leap seconds since start of GPS time
        return static_cast<uint64>((315964800 + weekNumber * 604800 + static_cast<uint64>(seconds) - Timestamp::getLeapSeconds()) * TimeSpan::NANOSECONDS_PER_SECOND) + static_cast<uint64>(std::round(subseconds * static_cast<double>(TimeSpan::NANOSECONDS_PER_SECOND)));
    }
}