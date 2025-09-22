// show the channel mask 
// show channels 1-3 enable accel mode 4-5 only enabled tilt mode 
// include derived channels 

#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>

void idleAndPing_accel(mscl::WirelessNode& node)
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

static void enableChannelsGLink200(mscl::WirelessNode& node)
{
    idleAndPing_accel(node); // Idle and ping node to prepare it for channel configuration.  Node must be idle to alter configuration.
    // Pining a node is good practice to confirm a reasonable connection though it's not essential int he way idling a node is 

    std::vector<mscl::WirelessChannel> channels = node.features().channels();
    //Create a list of WirelessChannel's to loop through available channels on GLink200 

    for (const mscl::WirelessChannel& ch : channels)
    {
        std::cout << "Channel " << ch.id() << ": " << ch.channelName(ch.id()) << " - ";


        // GLink200 as tilt mode or accel mode.  Only one can be enabled at a time and only the channel of the mode selected can be enabled 
        // the below line accesses the channel type 
        mscl::WirelessTypes::ChannelType type = ch.type();   
        switch (type)
        {
        case mscl::WirelessTypes::ChannelType::chType_acceleration: std::cout << "Accelerometer Channel";
            break;

        case mscl::WirelessTypes::ChannelType::chType_tilt: std::cout << "Tilt Channel";
            break;

        default: std::cout << "Other";
            break;
        }
        std::cout << std::endl;
    }

    mscl::WirelessNodeConfig config;  // Create Config object to start setting up Node configuration 

    // if we want to output tilt 
    config.sensorOutputMode(mscl::WirelessTypes::sensorOutputMode_tilt);

    // if we want to output accel mode
    config.sensorOutputMode(mscl::WirelessTypes::sensorOutputMode_accel);

    // === 6. Apply Configuration ===
    // Enable desired channels (Accel X/Y/Z, Gyro X/Y/Z)
    //mscl::ChannelMask mask;
    //mask.enable(1, true); // Accel X 
    //mask.enable(2, true); // Accel Y      Channels 1-3 are acecl channels 
    //mask.enable(3, true); // Accel Z                                        
    //mask.enable(4, true); // Pitch        Channels 4-5 are tilt channels
    //mask.enable(5, true); // Roll 
    // Channels 1-3 and 4-5 ARE mutually exclusive.. i.e. a g-link can either be in accel mode or tilt mode
    // You cannot stream both tilt and accel channels.. It's one or the other 

    //config.activeChannels(mask);
    node.applyConfig(config);
    std::cout << "Configuration applied." << std::endl;
}
