/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include <boost/utility/binary.hpp>    

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(ChannelMask_Test)

BOOST_AUTO_TEST_CASE(ChannelMask_DefaultConstructor)
{
    ChannelMask chs;

    //verify that no channels are enabled
    BOOST_CHECK_EQUAL(chs.count(), 0);
    BOOST_CHECK_EQUAL(chs.toMask(), 0);
}

BOOST_AUTO_TEST_CASE(ChannelMask_constructor)
{
    uint16 mask = BOOST_BINARY(01001101);

    ChannelMask chs(mask);

    BOOST_CHECK_EQUAL(chs.count(), 4);
    BOOST_CHECK_EQUAL(chs.toMask(), mask);
}

BOOST_AUTO_TEST_CASE(ChannelMask_fromMask)
{
    uint16 mask = 42529; //1010011000100001 

    ChannelMask chs;

    //verify that no channels are enabled
    BOOST_CHECK_EQUAL(chs.count(), 0);
    BOOST_CHECK_EQUAL(chs.toMask(), 0);

    chs.fromMask(mask);

    BOOST_CHECK_EQUAL(chs.count(), 6);
    BOOST_CHECK_EQUAL(chs.toMask(), mask);
}

BOOST_AUTO_TEST_CASE(ChannelMask_enabled)
{
    uint16 mask = 42529; //1010011000100001 

    ChannelMask chs(mask);

    BOOST_CHECK_EQUAL(chs.enabled(1), true);
    BOOST_CHECK_EQUAL(chs.enabled(2), false);
    BOOST_CHECK_EQUAL(chs.enabled(3), false);
    BOOST_CHECK_EQUAL(chs.enabled(4), false);
    BOOST_CHECK_EQUAL(chs.enabled(5), false);
    BOOST_CHECK_EQUAL(chs.enabled(6), true);
    BOOST_CHECK_EQUAL(chs.enabled(7), false);
    BOOST_CHECK_EQUAL(chs.enabled(8), false);
    BOOST_CHECK_EQUAL(chs.enabled(9), false);
    BOOST_CHECK_EQUAL(chs.enabled(10), true);
    BOOST_CHECK_EQUAL(chs.enabled(11), true);
    BOOST_CHECK_EQUAL(chs.enabled(12), false);
    BOOST_CHECK_EQUAL(chs.enabled(13), false);
    BOOST_CHECK_EQUAL(chs.enabled(14), true);
    BOOST_CHECK_EQUAL(chs.enabled(15), false);
    BOOST_CHECK_EQUAL(chs.enabled(16), true);
}

BOOST_AUTO_TEST_CASE(ChannelMask_enable)
{
    ChannelMask chs;

    BOOST_CHECK_EQUAL(chs.enabled(1), false);
    BOOST_CHECK_EQUAL(chs.enabled(2), false);
    BOOST_CHECK_EQUAL(chs.enabled(3), false);
    BOOST_CHECK_EQUAL(chs.enabled(4), false);
    BOOST_CHECK_EQUAL(chs.enabled(5), false);

    chs.enable(2);

    BOOST_CHECK_EQUAL(chs.enabled(1), false);
    BOOST_CHECK_EQUAL(chs.enabled(2), true);
    BOOST_CHECK_EQUAL(chs.enabled(3), false);
    BOOST_CHECK_EQUAL(chs.enabled(4), false);
    BOOST_CHECK_EQUAL(chs.enabled(5), false);

    chs.enable(5, true);

    BOOST_CHECK_EQUAL(chs.enabled(1), false);
    BOOST_CHECK_EQUAL(chs.enabled(2), true);
    BOOST_CHECK_EQUAL(chs.enabled(3), false);
    BOOST_CHECK_EQUAL(chs.enabled(4), false);
    BOOST_CHECK_EQUAL(chs.enabled(5), true);

    chs.enable(2, false);

    BOOST_CHECK_EQUAL(chs.enabled(1), false);
    BOOST_CHECK_EQUAL(chs.enabled(2), false);
    BOOST_CHECK_EQUAL(chs.enabled(3), false);
    BOOST_CHECK_EQUAL(chs.enabled(4), false);
    BOOST_CHECK_EQUAL(chs.enabled(5), true);

    chs.enable(3, false);

    BOOST_CHECK_EQUAL(chs.enabled(1), false);
    BOOST_CHECK_EQUAL(chs.enabled(2), false);
    BOOST_CHECK_EQUAL(chs.enabled(3), false);
    BOOST_CHECK_EQUAL(chs.enabled(4), false);
    BOOST_CHECK_EQUAL(chs.enabled(5), true);
}

BOOST_AUTO_TEST_CASE(ChannelMask_lastChEnabled)
{
    ChannelMask chs(42529); //1010011000100001 

    BOOST_CHECK_EQUAL(chs.lastChEnabled(), 16);

    chs.enable(16, false);
    BOOST_CHECK_EQUAL(chs.lastChEnabled(), 14);

    chs.enable(14, false);
    BOOST_CHECK_EQUAL(chs.lastChEnabled(), 11);

    chs.enable(11, false);
    chs.enable(10, false);
    BOOST_CHECK_EQUAL(chs.lastChEnabled(), 6);

    chs.enable(6, false);
    BOOST_CHECK_EQUAL(chs.lastChEnabled(), 1);

    chs.enable(1, false);
    BOOST_CHECK_EQUAL(chs.lastChEnabled(), 0);

    chs.enable(5);
    BOOST_CHECK_EQUAL(chs.lastChEnabled(), 5);
}

BOOST_AUTO_TEST_SUITE_END()