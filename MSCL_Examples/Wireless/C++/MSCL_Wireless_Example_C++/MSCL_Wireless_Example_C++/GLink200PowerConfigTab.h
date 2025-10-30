#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

mscl::WirelessTypes::DefaultMode GLink200DefaultMode(mscl::WirelessNode& node)
{
    // Default Operation Mode ////////////////////////////////////////////////////////////////////////
    unsigned char choice;
    std::cout << "\nDefault Operation Mode: " << std::endl;
    std::cout << "Current Config: " << node.getDefaultMode() << std::endl << std::endl; 
    std::cout << "(0) Idle" << std::endl;
    std::cout << "(5) Sleep" << std::endl;
    std::cout << "(6) Sample" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
        case '0': return mscl::WirelessTypes::defaultMode_idle;
        case '5': return mscl::WirelessTypes::defaultMode_sleep;
        case '6': return mscl::WirelessTypes::defaultMode_sync;
            
        default: return mscl::WirelessTypes::defaultMode_idle;
    }
}

mscl::WirelessTypes::TransmitPower GLink200TransmitPower(mscl::WirelessNode& node)
{
    unsigned char choice; 
    // Transmit Power  ///////////////////////////////////////////////////////////////////////////////
    std::cout << "\nTransmit Power Options: " << std::endl;
    std::cout << "Current Config: " << node.getTransmitPower() << std::endl << std::endl; 
    std::cout << "(1) 0dBm" << std::endl;
    std::cout << "(2) 5dBm" << std::endl;
    std::cout << "(3) 10dBm" << std::endl;
    std::cout << "(4) 16dBm" << std::endl;
    std::cout << "(5) 20dBm" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::power_0dBm;
    case '2': return mscl::WirelessTypes::power_5dBm;
    case '3': return mscl::WirelessTypes::power_10dBm;
    case '4': return mscl::WirelessTypes::power_16dBm;
    case '5': return mscl::WirelessTypes::power_20dBm;

    default: return mscl::WirelessTypes::power_16dBm;
    }
}

int userInactivityTimeOutInput(mscl::WirelessNode& node)
{
    std::string input; 

    // User Inactivity Input (range 30 - 65534) //////////////////////////////////////////////////////
    std::cout << "\nUser Inactivity input: (range 30 - 65534 or 0 to turn off)" << std::endl;
    std::cout << "Current Config: " << node.getInactivityTimeout() << std::endl << std::endl; 
    std::cout << "Seconds: ";

    while (true)
    {
        std::getline(std::cin, input);
        std::getline(std::cin, input);

        if ((std::stoi(input) >= 30 && std::stoi(input) <= 65533) || std::stoi(input) == 0)
            return std::stoi(input);
        else
            std::cout << "Out of Range" << std::endl;
    }
}

int8_t checkRadioIntervalInput(mscl::WirelessNode& node)
{
    std::string input; 
       
    // Check Radio Interval (range 1-60) ////////////////////////////////////////////////////////////
    std::cout << "\nCheck Radio Interval Input: (range 1-60)" << std::endl;
    std::cout << "Current Config: " << node.getCheckRadioInterval() << std::endl; 

    while (true)
    {
        std::cout << "Seconds: ";
        std::getline(std::cin, input);

        if (std::stoi(input) > 1 && std::stoi(input) <= 60)
            return std::stoi(input);
        else
            std::cout << "Out of Range" << std::endl;
    }
}

void GLink200PowerConfigTab(mscl::WirelessNode& node)
{
    mscl::WirelessNodeConfig config;

    // Default Operation Mode 
    config.defaultMode(GLink200DefaultMode(node));

    // User Inactivity Timeout
    config.inactivityTimeout(userInactivityTimeOutInput(node)); 

    // Check Radio Interval 
    config.checkRadioInterval(checkRadioIntervalInput(node)); 

    // Transmit Power
    config.transmitPower(GLink200TransmitPower(node)); 

    //apply config
    node.applyConfig(config);
    std::cout << "Configuration applied ! " << std::endl;

    std::cout << "Default Mode setting: " << node.getDefaultMode() << std::endl; 
    std::cout << "User Inactivity Timeout Setting: " << node.getInactivityTimeout() << std::endl; 
    std::cout << "Check Radio Interval Settting: " << node.getCheckRadioInterval() << std::endl; 
    std::cout << "Transmit Power setting: " << node.getTransmitPower() << "dBm" << std::endl << std::endl;

    /*enum DefaultMode
    {
        defaultMode_idle = 0,
        defaultMode_ldc = 1,
        defaultMode_datalog = 4,
        defaultMode_sleep = 5,
        defaultMode_sync = 6
    }*/
}