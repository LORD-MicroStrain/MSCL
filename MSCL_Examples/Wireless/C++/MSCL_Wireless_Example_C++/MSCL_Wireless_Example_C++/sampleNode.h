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

mscl::WirelessTypes::SamplingMode setSyncType_(unsigned char choice) 
{
    switch (choice)
    {
        case '1': return mscl::WirelessTypes::samplingMode_sync;  
        case '2': return mscl::WirelessTypes::samplingMode_nonSync;  

        default: return mscl::WirelessTypes::samplingMode_sync;
    }
}

mscl::WirelessTypes::CommProtocol setLxrsMode_(unsigned char choice) 
{
    switch (choice)
    {
    case '1': return mscl::WirelessTypes::commProtocol_lxrs;  
    case '2': return mscl::WirelessTypes::commProtocol_lxrsPlus;  

    default: return mscl::WirelessTypes::commProtocol_lxrs;
    }
}

bool setLosslessMode_(unsigned char choice) 
{
    switch (choice) 
    {
        case '1': return 1;  // Sync
        case '2': return 0;  // Non Sync

        default: return 1; 
    }
}

// This example shows how you can set up a node 
//
static void startSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode> nodes)
{
    unsigned char choice; 
    mscl::WirelessTypes::SamplingMode sampleModeChoice; 
    mscl::WirelessTypes::CommProtocol lxrsChoice; 
    bool losslessChoice; 

    printf("\nSetting up Stream configuration settings...");

    // SyncSamplingNetwork network is the sampling network that we need to set up 
    mscl::SyncSamplingNetwork network(base); 

    //sync
    std::cout << "Sampling Mode Options: " << std::endl;
    std::cout << "(1) Sync" << std::endl;
    std::cout << "(2) Non-Sync and Lossy" << std::endl; // If Non Sync is selected Lossless gets disabled 
    std::cin >> choice; 
    sampleModeChoice = setSyncType_(choice); 

    //lxrs
    std::cout << "LXRS Mode Options: " << std::endl;
    std::cout << "(1) LXRS" << std::endl;
    std::cout << "(2) LXRS+" << std::endl;
    std::cin >> choice; 
    lxrsChoice = setLxrsMode_(choice); 

    //lossless
    std::cout << "Lossless Options: " << std::endl;
    std::cout << "(1) Lossless" << std::endl;
    std::cout << "(2) Lossy" << std::endl;
    std::cin >> choice; 
    losslessChoice = setLosslessMode_(choice); 

    mscl::WirelessNodeConfig config;  

    /*for (mscl::WirelessNode& node : nodes)
    {   // Goes through a list of nodes and adds them to our SyncSamplingNetwork object

        //create WirelessNodeConfig object to configure each node individually 
        mscl::WirelessNodeConfig config;
        mscl::ConfigIssues issues;

        if (!node.verifyConfig(config, issues))
        {
            printf("Failed to verify the configuration. The following issues were found:\n");

            // Print out all the issues that were found
            for (const mscl::ConfigIssue& issue : issues)
            {
                printf("%s\n", issue.description().c_str());
            }

            printf("Configuration will not be applied.\n");
        }
        else
        {
            node.applyConfig(config);
            printf("Configuration applied.\n");
        }

        // If no issue with the node specific configuration add it to our SyncSamplingNetwork object
        network.addNode(node);
    }*/

    // set the configuration options that we want to change
    // config.defaultmode(mscl::wirelesstypes::defaultmode_idle);
    // config.inactivitytimeout(7200);
    
    //config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrs); 
    //config.samplingMode(mscl::WirelessTypes::samplingMode_sync);
    //config.samplingMode(mscl::WirelessTypes::samplingMode_nonSync);
    //config.sampleRate(mscl::WirelessTypes::sampleRate_256Hz);

    printf("Done.\n");
}

