/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(SampleRate_Test)

BOOST_AUTO_TEST_CASE(SampleRate_DefaultConstructor)
{
    //build a default sample rate (1 Hz)
    SampleRate sr;

    //check that the string is "1Hz"
    BOOST_CHECK_EQUAL(sr.str(), "1-hertz");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "1Hz");

    //check that the TimeSpan is 1 second
    BOOST_CHECK_EQUAL(sr.samplePeriod().getNanoseconds(), 1000000000);

    //check that the rate type is hertz
    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_hertz);

    //check that the number of samples is 1
    BOOST_CHECK_EQUAL(sr.samples(), 1);
}

BOOST_AUTO_TEST_CASE(SampleRate_Constructor_Hz)
{
    //build a sample rate of 256 Hz
    SampleRate sr(SampleRate::rateType_hertz, 256);

    //check that the string is "256Hz"
    BOOST_CHECK_EQUAL(sr.str(), "256-hertz");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "256Hz");

    //check that the TimeSpan is the correct number of nanoseconds
    BOOST_CHECK_EQUAL(sr.samplePeriod().getNanoseconds(), 3906250);

    //check that the rate type is hertz
    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_hertz);

    //check that the number of samples is 256
    BOOST_CHECK_EQUAL(sr.samples(), 256);
}

BOOST_AUTO_TEST_CASE(SampleRate_Constructor_Seconds)
{
    //build a sample rate of 1 per 60 seconds
    SampleRate sr(SampleRate::rateType_seconds, 60);

    //check that the string is "Every 1 min"
    BOOST_CHECK_EQUAL(sr.str(), "60-seconds");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "Every 1 min");

    //check that the TimeSpan is the correct number of nanoseconds
    BOOST_CHECK_EQUAL(sr.samplePeriod().getNanoseconds(), 60000000000);

    //check that the rate type is hertz
    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_seconds);

    //check that the number of samples is 60
    BOOST_CHECK_EQUAL(sr.samples(), 60);
}

BOOST_AUTO_TEST_CASE(SampleRate_Hertz)
{
    //build a sample rate of 512 Hz
    SampleRate sr = SampleRate::Hertz(512);

    //check that the string is "512Hz"
    BOOST_CHECK_EQUAL(sr.str(), "512-hertz");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "512Hz");

    //check that the TimeSpan is the correct number of nanoseconds
    BOOST_CHECK_EQUAL(sr.samplePeriod().getNanoseconds(), 1953125);

    //check that the rate type is hertz
    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_hertz);

    //check that the number of samples is 512
    BOOST_CHECK_EQUAL(sr.samples(), 512);
}

BOOST_AUTO_TEST_CASE(SampleRate_KiloHertz)
{
    //build a sample rate of 4 kHz
    SampleRate sr = SampleRate::KiloHertz(4);

    //check that the string is "4kHz"
    BOOST_CHECK_EQUAL(sr.str(), "4000-hertz");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "4kHz");

    //check that the TimeSpan is the correct number of nanoseconds
    BOOST_CHECK_EQUAL(sr.samplePeriod().getNanoseconds(), 250000);

    //check that the rate type is hertz
    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_hertz);

    //check that the number of samples is 512
    BOOST_CHECK_EQUAL(sr.samples(), 4000);
}

BOOST_AUTO_TEST_CASE(SampleRate_Event)
{
    //build a sample rate of 4 kHz
    SampleRate sr(SampleRate::rateType_event, 0);

    BOOST_CHECK_EQUAL(sr.str(), "Event");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "Event");

    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_event);

    BOOST_CHECK_THROW(sr.samplePeriod(), Error_UnknownSampleRate);
}

BOOST_AUTO_TEST_CASE(SampleRate_Seconds)
{
    //build a sample rate of 1 per 30 seconds
    SampleRate sr = SampleRate::Seconds(30);

    //check that the string is "Every 30 sec"
    BOOST_CHECK_EQUAL(sr.str(), "30-seconds");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "Every 30 sec");

    //check that the TimeSpan is the correct number of nanoseconds
    BOOST_CHECK_EQUAL(sr.samplePeriod().getNanoseconds(), 30000000000);

    //check that the rate type is seconds
    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_seconds);

    //check that the number of samples is 30
    BOOST_CHECK_EQUAL(sr.samples(), 30);
}

BOOST_AUTO_TEST_CASE(SampleRate_Minutes)
{
    //build a sample rate of 1 per 2 minutes
    SampleRate sr = SampleRate::Seconds(120);

    //check the string representations
    BOOST_CHECK_EQUAL(sr.str(), "120-seconds");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "Every 2 min");

    //check that the TimeSpan is the correct number of nanoseconds
    BOOST_CHECK_EQUAL(sr.samplePeriod().getNanoseconds(), 120000000000);

    //check that the rate type is seconds
    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_seconds);

    //check that the number of samples is 30
    BOOST_CHECK_EQUAL(sr.samples(), 120);
}

BOOST_AUTO_TEST_CASE(SampleRate_Minutes_float)
{
    //build a sample rate of 1 per 125 seconds
    SampleRate sr = SampleRate::Seconds(125);

    //check the string representations
    BOOST_CHECK_EQUAL(sr.str(), "125-seconds");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "Every 2.08333 min");

    //check that the TimeSpan is the correct number of nanoseconds
    BOOST_CHECK_EQUAL(sr.samplePeriod().getNanoseconds(), 125000000000);

    //check that the rate type is seconds
    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_seconds);

    //check that the number of samples is 30
    BOOST_CHECK_EQUAL(sr.samples(), 125);
}

