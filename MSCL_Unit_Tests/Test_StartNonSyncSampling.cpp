/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Commands/StartNonSyncSampling.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(StartNonSyncSampling_Test)

BOOST_AUTO_TEST_CASE(StartNonSyncSampling_buildCommand)
{
    ByteStream result = StartNonSyncSampling::buildCommand(123);

    uint8 sop = WirelessPacket::ASPP_V1_SOP;

    BOOST_CHECK_EQUAL(result.read_uint8(0), sop);
    BOOST_CHECK_EQUAL(result.read_uint8(1), 0x05);
    BOOST_CHECK_EQUAL(result.read_uint8(2), 0x00);
    BOOST_CHECK_EQUAL(result.read_uint16(3), 123);
    BOOST_CHECK_EQUAL(result.read_uint8(5), 0x02);
    BOOST_CHECK_EQUAL(result.read_uint16(6), 0x0038);
    BOOST_CHECK_EQUAL(result.read_uint16(8), 0x00BA);
}

BOOST_AUTO_TEST_SUITE_END()