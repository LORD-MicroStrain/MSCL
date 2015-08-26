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
#include "mscl/TimedCondition.h"
#include "mscl/TimeSpan.h"
#include "mscl/Utils.h"
#include <thread>

#include <boost/test/unit_test.hpp>

using namespace mscl;

struct TimedConditionFixture
{
	TimedCondition condition;

	void notifyCondition()
	{
		//sleep to give time for the condition to call timedWait
		Utils::threadSleep(200);

		//notify the condition
		condition.notify();		
	}
};
//static TimedCondition condition;

BOOST_FIXTURE_TEST_SUITE(TimedCondition_Test, TimedConditionFixture)


BOOST_AUTO_TEST_CASE(TimedCondition_ConditionMet)
{
	//create a thread that will notify the condition
	std::thread testThread(&TimedConditionFixture::notifyCondition, this);

	//call timedWait on the condition
	bool result = condition.timedWait(2000);

	//check that the condition was met
	BOOST_CHECK_EQUAL(result, true);

	testThread.join();
}

BOOST_AUTO_TEST_CASE(TimedCondition_Timeout)
{
	//call timedWait on the condition
	bool result = condition.timedWait(2);

	//check that the timeout was called
	BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_SUITE_END()