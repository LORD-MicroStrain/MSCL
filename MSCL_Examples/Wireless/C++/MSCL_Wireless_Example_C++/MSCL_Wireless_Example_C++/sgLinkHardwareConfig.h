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

mscl::WirelessTypes::InputRange sgLinkInputRangeCh1(mscl::WirelessNodeConfig& config)
{
    mscl::LinearEquation lin;
    mscl::ChannelMask mask_ch1;
    mask_ch1.enable(1, true);

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
    case '1': 
    {
        lin.slope(2.9802e-7);
        lin.offset(2.5);
        config.linearEquation(mask_ch1, lin);
        
        return mscl::WirelessTypes::range_2_5V;
    }

    case '2':
    { 
        lin.slope(1.4901e-7);
        lin.offset(1.25);
        config.linearEquation(mask_ch1, lin);

        return mscl::WirelessTypes::range_1_25V;
    }
    
    case '3': 
    {
        lin.slope(7.4506e-8);
        lin.offset(0.625);
        config.linearEquation(mask_ch1, lin);
        
        return mscl::WirelessTypes::range_625mV;
    }

    case '4': 
    {
        lin.slope(3.7253e-8);
        lin.offset(0.3125);
        config.linearEquation(mask_ch1, lin);

        return mscl::WirelessTypes::range_312_5mV;
    }

    case '5': 
    {
        lin.slope(1.8626e-8);
        lin.offset(0.1563);
        config.linearEquation(mask_ch1, lin);

        return mscl::WirelessTypes::range_156_25mV;
    }
    
    case '6': 
    {
        lin.slope(9.3132e-9);
        lin.offset(7.8125e-2);
        config.linearEquation(mask_ch1, lin);

        return mscl::WirelessTypes::range_78_125mV;
    }

    case '7': 
    {
        lin.slope(4.6566e-9);
        lin.offset(3.9063e-2);
        config.linearEquation(mask_ch1, lin);

        return mscl::WirelessTypes::range_39_0625mV;
    }

    case '8': 
    {
        lin.slope(2.3283e-9);
        lin.offset(1.9531e-2);
        config.linearEquation(mask_ch1, lin);

        return mscl::WirelessTypes::range_19_5313mV;
    }
        
    default: return mscl::WirelessTypes::range_2_5V;
    }
}

mscl::WirelessTypes::InputRange sgLinkInputRangeCh2(mscl::WirelessNodeConfig& config)
{
    mscl::LinearEquation lin;
    mscl::ChannelMask mask_ch2;
    mask_ch2.enable(2, true);

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
    case '1':
    {
        lin.slope(1.4901e-7);
        config.linearEquation(mask_ch2, lin);

        return mscl::WirelessTypes::range_0to2_5V;
    }
    case '2':
    {
        lin.slope(7.4506e-8);
        config.linearEquation(mask_ch2, lin);

        return mscl::WirelessTypes::range_0to1_25V;
    }
    case '3':
    {
        lin.slope(3.7253e-8);
        config.linearEquation(mask_ch2, lin);

        return mscl::WirelessTypes::range_0to625mV;
    }
    case '4':
    {
        lin.slope(1.8626e-8);
        config.linearEquation(mask_ch2, lin);

        return mscl::WirelessTypes::range_0to312_5mV;
    }
    case '5':
    {
        lin.slope(9.3132e-9);
        config.linearEquation(mask_ch2, lin);

        return mscl::WirelessTypes::range_0to156_25mV;
    }
    case '6':
    {
        lin.slope(4.6566e-9);
        config.linearEquation(mask_ch2, lin);

        return mscl::WirelessTypes::range_0to78_125mV;
    }
    case '7':
    {
        lin.slope(2.3283e-9);
        config.linearEquation(mask_ch2, lin);

        return mscl::WirelessTypes::range_0to39_063mV;
    }
    case '8':
    {
        lin.slope(1.1642e-9);
        config.linearEquation(mask_ch2, lin);

        return mscl::WirelessTypes::range_0to19_532mV;
    }

    default: return mscl::WirelessTypes::range_0to2_5V;
    }
    
}

