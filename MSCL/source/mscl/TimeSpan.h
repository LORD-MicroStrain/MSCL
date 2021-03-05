/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "Types.h"

namespace mscl
{
    
    //API Class: TimeSpan
    //    Represents a range of time
    class TimeSpan
    {
#ifndef SWIG
        friend TimeSpan operator*(TimeSpan timeSpan, uint32 factor);
        friend TimeSpan operator*(uint32 factor, TimeSpan timeSpan);
        friend TimeSpan operator/(TimeSpan timeSpan, uint32 divisor);
        friend TimeSpan operator/(uint32 divisor, TimeSpan timeSpan);
#endif        

    public:
        //===========================================================================================
        //API Constants:
        //    NANOSECONDS_PER_MICROSECOND   - 1000          - The number of nanoseconds in 1 microsecond
        //    NANOSECONDS_PER_MILLISECOND   - 1000000       - The number of nanoseconds in 1 millisecond
        //    NANOSECONDS_PER_SECOND        - 1000000000L   - The number of nanoseconds in 1 second
        //===========================================================================================
        static const uint64 NANOSECONDS_PER_MICROSECOND = 1000;
        static const uint64 NANOSECONDS_PER_MILLISECOND = 1000000;
        static const uint64 NANOSECONDS_PER_SECOND      = 1000000000L;

    private:
        TimeSpan(){};    //default constructor disabled

        //Constructor: TimeSpan
        //    Creates a TimeSpan given the nanoseconds value.
        //    This constructor is private to force use of the static constructor methods to create a timespan.
        //
        //Parameters:
        //    nanoseconds - The number of nanoseconds to create the TimeSpan with.
        explicit TimeSpan(uint64 nanoseconds);

    protected:
        //Variable: m_nanoseconds
        //    The number of nanoseconds in the timespan
        uint64 m_nanoseconds;

    public:
#ifndef SWIG
        bool operator == (const TimeSpan& other) const;
        bool operator != (const TimeSpan& other) const;
        bool operator < (const TimeSpan& other) const;
        bool operator <= (const TimeSpan& other) const;
        bool operator > (const TimeSpan& other) const;
        bool operator >= (const TimeSpan& other) const;
#endif

    private:
        //Function: compare
        //    Gets the difference (in nanoseconds) of the two TimeSpans.
        //
        //Parameters:
        //    other - The other <TimeSpan> to compare.
        //
        //Returns:
        //    The difference in nanoseconds of the two TimeSpans.
        int64 compare(const TimeSpan& other) const;

    public:
        //API Function: getNanoseconds
        //    Gets the nanoseconds resolution of the TimeSpan
        //
        //Returns:
        //    The TimeSpan in nanoseconds resolution
        uint64 getNanoseconds() const;

        //API Function: getMicroseconds
        //    Gets the microsecond resolution of the TimeSpan
        //
        //Returns:
        //    The TimeSpan in microsecond resolution
        uint64 getMicroseconds() const;

        //API Function: getMilliseconds
        //    Gets the millisecond resolution of the TimeSpan
        //
        //Returns:
        //    The TimeSpan in milliseconds resolution
        uint64 getMilliseconds() const;

        //API Function: getSeconds
        //    Gets the seconds resolution of the TimeSpan
        //
        //Returns:
        //    The TimeSpan in seconds resolution
        uint64 getSeconds() const;

    public:
        //API Function: NanoSeconds
        //    Creates a TimeSpan object from nanoseconds
        //
        //Parameters:
        //    nanoseconds - The number of nanoseconds for the timespan
        //
        //Returns:
        //    A TimeSpan object representative of the passed in value
        static TimeSpan NanoSeconds(uint64 nanoseconds);

        //API Function: MicroSeconds
        //    Creates a TimeSpan object from microseconds
        //
        //Parameters:
        //    microseconds - The number of microseconds for the timespan
        //
        //Returns:
        //    A TimeSpan object representative of the passed in value
        static TimeSpan MicroSeconds(uint64 microseconds);

        //API Function: MilliSeconds
        //    Creates a TimeSpan object from milliseconds
        //
        //Parameters:
        //    milliseconds - The number of milliseconds for the timespan
        //
        //Returns:
        //    A TimeSpan object representative of the passed in value
        static TimeSpan MilliSeconds(uint64 milliseconds);

        //API Function: Seconds
        //    Creates a TimeSpan object from seconds
        //
        //Parameters:
        //    seconds - The number of seconds for the timespan
        //
        //Returns:
        //    A TimeSpan object representative of the passed in value
        static TimeSpan Seconds(uint64 seconds);

        //API Function: Minutes
        //    Creates a TimeSpan object from minutes
        //
        //Parameters:
        //    minutes - The number of minutes for the timespan
        //
        //Returns:
        //    A TimeSpan object representative of the passed in value
        static TimeSpan Minutes(int minutes);

        //API Function: Hours
        //    Creates a TimeSpan object from hours
        //
        //Parameters:
        //    hours - The number of hours for the timespan
        //
        //Returns:
        //    A TimeSpan object representative of the passed in value
        static TimeSpan Hours(int hours);

        //API Function: Days
        //    Creates a TimeSpan object from days
        //
        //Parameters:
        //    days - The number of days for the timespan
        //
        //Returns:
        //    A TimeSpan object representative of the passed in value
        static TimeSpan Days(int days);
    };
    
#ifndef SWIG
    TimeSpan operator*(TimeSpan timeSpan, uint32 factor);
    TimeSpan operator*(uint32 factor, TimeSpan timeSpan);
    TimeSpan operator/(TimeSpan timeSpan, uint32 divisor);
    TimeSpan operator/(uint32 divisor, TimeSpan timeSpan);
#endif
}