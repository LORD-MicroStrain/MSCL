/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

using namespace mscl;

BOOST_AUTO_TEST_SUITE(TimeSpan_Test)

BOOST_AUTO_TEST_CASE(TimeSpan_NanoSeconds)
{
    //create a TimeSpan of 1 hour
    TimeSpan ts = TimeSpan::NanoSeconds(3600000000000);

    //check that calling all the time functions gets 1 hour in each unit
    BOOST_CHECK_EQUAL(ts.getNanoseconds(), 3600000000000);
    BOOST_CHECK_EQUAL(ts.getMilliseconds(), 3600000);
    BOOST_CHECK_EQUAL(ts.getSeconds(), 3600);
}

BOOST_AUTO_TEST_CASE(TimeSpan_MicroSeconds)
{
    //create a TimeSpan of 1 hour
    TimeSpan ts = TimeSpan::MicroSeconds(static_cast<uint64>(3600000000));

    //check that calling all the time functions gets 1 hour in each unit
    BOOST_CHECK_EQUAL(ts.getNanoseconds(), 3600000000000);
    BOOST_CHECK_EQUAL(ts.getMilliseconds(), 3600000);
    BOOST_CHECK_EQUAL(ts.getSeconds(), 3600);
}

BOOST_AUTO_TEST_CASE(TimeSpan_MilliSeconds)
{
    //create a TimeSpan of 1 hour
    TimeSpan ts = TimeSpan::MilliSeconds(3600000);

    //check that calling all the time functions gets 1 hour in each unit
    BOOST_CHECK_EQUAL(ts.getNanoseconds(), 3600000000000);
    BOOST_CHECK_EQUAL(ts.getMilliseconds(), 3600000);
    BOOST_CHECK_EQUAL(ts.getSeconds(), 3600);
}

BOOST_AUTO_TEST_CASE(TimeSpan_Seconds)
{
    //create a TimeSpan of 1 hour
    TimeSpan ts = TimeSpan::Seconds(3600);

    //check that calling all the time functions gets 1 hour in each unit
    BOOST_CHECK_EQUAL(ts.getNanoseconds(), 3600000000000);
    BOOST_CHECK_EQUAL(ts.getMilliseconds(), 3600000);
    BOOST_CHECK_EQUAL(ts.getSeconds(), 3600);
}

BOOST_AUTO_TEST_CASE(TimeSpan_Minutes)
{
    //create a TimeSpan of 1 hour
    TimeSpan ts = TimeSpan::Minutes(60);

    //check that calling all the time functions gets 1 hour in each unit
    BOOST_CHECK_EQUAL(ts.getNanoseconds(), 3600000000000);
    BOOST_CHECK_EQUAL(ts.getMilliseconds(), 3600000);
    BOOST_CHECK_EQUAL(ts.getSeconds(), 3600);
}

BOOST_AUTO_TEST_CASE(TimeSpan_Hours)
{
    //create a TimeSpan of 1 hour
    TimeSpan ts = TimeSpan::Hours(1);

    //check that calling all the time functions gets 1 hour in each unit
    BOOST_CHECK_EQUAL(ts.getNanoseconds(), 3600000000000);
    BOOST_CHECK_EQUAL(ts.getMilliseconds(), 3600000);
    BOOST_CHECK_EQUAL(ts.getSeconds(), 3600);
}

BOOST_AUTO_TEST_CASE(TimeSpan_Days)
{
    //create a TimeSpan of 2 days
    TimeSpan ts = TimeSpan::Days(2);

    //check that calling all the time functions gets 2 days in each unit
    BOOST_CHECK_EQUAL(ts.getNanoseconds(), 172800000000000);
    BOOST_CHECK_EQUAL(ts.getMilliseconds(), 172800000);
    BOOST_CHECK_EQUAL(ts.getSeconds(), 172800);
}

BOOST_AUTO_TEST_CASE(TimeSpan_Operators)
{
    //create TimeSpans to compare
    TimeSpan ts1 = TimeSpan::Days(1);
    TimeSpan ts2 = TimeSpan::Seconds(60);
    TimeSpan ts3 = TimeSpan::Minutes(1);

    BOOST_CHECK_EQUAL(ts1 > ts2, true);
    BOOST_CHECK_EQUAL(ts1 >= ts2, true);
    BOOST_CHECK_EQUAL(ts1 == ts2, false);
    BOOST_CHECK_EQUAL(ts1 != ts2, true);
    BOOST_CHECK_EQUAL(ts1 < ts2, false);
    BOOST_CHECK_EQUAL(ts1 <= ts2, false);

    BOOST_CHECK_EQUAL(ts2 > ts3, false);
    BOOST_CHECK_EQUAL(ts2 >= ts3, true);
    BOOST_CHECK_EQUAL(ts2 == ts3, true);
    BOOST_CHECK_EQUAL(ts2 != ts3, false);
    BOOST_CHECK_EQUAL(ts2 < ts3, false);
    BOOST_CHECK_EQUAL(ts2 <= ts3, true);
}

BOOST_AUTO_TEST_CASE(TimeSpan_Multiplication)
{
    TimeSpan span = TimeSpan::NanoSeconds(500);
    TimeSpan rightFactor1 = span * 4;
    TimeSpan leftFactor1 = 4 * span;
    TimeSpan rightFactor2 = span * 1000000000;
    TimeSpan leftFactor2 = 1000000000 * span;

    BOOST_CHECK_EQUAL(rightFactor1.getNanoseconds(), 2000);
    BOOST_CHECK_EQUAL(leftFactor1.getNanoseconds(), 2000);
    BOOST_CHECK_EQUAL(rightFactor2.getSeconds(), 500);
    BOOST_CHECK_EQUAL(leftFactor2.getSeconds(), 500);
}

BOOST_AUTO_TEST_CASE(TimeSpan_Division)
{
    TimeSpan span = TimeSpan::Seconds(1000);
    TimeSpan rightFactor1 = span / 4;
    TimeSpan leftFactor1 = 4 / span;
    TimeSpan rightFactor2 = span / 1000000000;
    TimeSpan leftFactor2 = 1000000000 / span;

    BOOST_CHECK_EQUAL(rightFactor1.getSeconds(), 250);
    BOOST_CHECK_EQUAL(leftFactor1.getSeconds(), 250);
    BOOST_CHECK_EQUAL(rightFactor2.getNanoseconds(), 1000);
    BOOST_CHECK_EQUAL(leftFactor2.getNanoseconds(), 1000);
}

BOOST_AUTO_TEST_SUITE_END()
