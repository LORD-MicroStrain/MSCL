// show the channel mask 
// show channels 1-3 enable accel mode 4-5 only enabled tilt mode 
// include derived channels 

#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>

static void enableChannelsGLink200(mscl::WirelessNode& node)
{
    mscl::WirelessNodeConfig config;

    // Set sample rate (check what's supported for your node)
    config.sampleRate();

    // Enable desired channels (Accel X/Y/Z, Gyro X/Y/Z)
    mscl::ChannelMask mask;
    mask.enable(1, true); // Accel X
    mask.enable(2, true); // Accel Y
    mask.enable(3, true); // Accel Z
    mask.enable(4, true); // Gyro X
    mask.enable(5, true); // Gyro Y
    mask.enable(6, true); // Gyro Z

    config.activeChannels(mask);

    // === 6. Apply Configuration ===
    node.applyConfig(config);
    std::cout << "Configuration applied." << std::endl;

    // === 7. Start Sampling ===
    node.startSampling();
    std::cout << "Sampling started. Press Ctrl+C to stop..." << std::endl;

}
