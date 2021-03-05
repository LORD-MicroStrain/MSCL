/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/TimeSpan.h"
#include "Wireless/WirelessTypes.h"

namespace mscl
{
    
    //API Class: SampleRate
    //    Represents a MicroStrain sample rate (rate at which data is sampling)
    class SampleRate
    {        
#ifndef SWIG
        friend SampleRate operator*(const SampleRate& sampleRate, uint32 factor);
        friend SampleRate operator*(uint32 factor, const SampleRate& sampleRate);
        friend SampleRate operator/(const SampleRate& sampleRate, uint32 divisor);
        friend SampleRate operator/(uint32 divisor, const SampleRate& sampleRate);
#endif
        
    public:
        //=====================================================================================================
        //API Enums: RateType
        //    rateType_seconds      - 0 - Sample rate type of seconds    (less than 1 Hz) 
        //    rateType_hertz        - 1 - Sample rate type of Hertz        (1 Hz and above)
        //    rateType_event        - 2 - Event triggered, no sample rate
        //    rateType_decimation   - 3 - Every x sample sent, no sample rate
        //=====================================================================================================
        enum RateType
        {
            rateType_seconds      = 0,
            rateType_hertz        = 1,
            rateType_event        = 2,
            rateType_decimation   = 3
        };

    public:
        //API Default Constructor: SampleRate
        //    Creates a default sample rate of 1 Hz
        SampleRate();

        //API Constructor: SampleRate
        //    Creates a sample rate with the given type and samples
        //
        //Parameters:
        //    type - The <RateType> of the given sample rate
        //    samples - The number of samples in the given sample rate (or seconds if the type is rateType_seconds)
        SampleRate(RateType type, uint32 samples);

    public:
#ifndef SWIG
        bool operator == (const SampleRate& other) const;
        bool operator != (const SampleRate& other) const;
        bool operator < (const SampleRate& other) const;
        bool operator <= (const SampleRate& other) const;
        bool operator > (const SampleRate& other) const;
        bool operator >= (const SampleRate& other) const;
        SampleRate& operator+=(uint32 samplesPerSecond);
#endif


        //API Function: str
        //    Gets the string representation of the sample rate.
        //    Ex. 1Hz = "1-hertz", 10kHz = "10000-hertz", 1 per 10 seconds = "10-seconds", 1 per 1 minute = "60 seconds"
        //
        //Returns:
        //    The sample rate represented as a string
        std::string str() const;

        //API Function: prettyStr
        //    Gets the string representation of the sample rate in a more human-readable format.
        //    Ex. 1Hz = "1Hz", 10kHz = "10kHz", 1 per 10 seconds = "Every 10 sec", 1 per 1 minute = "Every 1 min"
        //
        //Returns:
        //    The sample rate represented as a string
        std::string prettyStr() const;

        //API Function: samplePeriod
        //    Gets the sample period (time between samples) as a <TimeSpan> for the current sample rate
        //
        //Returns:
        //    The <TimeSpan> representing the sample period
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: The sample rate is unknown (such as with rateType_event)
        TimeSpan samplePeriod() const;

        //API Function: samplesPerSecond
        //    Gets the number of samples per second.
        //
        //Returns:
        //    The number of samples per second as a double
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: The sample rate is unknown (such as with rateType_event)
        double samplesPerSecond() const;

        //API Function: rateType
        //    Gets the sample rate type
        //
        //Returns:
        //    The type of the current sample rate
        RateType rateType() const;

        //API Function: samples
        //    Gets the number of samples for the sample rate (or seconds if less than 1 Hz)
        //
        //Returns:
        //    The number of samples for the sample rate
        uint32 samples() const;

        //API Function: toWirelessSampleRate
        //    Gets the <WirelessTypes::WirelessSampleRate> enum for the current SampleRate.
        //
        //Returns:
        //    The <WirelessTypes::WirelessSampleRate> that is associated with the current SampleRate.
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: The current <SampleRate> does not match a <WirelessTypes::WirelessSampleRate>.
        WirelessTypes::WirelessSampleRate toWirelessSampleRate() const;

    public:
        //API Function: Hertz
        //    Creates a SampleRate object from the given samples per second
        //
        //Parameters:
        //    samplesPerSecond - The number of samples per second (Hz)
        //
        //Returns:
        //    A SampleRate object built from the given parameter
        static SampleRate Hertz(uint32 samplesPerSecond);

        //API Function: KiloHertz
        //    Creates a SampleRate object from the given 1000 samples per second
        //
        //Parameters:
        //    kSamplesPerSecond - The number of 1000's samples per second (kHz) (20 kHz = 20)
        //
        //Returns:
        //    A SampleRate object built from the given parameter
        static SampleRate KiloHertz(uint32 kSamplesPerSecond);

        //API Function: Seconds
        //    Creates a SampleRate object from the given seconds between samples
        //
        //Parameters:
        //    secondsBetweenSamples - The number of seconds between samples (1 sample every 2 minutes = 120)
        //
        //Returns:
        //    A SampleRate object built from the given parameter
        static SampleRate Seconds(uint32 secondsBetweenSamples);

        //API Function: Event
        //    Creates a SampleRate object with the asynchronous/event type.
        //
        //Returns:
        //    A SampleRate object of the event type.
        static SampleRate Event();

        //API Function: Decimation
        //    Creates a SampleRate object with the decimation type.
        //
        //Returns:
        //    A SampleRate object of the decimation type.
        static SampleRate Decimation(uint32 rateDecimation);

        //API Function: FromWirelessEepromValue
        //    Creates a SampleRate object from the <WirelessTypes::WirelessSampleRate> value (the value that gets stored in eeprom).
        //
        //Parameters:
        //    eepromValue - The <WirelessTypes::WirelessSampleRate> value (the value that gets stored in eeprom).
        //
        //Returns:
        //    A SampleRate object built from the given parameter.
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: The given <WirelessTypes::WirelessSampleRate> is invalid or unknown.
        static SampleRate FromWirelessEepromValue(WirelessTypes::WirelessSampleRate eepromValue);

        //API Function: FromInertialRateDecimationInfo
        //    Creates a SampleRate object from the base rate and rate decimation value read from an inertial device
        //
        //Parameters:
        //    uint16 - The data base rate
        //    uint16 - The rate decimation value
        //
        //Returns:
        //    A SampleRate object built from the given parameter.
        static SampleRate FromInertialRateDecimationInfo(uint16 baseRate, uint16 rateDecimation);

    private:
        //Variable: m_rateType
        //    The type of the sample rate
        RateType m_rateType;

        //Variable: m_samples
        //    Represents the number of samples.
        //    If the sample rate type is Hertz, m_samples represents the number of samples per second (256 = 256 Hz).
        //    If the sample rate type is Seconds, m_samples represents the number of seconds (60 = 1 per 60 seconds, 120 = 1 per 2 minutes).
        uint32 m_samples;
    };

    //API Typedef: SampleRates
    //    A typedef for a vector of <SampleRate> objects.
    typedef std::vector<SampleRate> SampleRates;
    
#ifndef SWIG
    SampleRate operator*(const SampleRate& sampleRate, uint32 factor);
    SampleRate operator*(uint32 factor, const SampleRate& sampleRate);
    SampleRate operator/(const SampleRate& sampleRate, uint32 divisor);
    SampleRate operator/(uint32 divisor, const SampleRate& sampleRate);
#endif
}