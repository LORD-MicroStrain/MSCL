#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "helperFunctions.h"


void idleAndPing(mscl::WirelessNode& node) 
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

void printChannels(mscl::WirelessNode& node)
{
    for (const mscl::WirelessChannel& channel : node.features().channels())
        std::cout << "Channel " << channel.id() << ": " << channel.channelName(channel.id()) << " - " << channel.description() << std::endl;
}

bool checkConfig(mscl::WirelessNode& node, mscl::WirelessNodeConfig& config)
{
    mscl::ConfigIssues issues;

    if (!node.verifyConfig(config, issues))
    {
        printf("Failed to verify the configuration. The following issues were found:\n");

        // Print out all the issues that were found
        for (const mscl::ConfigIssue& issue : issues)
            printf("%s\n", issue.description().c_str());

        printf("Configuration will not be applied.\n");

        return false; 
    }
    else
        return true; 

}
