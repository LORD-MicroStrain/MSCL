#pragma once

#include <vector>
#include "mscl/mscl.h"

static void startSyncSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode> nodes)
{
    //create a SyncSamplingNetwork object, giving it the BaseStation that will be the master BaseStation for the network.
    mscl::SyncSamplingNetwork network(base);

    //add the WirelessNodes to the network.
    //Note: The Nodes must already be configured for Sync Sampling before adding to the network, or else Error_InvalidNodeConfig will be thrown.
    for(mscl::WirelessNode& node : nodes)
    {
        cout << "Adding Node " << node.nodeAddress() << " to the network...";
        network.addNode(node);
        cout << "Done." << endl;
    }

    //can get information about the network
    cout << "Network info: " << endl;
    cout << "Network OK: " << network.ok() << endl;
    cout << "Percent of Bandwidth: " << network.percentBandwidth() << "%" << endl;
    cout << "Lossless Enabled: " << network.lossless() << endl;

    //apply the network configuration to every node in the network
    cout << "Applying network configuration...";
    network.applyConfiguration();
    cout << "Done." << endl;

    //start all the nodes in the network sampling. The master BaseStation's beacon will be enabled with the system time.
    //  Note: if you wish to provide your own start time (not use the system time), pass a mscl::Timestamp object as a second parameter to this function.
    //  Note: if you do not want to enable a beacon at this time, use the startSampling_noBeacon() function. (The nodes will wait until they hear a beacon to start sampling).
    cout << "Starting the network...";
    network.startSampling();
    cout << "Done." << endl;

    //=======================================================================================
    //Many other functions are available for the SyncSamplingNetwork:
    //
    //network.lossless()                        //enable or disable "lossless" mode for the network (default of enabled).
    //network.ok()                              //check whether or not the network is "OK" meaning all nodes fit in the network and have communicated successfully.
    //network.percentBandwidth()                //get the percent of bandwidth for the entire network.
    //network.refresh()                         //refreshes the entire network. Should be called any time a change is made to the node after it has been added to the network.
    //network.removeNode()                      //remove a node from the network.
    //network.getNodeNetworkInfo(nodeAddress)   //get network information for an individual node in the network (TDMA address, percent bandwidth, etc.)
    //=======================================================================================
}