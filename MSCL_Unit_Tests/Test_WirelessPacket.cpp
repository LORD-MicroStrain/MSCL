/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(WirelessPacket_Test)

BOOST_AUTO_TEST_SUITE(DeliveryStopFlags_Suite)

BOOST_AUTO_TEST_CASE(DeliveryStopFlag_ToFrom)
{
	uint8 originalByte = 6;	//0000 0110

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

	ChannelMask channels2(198);	//1100 0110

	//check that 4 channels are enabled
	BOOST_CHECK_EQUAL(channels2.count(), 4);

	//build the channels via the fromMask() function
	ChannelMask channels3;
	channels3.fromMask(246);		//1111 0110

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

BOOST_AUTO_TEST_SUITE_END()