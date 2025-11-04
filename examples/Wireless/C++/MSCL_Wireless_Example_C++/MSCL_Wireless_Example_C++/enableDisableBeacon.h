#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Wireless/BaseStation.h>
#include <mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h>

static void enableDisableBeacon(mscl::BaseStation& base)
{
    // Make sure we can ping the base station
    if (!base.ping())
    {
        printf("Failed to ping the Base Station\n");
    }

    if (base.features().supportsBeaconStatus())
    {
        mscl::BeaconStatus status = base.beaconStatus();
        printf("Beacon current status: Enabled?: %s", status.enabled() ? "TRUE" : "FALSE");
        printf(" Time: %s\n", status.timestamp().str().c_str());
    }

    printf("Attempting to enable the beacon...\n");

    // Enable the beacon on the Base Station using the PC time
    mscl::Timestamp beaconTime = base.enableBeacon();

    // If we got here, no exception was thrown, so enableBeacon was successful
    printf("Successfully enabled the beacon on the Base Station\n");
    printf("Beacon's initial Timestamp: %s\n", beaconTime.str().c_str());

    printf("Beacon is active\n");
    printf("Sleeping for 3 seconds...\n");

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Disable the beacon on the Base Station
    base.disableBeacon();

    // If we got here, no exception was thrown, so disableBeacon was successful
    printf("Successfully disabled the beacon on the Base Station\n");
}
