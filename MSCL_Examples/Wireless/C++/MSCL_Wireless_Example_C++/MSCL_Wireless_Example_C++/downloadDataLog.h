#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/DatalogDownloader.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

void downloadDataLog(mscl::WirelessNode& node)
{
    mscl::DatalogDownloader downloader(node); 

    while (!downloader.complete())
    {
        // Download the next data packet
        mscl::LoggedDataSweep sweep; 

        try 
        {
            sweep = downloader.getNextData();
        }
        catch (const mscl::Error_NodeCommunication& e){}

        // Print out the data
        std::cout << "Timestamp: " << sweep.timestamp().str() << std::endl;
        std::cout << "Channel Data: " << std::endl;
        for (const auto& dataPoint : sweep.data())
        {
            std::cout << "  " << dataPoint.channelName()
                << " = " << dataPoint.as_string() << std::endl;
        }

        // Show progress
        std::cout << "Progress: " << downloader.percentComplete() << "%\n";
    }

    std::cout << "Download complete." << std::endl;
}

