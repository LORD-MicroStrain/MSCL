#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>

void idleAndPing(mscl::WirelessNode& node); 

void printChannels(mscl::WirelessNode& node); 

bool checkConfig(mscl::WirelessNode& node, mscl::WirelessNodeConfig& config); 
