/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"

#include "TimestampCounter.h"
#include "TimeSpan.h"

namespace mscl
{
    TimestampCounter::TimestampCounter():
        m_sampleRate(SampleRate::Hertz(1)),
        m_time(0),
        m_sampleCount(0)
    {
    }

    TimestampCounter::TimestampCounter(const SampleRate& sampleRate, uint64 startTime):
        m_sampleRate(sampleRate),
        m_time(startTime),
        m_sampleCount(0)
    {
    }

    void TimestampCounter::reset(const SampleRate& sampleRate, uint64 time)
    {
        m_sampleRate = sampleRate;
        m_time = time;
        m_sampleCount = 0;
    }

    void TimestampCounter::reset(uint64 time)
    {
        m_time = time;
        m_sampleCount = 0;
    }

    void TimestampCounter::advance(size_t n)
    {
        switch(m_sampleRate.rateType())
        {
            case SampleRate::rateType_hertz:
                m_sampleCount += n;
                if(m_sampleCount >= m_sampleRate.samples())
                {
                    // overrun a second
                    m_time += TimeSpan::NANOSECONDS_PER_SECOND * (m_sampleCount / m_sampleRate.samples());
                    m_sampleCount = m_sampleCount % m_sampleRate.samples();
                }
                break;

            default:
                m_time += static_cast<uint64>(m_sampleRate.samples()) * n * TimeSpan::NANOSECONDS_PER_SECOND;
        };
    }

    void TimestampCounter::advance()
    {
        return advance(1);
    }

    void TimestampCounter::reverse(size_t n)
    {
        uint64 origTime = m_time;
        size_t origSampleCount = m_sampleCount;

        switch(m_sampleRate.rateType())
        {
            case SampleRate::rateType_hertz:

                //if we are going to roll back over 0
                if(n > m_sampleCount)
                {
                    m_time -= TimeSpan::NANOSECONDS_PER_SECOND * ( ( (n - m_sampleCount) / m_sampleRate.samples() ) + 1);
                    m_sampleCount = m_sampleRate.samples() - ( (n - m_sampleCount) % m_sampleRate.samples() );
                }
                else
                {
                    m_sampleCount -= n;
                }
                break;

            default:
                m_time -= static_cast<uint64>(m_sampleRate.samples()) * n * TimeSpan::NANOSECONDS_PER_SECOND;
        };

        if(m_time > origTime)
        {
            m_time = origTime;
            m_sampleCount = origSampleCount;
            throw Error("Cannot reverse past the beginning of Unix Epoch!");
        }
    }

    void TimestampCounter::reverse()
    {
        reverse(1);
    }

    uint64 TimestampCounter::time() const
    {
        switch(m_sampleRate.rateType())
        {
            case SampleRate::rateType_hertz:
                return m_time + ((static_cast<uint64>(m_sampleCount) * TimeSpan::NANOSECONDS_PER_SECOND) / m_sampleRate.samples());

            default:
                return m_time;
        };
    }

}
