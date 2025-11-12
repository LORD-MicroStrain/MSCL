
#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>


// This example toggles the WSDA200USB's communication protocol
mscl::WirelessTypes::Frequency frequencySelect()
{
    std::string input; 

    // log and transmit
    std::cout << "\nFrequency Options: " << std::endl;
    std::cout << "(11) frequency 11" << std::endl;
    std::cout << "(12) frequency 12" << std::endl;
    std::cout << "(13) frequency 13" << std::endl;
    std::cout << "(14) frequency 14" << std::endl;
    std::cout << "(15) frequency 15" << std::endl;
    std::cout << "(16) frequency 16" << std::endl;
    std::cout << "(17) frequency 17" << std::endl;
    std::cout << "(18) frequency 18" << std::endl;
    std::cout << "(19) frequency 19" << std::endl;
    std::cout << "(20) frequency 20" << std::endl;
    std::cout << "(21) frequency 21" << std::endl;
    std::cout << "(22) frequency 22" << std::endl;
    std::cout << "(23) frequency 23" << std::endl;
    std::cout << "(24) frequency 24" << std::endl;
    std::cout << "(25) frequency 25" << std::endl;
    std::cout << "(26) frequency 26" << std::endl;
    std::cout << "Choice: ";
    std::getline(std::cin, input);
    std::getline(std::cin, input);

    switch (std::stoi(input))
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


void manuallyAddNode(mscl::BaseStation& base) 
{
    std::string node_input; 

    std::cout << "Enter Node Address to Mannualy Add" << std::endl << "Address: ";
    std::getline(std::cin, node_input);

    unsigned char choice;
    std::cout << std::endl << "Search a..."; 
    std::cout << std::endl << "(1) Particular frequency"; 
    std::cout << std::endl << "(2) Scan All Frequencies"; 
    std::cout << std::endl << "Choice: "; 
    std::cin >> choice;


    auto initialFrequency = base.frequency(); 
    mscl::WirelessNode node(std::stoi(node_input), base); 

    if (choice == '1') // particular frequency
    {
        auto choiceFrequency = frequencySelect(); 
        base.changeFrequency(choiceFrequency); 

        auto ping = node.ping();

        if (ping.success())
        {
            std::cout << "Successfully Pinged";
            node.changeFrequency(initialFrequency); 
            std::cout << "\n\nNode changed to frequency: " << node.frequency() << std::endl;
        }
        else
        {
            std::cout << "Couldn't Find Node"; 
            base.changeFrequency(initialFrequency); 
            return; 
        }
        base.changeFrequency(initialFrequency); 
    }
    else if (choice == '2')
    {
        for (int k = 11; k < 26; k++)
        {
            std::cout << "\nPinging on Frequency: " << k << std::endl; 
            base.changeFrequency((mscl::WirelessTypes::Frequency)k); 
            
            auto ping = node.ping();

            if (ping.success())
            {
                std::cout << "Successfully Pinged";
                node.changeFrequency(initialFrequency); 
                std::cout << "\n\nNode changed to frequency: " << node.frequency() << std::endl;
                base.changeFrequency(initialFrequency); 
                return; 
            }
            else
            {
                std::cout << "Couldn't Find Node"; 
                base.changeFrequency(initialFrequency); 
            }
        }
    }
}