/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/Timestamp.h"

namespace mscl
{
    //API Class: BeaconStatus
    //    Represents the status of a BaseStation beacon.
    //    See also <BaseStation::beaconStatus>.
    class BeaconStatus
    {
    public:
        //Constructor: BeaconStatus
        //    Creates a default BeaconStatus object.
        BeaconStatus();

        //Constructor: BeaconStatus
        //    Creates a BeaconStatus object with the given parameters.
        //
        //Parameters:
        //    beaconEnabled - Whether the beacon is enabled or disabled.
        //    currentTimestamp - The current <Timestamp> of the beacon.
        BeaconStatus(bool beaconEnabled, const Timestamp& currentTimestamp);

    private:
        //Variable: m_enabled
        //    Whether the beacon is enabled or disabled.
        bool m_enabled;

        //Variable: m_timestamp
        //    The current <Timestamp> of the beacon.
        Timestamp m_timestamp;

    public:
        //API Function: enabled
        //    Gets whether the beacon is enabled (true) or disabled (false).
        bool enabled();

        //API Function: timestamp;
        //    Gets the current <Timestamp> of the beacon.
        const Timestamp& timestamp();
    };

}