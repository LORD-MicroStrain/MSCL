/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "SampleRate.h"
#include "SampleUtils.h"
#include "mscl/Utils.h"
#include "mscl/Exceptions.h"

namespace mscl
{
    SampleRate::SampleRate() :
        m_rateType(rateType_hertz),
        m_samples(1)
    {
    }

    SampleRate::SampleRate(RateType type, uint32 samples) :
        m_rateType(type),
        m_samples(samples)
    {
    }

    bool SampleRate::operator == (const SampleRate& other) const { return samplePeriod() == other.samplePeriod(); }
    bool SampleRate::operator != (const SampleRate& other) const { return samplePeriod() != other.samplePeriod(); }
    bool SampleRate::operator < (const SampleRate& other) const { return samplePeriod() > other.samplePeriod(); }    // '>' because slower sample rates have greater sample periods
    bool SampleRate::operator <= (const SampleRate& other) const { return samplePeriod() >= other.samplePeriod(); } // '>' because slower sample rates have greater sample periods
    bool SampleRate::operator > (const SampleRate& other) const { return samplePeriod() < other.samplePeriod(); }    // '<' because slower sample rates have greater sample periods
    bool SampleRate::operator >= (const SampleRate& other) const { return samplePeriod() <= other.samplePeriod(); }    // '<' because slower sample rates have greater sample periods

    SampleRate& SampleRate::operator+=(uint32 samplesPerSecond)
    {
        //if the rate type is seconds
        if(m_rateType == SampleRate::rateType_seconds)
        {
            //if we are adding more than the number of seconds in this sample rate
            //ex. 1 sample per 5 seconds + 10 seconds = 5Hz
            if(samplesPerSecond >= m_samples)
            {
                //change to hertz
                m_samples = (samplesPerSecond - m_samples);
                m_rateType = SampleRate::rateType_hertz;
            }
            //if we are adding seconds less than the current number of seconds in this sample rate
            //ex. 1 sample per 5 seconds + 2 seconds = 1 sample per 3 seconds
            else
            {
                //just subtract the seconds
                m_samples -= samplesPerSecond;
            }
        }
        else if(m_rateType == SampleRate::rateType_hertz)
        {
            //ex. 5Hz + 2 samples/second = 7Hz

            //just add the seconds
            m_samples += samplesPerSecond;
        }

        return *this;
    }

    std::string SampleRate::str() const
    {
        switch(m_rateType)
        {
            //1 Hz and faster
            case rateType_hertz:
                return Utils::toStr(m_samples) + "-hertz";

                //slower than 1 Hz
            case rateType_seconds:
                return Utils::toStr(m_samples) + "-seconds";

                //event, no real sample rate
            case rateType_event:
                return "Event";

            case rateType_decimation:
                return Utils::toStr(m_samples) + "-decimation";

            default:
                assert(false);    //unknown sample rate type
                return "Unknown";
        }
    }

    std::string SampleRate::prettyStr() const
    {
        switch(m_rateType)
        {
            //1 Hz and faster
            case rateType_hertz:
                //less than 1 kHz
                if(m_samples < 1000)
                {
                    return Utils::toStr(m_samples) + "Hz";
                }
                //1 kHz and faster
                else
                {
                    return Utils::toStrWithPrecision(m_samples / 1000.0) + "kHz";
                }

                //slower than 1 Hz
            case rateType_seconds:
                //seconds resolution
                if(m_samples < 60)
                {
                    return "Every " + Utils::toStr(m_samples) + " sec";
                }
                //minutes resolution
                else if(m_samples < 3600)
                {
                    return "Every " + Utils::toStrWithPrecision(m_samples / 60.0) + " min";
                }
                //hours resolution
                else
                {
                    return "Every " + Utils::toStrWithPrecision(m_samples / 3600.0) + " hr";
                }

                //event, no real sample rate
            case rateType_event:
                return "Event";

            case rateType_decimation:
                if (m_samples <= 1)
                {
                    return "Every sample";
                }
                else
                {
                    return "Every " + Utils::toStr(m_samples) + " samples";
                }

            default:
                assert(false);    //unknown sample rate type
                return "Unknown";
        }
    }

    TimeSpan SampleRate::samplePeriod() const
    {
        switch(m_rateType)
        {
            case rateType_seconds:
                //seconds between samples
                return TimeSpan::Seconds(m_samples);

            case rateType_hertz:
                //nanoseconds between samples
                return TimeSpan::NanoSeconds(TimeSpan::NANOSECONDS_PER_SECOND / m_samples);

                //unknown sample rates
            case rateType_event:
            case rateType_decimation:
            default:
                throw Error_UnknownSampleRate();
        }
    }

