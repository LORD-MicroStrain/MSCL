#pragma once

#include "mscl/mscl.h"

static void enableDisableBeacon(mscl::BaseStation& base)
{
    //make sure we can ping the base station
    if(!base.ping())
    {
        cout << "Failed to ping the Base Station" << endl;
    }

    if(base.features().supportsBeaconStatus())
    {
        mscl::BeaconStatus status = base.beaconStatus();
        cout << "Beacon current status: Enabled?: " << status.enabled() << " Time: " << status.timestamp().str() << endl;
    }

    cout << "Attempting to enable the beacon..." << endl;

    //enable the beacon on the Base Station using the PC time
    mscl::Timestamp beaconTime = base.enableBeacon();

    //if we got here, no exception was thrown, so enableBeacon was successful
    cout << "Successfully enabled the beacon on the Base Station" << endl;
    cout << "Beacon's initial Timestamp: " << beaconTime.str() << endl;

    cout << "Beacon is active" << endl << "Sleeping for 3 seconds..." << endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));

    //disable the beacon on the Base Station
    base.disableBeacon();

    //if we got here, no exception was thrown, so disableBeacon was successful
    cout << "Successfully disabled the beacon on the Base Station" << endl;
}