#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

mscl::WirelessTypes::TransmitPower baseTransmitPowerSelector(mscl::BaseStation& base)
{
    unsigned char choice;
    // Transmit Power  ///////////////////////////////////////////////////////////////////////////////
    std::cout << "\nTransmit Power Options: " << std::endl;
    std::cout << "Current Config: " << base.getTransmitPower() << std::endl << std::endl;
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

void baseTransmitPower(mscl::BaseStation& base)
{
    mscl::BaseStationConfig config;
   
    config.transmitPower(baseTransmitPowerSelector(base)); 

    //apply config to node 
    base.applyConfig(config);
    std::cout << "Configuration applied ! " << std::endl;
}