BOOST_AUTO_TEST_CASE(SampleRate_Hours)
{
    //build a sample rate of 1 per 2 minutes
    SampleRate sr = SampleRate::Seconds(86400);

    //check the string representations
    BOOST_CHECK_EQUAL(sr.str(), "86400-seconds");
    BOOST_CHECK_EQUAL(sr.prettyStr(), "Every 24 hr");

    //check that the TimeSpan is the correct number of nanoseconds
    BOOST_CHECK_EQUAL(sr.samplePeriod().getNanoseconds(), 86400000000000);

    //check that the rate type is seconds
    BOOST_CHECK_EQUAL(sr.rateType(), SampleRate::rateType_seconds);

    //check that the number of samples is 30
    BOOST_CHECK_EQUAL(sr.samples(), 86400);
}

BOOST_AUTO_TEST_CASE(SampleRate_Operators)
{
    SampleRate hz_1 = SampleRate::Hertz(1);
    SampleRate hz_512 = SampleRate::Hertz(512);
    SampleRate sec_10 = SampleRate::Seconds(10);
    SampleRate sec_1 = SampleRate::Seconds(1);

    BOOST_CHECK_EQUAL(hz_1 < hz_512, true);
    BOOST_CHECK_EQUAL(hz_1 <= hz_512, true);
    BOOST_CHECK_EQUAL(hz_1 != hz_512, true);
    BOOST_CHECK_EQUAL(hz_1 == sec_1, true);
    BOOST_CHECK_EQUAL(hz_512 > sec_10, true);
    BOOST_CHECK_EQUAL(hz_512 >= sec_10, true);
    BOOST_CHECK_EQUAL(hz_512 != sec_10, true);
    BOOST_CHECK_EQUAL(hz_512 < sec_10, false);
    BOOST_CHECK_EQUAL(sec_1 > sec_10, true);
}

BOOST_AUTO_TEST_CASE(SampleRate_PlusEquals)
{
    SampleRate hz_1 = SampleRate::Hertz(1);
    SampleRate sec_10 = SampleRate::Seconds(10);

    hz_1 += 49;
    BOOST_CHECK_EQUAL(hz_1.samplesPerSecond(), SampleRate::Hertz(50).samplesPerSecond());
    hz_1 += 2;
    BOOST_CHECK_EQUAL(hz_1.samplesPerSecond(), SampleRate::Hertz(52).samplesPerSecond());

    sec_10 += 5;
    BOOST_CHECK_EQUAL(sec_10.samplesPerSecond(), SampleRate::Seconds(5).samplesPerSecond());

    sec_10 += 10;
    BOOST_CHECK_EQUAL(sec_10.samplesPerSecond(), SampleRate::Hertz(5).samplesPerSecond());
    BOOST_CHECK_EQUAL(sec_10.rateType(), SampleRate::rateType_hertz);
}

BOOST_AUTO_TEST_CASE(SampleRate_samplesPerSecond)
{
    SampleRate hz_1 = SampleRate::Hertz(1);
    SampleRate hz_512 = SampleRate::Hertz(512);
    SampleRate hz_4096 = SampleRate::Hertz(4096);
    SampleRate sec_10 = SampleRate::Seconds(10);
    SampleRate sec_1 = SampleRate::Seconds(1);

    BOOST_CHECK_EQUAL(hz_1.samplesPerSecond(), 1.0);
    BOOST_CHECK_EQUAL(hz_512.samplesPerSecond(), 512);
    BOOST_CHECK_EQUAL(hz_4096.samplesPerSecond(), 4096);
    BOOST_CHECK_EQUAL(sec_10.samplesPerSecond(), 0.1);
    BOOST_CHECK_EQUAL(sec_1.samplesPerSecond(), 1.0);
}

BOOST_AUTO_TEST_CASE(SampleRate_Multiply)
{
    SampleRate initial = SampleRate::Seconds(10);
    SampleRate rightMult1 = initial * 5;
    SampleRate leftMult1 = 5 * initial;
    SampleRate rightMult2 = initial * 10;
    SampleRate leftMult2 = 10 * initial;
    SampleRate rightMult3 = initial * 100;
    SampleRate leftMult3 = 100 * initial;
    
    BOOST_CHECK(rightMult1 == SampleRate::Seconds(2));
    BOOST_CHECK(leftMult1 == SampleRate::Seconds(2));
    BOOST_CHECK(rightMult2 == SampleRate::Hertz(1));
    BOOST_CHECK(leftMult2 == SampleRate::Hertz(1));
    BOOST_CHECK(rightMult3 == SampleRate::Hertz(10));
    BOOST_CHECK(leftMult3 == SampleRate::Hertz(10));
}

BOOST_AUTO_TEST_CASE(SampleRate_Divide)
{
    SampleRate initial = SampleRate::Hertz(10);
    SampleRate rightDiv1 = initial / 5;
    SampleRate leftDiv1 = 5 / initial;
    SampleRate rightDiv2 = initial / 10;
    SampleRate leftDiv2 = 10 / initial;
    SampleRate rightDiv3 = initial / 100;
    SampleRate leftDiv3 = 100 / initial;
    
    BOOST_CHECK(rightDiv1 == SampleRate::Hertz(2));
    BOOST_CHECK(leftDiv1 == SampleRate::Hertz(2));
    BOOST_CHECK(rightDiv2 == SampleRate::Seconds(1));
    BOOST_CHECK(leftDiv2 == SampleRate::Seconds(1));
    BOOST_CHECK(rightDiv3 == SampleRate::Seconds(10));
    BOOST_CHECK(leftDiv3 == SampleRate::Seconds(10));
}

BOOST_AUTO_TEST_SUITE_END()