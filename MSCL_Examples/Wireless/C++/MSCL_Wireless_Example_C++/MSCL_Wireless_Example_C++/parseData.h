#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Wireless/BaseStation.h>

static void parseData(mscl::BaseStation& base)
{
    // Endless loop of reading in data
    while (true)
    {
        // Loop through all the data sweeps that have been collected by the BaseStation, with a timeout of 10 milliseconds
        for (const mscl::DataSweep& sweep : base.getData(10))
        {
            // Print out information about the sweep
            printf("Packet Received: ");
            printf("Node %d ", sweep.nodeAddress());
            printf("Timestamp: %s ", sweep.timestamp().str().c_str());
            printf("Tick: %d ", sweep.tick());
            printf("Sample Rate: %s ", sweep.sampleRate().prettyStr().c_str());
            printf("Base RSSI: %d ", sweep.baseRssi());
            printf("Node RSSI: %d ", sweep.nodeRssi());

            printf("DATA: ");

            // Iterate over each point in the sweep
            for (const mscl::WirelessDataPoint& dataPoint: sweep.data())
            {
                // Print out the channel name
                printf("%s: ", dataPoint.channelName().c_str());

                // Print out the channel data
                // Note: The as_string() function is being used here for simplicity.
                //      Other methods (i.e., as_float, as_uint16, as_Vector) are also available.
                //      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                printf("%s ", dataPoint.as_string().c_str());
            }

            printf("\n");
        }
    }
}
