#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <mscl/MicroStrain/Wireless/ArmedDataloggingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>


#include "bandWidthAndStatus.cpp"
#include "switchNodeProtocol.cpp"

mscl::WirelessTypes::WirelessSampleRate setSampleRate() 
{
    unsigned char choice;
    // log and transmit
    std::cout << "Log and Transmit Options: " << std::endl;
    std::cout << "(0) 1Hz" << std::endl;
    std::cout << "(1) 4Hz" << std::endl;
    std::cout << "(2) 8Hz" << std::endl;
    std::cout << "(3) 16Hz" << std::endl;
    std::cout << "(4) 64Hz" << std::endl;
    std::cout << "(5) 256Hz" << std::endl;
    std::cout << "(6) 512Hz" << std::endl;
    std::cout << "(7) 1024Hz" << std::endl;
    std::cout << "(8) 2048Hz" << std::endl;
    std::cout << "(9) 4096Hz" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '0': return mscl::WirelessTypes::sampleRate_1Hz;
    case '1': return mscl::WirelessTypes::sampleRate_4Hz;
    case '2': return mscl::WirelessTypes::sampleRate_8Hz;
    case '3': return mscl::WirelessTypes::sampleRate_16Hz;
    case '4': return mscl::WirelessTypes::sampleRate_64Hz;
    case '5': return mscl::WirelessTypes::sampleRate_256Hz;
    case '6': return mscl::WirelessTypes::sampleRate_512Hz;
    case '7': return mscl::WirelessTypes::sampleRate_1024Hz;
    case '8': return mscl::WirelessTypes::sampleRate_2048Hz;
    case '9': return mscl::WirelessTypes::sampleRate_4096Hz;

    default: return mscl::WirelessTypes::sampleRate_1Hz;
    }
}

mscl::WirelessTypes::CommProtocol setLxrsMode()
{
    unsigned char choice; 
    // lxrs
    std::cout << "LXRS Mode Options: " << std::endl;
    std::cout << "(1) LXRS" << std::endl;
    std::cout << "(2) LXRS+" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::commProtocol_lxrs;
    case '2': return mscl::WirelessTypes::commProtocol_lxrsPlus;

    default: return mscl::WirelessTypes::commProtocol_lxrs;
    }
}

mscl::WirelessTypes::DataCollectionMethod setLogAndTransmit()
{
    unsigned char choice; 
    // log and transmit
    std::cout << "Log and Transmit Options: " << std::endl;
    std::cout << "(1) Log and Transmit" << std::endl;
    std::cout << "(2) Transmit" << std::endl;
    std::cout << "(3) Log" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return mscl::WirelessTypes::DataCollectionMethod::collectionMethod_logAndTransmit;
    case '2': return mscl::WirelessTypes::DataCollectionMethod::collectionMethod_transmitOnly;
    case '3': return mscl::WirelessTypes::DataCollectionMethod::collectionMethod_logOnly;
    
    default: return mscl::WirelessTypes::DataCollectionMethod::collectionMethod_logAndTransmit;
    }
}

bool setLosslessMode()
{
    unsigned char choice; 

     // lossless
    std::cout << "Lossless Options: " << std::endl;
    std::cout << "(1) Lossless" << std::endl;
    std::cout << "(2) Lossy" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return 1;  // Sync
    case '2': return 0;  // Non Sync

    default: return 1;
    }
}

bool syncOrArmed()
{
    unsigned char choice;

    // lossless
    std::cout << "Synced or Armed: " << std::endl;
    std::cout << "(1) Sync" << std::endl;
    std::cout << "(2) Armed" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case '1': return 1;  // Sync
    case '2': return 0;  // Armed

    default: return 1;
    }
}

// This example shows how you can configure a synchronized network of nodes 
static void syncSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode> nodes)
{
    printf("\nSetting up Stream configuration settings...\n");

    // SyncSamplingNetwork is the sampling network that we need to set up to stream a synchronized network
    mscl::SyncSamplingNetwork sync_network(base);

    mscl::ArmedDataloggingNetwork armed_network(base);

    auto protocol = setLxrsMode(); 

    if (syncOrArmed())
    {
        // Setting the network to lossless or lossy depending on User Input
        sync_network.lossless(setLosslessMode());

        // Setting the network to lxrs or lxrs+ depending on User Input
        sync_network.communicationProtocol(protocol);

        // Goes through a list of nodes and adds them to our SyncSamplingNetwork object

        for (mscl::WirelessNode& node : nodes)
        {
            std::cout << "\n\nConfig for Node: " << node.nodeAddress() << "\n\n";

            // create WirelessNodeConfig object to configure each node individually
            mscl::WirelessNodeConfig config;

            // set the sampling mode config for the node to sync sampling
            config.samplingMode(mscl::WirelessTypes::samplingMode_sync);

            // switch protocol to choice based on user input
            switchNodeProtocol(node, base, protocol);

            // apply log/transmit setting
            config.dataCollectionMethod(setLogAndTransmit());

            //  ADD SAMPLE RATE CONFIGURATION HERE
            config.sampleRate(setSampleRate());

            // apply our configuration to node
            node.applyConfig(config);

            // Add node to our SyncSamplingNetwork object
            sync_network.addNode(node);
        }

        // basestation configuration object
        mscl::BaseStationConfig b_config;
        // After all nodes are set to particular comm protocol set the basestation's comm protocol 
        b_config.communicationProtocol(protocol);

        // data print out of configuration validity 
        bandWidthAndStatus(sync_network);

        // Apply the network configuration to every node in the network
        printf("Applying network and base configuration...");
        base.applyConfig(b_config);
        sync_network.applyConfiguration(); //   AN APPLY ONLY EXAMPLE WOULD STOP HERE

        printf("Done.\n");

        // Start all the nodes in the network sampling. The master BaseStation's beacon will be enabled with the system time.
        //  Note: if you wish to provide your own start time (not use the system time), pass a mscl::Timestamp object as a second parameter to this function.
        //  Note: if you do not want to enable a beacon at this time, use the startSampling_noBeacon() function. (The nodes will wait until they hear a beacon to start sampling).
        printf("Starting the Synchronized network...");
        sync_network.startSampling();
        printf("Done.\n");
    }
    else
    {
        for (mscl::WirelessNode& node : nodes)
        {
            // create WirelessNodeConfig object to configure each node individually
            mscl::WirelessNodeConfig config;

            // set the sampling mode config for the node to sync sampling
            config.samplingMode(mscl::WirelessTypes::samplingMode_armedDatalog);

            // switch protocol to choice based on user input
            switchNodeProtocol(node, base, protocol);

            // apply log/transmit setting
            config.dataCollectionMethod(setLogAndTransmit());

            //  ADD SAMPLE RATE CONFIGURATION HERE
            config.sampleRate(setSampleRate());

            // apply our configuration to node
            node.applyConfig(config);

            // Add node to our SyncSamplingNetwork object
            armed_network.addNode(node);
        }

        // basestation configuration object
        mscl::BaseStationConfig b_config;
        // After all nodes are set to particular comm protocol set the basestation's comm protocol 
        b_config.communicationProtocol(protocol);
        // Apply the network configuration to every node in the network
        printf("Applying network and base configuration...");
        base.applyConfig(b_config);

        printf("Applying Armed network...");
        armed_network.startSampling();
        printf("Done.\n");
    }
}
