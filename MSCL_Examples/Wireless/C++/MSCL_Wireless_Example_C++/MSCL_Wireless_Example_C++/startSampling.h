#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>

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

static void startSampling(mscl::WirelessNode& node)
{
    printf("\nSetting up Stream configuration settings...");

    // Create a WirelessNodeConfig which is used to set all node configuration options
    mscl::WirelessNodeConfig config;
    std::vector<mscl::WirelessNode> networkNodes;
    networkNodes.push_back(node);

    // Set the configuration options that we want to change
    // config.defaultMode(mscl::WirelessTypes::defaultMode_idle);
    // config.inactivityTimeout(7200);
    
    config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrs); 
    config.samplingMode(mscl::WirelessTypes::samplingMode_sync);
    config.samplingMode(mscl::WirelessTypes::samplingMode_nonSync);
    config.sampleRate(mscl::WirelessTypes::sampleRate_256Hz);

    //  Attempt to verify the configuration with the Node we want to apply it to
    //  Note that this step is not required before applying; however, the apply will throw an
    //  Error_InvalidNodeConfig exception if the config fails to verify.
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
        // Apply the configuration to the Node
        //  Note that this writes multiple options to the Node.
        //  If an Error_NodeCommunication exception is thrown, it is possible that
        //  some options were successfully applied, while others failed.
        //  It is recommended to keep calling applyConfig until no exception is thrown.
        node.applyConfig(config);
    }

    printf("Done.\n");
}

