#include "enableDisableBeacon.h"
#include "getCurrentConfig.h"
#include "parseData.h"
#include "pingNode.h"
#include "setCurrentConfig.h"
#include "setToIdle.h"
#include "startSyncSampling.h"

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Wireless/BaseStation.h>
#include <mscl/MicroStrain/Wireless/WirelessNode.h>

int main(int argc, char** argv)
{
    // TODO: Change these constants to match your setup
#ifdef _WIN32
    static constexpr const char* COM_PORT = "COM1";
#elif __linux__
    static constexpr const char* COM_PORT = "/dev/tty/ACM0";
#endif // _WIN32

    // Basestations use a baudrate of 3000000
    static constexpr uint32_t BAUDRATE = 3000000;

    static constexpr int NODE_ADDRESS = 65364;

    try
    {
        // Create a SerialConnection with the COM port and (optional) baudrate
        mscl::Connection connection = mscl::Connection::Serial(COM_PORT, BAUDRATE);

        // Create a BaseStation with the SerialConnection
        mscl::BaseStation baseStation(connection);

        // Create a Wireless Node with the BaseStation
        mscl::WirelessNode node(NODE_ADDRESS, baseStation);

        // TODO: add as many other WirelessNode objects here as you want (used in the startSyncSampling example)
        std::vector<mscl::WirelessNode> networkNodes;
        networkNodes.push_back(node);

        // Due to the nature of wireless devices, it is possible to lose packets over the air.
        // MSCL has a built-in way of performing retries whenever an eeprom address is attempted to be read.
        // By default, this value is set to 0. You may wish to keep it at 0 and handle retries yourself depending on your application.
        baseStation.readWriteRetries(3);
        node.readWriteRetries(3);

        // TODO: Uncomment the lines below to run the examples

        // Example: Ping Node
        // pingNode(node);

        // Example: Get Configuration
        // getCurrentConfig(node);

        // Example: Set Configuration
        // setCurrentConfig(node);       // Warning: this example changes settings on your Node!

        // Example: Start Sampling
        // startSyncSampling(baseStation, networkNodes);

        // Example: Set to Idle
        // setToIdle(node);

        // Example: Parse Data
        // parseData(baseStation);

        // Example: Enable and Disable beacon
        // enableDisableBeacon(baseStation);
    }
    catch (mscl::Error& e)
    {
        fprintf(stderr, "Error: %s\n", e.what());
    }

    printf("Press enter to continue...");
    getchar();

    return 0;
}
