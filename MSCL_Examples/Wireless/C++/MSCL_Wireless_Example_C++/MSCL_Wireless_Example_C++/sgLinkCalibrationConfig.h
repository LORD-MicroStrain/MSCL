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

mscl::WirelessTypes::InputRange sgLinkCh1LinearCal(mscl::WirelessNodeConfig& config)
{
    mscl::LinearEquation lin;
    mscl::ChannelMask mask_ch1;
    mask_ch1.enable(1, true);

    unsigned char choice;

    // log and transmit
    std::cout << "Ch. 1 Options: " << std::endl;
    std::cout << "(1) Raw MicroVolts" << std::endl;
    std::cout << "(1) Raw MilliVolts" << std::endl;
    std::cout << "(1) Raw Volts" << std::endl;
    std::cout << "(1) g's" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::range_2_5V; 
           
    default: return mscl::WirelessTypes::range_2_5V;
    }
}

mscl::WirelessTypes::InputRange sgLinkCh2LinearCal(mscl::WirelessNodeConfig& config)
{
    mscl::LinearEquation lin;
    mscl::ChannelMask mask_ch1;
    mask_ch1.enable(1, true);

    unsigned char choice;

    // log and transmit
    std::cout << "Input Range Ch. 1 Options: " << std::endl;
    std::cout << "(1) +/- 2.5V (Gain 1)" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::range_2_5V; 
           
    default: return mscl::WirelessTypes::range_2_5V;
    }
}

mscl::WirelessTypes::InputRange sgLinkCh5LinearCal(mscl::WirelessNodeConfig& config)
{
    mscl::LinearEquation lin;
    mscl::ChannelMask mask_ch1;
    mask_ch1.enable(1, true);

    unsigned char choice;

    // log and transmit
    std::cout << "Input Range Ch. 1 Options: " << std::endl;
    std::cout << "(1) +/- 2.5V (Gain 1)" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::range_2_5V; 
           
    default: return mscl::WirelessTypes::range_2_5V;
    }
}

mscl::WirelessTypes::InputRange sgLinkCh6LinearCal(mscl::WirelessNodeConfig& config)
{
    mscl::LinearEquation lin;
    mscl::ChannelMask mask_ch1;
    mask_ch1.enable(1, true);

    unsigned char choice;

    // log and transmit
    std::cout << "Input Range Ch. 1 Options: " << std::endl;
    std::cout << "(1) +/- 2.5V (Gain 1)" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::range_2_5V; 
           
    default: return mscl::WirelessTypes::range_2_5V;
    }
}

void sgLinkCalibrationConfig(mscl::BaseStation& base, mscl::WirelessNode& node)
{
    mscl::WirelessNodeConfig config; // try switching order 

       std::cout << "\nCalibration Configuration Applied!" << std::endl;
}


