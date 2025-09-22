#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>

void idleAndPing_tiltexample(mscl::WirelessNode& node)
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

static void enableChannelsGLink200_tilt(mscl::WirelessNode& node)
{
    idleAndPing_tiltexample(node); // Idle and ping node to prepare it for channel configuration.  Node must be idle to alter configuration.
    // Pining a node is good practice to confirm a reasonable connection though it's not essential int he way idling a node is 

    std::vector<mscl::WirelessChannel> channels = node.features().channels();
    //Create a list of WirelessChannel's to loop through available channels on GLink200 

    for (const mscl::WirelessChannel& ch : channels)
    {
        // Using the below varaible we can distinguish tilt channel from accel channel
        mscl::WirelessTypes::ChannelType type = ch.type();

        if (type == mscl::WirelessTypes::ChannelType::chType_tilt)
            std::cout << "Channel " << ch.id() << ": " << ch.channelName(ch.id()) << " - " << ch.description() << std::endl;
    }

    // Create Config object to start setting up Node configuration 
    mscl::WirelessNodeConfig config;

    // Set Config to TILT output mode
    config.sensorOutputMode(mscl::WirelessTypes::sensorOutputMode_tilt);

    // === 6. Apply Configuration ===
    // Enable desired channels (Tilt Pitch/Roll)
    mscl::ChannelMask mask;
    mask.enable(4, true); // Tilt Pitch
    mask.enable(5, true); // Tilt Roll      Channels 4 and 5 are tilt channels 

    config.activeChannels(mask);
    node.applyConfig(config);
    std::cout << "Configuration applied." << std::endl;
}
