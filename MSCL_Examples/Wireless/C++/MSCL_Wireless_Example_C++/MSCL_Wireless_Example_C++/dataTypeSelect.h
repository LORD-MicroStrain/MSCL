#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>

mscl::WirelessTypes::WirelessSampleRate setSampleRate(unsigned char choice) 
{
    switch(choice)
    {
        case '1':  return mscl::WirelessTypes::sampleRate_1Hz; break;
        case '2':  return mscl::WirelessTypes::sampleRate_16Hz; break;
        case '3':  return mscl::WirelessTypes::sampleRate_64Hz; break;
        case '4':  return mscl::WirelessTypes::sampleRate_256Hz; break;
        case '5':  return mscl::WirelessTypes::sampleRate_512Hz; break;
        case '6':  return mscl::WirelessTypes::sampleRate_1024Hz; break;
        case '7':  return mscl::WirelessTypes::sampleRate_2048Hz; break;
        case '8':  return mscl::WirelessTypes::sampleRate_4096Hz; break;

        default: return mscl::WirelessTypes::sampleRate_1Hz; 
    }
}

static void dataTypeSelect(mscl::WirelessNode& node)
{   // This example will use the accel channels on the GLink200
    
    mscl::WirelessNodeConfig config;  // WirelessNodeConfig object needed to configure node sample rate
    mscl::WirelessTypes::WirelessSampleRate rate; // WirelessSampleRate object will hold our chosen sample rate 

    unsigned char choice; 
    std::cout << "Sample Rate Options: " << std::endl;
    std::cout << "(1) 1 Hz" << std::endl;
    std::cout << "(2) 16 Hz" << std::endl;
    std::cout << "(3) 64 Hz" << std::endl;
    std::cout << "(4) 256 Hz" << std::endl;
    std::cout << "(5) 512 Hz" << std::endl;
    std::cout << "(6) 1024 Hz" << std::endl;
    std::cout << "(7) 2048 Hz" << std::endl;
    std::cout << "(8) 4096 Hz" << std::endl;
    std::cout << "Choice: "; 
    std::cin >> choice;
    rate = setSampleRate(choice);
    
    config.sampleRate(rate);  // Update the config object with our selected sample rate
    node.applyConfig(config); // Once satified with configuration apply it to the node

    std::cout << "done." << std::endl; 
}
