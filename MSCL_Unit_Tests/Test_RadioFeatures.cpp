/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/RadioFeatures.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(RadioFeatures_Test)

BOOST_AUTO_TEST_CASE(RadioFeatures_DefaultConstructor)
{
    RadioFeatures f;

    //verify that everything was initialized as it should be
    BOOST_CHECK_EQUAL(f.extendedRange(), false);
}

BOOST_AUTO_TEST_CASE(RadioFeatures_Constructor)
{
    uint16 eepromValXR = 1; //(0001)
    uint16 eepromValNotXR = 2; //(0010)
    uint16 eepromValNotInit = 0xFFFF;

    RadioFeatures xr(eepromValXR);
    BOOST_CHECK_EQUAL(xr.extendedRange(), true);

    RadioFeatures notXr(eepromValNotXR);
    BOOST_CHECK_EQUAL(notXr.extendedRange(), false);

    RadioFeatures notInit(eepromValNotInit);
    BOOST_CHECK_EQUAL(notInit.extendedRange(), false);
}

BOOST_AUTO_TEST_SUITE_END()