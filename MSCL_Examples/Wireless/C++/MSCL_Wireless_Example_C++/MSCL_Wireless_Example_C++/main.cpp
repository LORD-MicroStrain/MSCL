#include "enableDisableBeacon.h"
#include "getCurrentConfig.h"
#include "parseData.h"
#include "pingNode.h"
#include "setCurrentConfig.h"
#include "setToIdle.h"
#include "startSyncSampling.h"
//
#include "nodeDiscovery.h"
#include "supportedSampleRates.h"
#include "enableChannelsGLink200.h"


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

    static constexpr int NODE_ADDRESS = 8582;

    // Create a SerialConnection with the COM port and (optional) baudrate
    mscl::Connection connection = mscl::Connection::Serial(COM_PORT, BAUDRATE);

    // Create a BaseStation with the SerialConnection
    mscl::BaseStation baseStation(connection);

    // Create a Wireless Node with the BaseStation
    mscl::WirelessNode node(NODE_ADDRESS, baseStation);

    // TODO: add as many other WirelessNode objects here as you want (used in the startSyncSampling example)
    //std::vector<mscl::WirelessNode> networkNodes;
    //networkNodes.push_back(node);

    // Due to the nature of wireless devices, it is possible to lose packets over the air.
    // MSCL has a built-in way of performing retries whenever an eeprom address is attempted to be read.
    // By default, this value is set to 0. You may wish to keep it at 0 and handle retries yourself depending on your application.
    //baseStation.readWriteRetries(3);
   // node.readWriteRetries(3);

    // TODO: Uncomment the lines below to run the examples

    //nodeDiscovery(baseStation); 

    supportedSampleRates(node); 

    enableChannelsGLink200(node); 

    // Example: Ping Node
    //pingNode(node);

    // Example: Get Configuration
    //getCurrentConfig(node);

    // Example: Set Configuration
    //setCurrentConfig(node);       // Warning: this example changes settings on your Node!

    // Example: Start Sampling
    //startSyncSampling(baseStation, networkNodes);

    // Example: Set to Idle
    //setToIdle(node);

    // Example: Parse Data
    //parseData(baseStation);

    // Example: Enable and Disable beacon
    // enableDisableBeacon(baseStation);

    /*
    const mscl::NodeFeatures& features = node.features();

         // Get node info
    std::cout << "Node model: " << node.model() << std::endl;
    std::cout << "Node ID: " << node.nodeAddress() << std::endl;

    std::cout << "\n--- Node Features ---\n";

    // Channels
    auto chCount = features.channelGroups().size(); 
    std::cout << "Channel Count: " << chCount << std::endl;

    for (uint8_t ch = 0; ch < chCount; ++ch)
    {
        std::cout << "  Channel " << (int)ch << ": ";
        std::cout << features.channelGroups()[ch].name() << std::endl;
    }

    /*
    // Sampling Modes
    auto samplingModes = features.supportedSamplingModes();
    std::cout << "\nSupported Sampling Modes:\n";
    for (const auto& mode : samplingModes)
    {
        std::cout << "  - " << mscl::SamplingModes::str(mode) << std::endl;

        // Sample rates for this mode
        auto rates = features.supportedSampleRates(mode);
        std::cout << "    Sample Rates:\n";
        for (const auto& rate : rates)
        {
            std::cout << "      * " << rate.str() << std::endl;
        }
    }

    // Data Formats
    auto dataFormats = features.supportedDataFormats();
    std::cout << "\nSupported Data Formats:\n";
    for (const auto& format : dataFormats)
    {
        std::cout << "  - " << mscl::WirelessTypes::dataFormatToStr(format) << std::endl;
    }

    // Transmit Power
    auto txPowers = features.supportedTransmitPowers();
    std::cout << "\nSupported Transmit Powers:\n";
    for (const auto& power : txPowers)
    {
        std::cout << "  - " << (int)power << " dBm" << std::endl;
    }

    // Data Collection Methods
    auto methods = features.supportedDataCollectionMethods();
    std::cout << "\nSupported Data Collection Methods:\n";
    for (const auto& method : methods)
    {
        std::cout << "  - " << mscl::WirelessTypes::dataCollectionMethodToStr(method) << std::endl;
    }

    */

    printf("\nPress enter to continue...");
    getchar();
    getchar();

    return 0;
}
