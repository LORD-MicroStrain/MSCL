/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(WirelessPacket_Test)

BOOST_AUTO_TEST_SUITE(DeliveryStopFlags_Suite)

BOOST_AUTO_TEST_CASE(DeliveryStopFlag_ToFrom_Inverted)
{
    uint8 originalByte = 6;    //0000 0110

    //build the flags from the byte
    DeliveryStopFlags flags = DeliveryStopFlags::fromInvertedByte(originalByte);    

    //verify that all the flags are what we want them to be
    BOOST_CHECK_EQUAL(flags.pc, true);
    BOOST_CHECK_EQUAL(flags.appBoard, false);
    BOOST_CHECK_EQUAL(flags.linkBoard, false);
    BOOST_CHECK_EQUAL(flags.baseStation, true);

    //build a byte from the flags
    uint8 revert = flags.toInvertedByte();

    //make sure they are equal
    BOOST_CHECK_EQUAL(originalByte, revert);
}

BOOST_AUTO_TEST_CASE(DeliveryStopFlag_ToFrom)
{
    uint8 originalByte = 9;    //0000 1001

    //build the flags from the byte
    DeliveryStopFlags flags = DeliveryStopFlags::fromByte(originalByte);

    //verify that all the flags are what we want them to be
    BOOST_CHECK_EQUAL(flags.pc, true);
    BOOST_CHECK_EQUAL(flags.appBoard, false);
    BOOST_CHECK_EQUAL(flags.linkBoard, false);
    BOOST_CHECK_EQUAL(flags.baseStation, true);

    //build a byte from the flags
    uint8 revert = flags.toByte();

    //make sure they are equal
    BOOST_CHECK_EQUAL(originalByte, revert);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ChannelMask_Suite)

BOOST_AUTO_TEST_CASE(ChannelMask_Constructor)
{
    //default constructor
    ChannelMask channels;

    //check that no channels are enabled
    BOOST_CHECK_EQUAL(channels.count(), 0);

    ChannelMask channels2(198);    //1100 0110

    //check that 4 channels are enabled
    BOOST_CHECK_EQUAL(channels2.count(), 4);

    //build the channels via the fromMask() function
    ChannelMask channels3;
    channels3.fromMask(246);        //1111 0110

    //check that 6 channels are enabled
    BOOST_CHECK_EQUAL(channels3.count(), 6);

    //check that converting back to a byte is the same as before
    BOOST_CHECK_EQUAL(channels3.toMask(), 246);

    //verify that all the correct channels are enabled/disabled
    BOOST_CHECK_EQUAL(channels3.enabled(1), false);
    BOOST_CHECK_EQUAL(channels3.enabled(2), true);
    BOOST_CHECK_EQUAL(channels3.enabled(3), true);
    BOOST_CHECK_EQUAL(channels3.enabled(4), false);
    BOOST_CHECK_EQUAL(channels3.enabled(5), true);
    BOOST_CHECK_EQUAL(channels3.enabled(6), true);
    BOOST_CHECK_EQUAL(channels3.enabled(7), true);
    BOOST_CHECK_EQUAL(channels3.enabled(8), true);
    
    //check that an unavailable channel shows disabled
    BOOST_CHECK_EQUAL(channels3.enabled(25), false);

    //switch some channels
    channels3.enable(1, true);
    channels3.enable(2, false);
    channels3.enable(3, true);

    BOOST_CHECK_EQUAL(channels3.enabled(1), true);
    BOOST_CHECK_EQUAL(channels3.enabled(2), false);
    BOOST_CHECK_EQUAL(channels3.enabled(3), true);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(WirelessDataPacket_timestampWithinRange)
{
    Timestamp ts(Utils::getCurrentSystemTime() + 1800000000000);    //half hour in the future
    BOOST_CHECK_EQUAL(WirelessDataPacket::timestampWithinRange(ts), true);

    Timestamp ts4(Utils::getCurrentSystemTime());
    BOOST_CHECK_EQUAL(WirelessDataPacket::timestampWithinRange(ts4), true);

    Timestamp ts5(Utils::getCurrentSystemTime() + 60000000000);      //1 minute in the future
    BOOST_CHECK_EQUAL(WirelessDataPacket::timestampWithinRange(ts5), true);

    Timestamp ts2(Utils::getCurrentSystemTime() + 7200000000000);    //2 hours in the future
    BOOST_CHECK_EQUAL(WirelessDataPacket::timestampWithinRange(ts2), false);

    Timestamp ts3(Utils::getCurrentSystemTime() - 7200000000000);    //2 hours in the past
    BOOST_CHECK_EQUAL(WirelessDataPacket::timestampWithinRange(ts3), true);
}

BOOST_AUTO_TEST_SUITE_END()