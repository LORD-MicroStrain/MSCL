#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <mscl/MicroStrain/Wireless/WirelessNode.h>

static void startSyncSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode> nodes)
{
    // Create a SyncSamplingNetwork object, giving it the BaseStation that will be the master BaseStation for the network.
    mscl::SyncSamplingNetwork network(base);

    // Add the WirelessNodes to the network.
    // Note: The Nodes must already be configured for Sync Sampling before adding to the network, or else Error_InvalidNodeConfig will be thrown.
    for (mscl::WirelessNode& node : nodes)
    {
        printf("Adding Node %d to the network...", node.nodeAddress());
        network.addNode(node);
        printf("Done.\n");
    }

    // Can get information about the network
    printf("Network info: \n");
    printf("Network OK: %s\n", network.ok() ? "TRUE" : "FALSE");
    printf("Percent of Bandwidth: %00.02f%%\n", network.percentBandwidth());
    printf("Lossless Enabled: %s\n", network.lossless() ? "TRUE" : "FALSE");

    // Apply the network configuration to every node in the network
    printf("Applying network configuration...");
    network.applyConfiguration();
    printf("Done.\n");

    // Start all the nodes in the network sampling. The master BaseStation's beacon will be enabled with the system time.
    //  Note: if you wish to provide your own start time (not use the system time), pass a mscl::Timestamp object as a second parameter to this function.
    //  Note: if you do not want to enable a beacon at this time, use the startSampling_noBeacon() function. (The nodes will wait until they hear a beacon to start sampling).
    printf("Starting the network...");
    network.startSampling();
    printf("Done.\n");

    //=======================================================================================
    // Many other functions are available for the SyncSamplingNetwork:
    //
    // network.lossless()                        //enable or disable "lossless" mode for the network (default of enabled).
    // network.ok()                              //check whether the network is "OK" meaning all nodes fit in the network and have communicated successfully.
    // network.percentBandwidth()                //get the percentage of bandwidth for the entire network.
    // network.refresh()                         //refreshes the entire network. Should be called any time a change is made to the node after it has been added to the network.
    // network.removeNode()                      //remove a node from the network.
    // network.getNodeNetworkInfo(nodeAddress)   //get network information for an individual node in the network (TDMA address, percent bandwidth, etc.)
    //=======================================================================================
}