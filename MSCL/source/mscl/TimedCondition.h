/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "TimeSpan.h"
#include "Types.h"

#include <condition_variable>

namespace mscl
{
    //Class: TimedCondition
    //    Class that acts as a simple wrapper around a std::condition_variable.
    //    Used for one process waiting on a certain condition to be met or a timeout, 
    //    in which case the other process is notified of the action.
    class TimedCondition
    {
    public:
        //Constructor: TimedCondition
        //    Creates a TimedCondition object
        TimedCondition();

    private:
        TimedCondition(const TimedCondition&);                //copy constructor disabled
        TimedCondition& operator=(const TimedCondition&);    //assignement operator disabled

    private:
        //Variable: m_condition
        //    The condition object that this class provides a wrapper for.
        std::condition_variable m_condition;

        //Variable: m_mutex
        //    The mutex to handle thread-safe access
        std::mutex m_mutex;

        //Variable: m_isNotified
        //    Whether or not the condition has been notified
        bool m_isNotified;

    public:
        //Function: timedWait
        //    Blocks until the condition is met by calling notify() or until the timeout has expired. 
        //    Also returns true immediately if the condition has already been notified.
        //
        //Parameters:
        //    timeout - The timeout (in milliseconds) to set for the condition.
        //
        //Returns:
        //    true if the condition was met from a call to notify(). false if the timeout has expired.
        bool timedWait(uint64 timeout);

        //Function: notify
        //    Unblocks the TimedCondition if it is currently blocked from calling timedWait()
        void notify();
    };
}