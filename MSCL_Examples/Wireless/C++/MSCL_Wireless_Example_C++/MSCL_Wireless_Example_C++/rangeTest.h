#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

void rangeTest(mscl::BaseStation& base, mscl::WirelessNode& node)
{
    const mscl::PingResponse response = node.ping();

    int16_t pings = 0; 
    int16_t fails = 0; 

    int32_t node_sum = 0; 
    int32_t base_sum = 0; 

    std::cout << "Range test of 1000 Pings" << std::endl; 

    while (pings + fails < 1000)
    {
        if (response.success())
        {
            node_sum += response.baseRssi(); 
            base_sum += response.nodeRssi(); 
            pings++;
        }
        else
        {
            fails++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        std::cout << "."; 
    }

    std::cout << "\nBase RSSI Average: " << base_sum/1000 << std::endl; 
    std::cout << "Node RSSI Average: " << node_sum/1000 << std::endl; 
    std::cout << "Pings: " << pings << std::endl; 
    std::cout << "Fails: " << fails << std::endl; 
}