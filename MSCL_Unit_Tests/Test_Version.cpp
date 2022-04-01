/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "mscl/Version.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(Version_Test)

BOOST_AUTO_TEST_CASE(Version_DefaultConstructor)
{
    Version v;

    //check that the version defaults to 0.00
    BOOST_CHECK_EQUAL(v.majorPart(), 0);
    BOOST_CHECK_EQUAL(v.minorPart(), 0);
    BOOST_CHECK_EQUAL(v.patchPart(), 0);
    BOOST_CHECK_EQUAL(v.str(), "0.0.0");
}

BOOST_AUTO_TEST_CASE(Version_Constructor)
{
    Version v1(1, 45);

    //check that the version is "1.45"
    BOOST_CHECK_EQUAL(v1.majorPart(), 1);
    BOOST_CHECK_EQUAL(v1.minorPart(), 45);
    BOOST_CHECK_EQUAL(v1.patchPart(), 0);
    BOOST_CHECK_EQUAL(v1.str(), "1.45.0");

    Version v2(12, 6, 3);

    //check that the version is "12.06"
    BOOST_CHECK_EQUAL(v2.majorPart(), 12);
    BOOST_CHECK_EQUAL(v2.minorPart(), 6);
    BOOST_CHECK_EQUAL(v2.patchPart(), 3);
    BOOST_CHECK_EQUAL(v2.str(), "12.6.3");
}

BOOST_AUTO_TEST_CASE(Version_CopyConstructor)
{
    Version v(1, 23, 45);

    Version vCopy(v);

    BOOST_CHECK_EQUAL(vCopy.majorPart(), 1);
    BOOST_CHECK_EQUAL(vCopy.minorPart(), 23);
    BOOST_CHECK_EQUAL(vCopy.patchPart(), 45);
    BOOST_CHECK_EQUAL(vCopy.str(), "1.23.45");
}

BOOST_AUTO_TEST_CASE(Version_EqualOperator)
{
    Version v1(1, 23);
    Version v2(1, 23);
    Version v3(1, 24);
    Version v4(0, 23);
    Version v5(1, 23, 45);
    Version v6(1, 23, 45);
    Version v7(1, 23, 44);
    Version v8(1, 23, 0);

    BOOST_CHECK_EQUAL(v1 == v2, true);
    BOOST_CHECK_EQUAL(v1 == v3, false);
    BOOST_CHECK_EQUAL(v1 == v4, false);
    BOOST_CHECK_EQUAL(v5 == v6, true);
    BOOST_CHECK_EQUAL(v5 == v1, false);
    BOOST_CHECK_EQUAL(v6 == v7, false);
    BOOST_CHECK_EQUAL(v1 == v8, true);
}

BOOST_AUTO_TEST_CASE(Version_NotEqualOperator)
{
    Version v1(1, 23);
    Version v2(1, 23);
    Version v3(1, 24);
    Version v4(0, 23);
    Version v5(1, 23, 45);
    Version v6(1, 23, 45);
    Version v7(1, 23, 44);

    BOOST_CHECK_EQUAL(v1 != v2, false);
    BOOST_CHECK_EQUAL(v1 != v3, true);
    BOOST_CHECK_EQUAL(v1 != v4, true);
    BOOST_CHECK_EQUAL(v5 != v6, false);
    BOOST_CHECK_EQUAL(v5 != v1, true);
    BOOST_CHECK_EQUAL(v6 != v7, true);
}

BOOST_AUTO_TEST_CASE(Version_LessThanOperator)
{
    Version v1(1, 23);
    Version v2(1, 23);
    Version v3(1, 24);
    Version v4(0, 23);
    Version v5(1, 23, 45);
    Version v6(1, 23, 45);
    Version v7(1, 23, 44);

    BOOST_CHECK_EQUAL(v1 < v2, false);
    BOOST_CHECK_EQUAL(v1 < v3, true);
    BOOST_CHECK_EQUAL(v1 < v4, false);
    BOOST_CHECK_EQUAL(v5 < v6, false);
    BOOST_CHECK_EQUAL(v6 < v7, false);
    BOOST_CHECK_EQUAL(v7 < v6, true);
}

