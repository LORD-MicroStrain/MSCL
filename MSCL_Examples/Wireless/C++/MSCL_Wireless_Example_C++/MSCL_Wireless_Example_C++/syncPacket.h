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

void syncPacket(mscl::BaseStation& base, mscl::WirelessNode& node) 
{
    // Node should already be streaming 
    std::cout << "Collecting data..." << std::endl;

    for (int i = 0; i < 20; ++i)
    {
        mscl::DataSweeps sweeps = base.getData();

        for (const auto& sweep : sweeps)
        {   // Everything available in a sweep 
            std::cout << std::endl << "Timestamp: " << sweep.timestamp().str() << std::endl;
            std::cout << "Tick: " << sweep.tick() << std::endl;
            std::cout << "SampleRate: " << sweep.sampleRate().str() << std::endl;
            std::cout << "Node Address: " << sweep.nodeAddress() << std::endl;
            std::cout << "Sampling Mode: " << sweep.samplingType() << std::endl;
            std::cout << "Node RSSI: " << sweep.nodeRssi() << std::endl;
            std::cout << "Base RSSI: " << sweep.baseRssi() << std::endl;
            std::cout << "Frequency: " << sweep.frequency() << std::endl;
            std::cout << "Cals Applied: " << sweep.calApplied() << std::endl;
            std::cout << "Cals Applied: " << sweep.samplingType() << std::endl;

            if(sweep.samplingType() == 2)           // Packet Type Sync 
                for (const auto& dp : sweep.data())
                {
                    std::cout << "  " << dp.channelName()
                        << " = " << dp.as_float() << std::endl;
                }

            mscl::Utils::threadSleep(1000);
        }
    }
}