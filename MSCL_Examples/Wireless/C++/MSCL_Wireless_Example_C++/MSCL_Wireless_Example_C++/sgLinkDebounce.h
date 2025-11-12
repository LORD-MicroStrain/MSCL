#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

// This example toggles the WSDA200USB's communication protocol

mscl::WirelessTypes::InputRange sgLinkInputRangeCh1()
{
    unsigned char choice;

    // log and transmit
    std::cout << "Input Range Ch. 1 Options: " << std::endl;
    std::cout << "(1) +/- 2.5V (Gain 1)" << std::endl;
    std::cout << "(2) +/- 1.25V (Gain 2)" << std::endl;
    std::cout << "(3) +/- 625mV (Gain 4)" << std::endl;
    std::cout << "(4) +/- 312.5mV (Gain 8)" << std::endl;
    std::cout << "(5) +/- 156.25mV (Gain 16)" << std::endl;
    std::cout << "(6) +/- 78.125mV (Gain 32)" << std::endl;
    std::cout << "(7) +/- 39.063mV (Gain 64)" << std::endl;
    std::cout << "(8) +/- 19.532V (Gain 128)" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::range_2_5V;
    case '2': return mscl::WirelessTypes::range_1_25V;
    case '3': return mscl::WirelessTypes::range_625mV;
    case '4': return mscl::WirelessTypes::range_312_5mV;
    case '5': return mscl::WirelessTypes::range_156_25mV;
    case '6': return mscl::WirelessTypes::range_78_125mV;
    case '7': return mscl::WirelessTypes::range_39_0625mV;
    case '8': return mscl::WirelessTypes::range_19_5313mV;

    default: return mscl::WirelessTypes::range_2_5V;
    }
}

mscl::WirelessTypes::InputRange sgLinkInputRangeCh2()
{
    unsigned char choice;

    // log and transmit
    std::cout << "\nInput Range Ch. 1 Options: " << std::endl;
    std::cout << "(1) 0 to 2.5V" << std::endl;
    std::cout << "(2) 0 to 1.25V" << std::endl;
    std::cout << "(3) 0 to 625mV" << std::endl;
    std::cout << "(4) 0 to 312.5mV" << std::endl;
    std::cout << "(5) 0 to 156.25mV" << std::endl;
    std::cout << "(6) 0 to 78.125mV" << std::endl;
    std::cout << "(7) 0 to 39.063mV" << std::endl;
    std::cout << "(8) 0 to 19.532mV" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::range_0to2_5V;
    case '2': return mscl::WirelessTypes::range_0to1_25V;
    case '3': return mscl::WirelessTypes::range_0to625mV;
    case '4': return mscl::WirelessTypes::range_0to312_5mV;
    case '5': return mscl::WirelessTypes::range_0to156_25mV;
    case '6': return mscl::WirelessTypes::range_0to78_125mV;
    case '7': return mscl::WirelessTypes::range_0to39_063mV;
    case '8': return mscl::WirelessTypes::range_0to19_532mV;

    default: return mscl::WirelessTypes::range_0to2_5V;
    }
}

void sgLinkHardwareConfig(mscl::BaseStation& base, mscl::WirelessNode& node) 
{
    mscl::WirelessNodeConfig config; 
    mscl::ChannelMask mask; 

    mask.enable(1, true); 
    config.inputRange(mask, sgLinkInputRangeCh1()); 

    mask.enable(1, false); 
    mask.enable(2, true); 
    config.inputRange(mask, sgLinkInputRangeCh2()); 

    node.applyConfig(config); 

    std::cout << "Configuration Applied!" << std::endl; 
}