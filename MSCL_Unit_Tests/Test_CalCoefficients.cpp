/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/CalCoefficients.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(CalCoefficients_Test)

BOOST_AUTO_TEST_CASE(CalCoefficients_DefaultConstructor)
{
    CalCoefficients cals;

    //verify that everything was initialized as it should be
    BOOST_CHECK_EQUAL(cals.equationType(), WirelessTypes::equation_standard);
    BOOST_CHECK_EQUAL(cals.unit(), WirelessTypes::unit_none);
    BOOST_CHECK_EQUAL(cals.linearEquation().slope(), 1.0f);
    BOOST_CHECK_EQUAL(cals.linearEquation().offset(), 0.0f);
}

BOOST_AUTO_TEST_CASE(CalCoefficients_Equals)
{
    CalCoefficients cal1(WirelessTypes::equation_standard, WirelessTypes::unit_accel_g, LinearEquation(3.1245f, 0.07823f));
    BOOST_CHECK_EQUAL(cal1.equationType(), WirelessTypes::equation_standard);
    BOOST_CHECK_EQUAL(cal1.unit(), WirelessTypes::unit_accel_g);
    BOOST_CHECK_EQUAL(cal1.linearEquation().slope(), 3.1245f);
    BOOST_CHECK_EQUAL(cal1.linearEquation().offset(), 0.07823f);

    CalCoefficients cal2(WirelessTypes::equation_standard, WirelessTypes::unit_accel_g, LinearEquation(3.1245f, 0.07823f));
    BOOST_CHECK_EQUAL(cal1 == cal2, true);

    CalCoefficients cal3(WirelessTypes::equation_none, WirelessTypes::unit_accel_g, LinearEquation(3.1245f, 0.07823f));
    BOOST_CHECK_EQUAL(cal1 == cal3, false);

    CalCoefficients cal4(WirelessTypes::equation_standard, WirelessTypes::unit_accel_milliG, LinearEquation(3.1245f, 0.07823f));
    BOOST_CHECK_EQUAL(cal1 == cal4, false);

    CalCoefficients cal5(WirelessTypes::equation_standard, WirelessTypes::unit_accel_g, LinearEquation(5.1245f, 0.07823f));
    BOOST_CHECK_EQUAL(cal1 == cal5, false);

    CalCoefficients cal6(WirelessTypes::equation_standard, WirelessTypes::unit_accel_g, LinearEquation(3.1245f, 0.078231f));
    BOOST_CHECK_EQUAL(cal1 == cal6, false);
}

BOOST_AUTO_TEST_SUITE_END()