/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

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
