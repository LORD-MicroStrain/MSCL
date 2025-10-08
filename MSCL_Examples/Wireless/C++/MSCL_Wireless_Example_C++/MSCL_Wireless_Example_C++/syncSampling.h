#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "bandWidthAndStatus.h"

// lxrs or lxrs+
// lossless enable disable
// sync enable disable
// where should things like idle/sample on start up live? 

mscl::WirelessTypes::SamplingMode setSyncType(unsigned char choice)
{
    switch (choice)
    {
    case '1': return mscl::WirelessTypes::samplingMode_sync;
    case '2': return mscl::WirelessTypes::samplingMode_nonSync;

    default: return mscl::WirelessTypes::samplingMode_sync;
    }
}

mscl::WirelessTypes::CommProtocol setLxrsMode(unsigned char choice)
{
    switch (choice)
    {
    case '1': return mscl::WirelessTypes::commProtocol_lxrs;
    case '2': return mscl::WirelessTypes::commProtocol_lxrsPlus;

    default: return mscl::WirelessTypes::commProtocol_lxrs;
    }
}

bool setLosslessMode(unsigned char choice)
{
    switch (choice)
    {
    case '1': return 1;  // Sync
    case '2': return 0;  // Non Sync

    default: return 1;
    }
}

// This example shows how you can configure a synchronized network of nodes 
static void syncSampling(mscl::BaseStation& base, std::vector<mscl::WirelessNode> nodes)
{ 
    unsigned char choice;
    mscl::WirelessTypes::CommProtocol lxrsChoice;
    bool losslessChoice;
    printf("\nSetting up Stream configuration settings...\n");

    //lxrs
    std::cout << "LXRS Mode Options: " << std::endl;
    std::cout << "(1) LXRS" << std::endl;
    std::cout << "(2) LXRS+" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;
    lxrsChoice = setLxrsMode(choice);

    //lossless
    std::cout << "Lossless Options: " << std::endl;
    std::cout << "(1) Lossless" << std::endl;
    std::cout << "(2) Lossy" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;
    losslessChoice = setLosslessMode(choice);

    // SyncSamplingNetwork is the sampling network that we need to set up to stream a synchronized network
    mscl::SyncSamplingNetwork network(base);

    // basestation configuration object
    mscl::BaseStationConfig b_config;

    // Setting the network to lossless or lossy depending on User Input
    network.lossless(losslessChoice); 

    // Setting the network to lxrs or lxrs+ depending on User Input
    network.communicationProtocol(lxrsChoice);
    
    // Goes through a list of nodes and adds them to our SyncSamplingNetwork object
    
    for (mscl::WirelessNode& node : nodes)
    {   
        //create WirelessNodeConfig object to configure each node individually
        mscl::WirelessNodeConfig config;

        // set the sampling mode config for the node to sync sampling
        config.samplingMode(mscl::WirelessTypes::samplingMode_sync); 

        // Set basestation to comm protocol of the partiuclar node it is trying to communicate with 
        b_config.communicationProtocol(node.communicationProtocol()); 
        base.applyConfig(b_config); 

        // Setting every node to either LXRS or LXRS+ depending on User input
        config.communicationProtocol(lxrsChoice);

        // Add node to our SyncSamplingNetwork object
        node.applyConfig(config);
        network.addNode(node);
    }

    // After all nodes are set to particular comm protocol set the basestation's comm protocol 
    b_config.communicationProtocol(lxrsChoice);

    // Diagnostic print outs
    printf("Network info: \n");
    printf("Network OK: %s\n", network.ok() ? "TRUE" : "FALSE");
    printf("Percent of Bandwidth: %00.02f%%\n", network.percentBandwidth());
    printf("Lossless Enabled: %s\n", network.lossless() ? "TRUE" : "FALSE");
    // Apply the network configuration to every node in the network
    printf("Applying network and base configuration...");
    base.applyConfig(b_config); 
    network.applyConfiguration();
    printf("Done.\n");

    // Start all the nodes in the network sampling. The master BaseStation's beacon will be enabled with the system time.
    //  Note: if you wish to provide your own start time (not use the system time), pass a mscl::Timestamp object as a second parameter to this function.
    //  Note: if you do not want to enable a beacon at this time, use the startSampling_noBeacon() function. (The nodes will wait until they hear a beacon to start sampling).
    printf("Starting the network...");
    network.startSampling();
    printf("Done.\n");
}

/*
Xdr xdr(request);

  request XDR format

   unsigned int commProtocol;    //  mscl::WirelessTypes::CommProtocol
   bool updateTxPower
   unsigned int txPower          // mscl::WirelessTypes::TransmitPower

mscl::WirelessTypes::CommProtocol protocol = static_cast<mscl::WirelessTypes::CommProtocol>(xdr.readUint());
bool updateTxPower = xdr.readBool();
mscl::WirelessTypes::TransmitPower specifiedTxPower = static_cast<mscl::WirelessTypes::TransmitPower>(xdr.readUint());

mscl::BaseStationConfig config;
config.communicationProtocol(protocol);


// get the region and tx power currently set on the device
const mscl::WirelessTypes::RegionCode region = m_msclBaseStationPtr->regionCode();
mscl::WirelessTypes::TransmitPower currentTxPower = m_msclBaseStationPtr->getTransmitPower();

const mscl::WirelessTypes::TransmitPower maxTxPower = m_msclBaseStationPtr->features().maxTransmitPower(region, protocol);
const mscl::WirelessTypes::TransmitPower minTxPower = m_msclBaseStationPtr->features().minTransmitPower(region, protocol);
const mscl::WirelessTypes::TransmitPowers& txPowers = m_msclBaseStationPtr->features().transmitPowers(protocol);

//adjust the transmit power to be within range for the new comm protocol
mscl::WirelessTypes::TransmitPower newTxPower = updateTxPower
? Backend::getValidTxPower(txPowers, maxTxPower, minTxPower, specifiedTxPower)
    : Backend::getValidTxPower(txPowers, maxTxPower, minTxPower, currentTxPower);
config.transmitPower(newTxPower);

bool success = false;
uint8_t retries = 0;
while (!success)
{
    try
    {
        m_msclBaseStationPtr->applyConfig(config);
        success = true;
    }
    catch (mscl::Error_Communication& e)
    {
        retries++;
        if (retries >= 2)
        {
            throw e;
        }
    }


}



  response XDR format

   unsigned int commProtocol;    //  mscl::WirelessTypes::CommProtocol
   bool  txPowerChanged;
   unsigned int previousTxPower; // mscl::WirelessTypes::TransmitPower
   unsigned int newTxPower;      // mscl::WirelessTypes::TransmitPower

responseBody.writeUint(protocol);
responseBody.writeBool(newTxPower != currentTxPower);
responseBody.writeUint(currentTxPower);
responseBody.writeUint(newTxPower);
*/
