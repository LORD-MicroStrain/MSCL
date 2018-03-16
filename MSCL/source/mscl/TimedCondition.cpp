/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

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
        //Note: wait_for returns a std::cv_status of timeout or no_timeout
        //      however, we cannot rely on this because the clock accuracy isn't great
        //      and therefore the implementation of the call sometimes returns no_timeout
        //      when really there likely was a timeout, but the wait didn't get that far.
        m_condition.wait_for(lock, std::chrono::milliseconds(timeout));

        bool result = m_isNotified;

        //set the notified flag to false so that wait can be called again
        m_isNotified = false;

        //return true if we were notified, false if we timed out
        return result;
    }

    void TimedCondition::notify()
    {
        //create a lock around the class's mutex object
        //    this will lock the mutex automatically
        mutex_lock_guard lock(m_mutex);

        //let it be known that we notified already
        //    this is so that timedWait() can return immediately if called after already being notified
        m_isNotified = true;

        //notify the condition
        m_condition.notify_one();
    }
}