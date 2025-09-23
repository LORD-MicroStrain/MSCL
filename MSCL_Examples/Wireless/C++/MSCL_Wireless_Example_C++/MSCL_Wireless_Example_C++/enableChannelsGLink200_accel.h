#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>


move this to a .h
void idleAndPing_accelexample(mscl::WirelessNode& node)
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

static void enableChannelsGLink200_accel(mscl::WirelessNode& node)
{
    // Ensure the node is idle before configuring its channels.
    // While pinging the node isn't strictly required, it's good practice to verify connectivity.
    // Idling the node is essential for making configuration changes.
    idleAndPing_accelexample(node); 


    // === 6. Apply Configuration ===
    // Enable desired channels (Accel X/Y/Z)
    mscl::ChannelMask mask;
    mask.enable(1, true); // Accel X
    mask.enable(2, true); // Accel Y      Channels 1-3 are accel channels 
    mask.enable(3, true); // Accel Z    

    std::vector<mscl::WirelessChannel> channels = node.features().channels();
    //Create a list of WirelessChannel's to loop through available channels on GLink200 

    for (const mscl::WirelessChannel& ch : channels)
    {   
        // Using the below varaible we can distinguish accel channel from tilt channel
        mscl::WirelessTypes::ChannelType type = ch.type();   

        if (type == mscl::WirelessTypes::ChannelType::chType_acceleration)
            std::cout << "Channel " << ch.id() << ": " << ch.channelName(ch.id()) << " - " << ch.description() << std::endl;
    }

    // Create Config object to start setting up Node configuration 
    mscl::WirelessNodeConfig config;  

    // Set Config to ACCEL output mode
    config.sensorOutputMode(mscl::WirelessTypes::sensorOutputMode_accel);

                                    

    config.activeChannels(mask);
    node.applyConfig(config);
    std::cout << "Configuration applied." << std::endl;
}
