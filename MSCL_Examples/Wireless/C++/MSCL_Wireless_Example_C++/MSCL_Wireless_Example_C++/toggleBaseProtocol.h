
#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

// This example toggles the WSDA200USB's communication protocol

void toggleBaseProtocol(mscl::BaseStation& base) 
{
    mscl::BaseStationConfig b_config;

    if (base.communicationProtocol() == mscl::WirelessTypes::commProtocol_lxrs)
        b_config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrsPlus); 
    else
        b_config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrs); 

    std::cout << "Base Communication Protocol changed to: " << base.communicationProtocol() << std::endl; 

    std::cout <<
        "commProtocol_lxrs = 0,\n"
        "commProtocol_lxrsPlus = 1"
    << std::endl; 

    base.applyConfig(b_config);
}