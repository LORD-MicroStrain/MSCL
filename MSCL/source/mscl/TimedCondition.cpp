/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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
        //    this will lock the mutex automatically
        std::unique_lock<std::mutex> lock(m_mutex);

        //if the condition has already been notified
        if(m_isNotified)
        {
            //set the notified flag to false so that wait can be called again
            m_isNotified = false;

            //return true immediately, don't wait
            return true;
        }

        //perform a timed_wait with the given timeout
        //    this unlocks the lock/mutex that we pass to it
        bool result = (m_condition.wait_for(lock, std::chrono::milliseconds(timeout)) == std::cv_status::no_timeout);

        //set the notified flag to false so that wait can be called again
        m_isNotified = false;

        //return the result of the 
        return result;
    }

    void TimedCondition::notify()
    {
        //create a lock around the class's mutex object
        //    this will lock the mutex automatically
        mutex_lock_guard lock(m_mutex);

        //notify the condition
        m_condition.notify_one();

        //let it be known that we notified already
        //    this is so that timedWait() can return immediately if called after already being notified
        m_isNotified = true;
    }
}