mscl::WirelessTypes::Filter sgLinkLPF(mscl::WirelessNodeConfig& config)
{
    unsigned char choice;

    // log and transmit
    std::cout << "\nLPF (ch1-ch2) options: " << std::endl;
    std::cout << "(1) 4416 HZ" << std::endl;
    std::cout << "(2) 1104 HZ" << std::endl;
    std::cout << "(3) 12.66 HZ" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::filter_4416hz;

    case '2':
    {
        config.sampleRate(mscl::WirelessTypes::sampleRate_256Hz); 
        return mscl::WirelessTypes::filter_1104hz;
    }
    case '3':
    {
        config.sampleRate(mscl::WirelessTypes::sampleRate_4Hz); 
        return mscl::WirelessTypes::filter_12_66hz;
    }
    default: return mscl::WirelessTypes::filter_4416hz;
    }
}

int8_t sgLinkDebounceFilter()
{
    std::string input;

    // log and transmit
    std::cout << "\nDebounce Filter (ch5-ch6) range 0-250ms ";
    
    while (true)
    {
        std::cout << "\nmillisecond(s): ";
        std::getline(std::cin, input);
        std::getline(std::cin, input);

        if (std::stoi(input) >= 0 && std::stoi(input) <= 250)
            return std::stoi(input);
        else
            std::cout << "Out of Range" << std::endl;
    }
}

bool sgLinkInternalPullUp()
{
    unsigned char choice;

    // log and transmit
    std::cout << "\nInternal Pull-up Resistor (ch5-ch6): " << std::endl;
    std::cout << "(1) on" << std::endl;
    std::cout << "(0) off" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return 1;
    case '0': return 0;

    default: return 1;
    }
}

void sgLinkHardwareConfig(mscl::BaseStation& base, mscl::WirelessNode& node)
{
    mscl::WirelessNodeConfig config; // try switching order 

    /////////////////////////////////////////////////  Input Range

    // SG-Link chanel 1 and channel 2 have their own unique input range set up so masks need to be configured accordigly 
    mscl::LinearEquation lin; 

    mscl::ChannelMask mask_ch1;
    mask_ch1.enable(1, true);
    config.inputRange(mask_ch1, sgLinkInputRangeCh1(config));
    config.linearEquation(mask_ch1, lin); 
    
    //mscl::ChannelMask mask_ch2;
    //mask_ch2.enable(2, true);
    //config.inputRange(mask_ch2, sgLinkInputRangeCh1(config));
    //config.linearEquation(mask_ch2, lin); 

    node.applyConfig(config);

    std::cout << "\nInput Range Configuration Applied!" << std::endl;

    /////////////////////////////////////////////////  Low Pass Filter

    mscl::ChannelMask lpf_mask;
    lpf_mask.enable(1, true);                                               // 4416Hz is agnostic     
    lpf_mask.enable(2, true);                                               // 1104Hz requires a sample rate of 256hz or less
                                                                        // 12.66Hz requires 4hz or less      
    config.lowPassFilter(lpf_mask, sgLinkLPF(config)); 

    node.applyConfig(config);

    std::cout << "\nLPF Configuration Applied!" << std::endl;

    /////////////////////////////////////////////////  Debounce Filter

    mscl::ChannelMask debounce_mask;

    debounce_mask.enable(5, true); 
    debounce_mask.enable(6, true); 

    config.debounceFilter(debounce_mask, sgLinkDebounceFilter()); 

    node.applyConfig(config);

    std::cout << "\n Debounce Filter Configuration Applied!" << std::endl;

    /////////////////////////////////////////////////  Internal Pull Up Resistor

    mscl::ChannelMask pullup_mask;

    pullup_mask.enable(5, true); 
    pullup_mask.enable(6, true); 

    config.pullUpResistor(pullup_mask, sgLinkInternalPullUp()); 

    node.applyConfig(config);

    std::cout << "\nInternal Pull-up Resistor Configuration Applied!" << std::endl;
}


