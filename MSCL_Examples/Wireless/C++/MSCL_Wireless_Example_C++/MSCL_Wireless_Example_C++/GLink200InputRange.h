#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

mscl::WirelessTypes::InputRange GLink200InputRange()
{
    unsigned char choice; 

    // log and transmit
    std::cout << "Input Range Options: " << std::endl;
    std::cout << "(1) 2G" << std::endl;
    std::cout << "(2) 4G" << std::endl;
    std::cout << "(3) 8G" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
        case '1': return mscl::WirelessTypes::range_2G;
        case '2': return mscl::WirelessTypes::range_4G;
        case '3': return mscl::WirelessTypes::range_8G;

        default: return mscl::WirelessTypes::range_2G;
    }
}


void GLink200InputRange(mscl::WirelessNode& node)
{
    //set up mask
    //GLink-200 input range sets all channels (1-3) at the same time 
    mscl::ChannelMask mask; 
    mscl::WirelessNodeConfig config; 
    mask.enable(1, true); 
    mask.enable(2, true); 
    mask.enable(3, true); 

    //configure the input range using our mask and rangeChoice from user input
    config.inputRange(mask, GLink200InputRange()); 

    //apply config
    node.applyConfig(config); 
}