BOOST_AUTO_TEST_CASE(Version_LessThanOrEqualToOperator)
{
    Version v1(1, 23);
    Version v2(1, 23);
    Version v3(1, 24);
    Version v4(0, 23);
    Version v5(1, 23, 45);
    Version v6(1, 23, 45);
    Version v7(1, 23, 44);

    BOOST_CHECK_EQUAL(v1 <= v2, true);
    BOOST_CHECK_EQUAL(v1 <= v3, true);
    BOOST_CHECK_EQUAL(v1 <= v4, false);
    BOOST_CHECK_EQUAL(v5 <= v6, true);
    BOOST_CHECK_EQUAL(v6 <= v7, false);
    BOOST_CHECK_EQUAL(v7 <= v6, true);
}

BOOST_AUTO_TEST_CASE(Version_GreaterThanOperator)
{
    Version v1(1, 23);
    Version v2(1, 23);
    Version v3(1, 24);
    Version v4(0, 23);
    Version v5(1, 23, 45);
    Version v6(1, 23, 45);
    Version v7(1, 23, 44);

    BOOST_CHECK_EQUAL(v1 > v2, false);
    BOOST_CHECK_EQUAL(v1 > v3, false);
    BOOST_CHECK_EQUAL(v1 > v4, true);
    BOOST_CHECK_EQUAL(v5 > v6, false);
    BOOST_CHECK_EQUAL(v6 > v7, true);
    BOOST_CHECK_EQUAL(v7 > v6, false);
}

BOOST_AUTO_TEST_CASE(Version_GreaterThanOrEqualToOperator)
{
    Version v1(1, 23);
    Version v2(1, 23);
    Version v3(1, 24);
    Version v4(0, 23);
    Version v5(1, 23, 45);
    Version v6(1, 23, 45);
    Version v7(1, 23, 44);

    BOOST_CHECK_EQUAL(v1 >= v2, true);
    BOOST_CHECK_EQUAL(v1 >= v3, false);
    BOOST_CHECK_EQUAL(v1 >= v4, true);
    BOOST_CHECK_EQUAL(v5 >= v6, true);
    BOOST_CHECK_EQUAL(v6 >= v7, true);
    BOOST_CHECK_EQUAL(v7 >= v6, false);
}

BOOST_AUTO_TEST_CASE(Version_FromString)
{
    Version v1(1, 45);

    //check that the version is "1.45"
    BOOST_CHECK_EQUAL(v1.majorPart(), 1);
    BOOST_CHECK_EQUAL(v1.minorPart(), 45);
    BOOST_CHECK_EQUAL(v1.patchPart(), 0);
    BOOST_CHECK_EQUAL(v1.str(), "1.45.0");

    v1.fromString("1.7");

    //check that the version is updated
    BOOST_CHECK_EQUAL(v1.majorPart(), 1);
    BOOST_CHECK_EQUAL(v1.minorPart(), 7);
    BOOST_CHECK_EQUAL(v1.patchPart(), 0);
    BOOST_CHECK_EQUAL(v1.str(), "1.7.0");

    v1.fromString("2.36.75");

    //check that the version is updated
    BOOST_CHECK_EQUAL(v1.majorPart(), 2);
    BOOST_CHECK_EQUAL(v1.minorPart(), 36);
    BOOST_CHECK_EQUAL(v1.patchPart(), 75);
    BOOST_CHECK_EQUAL(v1.str(), "2.36.75");

    v1.fromString("7.1.4");

    //check that the version is updated
    BOOST_CHECK_EQUAL(v1.majorPart(), 7);
    BOOST_CHECK_EQUAL(v1.minorPart(), 1);
    BOOST_CHECK_EQUAL(v1.patchPart(), 4);
    BOOST_CHECK_EQUAL(v1.str(), "7.1.4");


    BOOST_CHECK_EQUAL(v1.fromString("HelloWorld"), false);
}


BOOST_AUTO_TEST_SUITE_END()