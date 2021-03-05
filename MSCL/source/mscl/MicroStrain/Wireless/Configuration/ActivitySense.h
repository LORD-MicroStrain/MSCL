/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"

namespace mscl
{
    //API Class: ActivitySense
    //    Contains all of the ActivitySense options that can be configured for a WirelessNode.
    //    Activity Sense is a power saving feature that allows a Node to be in a low-power state when
    //    no activity is suspected, and then immediately jump to its normal sampling state when a
    //    certain activity threshold is reached.
    class ActivitySense
    {
    public:
        //API Default Constructor: ActivitySense
        //    Creates a default constructed ActivitySense object.
        ActivitySense();

    private:
        //Variable: m_enabled
        //    Whether Activity Sense is enabled or disabled.
        bool m_enabled;

        //Variable: m_activityThreshold
        //    The activity threshold (in G's).
        float m_activityThreshold;

        //Variable: m_inactivityThreshold
        //    The inactivity threshold (in G's).
        float m_inactivityThreshold;

        //Variable: m_activityTime
        //    The activity time (in seconds).
        float m_activityTime;

        //Variable: m_inactivityTimeout
        //    The inactivity timeout (in seconds).
        float m_inactivityTimeout;

    public:
        //API Function: enabled
        //    Gets whether Activity Sense is enabled or disabled in this options object.
        //
        //Returns:
        //    true if Activity Sense is enabled in this options object, false if it is disabled.
        bool enabled() const;

        //API function: enabled
        //    Sets whether Activity Sense is enabled or disabled in this options object.
        //
        //Parameters:
        //    enable - Whether to enable (true) or disable (false) Activity Sense mode in this options object.
        void enabled(bool enable);

        //API Function: activityThreshold
        //    Gets the current activity threshold value in this options object.
        //    This is the threshold the channel must exceed, for <activityTime> seconds to begin sampling.
        //
        //Returns:
        //    The activity threshold value (in G's) set in this options object.
        float activityThreshold() const;

        //API function: activityThreshold
        //    Sets the activity threshold value in this options object.
        //    This is the threshold the channel must exceed, for <activityTime> seconds to begin sampling.
        //
        //Parameters:
        //    threshold - The activity threshold value (in G's) to set in this options object.
        void activityThreshold(float threshold);

        //API Function: inactivityThreshold
        //    Gets the current inactivity threshold value in this options object.
        //    This is the threshold the channel must drop below, for <inactivityTimeout> seconds to begin sampling.
        //
        //Returns:
        //    The inactivity threshold value (in G's) set in this options object.
        float inactivityThreshold() const;

        //API function: inactivityThreshold
        //    Sets the inactivity threshold value in this options object.
        //    This is the threshold the channel must drop below, for <inactivityTimeout> seconds to begin sampling.
        //
        //Parameters:
        //    threshold - The inactivity threshold value (in G's) to set in this options object.
        void inactivityThreshold(float threshold);

        //API Function: activityTime
        //    Gets the amount of time that activity must be seen above <activityThreshold> before the Node
        //    enters its sampling mode, currently set in this options object.
        //
        //Returns:
        //    The activity time value set in this options object.
        float activityTime() const;

        //API function: activityTime
        //    Sets the amount of time that activity must be seen above <activityThreshold> before the Node
        //    enters its sampling mode, in this options object.
        //
        //Parameters:
        //    time - The activity time value to set in this options object.
        void activityTime(float time);

        //API Function: inactivityTimeout
        //    Gets the current amount of time that the Activity Sense mode runs without a value over the <activityThreshold>
        //    before it goes back into a low power mode, in this options object.
        //
        //Returns:
        //    The inactivity timeout value set in this options object.
        float inactivityTimeout() const;

        //API function: inactivityTimeout
        //    Sets the current amount of time that the Activity Sense mode runs without a value over the <activityThreshold>
        //    before it goes back into a low power mode, in this options object.
        //
        //Parameters:
        //    timeout - The inactivity timeout value to set in this options object.
        void inactivityTimeout(float timeout);
    };
}