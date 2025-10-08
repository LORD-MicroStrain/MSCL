#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>

mscl::WirelessTypes::DataFormat setDataType(unsigned char choice) 
{
    switch(choice)
    {
        case '1':  return mscl::WirelessTypes::dataFormat_raw_int16; break;
        case '2':  return mscl::WirelessTypes::dataFormat_raw_int24; break;
        case '3':  return mscl::WirelessTypes::dataFormat_cal_float; break;

        default: return mscl::WirelessTypes::dataFormat_raw_int16;
    }
}

static void dataTypeSelect(mscl::WirelessNode& node)
{   // This example will use the accel channels on the GLink200
    
    mscl::WirelessNodeConfig config;  // WirelessNodeConfig object needed to configure data type
    mscl::WirelessTypes::DataFormat type; // WirelessSampleRate object will hold our chosen data type

    unsigned char choice; 
    std::cout << "Sample Rate Options: " << std::endl;
    std::cout << "(1) int 16" << std::endl;
    std::cout << "(2) int 24" << std::endl;
    std::cout << "(3) float" << std::endl;
    std::cout << "Choice: "; 
    std::cin >> choice;
    type = setDataType(choice);
    
    config.dataFormat(type);  // Update the config object with our selected data type
    node.applyConfig(config); // Once satified with configuration apply it to the node

    std::cout << "done." << std::endl; 
}
