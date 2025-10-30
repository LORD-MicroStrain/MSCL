#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

void GLink200LinearCal(mscl::WirelessNode& node)
{
    mscl::WirelessNodeConfig config;

    // Lost Beacon Timeout
    mscl::LinearEquation eq = mscl::LinearEquation(-3.9284e-6f, 0);

    mscl::ChannelMask mask_ch1; 
    mask_ch1.enable(1); 
    mscl::ChannelMask mask_ch2; 
    mask_ch2.enable(2); 
    mscl::ChannelMask mask_ch3; 
    mask_ch3.enable(3); 
    mscl::ChannelMask mask_ch4; 
    mask_ch4.enable(4); 
    mscl::ChannelMask mask_ch5; 
    mask_ch5.enable(5); 

    config.linearEquation(mask_ch1, eq); 

    //apply config
    node.applyConfig(config);
    std::cout << "Configuration applied ! " << std::endl << std::endl;
}