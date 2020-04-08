/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(SampleUtils_Test)

BOOST_AUTO_TEST_CASE(SampleUtils_convertToSampleRate_sampleRateOption)
{
    //check that the rates turn into the actual SampleRate that they should
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_10kHz).prettyStr(), "10kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_20kHz).prettyStr(), "20kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_30kHz).prettyStr(), "30kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_40kHz).prettyStr(), "40kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_50kHz).prettyStr(), "50kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_60kHz).prettyStr(), "60kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_70kHz).prettyStr(), "70kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_80kHz).prettyStr(), "80kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_90kHz).prettyStr(), "90kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_100kHz).prettyStr(), "100kHz");

    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_4096Hz).prettyStr(), "4.096kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_2048Hz).prettyStr(), "2.048kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_1024Hz).prettyStr(), "1.024kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_512Hz).prettyStr(), "512Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_256Hz).prettyStr(), "256Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_128Hz).prettyStr(), "128Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_64Hz).prettyStr(), "64Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_32Hz).prettyStr(), "32Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_16Hz).prettyStr(), "16Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_8Hz).prettyStr(), "8Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_4Hz).prettyStr(), "4Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_2Hz).prettyStr(), "2Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_1Hz).prettyStr(), "1Hz");

    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_2Sec).prettyStr(), "Every 2 sec");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_5Sec).prettyStr(), "Every 5 sec");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_10Sec).prettyStr(), "Every 10 sec");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_30Sec).prettyStr(), "Every 30 sec");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_1Min).prettyStr(), "Every 1 min");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_2Min).prettyStr(), "Every 2 min");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_5Min).prettyStr(), "Every 5 min");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_10Min).prettyStr(), "Every 10 min");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_30Min).prettyStr(), "Every 30 min");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_60Min).prettyStr(), "Every 1 hr");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(WirelessTypes::sampleRate_24Hours).prettyStr(), "Every 24 hr");

    //check that an invalid sample rate throws an Error_UnknownSampleRate exception
    WirelessTypes::WirelessSampleRate rt = static_cast<WirelessTypes::WirelessSampleRate>(0);
    BOOST_CHECK_THROW(SampleUtils::convertToSampleRate(rt), Error_UnknownSampleRate);
}

BOOST_AUTO_TEST_CASE(SampleUtils_convertToSampleRate_eepromVal)
{
    //check that the rates turn into the actual SampleRate that they should
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(71).prettyStr(), "10kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(80).prettyStr(), "100kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(101).prettyStr(), "4.096kHz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(113).prettyStr(), "1Hz");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(114).prettyStr(), "Every 2 sec");
    BOOST_CHECK_EQUAL(SampleUtils::convertToSampleRate(123).prettyStr(), "Every 1 hr");

    //check that an invalid sample rate throws an Error_UnknownSampleRate exception
    BOOST_CHECK_THROW(SampleUtils::convertToSampleRate(967), Error_UnknownSampleRate);
}

BOOST_AUTO_TEST_CASE(SampleUtils_convertFromSampleRate)
{
    //check that the Sample Rate turns into the eeprom value that it should
    BOOST_CHECK_EQUAL(SampleUtils::convertFromSampleRate(SampleRate::KiloHertz(10)), 71);
    BOOST_CHECK_EQUAL(SampleUtils::convertFromSampleRate(SampleRate::KiloHertz(100)), 80);
    BOOST_CHECK_EQUAL(SampleUtils::convertFromSampleRate(SampleRate::Hertz(4096)), 101);
    BOOST_CHECK_EQUAL(SampleUtils::convertFromSampleRate(SampleRate::Hertz(1)), 113);
    BOOST_CHECK_EQUAL(SampleUtils::convertFromSampleRate(SampleRate::Seconds(2)), 114);
    BOOST_CHECK_EQUAL(SampleUtils::convertFromSampleRate(SampleRate::Seconds(3600)), 123);
    

    //check that an invalid sample rate throws an Error_UnknownSampleRate exception
    BOOST_CHECK_THROW(SampleUtils::convertFromSampleRate(SampleRate::Hertz(784)), Error_UnknownSampleRate);
}

BOOST_AUTO_TEST_SUITE_END();