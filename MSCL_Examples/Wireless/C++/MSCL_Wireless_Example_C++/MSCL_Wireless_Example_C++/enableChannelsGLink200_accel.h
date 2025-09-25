#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "helperFunctions.h"


static void enableChannelsGLink200_accel(mscl::WirelessNode& node)
{
    // Ensure the node is idle before configuring its channels.
    // While pinging the node isn't strictly required, it's good practice to verify connectivity.
    // Idling the node is essential for making configuration changes.
    idleAndPing(node); 

    // Enable desired channels (Accel X/Y/Z)
    mscl::ChannelMask mask;
    mask.enable(1, true); // Accel X
    mask.enable(2, true); // Accel Y      Channels 1-3 are accel channels 
    mask.enable(3, true); // Accel Z    

    printChannels(node); // Prints channels for clarity's sake 

    // Create Config object to start setting up Node configuration 
    mscl::WirelessNodeConfig config;  

    // Set Config to ACCEL output mode
    config.sensorOutputMode(mscl::WirelessTypes::sensorOutputMode_accel);

    config.activeChannels(mask);
    node.applyConfig(config);
    std::cout << "Configuration applied." << std::endl;
}
