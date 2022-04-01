/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

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