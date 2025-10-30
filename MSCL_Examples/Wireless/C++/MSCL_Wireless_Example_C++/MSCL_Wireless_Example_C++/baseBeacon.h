#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

bool baseBeaconSelector(mscl::BaseStation& base)
{
    unsigned char choice;
    // Transmit Power  ///////////////////////////////////////////////////////////////////////////////
    std::cout << "\nBeacon Setting: " << std::endl;
    std::cout << "Current Config: " << base.beaconStatus().enabled() << std::endl << std::endl;
    std::cout << "(0) off" << std::endl;
    std::cout << "(1) on" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
        case '0': return 0;
        case '1': return 1;

        default: return 0;
    }
}

void baseBeacon(mscl::BaseStation& base)
{
    mscl::BaseStationConfig config;
   
    if (baseBeaconSelector(base))
    {
        base.enableBeacon();
        std::cout << "(1) beacon enabled" << std::endl;
    }
    else
    {
        base.disableBeacon();
        std::cout << "(0) beacon disabled" << std::endl;
    }
}