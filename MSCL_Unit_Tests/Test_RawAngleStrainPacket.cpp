/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Packets/RawAngleStrainPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/Exceptions.h"
#include "mscl/Utils.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(normalizeAngle_fn)

BOOST_AUTO_TEST_CASE(Test1)
{
    float result = Utils::normalizeAngle(0);

    BOOST_CHECK_CLOSE(result, 0.0f, std::numeric_limits<float>::epsilon());
}

BOOST_AUTO_TEST_CASE(Test2)
{
    float result = Utils::normalizeAngle(360);

    BOOST_CHECK_CLOSE(result, 0.0f, std::numeric_limits<float>::epsilon());
}

BOOST_AUTO_TEST_CASE(Test3)
{
    float result = Utils::normalizeAngle(359);

    BOOST_CHECK_CLOSE(result, 359.0f, std::numeric_limits<float>::epsilon());
}

BOOST_AUTO_TEST_CASE(Test4)
{
    float result = Utils::normalizeAngle(-1);

    BOOST_CHECK_CLOSE(result, 359.0f, std::numeric_limits<float>::epsilon());
}

BOOST_AUTO_TEST_CASE(Test5)
{
    float result = Utils::normalizeAngle(245);

    BOOST_CHECK_CLOSE(result, 245.0f, std::numeric_limits<float>::epsilon());
}

BOOST_AUTO_TEST_CASE(Test6)
{
    float result = Utils::normalizeAngle(5640);

    BOOST_CHECK_CLOSE(result, 240.0f, std::numeric_limits<float>::epsilon());
}

BOOST_AUTO_TEST_CASE(Test7)
{
    float result = Utils::normalizeAngle(-725);

    BOOST_CHECK_CLOSE(result, 355.0f, std::numeric_limits<float>::epsilon());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(distributeAngles_fn)

BOOST_AUTO_TEST_CASE(LowerLessThanUpper)
{
    float expected[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    std::vector<float> result = RawAngleStrainPacket::distributeAngles(10, 25, 16);

    for(size_t i(0); i < 16; ++i)
    {
        BOOST_CHECK_CLOSE(expected[i], result[i], std::numeric_limits<float>::epsilon());
    }
}

BOOST_AUTO_TEST_CASE(UpperLessThanLower)
{
    float expected[] = {355, 356, 357, 358, 359, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<float> result = RawAngleStrainPacket::distributeAngles(355, 10, 16);

    for(size_t i(0); i < 16; ++i)
    {
        BOOST_CHECK_CLOSE(expected[i], result[i], std::numeric_limits<float>::epsilon());
    }
}

BOOST_AUTO_TEST_CASE(UpperEqualLower)
{
    float expected[] = {36, 72, 108, 144, 180, 216, 252, 288, 324, 0, 36};
    std::vector<float> result = RawAngleStrainPacket::distributeAngles(36, 36, 11);

    for(size_t i(0); i < 10; ++i)
    {
        BOOST_CHECK_CLOSE(expected[i], result[i], std::numeric_limits<float>::epsilon());
    }
}

BOOST_AUTO_TEST_CASE(InputNotNormalized)
{
    float expected[] = {36, 72, 108, 144, 180, 216, 252, 288, 324, 0, 36};
    std::vector<float> result = RawAngleStrainPacket::distributeAngles(396, 36, 11);

    for(size_t i(0); i < 10; ++i)
    {
        BOOST_CHECK_CLOSE(expected[i], result[i], std::numeric_limits<float>::epsilon());
    }
}

BOOST_AUTO_TEST_SUITE_END()