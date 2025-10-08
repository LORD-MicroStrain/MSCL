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
//
static void nonSyncSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode> nodes)
{
    unsigned char choice; 
    mscl::WirelessTypes::SamplingMode sampleModeChoice; 
    mscl::WirelessTypes::CommProtocol lxrsChoice; 
    bool losslessChoice; 

    printf("\nSetting up Stream configuration settings...");

    //lxrs
    std::cout << "LXRS Mode Options: " << std::endl;
    std::cout << "(1) LXRS" << std::endl;
    std::cout << "(2) LXRS+" << std::endl;
    std::cin >> choice; 
    lxrsChoice = setLxrsMode_(choice); 

    for (mscl::WirelessNode& node : nodes)
    {   // Goes through a list of nodes and adds them to our SyncSamplingNetwork object

        //create WirelessNodeConfig object to configure each node individually 
        mscl::WirelessNodeConfig config;
        config.samplingMode(mscl::WirelessTypes::samplingMode_nonSync); 

        if (lxrsChoice == mscl::WirelessTypes::commProtocol_lxrs)
            config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrs);
        else
            config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrsPlus);

        // If no issue with the node specific configuration add it to our SyncSamplingNetwork object
        node.applyConfig(config); 
        node.startNonSyncSampling(); 
    }

    printf("Done.\n");
}
