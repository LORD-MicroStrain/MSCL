#include "enableDisableBeacon.h"
#include "getCurrentConfig.h"
#include "parseData.h"
#include "pingNode.h"
#include "setCurrentConfig.h"
#include "setToIdle.h"
#include "startSyncSampling.h"
/////////////////////////////////////

#include "nodeDiscovery.h"
#include "supportedSampleRates.h"
#include "enableChannelsGLink200_accel.h"
#include "enableChannelsGLink200_tilt.h"

#include "syncSampling.h"
#include "nonSyncSampling.h"

#include "dataTypeSelect.h"

#include "changeBaseStationFrequency.h"

//#include "bandWidthAndStatus.cpp"

#include "nodeCyclePower.h"
#include "baseCyclePower.h"
#include "nodeSleep.h"
#include "baseTransmitPower.h"
#include "baseBeacon.h"
#include "nodesOnOtherFrequencies.h"

#include "switchBaseProtocol.h"

#include "nodeFirmwareUpgrade.h"
#include "baseFirmwareUpgrade.h"

#include "rangeTest.h"

#include "GLink200InputRange.h"
#include "GLink200LPF.h"
#include "GLink200HPF.h"
#include "GLink200LinearCal.h"
#include "GLink200SamplingConfigTab.h"
#include "GLink200PowerConfigTab.h"

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>
#include <mscl/MicroStrain/Wireless/BaseStation.h>
#include <mscl/MicroStrain/Wireless/WirelessNode.h>

int main(int argc, char** argv)
{
    // TODO: Change these constants to match your setup
#ifdef _WIN32
    static constexpr const char* COM_PORT = "COM10";
#elif __linux__
    static constexpr const char* COM_PORT = "/dev/tty/ACM0";
#endif // _WIN32

    // Basestations use a baudrate of 3000000
    static constexpr uint32_t BAUDRATE = 3000000;

    //static constexpr int NODE_ADDRESS = 8582;
    static constexpr int NODE_ADDRESS = 9717;

    // Create a SerialConnection with the COM port and (optional) baudrate
    mscl::Connection connection = mscl::Connection::Serial(COM_PORT, BAUDRATE);

    // Create a BaseStation with the SerialConnection
    mscl::BaseStation baseStation(connection);

    // Create a Wireless Node with the BaseStation
    mscl::WirelessNode node(NODE_ADDRESS, baseStation);

    // TODO: add as many other WirelessNode objects here as you want (used in the startSyncSampling example)
    std::vector<mscl::WirelessNode> networkNodes;
    networkNodes.push_back(node);
    mscl::WirelessNode secondNode(8582, baseStation); networkNodes.push_back(secondNode); // uncomment if you want to test network of two nodes

    // Due to the nature of wireless devices, it is possible to lose packets over the air.
    // MSCL has a built-in way of performing retries whenever an eeprom address is attempted to be read.
    // By default, this value is set to 0. You may wish to keep it at 0 and handle retries yourself depending on your application.
    baseStation.readWriteRetries(3);
    node.readWriteRetries(3);

    // TODO: Uncomment the lines below to run the examples

    // Example: Ping Node
    pingNode(node);

    /////////////////////////////////GLink200 Specific examples////////////////////////
    
    ////////////////////////                              Hardware Config
    
    //enableChannelsGLink200_accel(node); 
    
    //enableChannelsGLink200_tilt(node);  

    //GLink200InputRange(node); 

    //GLink200LPF(node); 

    //GLink200HPF(node); 

    ////////////////////////                              Calibration Config

    //GLink200LinearCal(node);

    ////////////////////////                              Sampling Config

    //GLink200SamplingConfigTab(node); 

    ////////////////////////                              Power Config

    //GLink200PowerConfigTab(node); 

    //////////////////////////////More General Examples////////////////////////////////

    //nodeDiscovery(baseStation); 

    //supportedSampleRates(node);  

    syncSampling(baseStation, networkNodes); 
    
    //nonSyncSampling(baseStation, networkNodes); 

    //changeBaseStationFrequency(baseStation); 

    //nodeCyclePower(node);  

    //baseTransmitPower(base); 

    //baseBeaconSelector(base); 
    
    //baseCyclePower(baseStation); 
    
    //dataTypeSelect(node); 

    //nodesOnOtherFrequencies(baseStation);  

    //switchBaseProtocol(baseStation); 

    //rangeTest(baseStation, node);
    
    //////////////////////////////Stock/////////////////////////////////////////////////

    // Example: Get Configuration
    //getCurrentConfig(node);

    // Example: Set Configuration
    //setCurrentConfig(node);       // Warning: this example changes settings on your Node!

    // Example: Start Sampling
    //startSyncSampling(baseStation, networkNodes);

    // Example: Set to Idle

    // Example: Parse Data
    //parseData(baseStation);

    // Example: Enable and Disable beacon
    // enableDisableBeacon(baseStation);

    printf("\nPress enter to idle and exit...");

    getchar();
    getchar();
    
    for (mscl::WirelessNode& node : networkNodes)
        setToIdle(node); 

    return 0;
}
