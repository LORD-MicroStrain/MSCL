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
#include "cyclePower.h"

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
    mscl::WirelessNode secondNode(8582, baseStation); networkNodes.push_back(secondNode); 

    // Due to the nature of wireless devices, it is possible to lose packets over the air.
    // MSCL has a built-in way of performing retries whenever an eeprom address is attempted to be read.
    // By default, this value is set to 0. You may wish to keep it at 0 and handle retries yourself depending on your application.
    baseStation.readWriteRetries(3);
    node.readWriteRetries(3);

    // TODO: Uncomment the lines below to run the examples

    // Example: Ping Node
    pingNode(node);

    ///////////////////////////////////////////////////////////////////////////////////

    //nodeDiscovery(baseStation);  // ready

    //supportedSampleRates(node);  // ready

    //enableChannelsGLink200_accel(node); // ready
    
    //enableChannelsGLink200_tilt(node);  // ready

    //syncSampling(baseStation, networkNodes);  // ready
    
    //nonSyncSampling(baseStation, networkNodes); // ready 

    changeBaseStationFrequency(baseStation);
    
    //dataTypeSelect(node);  // ready 
    
    //////////////////////////////////////////////////////////////////////////////////

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
    
    for (mscl::WirelessNode& node : networkNodes)
        setToIdle(node); 

    return 0;
}
