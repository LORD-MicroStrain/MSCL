#pragma once

#include "mscl/mscl.h"

static void pingNode(mscl::WirelessNode& node)
{
    mscl::PingResponse response = node.ping();

    if(response.success())
    {
        //get some details from the response
        cout << "Successfully pinged Node " << node.nodeAddress() << endl;
        cout << "Base Station RSSI: " << response.baseRssi() << endl;
        cout << "Node RSSI: " << response.nodeRssi() << endl << endl;

        //we can talk to the Node, so let's get some more info
        cout << "Node Information: " << endl;
        cout << "Model Number: " << node.model() << endl;
        cout << "Serial: " << node.serial() << endl;
        cout << "Firmware: " << node.firmwareVersion().str() << endl << endl;
    }
    else
    {
        //Note: In order to communicate with a Wireless Node, all of the following must be true:
        //  - The Node is powered on, and within range of the BaseStation
        //  - The Node is on the same frequency as the BaseStation
        //  - The Node is in Idle Mode (not sampling, and not sleeping)
        //  - The Node is on the same communication protocol as the BaseStation (LXRS vs LXRS+)
        cout << "Failed to ping Node " << node.nodeAddress() << "." << endl;
    }
}