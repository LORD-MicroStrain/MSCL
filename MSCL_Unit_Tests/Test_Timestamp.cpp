/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/Timestamp.h"
#include "mscl/Utils.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(Timestamp_Test)

BOOST_AUTO_TEST_CASE(Timestamp_Constructor)
{
    //create Timestamp with time 0 (default)
    Timestamp ts;

    //check that nanoseconds() returns 0
    BOOST_CHECK_EQUAL(ts.nanoseconds(), 0);

    //check that seconds() returns 0
    BOOST_CHECK_EQUAL(ts.seconds(), 0);

    //create a Timestamp passing in nanoseconds
    Timestamp ts2(15000000000);

    //check that nanoseconds() returns the correct value
    BOOST_CHECK_EQUAL(ts2.nanoseconds(), 15000000000);

    //check that seconds() returns the correct value
    BOOST_CHECK_EQUAL(ts2.seconds(), 15);
}

BOOST_AUTO_TEST_CASE(Timestamp_Constructor_Long)
{
    //create Timestamp with time 0 (default)
    Timestamp ts(2013, 3, 15, 10, 5, 55, 123); // 03/15/2013 10:05:55.123

    //check that nanoseconds() returns 0
    BOOST_CHECK_EQUAL(ts.nanoseconds(), 1363341955123000000);
}

BOOST_AUTO_TEST_CASE(Timestamp_TimeNow)
{
    //create a timestamp from the current time
    Timestamp ts = Timestamp::timeNow();

    uint64 startNanos = ts.nanoseconds();

    //sleep for a couple milliseconds
    Utils::threadSleep(2);

    //update the timestamp to now
    ts.setTimeNow();

    BOOST_CHECK(startNanos < ts.nanoseconds());
}

BOOST_AUTO_TEST_CASE(Timestamp_str)
{
    Timestamp ts(1363189940788455000);

    //check that the str function prints out the correct date/time
    BOOST_CHECK_EQUAL(ts.str(), "2013-03-13 15:52:20.788455000");
}

BOOST_AUTO_TEST_CASE(Timestamp_Difference)
{
    Timestamp ts(1363189940788455000);
    Timestamp ts2(1363189940788456000);

    BOOST_CHECK_EQUAL((ts - ts2).getNanoseconds(), 1000);
    BOOST_CHECK_EQUAL((ts2 - ts).getNanoseconds(), 1000);
}

BOOST_AUTO_TEST_SUITE_END()