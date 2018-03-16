/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/TimestampCounter.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(TimestampCounter_Test)

BOOST_AUTO_TEST_CASE(TimestampCounter_1Hz)
{
    TimestampCounter t(SampleRate::Hertz(1), 1505769554000000000);

    //advance by 1 sample
    t.advance();
    BOOST_CHECK_EQUAL(t.time(), 1505769555000000000);

    //advance by 5 samples
    t.advance(5);
    BOOST_CHECK_EQUAL(t.time(), 1505769560000000000);

    //advance by 150 samples
    t.advance(150);
    BOOST_CHECK_EQUAL(t.time(), 1505769710000000000);

    //reverse by 150 samples
    t.reverse(150);
    BOOST_CHECK_EQUAL(t.time(), 1505769560000000000);
}

BOOST_AUTO_TEST_CASE(TimestampCounter_256Hz)
{
    TimestampCounter t(SampleRate::Hertz(256), 1505769554000000000);

    //advance by 1 sample
    t.advance();
    BOOST_CHECK_EQUAL(t.time(), 1505769554003906250);

    //advance by 5 samples
    t.advance(5);
    BOOST_CHECK_EQUAL(t.time(), 1505769554023437500);

    //advance by 500 samples
    t.advance(500);
    BOOST_CHECK_EQUAL(t.time(), 1505769555976562500);

    //reverse by 500 samples
    t.reverse(500);
    BOOST_CHECK_EQUAL(t.time(), 1505769554023437500);
}

BOOST_AUTO_TEST_CASE(TimestampCounter_4096Hz)
{
    TimestampCounter t(SampleRate::Hertz(4096), 1505769554000000000);

    //advance by 1 sample
    t.advance();
    BOOST_CHECK_EQUAL(t.time(), 1505769554000244140);

    //advance by 5 samples
    t.advance(5);
    BOOST_CHECK_EQUAL(t.time(), 1505769554001464843);

    //advance by 5000 samples
    t.advance(5000);
    BOOST_CHECK_EQUAL(t.time(), 1505769555222167968);

    //reverse by 5000 samples
    t.reverse(5000);
    BOOST_CHECK_EQUAL(t.time(), 1505769554001464843);
}

BOOST_AUTO_TEST_CASE(TimestampCounter_2s)
{
    TimestampCounter t(SampleRate::Seconds(2), 1505769554000000000);

    //advance by 1 sample
    t.advance();
    BOOST_CHECK_EQUAL(t.time(), 1505769556000000000);

    //advance by 5 samples
    t.advance(5);
    BOOST_CHECK_EQUAL(t.time(), 1505769566000000000);

    //advance by 150 samples
    t.advance(150);
    BOOST_CHECK_EQUAL(t.time(), 1505769866000000000);

    //reverse by 150 samples
    t.reverse(150);
    BOOST_CHECK_EQUAL(t.time(), 1505769566000000000);
}

BOOST_AUTO_TEST_CASE(TimestampCounter_86400s) //24 hours
{
    TimestampCounter t(SampleRate::Seconds(86400), 1505769554000000000);

    //advance by 1 sample
    t.advance();
    BOOST_CHECK_EQUAL(t.time(), 1505855954000000000);

    //advance by 5 samples
    t.advance(5);
    BOOST_CHECK_EQUAL(t.time(), 1506287954000000000);

    //reverse by 365 samples
    t.reverse(365);
    BOOST_CHECK_EQUAL(t.time(), 1474751954000000000);
}

BOOST_AUTO_TEST_SUITE_END()