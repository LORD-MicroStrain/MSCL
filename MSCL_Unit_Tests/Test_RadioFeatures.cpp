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