#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

// example to switch a nodes protocol  (lxrs/lxrs+)
void switchNodeProtocol(mscl::WirelessNode& node, mscl::BaseStation& base, mscl::WirelessTypes::CommProtocol& protocol)
{
    mscl::WirelessNodeConfig config; 
    mscl::BaseStationConfig b_config; 

    // set to lxrs as a starting point
    b_config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrs);
    base.applyConfig(b_config); 

    // ping node to see if its operating in lxrs mode 
    // if its not switch basestation to lxrs+ 
    mscl::PingResponse response = node.ping();
    if (!response.success())
    {  
        b_config.communicationProtocol(mscl::WirelessTypes::commProtocol_lxrsPlus);
        base.applyConfig(b_config);
    }

    // if the new protocol is able to be communicated with safely go ahead and apply those changes 
    if (node.testCommunicationProtocol(protocol))
    {
        config.communicationProtocol(protocol);
        node.applyConfig(config);
    } 
    else
    {
        printf("Unable to switch node protocol... \n\nPress Enter to Continue or Exit the Program to Restart...");
        getchar();
    }
    
    b_config.communicationProtocol(protocol); 
    base.applyConfig(b_config);
}
