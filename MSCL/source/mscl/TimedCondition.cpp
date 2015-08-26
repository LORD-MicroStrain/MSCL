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
#include "stdafx.h"
#include "TimedCondition.h"
#include "Types.h"
#include "Utils.h"

namespace mscl
{
	TimedCondition::TimedCondition():
		m_isNotified(false)
	{
	}

	bool TimedCondition::timedWait(uint64 timeout)
	{
		//create a lock around the class's mutex object
		//	this will lock the mutex automatically
		std::unique_lock<std::mutex> lock(m_mutex);

		//if the condition has already been notified
		if(m_isNotified)
		{
			//set the notified flag to false so that wait can be called again
			m_isNotified = false;

			//return true immediately, don't wait
			return true;
		}

		//perform a timed_wait with the given timeout and return the result
		//	this unlocks the lock/mutex that we pass to it
		return (m_condition.wait_for(lock, std::chrono::milliseconds(timeout)) == std::cv_status::no_timeout);
	}

	void TimedCondition::notify()
	{
		//create a lock around the class's mutex object
		//	this will lock the mutex automatically
		mutex_lock_guard lock(m_mutex);

		//notify the condition
		m_condition.notify_one();

		//let it be known that we notified already
		//	this is so that timedWait() can return immediately if called after already being notified
		m_isNotified = true;
	}
}