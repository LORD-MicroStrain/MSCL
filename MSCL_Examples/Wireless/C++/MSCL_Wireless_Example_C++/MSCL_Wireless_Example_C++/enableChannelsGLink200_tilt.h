#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "helperFunctions.h"



static void enableChannelsGLink200_tilt(mscl::WirelessNode& node)
{
    // Ensure the node is idle before configuring its channels.
    // While pinging the node isn't strictly required, it's good practice to verify connectivity.
    // Idling the node is essential for making configuration changes.
    idleAndPing(node);

    // Enable desired channels (Tilt Pitch/Roll)
    mscl::ChannelMask mask;
    mask.enable(4, true); // Tilt Pitch
    mask.enable(5, true); // Tilt Roll      Channels 4 and 5 are tilt channels 

    printChannels(node);  // Prints channels for clarity's sake 
    
    // Create Config object to start setting up Node configuration 
    mscl::WirelessNodeConfig config;

    // Set Config to TILT output mode
    config.sensorOutputMode(mscl::WirelessTypes::sensorOutputMode_tilt);

    config.activeChannels(mask);
    node.applyConfig(config);
    std::cout << "Configuration applied." << std::endl;
}
