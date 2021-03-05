/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "Types.h"
#include "MicroStrain/SampleRate.h"

namespace mscl
{
    //Class: TimestampCounter
    //  A utility for accurately counting time without additive error.
    class TimestampCounter
    {
    public:
        TimestampCounter();

        //Constructor: TimestampCounter
        //
        //Parameters:
        //  sampleRate - The rate to count at.
        //  startTime - The time to start counting from, as the number of nanoseconds since Unix Epoch.
        TimestampCounter(const SampleRate& sampleRate, uint64 startTime = 0);

        //Function: reset
        //  Start counting again with the specificed Sample Rate and from the specified time.
        //
        //Parameters:
        //  sampleRate - The rate to count at.
        //  time - The time to start counting from, as the number of nanoseconds since Unix Epoch.
        void reset(const SampleRate& sampleRate, uint64 time);

        //Function: reset
        //  Start counting again from the specified time, keeping the same Sample Rate
        //
        //Parameters:
        //  time - The time to start counting from, as the number of nanoseconds since Unix Epoch.
        void reset(uint64 time);

        //Function: advance
        //  Advances the counter by n periods.
        //
        //Parameters:
        //  n - The number of periods to advance the counter.
        void advance(size_t n);

        //Function: advance
        //  Advances the counter by one period.
        void advance();

        //Function: reverse
        //  Reverse the counter by n periods.
        //
        //Parameters:
        //  n - The number of periods to advance the counter.
        void reverse(size_t n);

        //Function: reverse
        //  Reverse the counter by one period.
        void reverse();

        //Function: time
        //  Gets the current time of the counter.
        //
        //Returns:
        //  The current time of the counter, as the number of nanoseconds since Unix Epoch.
        uint64 time() const;

    private:
        SampleRate m_sampleRate;
        uint64 m_time;
        size_t m_sampleCount;
    };

}