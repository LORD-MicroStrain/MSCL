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

void setSyncType(unsigned char choice) {}

void setLxrsMode(unsigned char choice) {}

void setLosslessMode(unsigned char choice) {}

void idleAndPing_samplingexample(mscl::WirelessNode& node)
{
    auto status = node.setToIdle(); // can only read node information when nodes idled 
    std::cout << "\nIdling...";
    while (!status.complete())
    {
        std::cout << ".";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Idled" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    mscl::PingResponse ping = node.ping();
    if (!ping.success())
        throw std::runtime_error("Failed to ping the node.");
}

static void startSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode> nodes)
{
    unsigned char choice; 
    printf("\nSetting up Stream configuration settings...");

    // SyncSamplingNetwork network is the sampling network that we need to set up 
    mscl::SyncSamplingNetwork network(base); 

    //sync
    std::cout << "Sampling Mode Options: " << std::endl;
    std::cout << "(1) Sync" << std::endl;
    std::cout << "(2) Non-Sync" << std::endl;
    std::cin >> choice; 
    setSyncType(choice); 

    //lxrs
    std::cout << "LXRS Mode Options: " << std::endl;
    std::cout << "(1) LXRS" << std::endl;
    std::cout << "(2) LXRS+" << std::endl;
    std::cin >> choice; 
    setLxrsMode(choice); 

    //lossless
    std::cout << "Lossless Options: " << std::endl;
    std::cout << "(1) Sync" << std::endl;
    std::cout << "(2) Non-Sync" << std::endl;
    std::cin >> choice; 
    setLosslessMode(choice); 

    mscl::WirelessNodeConfig config;  


    for (mscl::WirelessNode& node : nodes)
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
    }

    // set the configuration options that we want to change
    // config.defaultmode(mscl::wirelesstypes::defaultmode_idle);
    // config.inactivitytimeout(7200);
    
    //config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrs); 
    //config.samplingMode(mscl::WirelessTypes::samplingMode_sync);
    //config.samplingMode(mscl::WirelessTypes::samplingMode_nonSync);
    //config.sampleRate(mscl::WirelessTypes::sampleRate_256Hz);

    printf("Done.\n");
}

