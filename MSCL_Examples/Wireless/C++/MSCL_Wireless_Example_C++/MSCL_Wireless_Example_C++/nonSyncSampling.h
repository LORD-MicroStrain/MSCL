#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

mscl::WirelessTypes::CommProtocol setLxrsMode_(unsigned char choice) 
{
    switch (choice)
    {
    case '1': return mscl::WirelessTypes::commProtocol_lxrs;  
    case '2': return mscl::WirelessTypes::commProtocol_lxrsPlus;  

    default: return mscl::WirelessTypes::commProtocol_lxrs;
    }
}

mscl::WirelessTypes::DataCollectionMethod setLogAndTransmit_(unsigned char choice)
{
    switch (choice)
    {
    case '1': return mscl::WirelessTypes::DataCollectionMethod::collectionMethod_logAndTransmit;
    case '2': return mscl::WirelessTypes::DataCollectionMethod::collectionMethod_transmitOnly;
    case '3': return mscl::WirelessTypes::DataCollectionMethod::collectionMethod_logOnly;

    default: return mscl::WirelessTypes::DataCollectionMethod::collectionMethod_logAndTransmit;
    }
}
// This example shows how you can set up a node 
static void nonSyncSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode>& nodes)
{
    unsigned char choice; 
    mscl::WirelessTypes::DataCollectionMethod logAndTransmitChoice;
    mscl::WirelessTypes::CommProtocol lxrsChoice; 

    printf("\nSetting up Stream configuration settings...");
    //lxrs
    std::cout << "LXRS Mode Options: " << std::endl;
    std::cout << "(1) LXRS" << std::endl;
    std::cout << "(2) LXRS+" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice; 
    lxrsChoice = setLxrsMode_(choice); 

    // log and transmit
    std::cout << "Log and Transmit Options: " << std::endl;
    std::cout << "(1) Log and Transmit" << std::endl;
    std::cout << "(2) Transmit" << std::endl;
    std::cout << "(2) Log" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;
    logAndTransmitChoice = setLogAndTransmit_(choice);

    // basestaion config object used to switch basestation comm protocol 
    mscl::BaseStationConfig b_config; 

    for (mscl::WirelessNode& node : nodes)
    {   // Goes through a list of nodes and adds them to our SyncSamplingNetwork object

        //create WirelessNodeConfig object to configure each node individually 
        mscl::WirelessNodeConfig config;

        // set the sampling mode to sync
        config.samplingMode(mscl::WirelessTypes::samplingMode_nonSync); 

        // apply log/transmit setting
        config.dataCollectionMethod(logAndTransmitChoice); 

        // switch protocol to choice based on user input
        switchNodeProtocol(node, base, lxrsChoice); 

        // apply our configuration to node
        node.applyConfig(config); 
    } 
    
    // now set basestaion to comm protocol based on user input
    b_config.communicationProtocol(lxrsChoice); 
    base.applyConfig(b_config); 

    // loop through node list and set to sample
    for (mscl::WirelessNode& node : nodes)
    {
        node.startNonSyncSampling();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    printf("Done.");
}
