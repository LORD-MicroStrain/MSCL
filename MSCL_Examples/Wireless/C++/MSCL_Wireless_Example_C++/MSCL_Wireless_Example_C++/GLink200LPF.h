#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

mscl::WirelessTypes::Filter GLink200LPFChoice()
{
    unsigned char choice; 
    std::cout << "Low Pass Filter Cutoff Options: " << std::endl;
    std::cout << "(1) 26hz" << std::endl;
    std::cout << "(2) 52hz" << std::endl;
    std::cout << "(3) 104hz" << std::endl;
    std::cout << "(4) 209hz" << std::endl;
    std::cout << "(5) 418hz" << std::endl;
    std::cout << "(6) 800hz" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
        case '1': return mscl::WirelessTypes::filter_26hz;
        case '2': return mscl::WirelessTypes::filter_52hz;
        case '3': return mscl::WirelessTypes::filter_104hz;
        case '4': return mscl::WirelessTypes::filter_209hz;
        case '5': return mscl::WirelessTypes::filter_418hz;
        case '6': return mscl::WirelessTypes::filter_800hz;

        default: return mscl::WirelessTypes::filter_26hz;
    }
}

void GLink200LPF(mscl::WirelessNode& node)
{
    mscl::WirelessNodeConfig config;
        
    // When configuring HPF all 3 channels (ch 1-3) are affected at once 
    mscl::ChannelMask mask; 
    mask.enable(1, true);
    mask.enable(2, true);
    mask.enable(3, true);

    // Apply lowpass filter config 
    config.lowPassFilter(mask, GLink200LPFChoice());
        
    // Apply config to node 
    node.applyConfig(config);
    std::cout << "Configuration applied ! " << std::endl;
}