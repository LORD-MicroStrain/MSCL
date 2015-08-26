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
#include "mscl/Types.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(Types_Test)

BOOST_AUTO_TEST_CASE(Types_CheckedCast_Fail)
{
	int val = 123456789;

	//check that casting from the current int val to a short throws an exception
	BOOST_CHECK_THROW(checked_cast<short>(val, "Test Val"), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Types_CheckedCast_Success)
{
	int val = 12;

	short result = checked_cast<short>(val, "Test Val");

	//check that casting from the current int val to a short throws an exception
	BOOST_CHECK_EQUAL(result, 12);
}

BOOST_AUTO_TEST_SUITE_END()