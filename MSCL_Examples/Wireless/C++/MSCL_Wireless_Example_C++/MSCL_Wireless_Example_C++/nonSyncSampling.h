#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

mscl::WirelessTypes::CommProtocol setLxrsMode_(unsigned char choice) 
{
    switch (choice)
    {
    case '1': return mscl::WirelessTypes::commProtocol_lxrs;  
    case '2': return mscl::WirelessTypes::commProtocol_lxrsPlus;  

    default: return mscl::WirelessTypes::commProtocol_lxrs;
    }
}

// This example shows how you can set up a node 
static void nonSyncSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode> nodes)
{
    unsigned char choice; 
    mscl::WirelessTypes::SamplingMode sampleModeChoice; 
    mscl::WirelessTypes::CommProtocol lxrsChoice; 
    bool losslessChoice; 

    printf("\nSetting up Stream configuration settings...");
    std::cout << "LXRS Mode Options: " << std::endl;
    std::cout << "(1) LXRS" << std::endl;
    std::cout << "(2) LXRS+" << std::endl;
    std::cin >> choice; 
    lxrsChoice = setLxrsMode_(choice); 

    // basestaion config object used to switch basestation comm protocol 
    mscl::BaseStationConfig b_config; 

    for (mscl::WirelessNode& node : nodes)
    {   // Goes through a list of nodes and adds them to our SyncSamplingNetwork object

        //create WirelessNodeConfig object to configure each node individually 
        mscl::WirelessNodeConfig config;

        // set base to lxrs plus as a starting point 
        b_config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrs);
        base.applyConfig(b_config);
        mscl::PingResponse response = node.ping();

        //if the ping response under lxrs was a success move on if not switch to lxrs+
        if (response.success())
            std::cout << "Node responded to ping." << std::endl;
        else
        {
            b_config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrsPlus);
            base.applyConfig(b_config);
        }

        // set the sampling mode to sync
        config.samplingMode(mscl::WirelessTypes::samplingMode_nonSync); 

        // set node to comm protocol based on User Input
        config.communicationProtocol(lxrsChoice);

        // apply our configuration to node
        node.applyConfig(config); 
    } 
    
    // now set basestaion to comm protocol based on user input
    b_config.communicationProtocol(lxrsChoice); 
    base.applyConfig(b_config); 

    // loop through node list and set to sample
    for (mscl::WirelessNode& node : nodes)
        node.startNonSyncSampling();

    printf("Done.\n");
}
