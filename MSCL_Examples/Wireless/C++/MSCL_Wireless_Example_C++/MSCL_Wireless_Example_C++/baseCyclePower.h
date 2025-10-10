#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

void baseCyclePower(mscl::BaseStation& base)
{
    try
    {   // Send the reboot command
        std::cout << "Power Cycling BaseStation" << std::endl;
        base.cyclePower();  
        std::cout << "BaseStation reset command sent successfully." << std::endl;
    }
    catch (const mscl::Error& e)
    {
        std::cerr << "MSCL Error: " << e.what() << std::endl;
    }
}