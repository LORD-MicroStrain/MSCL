/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Commands/TriggerArmedDatalogging.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(TriggerArmedDatalogging_Test)

BOOST_AUTO_TEST_CASE(TriggerArmedDatalogging_buildCommand)
{
    ByteStream result = TriggerArmedDatalogging::buildCommand(35567);

    BOOST_CHECK_EQUAL(result.size(), 18);

    uint8 sop = WirelessPacket::ASPP_V1_SOP;

    BOOST_CHECK_EQUAL(result.read_uint8(0), sop);
    BOOST_CHECK_EQUAL(result.read_uint8(1), 0x05);
    BOOST_CHECK_EQUAL(result.read_uint8(2), 0x00);
    BOOST_CHECK_EQUAL(result.read_uint16(3), 35567);
    BOOST_CHECK_EQUAL(result.read_uint8(5), 0x0A);
    BOOST_CHECK_EQUAL(result.read_uint16(6), 0x000E);
}

BOOST_AUTO_TEST_SUITE_END()