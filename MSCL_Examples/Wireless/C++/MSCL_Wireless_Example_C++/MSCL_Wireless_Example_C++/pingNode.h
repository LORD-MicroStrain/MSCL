#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Wireless/WirelessNode.h>

static void pingNode(mscl::WirelessNode& node)
{
    const mscl::PingResponse response = node.ping();

    if (response.success())
    {
        // Get some details from the response
        printf("Successfully pinged Node %d\n", node.nodeAddress());
        printf("Base Station RSSI: %d\n", response.baseRssi());
        printf("Node RSSI: %d\n\n", response.nodeRssi());

        // We can talk to the Node, so let's get some more info
        printf("Node Information: \n");
        printf("Model Number: %d\n", node.model());
        printf("Serial: %s\n", node.serial().c_str());
        printf("Firmware: %s\n\n", node.firmwareVersion().str().c_str());
    }
    else
    {
        // Note: In order to communicate with a Wireless Node, all the following must be true:
        //  - The Node is powered on, and within range of the BaseStation
        //  - The Node is on the same frequency as the BaseStation
        //  - The Node is in Idle Mode (not sampling, and not sleeping)
        //  - The Node is on the same communication protocol as the BaseStation (LXRS vs LXRS+)
        printf("Failed to ping Node %d.\n", node.nodeAddress());
    }
}
