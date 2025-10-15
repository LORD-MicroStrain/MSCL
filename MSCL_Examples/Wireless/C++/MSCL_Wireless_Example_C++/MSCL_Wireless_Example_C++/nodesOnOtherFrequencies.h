#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

void nodesOnOtherFrequencies(mscl::BaseStation& base_station)
{
    base_station.getNodeDiscoveries();
    printf("Discovering nodes...\n");
    printf("Press enter to continue...");
    getchar();
    mscl::NodeDiscoveries discoveries = base_station.getNodeDiscoveries();

    // printing out all nodes discovered and attributes including node address 
    if (discoveries.size() == 0)
    {
        std::cout << "No nodes discovered." << std::endl;
        return; 
    }
    else
        for (const mscl::NodeDiscovery& nodes_discovered : discoveries)
        {
            std::cout << std::endl << "Node:" << std::endl; 
            std::cout << "Node Address: " << nodes_discovered.nodeAddress() << std::endl;
            std::cout << "Model: " << nodes_discovered.model() << std::endl;
            std::cout << "Serial: " << nodes_discovered.serialNumber() << std::endl;
            std::cout << "Base Station RSSI: " << nodes_discovered.baseRssi() << " dBm" << std::endl;
            std::cout << "Frequency: " << nodes_discovered.frequency() << std::endl;
        }

    // User Chooses a node, on another frequency, by its node address to be switched over the the basestations frequency  
    printf("\nChoose node: ");
    std::string choice; 
    std::getline(std::cin, choice);

    // grab the frquency of the node address from user input
    // grabbing frequency data type-- mscl::WirelessTypes::Frequency
    mscl::WirelessTypes::Frequency nodeFrequency; 
    mscl::WirelessTypes::Frequency baseFrequency = base_station.frequency(); 
    for (const mscl::NodeDiscovery& nodes_discovered : discoveries)
        if (std::to_string((nodes_discovered.nodeAddress())) == choice) 
            nodeFrequency = nodes_discovered.frequency();  

    // 1. The basestations's frequency needs to be switched to the frequency of the node it wants the communicate with 
    // 2. Switch the nodes frequency to the frequency the basestation started with. 
    // 3. Set the basestations frequency to what it started with  
// step 1
    std::cout << "\nChanging Base Channel to: " << nodeFrequency << std::endl;
    base_station.changeFrequency(nodeFrequency);
// step 2
    std::cout << "Changing Node Channel to: " << baseFrequency << std::endl;
    mscl::WirelessNode node(std::stoi(choice), base_station);
    node.changeFrequency(baseFrequency); 
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
// step 3
    std::cout << "Changing Base Channel back to: " << baseFrequency << std::endl;
    base_station.changeFrequency(baseFrequency); 
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::cout << "\nBaseStation Frequency: " << base_station.frequency() << std::endl; 
    std::cout << "Node Frequency: " << node.frequency() << std::endl; 
}
