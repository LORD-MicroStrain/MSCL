#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

mscl::WirelessTypes::Frequency selectFrequency(int choice)
{
    switch (choice)
    {
        case 11: return mscl::WirelessTypes::freq_11;
        case 12: return mscl::WirelessTypes::freq_12;
        case 13: return mscl::WirelessTypes::freq_13;
        case 14: return mscl::WirelessTypes::freq_14;
        case 15: return mscl::WirelessTypes::freq_15;
        case 16: return mscl::WirelessTypes::freq_16;
        case 17: return mscl::WirelessTypes::freq_17;
        case 18: return mscl::WirelessTypes::freq_18;
        case 19: return mscl::WirelessTypes::freq_19;
        case 20: return mscl::WirelessTypes::freq_20;
        case 21: return mscl::WirelessTypes::freq_21;
        case 22: return mscl::WirelessTypes::freq_22;
        case 23: return mscl::WirelessTypes::freq_23;
        case 24: return mscl::WirelessTypes::freq_24;
        case 25: return mscl::WirelessTypes::freq_25;
        case 26: return mscl::WirelessTypes::freq_26;

        default: return mscl::WirelessTypes::freq_11;
    }
}

// This example shows how you can configure a synchronized network of nodes 
void changeBaseStationFrequency(mscl::BaseStation& base) 
{
    std::string choice; 
    mscl::WirelessTypes::Frequency selectedFrequency; 

    // print out current rf channel
    mscl::WirelessTypes::Frequency currentFrequency = base.frequency();
    std::cout << "Current RF Channel: " << currentFrequency << std::endl << std::endl;

    // user input to select frequency to switch base to 
    std::cout << "Choose Frequency to switch to (Ch. 11 - Ch. 26)" << std::endl; 
    std::cout << "Channel: "; 
    std::getline(std::cin, choice); 
    selectedFrequency = selectFrequency(std::stoi(choice)); 

    // Set a new RF channel
    std::cout << "Changing RF Channel to: " << selectedFrequency << std::endl;
    base.changeFrequency(selectedFrequency);

    // Confirm the change
    mscl::WirelessTypes::Frequency confirmedChannel = base.frequency();
    std::cout << "New RF Channel: " << confirmedChannel << std::endl;
}