    double SampleRate::samplesPerSecond() const
    {
        switch(m_rateType)
        {
            case rateType_seconds:
                return 1.0 / static_cast<double>(m_samples);

            case rateType_hertz:
                return static_cast<double>(m_samples);

                //unknown sample rates
            case rateType_event:
            case rateType_decimation:
            default:
                throw Error_UnknownSampleRate();
        }
    }

    SampleRate::RateType SampleRate::rateType() const
    {
        return m_rateType;
    }

    uint32 SampleRate::samples() const
    {
        return m_samples;
    }

    WirelessTypes::WirelessSampleRate SampleRate::toWirelessSampleRate() const
    {
        return SampleUtils::convertFromSampleRate(*this);
    }

    uint16 SampleRate::toDecimation(uint16 sampleRateBase) const
    {
        if (m_rateType == SampleRate::rateType_decimation)
        {
            return static_cast<uint16>(m_samples);
        }

        return static_cast<uint16>(sampleRateBase / samplesPerSecond());
    }

    SampleRate SampleRate::Hertz(uint32 samplesPerSecond)
    {
        //check the parameter is within the nanoseconds range
        assert(samplesPerSecond <= TimeSpan::NANOSECONDS_PER_SECOND);

        //build a sample rate from hertz and the samples per second
        return SampleRate(rateType_hertz, samplesPerSecond);
    }

    SampleRate SampleRate::KiloHertz(uint32 kSamplesPerSecond)
    {
        //check the parameter is within the nanoseconds range
        assert(kSamplesPerSecond <= TimeSpan::NANOSECONDS_PER_SECOND / 1000);

        //build a sample rate from hertz and the 1000's samples per second
        return SampleRate(rateType_hertz, kSamplesPerSecond * 1000);
    }

    SampleRate SampleRate::Seconds(uint32 secondsBetweenSamples)
    {
        //build a sample rate from seconds and the seconds between samples
        return SampleRate(rateType_seconds, secondsBetweenSamples);
    }

    SampleRate SampleRate::Event()
    {
        return SampleRate(rateType_event, 0);
    }

    SampleRate SampleRate::Decimation(uint32 rateDecimation)
    {
        return SampleRate(rateType_decimation, rateDecimation);
    }

    SampleRate SampleRate::FromWirelessEepromValue(WirelessTypes::WirelessSampleRate eepromValue)
    {
        return SampleUtils::convertToSampleRate(eepromValue);
    }

    SampleRate SampleRate::FromInertialRateDecimationInfo(uint16 baseRate, uint16 rateDecimation)
    {
        uint16 decimationActual = rateDecimation == 0 ? 1 : rateDecimation;

        if (baseRate == 0)
        {
            return SampleRate::Decimation(decimationActual);
        }
        else if (decimationActual <= baseRate)
        {
            uint32 rate = static_cast<uint32>(Utils::round(static_cast<float>(baseRate) / static_cast<float>(decimationActual)));
            return SampleRate::Hertz(rate);
        }
        else
        {
            uint32 rate = static_cast<uint32>(Utils::round(static_cast<float>(decimationActual) / static_cast<float>(baseRate)));
            return SampleRate::Seconds(rate);
        }
    }

    inline SampleRate fromTimeSpan(const TimeSpan& timeSpan)
    {
        if(timeSpan > TimeSpan::Seconds(1))
        {
            return SampleRate::Seconds(
                static_cast<uint32>(timeSpan.getSeconds()));
        }
        else
        {
            uint32 samplesPerSecond = static_cast<uint32>(
                TimeSpan::NANOSECONDS_PER_SECOND /
                timeSpan.getNanoseconds());
            return SampleRate::Hertz(samplesPerSecond);
        }
    }

    SampleRate operator*(const SampleRate& sampleRate, uint32 factor)
    {
        TimeSpan newSamplePeriod = sampleRate.samplePeriod() / factor;
        return fromTimeSpan(newSamplePeriod);
    }

    SampleRate operator*(uint32 factor, const SampleRate& sampleRate)
    {
        TimeSpan newSamplePeriod = sampleRate.samplePeriod() / factor;
        return fromTimeSpan(newSamplePeriod);
    }

    SampleRate operator/(const SampleRate& sampleRate, uint32 divisor)
    {
        TimeSpan newSamplePeriod = sampleRate.samplePeriod() * divisor;
        return fromTimeSpan(newSamplePeriod);
    }

    SampleRate operator/(uint32 divisor, const SampleRate& sampleRate)
    {
        TimeSpan newSamplePeriod = sampleRate.samplePeriod() * divisor;
        return fromTimeSpan(newSamplePeriod);
    }
}