/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/simple_any.h"
#include <cstdint>

#include <boost/test/unit_test.hpp>

struct dynamic_type
{
    dynamic_type(char value) :
    v(value)
    {}
    
    simple_any v;
};

struct large_class
{
    std::uintmax_t v1;
    std::uintmax_t v2;
};

BOOST_AUTO_TEST_SUITE(SimpleAny_class)

BOOST_AUTO_TEST_CASE(SmallValue)
{
    simple_any v('x');
    
    BOOST_CHECK_EQUAL(any_cast<char>(v), 'x');
}

BOOST_AUTO_TEST_CASE(LargeValue)
{
    large_class x = {234, 273490};
    simple_any v(x);
    
    BOOST_CHECK_EQUAL(x.v1, any_cast<large_class>(v).v1);
    BOOST_CHECK_EQUAL(x.v2, any_cast<large_class>(v).v2);
}

BOOST_AUTO_TEST_CASE(ExceptionWhenWrongType)
{
    simple_any v('x');
    
    BOOST_CHECK_THROW(any_cast<large_class>(v), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(SimpleAnyContainingSimpleAny)
{
    simple_any v(dynamic_type('x'));
    
    BOOST_CHECK_EQUAL(any_cast<char>(any_cast<dynamic_type>(v).v), 'x');
}

BOOST_AUTO_TEST_CASE(DynamicallyAllocatedSimpleAny)
{
    std::unique_ptr<simple_any> any(new simple_any('x'));
    
    BOOST_CHECK_EQUAL(any_cast<char>(*any), 'x');
}

BOOST_AUTO_TEST_CASE(CopyConstruct)
{
    simple_any v('x');
    simple_any v2(v);
    
    BOOST_CHECK_EQUAL(any_cast<char>(v), any_cast<char>(v2));
}

BOOST_AUTO_TEST_CASE(CopyConstructLargeValue)
{
    large_class data = {123123, 8234};
    simple_any v(data);
    simple_any v2(v);
    
    BOOST_CHECK_EQUAL(any_cast<large_class>(v2).v1, 123123);
    BOOST_CHECK_EQUAL(any_cast<large_class>(v2).v2, 8234);
}

BOOST_AUTO_TEST_CASE(AssignmentOperator)
{
    simple_any v('x');
    simple_any v2('y');
    
    v2 = v;
    
    BOOST_CHECK_EQUAL(any_cast<char>(v), any_cast<char>(v2));
}

BOOST_AUTO_TEST_CASE(AssignmentOperatorLargeValue)
{
    large_class data = {123123, 8234};
    large_class data2 = {345, 345345};
    simple_any v(data);
    simple_any v2(data2);
    
    v2 = v;
    
    BOOST_CHECK_EQUAL(any_cast<large_class>(v2).v1, 123123);
    BOOST_CHECK_EQUAL(any_cast<large_class>(v2).v2, 8234);
}

BOOST_AUTO_TEST_CASE(MutableAnyCast)
{
    large_class v = {123123, 8234};
    simple_any any(v);
    
    large_class v2 = {23423, 89489};
    any_cast<large_class>(any) = v2;
    
    BOOST_CHECK_EQUAL(any_cast<large_class>(any).v1, 23423);
    BOOST_CHECK_EQUAL(any_cast<large_class>(any).v2, 89489);
}

BOOST_AUTO_TEST_CASE(DefaultConstructorErrorOnCast)
{
    simple_any any;
    
    BOOST_CHECK_THROW(any_cast<int>(any), std::bad_cast);
}

BOOST_AUTO_TEST_SUITE_END()
