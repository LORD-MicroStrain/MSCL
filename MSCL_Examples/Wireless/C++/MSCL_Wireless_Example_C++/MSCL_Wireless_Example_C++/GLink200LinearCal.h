#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

// Slopes
// 
// (ch1-ch3)
// feet/seconds2   -1.2639e-4
// g               -3.9284e-6  
// milli-g         -3.9284e-3 
// meters/second2  -3.8524e-5 
// 
// (ch4-ch5)
// degrees          1.0000e-2 
// radians          1.7453e-4

float ch123LinearCal() 
{
    unsigned char choice;

    std::cout << "\nLinear Cal Options: " << std::endl;
    std::cout << "(1) feet/second squared" << std::endl;
    std::cout << "(2) g" << std::endl;
    std::cout << "(3) milli-g" << std::endl;
    std::cout << "(4) meters/second squared" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return -1.2639e-4;
    case '2': return -3.9284e-6;
    case '3': return -3.9284e-3;
    case '4': return -3.8524e-5;

    default: return -1.2639e-4;
    }
}

float ch45LinearCal() 
{
    unsigned char choice;

    std::cout << "\nLinaer Cal Options: " << std::endl;
    std::cout << "(1) degrees" << std::endl;
    std::cout << "(2) radians" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return 1.0000e-2;
    case '2': return 1.7453e-4;

    default: return 1.0000e-2;
    }
}

void GLink200LinearCal(mscl::WirelessNode& node)
{
    mscl::WirelessNodeConfig config;
    mscl::LinearEquation lin; 

    if (node.getSensorOutputMode() == mscl::WirelessTypes::sensorOutputMode_accel)
    {                                    // if accel enabled 
        std::cout << "\nSetting Accel Channels" << std::endl << std::endl;

        std::cout << "\nCh1 ";
        mscl::ChannelMask mask_ch1; 
        mask_ch1.enable(1, true); 
        lin.slope(ch123LinearCal());
        config.linearEquation(mask_ch1, lin); 

        std::cout << "\nCh2: "; 
        mscl::ChannelMask mask_ch2; 
        mask_ch2.enable(2, true); 
        lin.slope(ch123LinearCal());
        config.linearEquation(mask_ch2, lin); 

        std::cout << "\nCh3: "; 
        mscl::ChannelMask mask_ch3; 
        mask_ch3.enable(3, true); 
        lin.slope(ch123LinearCal());
        config.linearEquation(mask_ch3, lin); 
    }
    else                                 // if tilt enabled 
    {
        std::cout << "\nSetting Accel Channels" << std::endl << std::endl;

        std::cout << "\nCh4: "; 
        mscl::ChannelMask mask_ch4; 
        mask_ch4.enable(4, true); 
        lin.slope(ch45LinearCal());
        config.linearEquation(mask_ch4, lin); 


        std::cout << "\nCh5: ";
        mscl::ChannelMask mask_ch5; 
        mask_ch5.enable(5, true); 
        lin.slope(ch45LinearCal());
        config.linearEquation(mask_ch5, lin); 
    }
    
    //apply config
    node.applyConfig(config);
    std::cout << "\nLinear Cal applied ! " << std::endl << std::endl;
}