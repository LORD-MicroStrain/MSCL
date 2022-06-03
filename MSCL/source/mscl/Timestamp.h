/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include <iostream>
#include "TimeSpan.h"
#include "Types.h"

namespace mscl
{
    //API Class: Timestamp
    //    Represents a date/time object 
    class Timestamp
    {
    public:
        //API Enum: Epoch
        //  Epoch indicator: Unix, GPS.
        //  Timestamp class uses Unix epoch by default.
        //
        //      UNIX    - 0x01
        //      GPS     - 0x02
        enum Epoch
        {
            UNIX = 0x01,
            GPS = 0x02
        };

    public:
        //API Constructor: Timestamp
        //    Creates a Timestamp object based on the nanoseconds parameter
        //
        //Parameters:
        //    nanoseconds - The number of nanoseconds since unix epoch (default of 0)
        explicit Timestamp(uint64 nanoseconds=0, Epoch epoch = Epoch::UNIX);

        //API Constructor: Timestamp
        //    Creates a Timestamp object from the given year, month, day, hour, minute, second, millisecond parameters
        //
        //Parameters:
        //    year - The year of the timestamp (ex. 2013)
        //    month - The month of the timestamp (ex. 3)
        //    day - The day of the timestamp (ex. 31)
        //    hour - The hour of the timestamp (ex. 21)
        //    minute - The minute of the timestamp (ex. 58)
        //    second - The second of the timestamp (ex. 59)
        //    millisecond - The milliseconds of the timestamp (ex. 123)
        Timestamp(uint16 year, uint16 month, uint16 day, uint16 hour, uint16 minute, uint16 second, uint32 milli);

        virtual ~Timestamp() {};

    private:
        //Variable: m_nanoseconds
        //    The number of nanoseconds since the m_epoch epoch
        uint64 m_nanoseconds;

        //Variable: m_epoch
        //    The epoch the nanosecond count is stored in.
        //    This is to avoid loss of precision during conversion when the source value is GPS time, converting to and from Unix
        Epoch m_epoch;

        //Variable: s_gpsLeapSeconds
        //  The (hardcoded) number of leap seconds since Jan 1 1980, used in converting GPS timestamps to UTC timestamps.
        static uint8 s_gpsLeapSeconds;

    public:
#ifndef SWIG
        //Operator: -
        //    Gets the <TimeSpan> representing the distance (always positive) between two Timestamps. 
        //
        //Returns:
        //    A <TimeSpan> representing the difference between the 2 Timestamps.
        TimeSpan operator-(const Timestamp& other) const;

        //Operator: ==
        //  Equal operator for comparing Timestamps.
        virtual bool operator==(const Timestamp& other) const;

        //Operator: !=
        //  Not Equal operator for comparing Timestamps.
        virtual bool operator!=(const Timestamp& other) const;

        //Operator: <
        //  Less Than operator for comparing Timestamps.
        virtual bool operator<(const Timestamp& other) const;

        //Operator: <=
        //  Less Than or Equal To operator for comparing Timestamps.
        virtual bool operator<=(const Timestamp& other) const;

        //Operator: >
        //  Greater Than operator for comparing Timestamps.
        virtual bool operator>(const Timestamp& other) const;

        //Operator: >=
        //  Greater Than or Equal To operator for comparing Timestamps.
        virtual bool operator>=(const Timestamp& other) const;
#endif

    public:
        //API Function: nanoseconds
        //    Gets the number of nanoseconds since the specified epoch
        //
        //Parameters:
        //    epoch - the epoch for this value (default Unix)
        //
        //Returns:
        //    The number of nanoseconds since the specified epoch
        uint64 nanoseconds(Epoch epoch = Epoch::UNIX) const;

        //API Function: seconds
        //    Gets the number of seconds since the specified epoch
        //
        //Parameters:
        //    epoch - the epoch for this value (default Unix)
        //
        //Returns:
        //    The number of nanoseconds since the specified epoch
        uint64 seconds(Epoch epoch = Epoch::UNIX) const;

        //API Function: storedEpoch
        //    Gets the epoch the source value is stored in. Regardless of stored epoch, the value can be read out in both Unix and GPS.
        //
        //Returns:
        //    The stored <Epoch>
        Epoch storedEpoch() const { return m_epoch; };

        //API Function: str
        //    Gets a string representation of the Timestamp object in ISO 8601 Date/Time format.
        //
        //Returns:
        //    A string representation of the Timestamp.
        std::string str() const;

        //API Function: setTime
        //    Updates the Timestamp to the given number of nanoseconds since the unix epoch.
        //
        //Parameters:
        //    nanosSinceEpoch - The number of nanoseconds since the unix epoch.
        //    epoch - the epoch for this value (default Unix)
        void setTime(uint64 nanosSinceEpoch, Epoch epoch = Epoch::UNIX);

        //API Function: setTimeNow
        //    Sets the Timestamp object to the current system time in UTC
        void setTimeNow();

    public:
        //API Function: timeNow
        //    Creates a timestamp using the current system time
        //
        //Returns:
        //    A Timestamp object representing the current system time
        static Timestamp timeNow();

        //API Function: setLeapSeconds
        //  Adjusts the hardcoded number of leap seconds since Jan 1 1980, used in converting GPS timestamps to UTC timestamps.
        //  Note: New releases of MSCL should be available when the leap seconds change. You can also adjust this
        //        value yourself to correct your current version of MSCL without updating.
        //
        //Parameters:
        //  gpsLeapSeconds - The number of leap seconds since Jan 1 1980.
        static void setLeapSeconds(uint8 gpsLeapSeconds);

        //API Function: getLeapSeconds
        //  Gets the current number of leap seconds since Jan 1 1980, used in converting GPS timestamps to UTC timestamps.
        static uint8 getLeapSeconds();

        //API Function: gpsTimeToUtcTime
        //  Converts the gps time into the UTC time in nanoseconds since the unix epoch.
        //  Note: this uses the value stored in <Utils::gpsLeapSeconds> in its conversion.
        static uint64 gpsTimeToUtcTime(double timeOfWeek, uint16 weekNumber);

        //API Function: gpsTimeToUtcTime
        //  Converts the gps time into the UTC time in nanoseconds since the unix epoch.
        //  Note: this uses the value stored in <Utils::gpsLeapSeconds> in its conversion.
        static uint64 gpsTimeToUtcTime(uint64 gpsNanoseconds);

        //API Function: utcTimeToGpsTime
        //  Converts the UTC time into the GPS time in nanoseconds since the unix epoch.
        //  Note: this uses the value stored in <Utils::gpsLeapSeconds> in its conversion.
        static uint64 utcTimeToGpsTime(uint64 utcNanoseconds);
    };
}