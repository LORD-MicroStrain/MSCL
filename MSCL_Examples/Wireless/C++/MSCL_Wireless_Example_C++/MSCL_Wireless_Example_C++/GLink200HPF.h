#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

mscl::WirelessTypes::HighPassFilter GLink200HPF()
{
    unsigned char choice;

    std::cout << "High Pass Filter Enable: " << std::endl;
    std::cout << "(1) enabled" << std::endl;
    std::cout << "(0) disable" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
        case '1': return mscl::WirelessTypes::highPass_auto;
        case '0': return mscl::WirelessTypes::highPass_off;

        default: return mscl::WirelessTypes::highPass_auto;
    }
}

void GLink200HPF(mscl::WirelessNode& node)
{
    mscl::WirelessNodeConfig config;
   
    // When configuring LPF all 3 channels (ch 1-3) are affected at once 
    mscl::ChannelMask mask;
    mask.enable(1, true);
    mask.enable(2, true);
    mask.enable(3, true);

    // apply lowpass filter config
    config.highPassFilter(mask, GLink200HPF()); 

    //apply config to node 
    node.applyConfig(config);
    std::cout << "Configuration applied ! " << std::endl;
}