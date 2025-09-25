#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

// lxrs or lxrs+
// lossless enable disable
// sync enable disable
// where should things like idle/sample on start up live? 

mscl::WirelessTypes::SamplingMode setSyncType(unsigned char choice)
{
    switch (choice)
    {
    case '1': return mscl::WirelessTypes::samplingMode_sync;
    case '2': return mscl::WirelessTypes::samplingMode_nonSync;

    default: return mscl::WirelessTypes::samplingMode_sync;
    }
}

mscl::WirelessTypes::CommProtocol setLxrsMode(unsigned char choice)
{
    switch (choice)
    {
    case '1': return mscl::WirelessTypes::commProtocol_lxrs;
    case '2': return mscl::WirelessTypes::commProtocol_lxrsPlus;

    default: return mscl::WirelessTypes::commProtocol_lxrs;
    }
}

bool setLosslessMode(unsigned char choice)
{
    switch (choice)
    {
    case '1': return 1;  // Sync
    case '2': return 0;  // Non Sync

    default: return 1;
    }
}

// This example shows how you can configure a synchronized network of nodes 
// 
static void syncSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode> nodes)
{
    unsigned char choice;
    mscl::WirelessTypes::CommProtocol lxrsChoice;
    bool losslessChoice;

    printf("\nSetting up Stream configuration settings...");

    // SyncSamplingNetwork is the sampling network that we need to set up to stream a synchronized network
    mscl::SyncSamplingNetwork network(base);

    //lxrs
    std::cout << "LXRS Mode Options: " << std::endl;
    std::cout << "(1) LXRS" << std::endl;
    std::cout << "(2) LXRS+" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;
    lxrsChoice = setLxrsMode(choice);

    //lossless
    std::cout << "Lossless Options: " << std::endl;
    std::cout << "(1) Lossless" << std::endl;
    std::cout << "(2) Lossy" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;
    losslessChoice = setLosslessMode(choice);

    // Setting the network to lossless or lossy depending on User Input
    if (losslessChoice)
        network.lossless(true);
    else
        network.lossless(false); 

    // Goes through a list of nodes and adds them to our SyncSamplingNetwork object
    for (mscl::WirelessNode& node : nodes)
    {   

        //create WirelessNodeConfig object to configure each node individually
        mscl::WirelessNodeConfig config;
        mscl::ConfigIssues issues;
       
        // Setting every node to either LXRS or LXRS+ depending on User input
        if(lxrsChoice == mscl::WirelessTypes::commProtocol_lxrs)
            config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrs);
        else
            config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrsPlus);

        // Add node to our SyncSamplingNetwork object
        network.addNode(node);
    }

    // Can get information about the network
    printf("\nNetwork info: \n");
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
    //printf("Starting the network...");
    //network.startSampling();

    printf("Done.\n");
}

