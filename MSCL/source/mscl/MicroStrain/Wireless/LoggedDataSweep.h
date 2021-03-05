/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <memory>

#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/Timestamp.h"
#include "WirelessDataPoint.h"
#include "WirelessTypes.h"

namespace mscl
{
    //API Class: LoggedDataSweep
    //    Represents 1 data sweep that was logged to a <WirelessNode>.
    class LoggedDataSweep
    {
    public:
        //Function: LoggedDataSweep
        //    Creates a LoggedDataSweep object with a tick and timestamp of 0.
        LoggedDataSweep();
        
        //Function: LoggedDataSweep
        //    Creates a LoggedDataSweep object.
        //
        //Parameters:
        //    timestamp - The <Timestamp> of the sweep.
        //    tick - The tick of the sweep.
        //    data - The <ChannelData> containing the actual data points.
        //    calsApplied - Whether calibration coefficients have already been applied to the data or not.
        LoggedDataSweep(const Timestamp& timestamp, uint64 tick, const ChannelData& data, bool calsApplied);

    private:
        //Variable: m_timestamp
        //    The <Timestamp> of the data sweep.
        Timestamp m_timestamp;

        //Variable: m_tick
        //    The tick value representing the count of each sweep in a datalogging session (increments with each sweep).
        uint64 m_tick;

        //Variable: m_data
        //    Contains one or more <WirelessDataPoint>s, corresponding to each channel's data for this sweep.
        ChannelData m_data;

        //Variable: m_calsApplied
        //  Whether calibration coefficients have been applied to the data or not.
        bool m_calsApplied;

    public:
        //API Function: timestamp
        //    Gets the timestamp of the sweep as a <Timestamp>
        //
        //Returns:
        //    A <Timestamp> representing the timestamp of the sweep
        Timestamp timestamp() const;

        //API Function: tick
        //    Gets the tick value of the sweep
        //
        //Returns:
        //    The tick value of the sweep
        uint64 tick() const;

        //API Function: data
        //    Gets the channel data in this sweep as a <WirelessDataPoint::ChannelData> container.
        //
        //Returns:
        //    A <WirelessDataPoint::ChannelData> container holding the data for the sweep.
        const ChannelData& data() const;

        //API Function: calApplied
        //  Gets whether calibration coefficients have been applied to the data already.
        //
        //Returns:
        //  true if the data already has cal coefficients applied to it, false if it does not have any cal coefficients applied.
        bool calApplied() const;
    };

    //API Typedef: LoggedDataSweeps
    //    Typedef for a vector of <LoggedDataSweep> objects.
    typedef std::vector<LoggedDataSweep> LoggedDataSweeps;

}