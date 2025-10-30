#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

uint16_t GLink200LostBeaconTimeout(mscl::WirelessNode& node)
{
    std::string input;

    // Diagnostic Info Interval (range 2 - 600) //////////////////////////////////////////////////////

    std::cout << "\nLost Beacon Timeout Input: (range 2 - 600 or 0 to turn off)" << std::endl;
    std::cout << "Current Config: " << node.getLostBeaconTimeout() << std::endl << std::endl; 
    std::cout << "Minutes: ";

    while (true)
    {
        std::getline(std::cin, input);

        if ((std::stoi(input) >= 2 && std::stoi(input) <= 600) || std::stoi(input) == 0)
            return std::stoi(input);
        else
            std::cout << "Out of Range.. Retry" << std::endl;
    }
}

uint16_t GLink200DiagnosticInterval(mscl::WirelessNode& node)
{
    std::string input;

    // Diagnostic Info Interval (range 10 - 64800) //////////////////////////////////////////////////////

    std::cout << "\nDiagnostic Info Interval Input: (range 10 - 64800)" << std::endl;
    std::cout << "Current Config: " << node.getDiagnosticInterval() << std::endl << std::endl; 
    std::cout << "Seconds: ";

    while (true)
    {
        std::getline(std::cin, input);

        if ((std::stoi(input) >= 10 && std::stoi(input) <= 64800))
            return std::stoi(input);
        else
            std::cout << "Out of Range.. Retry" << std::endl;
    }
}

mscl::WirelessTypes::StorageLimitMode GLink200StorageLimitMode(mscl::WirelessNode& node)
{
    unsigned char choice;
    // Storage Limit Mode  ///////////////////////////////////////////////////////////////////////////////
    std::cout << "\nStorage Limit Mode: " << std::endl;
    std::cout << "Current Config: " << node.getStorageLimitMode() << std::endl << std::endl; 
    std::cout << "(0) overwrite" << std::endl;
    std::cout << "(1) stop" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
        case '0': return mscl::WirelessTypes::storageLimit_overwrite;
        case '1': return mscl::WirelessTypes::storageLimit_stop;
        
        default: return mscl::WirelessTypes::storageLimit_overwrite;
    }
}

void GLink200SamplingConfigTab(mscl::WirelessNode& node) 
{
    mscl::WirelessNodeConfig config;

    // Lost Beacon Timeout
    config.lostBeaconTimeout(GLink200LostBeaconTimeout(node));

    // Diagnostic Info Interval 
    config.diagnosticInterval(GLink200DiagnosticInterval(node));

    // Storage Limit Mode
    config.storageLimitMode(GLink200StorageLimitMode(node));

    //apply config
    node.applyConfig(config);
    std::cout << "Configuration applied ! " << std::endl << std::endl;

    std::cout << "Lost Beacon Timeout: " << node.getLostBeaconTimeout() << std::endl;
    std::cout << "Diagnostic Info Interval: " << node.getDiagnosticInterval() << std::endl;
    std::cout << "Storage Limit Mode: " << node.getStorageLimitMode() << std::endl << std::endl;
}