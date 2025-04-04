/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

namespace mscl
{
    //Class: HighResClock
    //    Helper class used to obtain the current system time from as high-resolution of a clock as possible.
    class HighResClock
    {
        //Variable: m_startHighResNanos
        //    The nanoseconds since epoch for the high-resolution clock.
        uint64 m_startHighResNanos;

        //Variable: m_startSysTimeNanos
        //    The nanoseconds since epoch for the system clock.
        uint64 m_startSysTimeNanos;

    public:
        //Default Constructor: HighResClock
        //    Creates a HighResClock object, which sets the start clock times.
        HighResClock();

        //Function: getCurrentSystemTime
        //    Gets the number of nanoseconds since Unix Epoch, using a high-resolution clock.
        uint64 getCurrentSystemTime() const;
    };
} // namespace mscl
