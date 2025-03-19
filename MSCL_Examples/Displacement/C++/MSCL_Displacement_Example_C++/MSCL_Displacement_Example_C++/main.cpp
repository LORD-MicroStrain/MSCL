#include "getCurrentConfig.h"
#include "parseData.h"
#include "setCurrentConfig.h"
#include "setToIdle.h"
#include "startSampling.h"

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Displacement/DisplacementNode.h>

int main(int argc, char** argv)
{
    // TODO: Change these constants to match your setup
#ifdef _WIN32
    const char* COM_PORT = "COM1";
#elif __linux__
    const std::string COM_PORT = "/dev/tty/ACM0";
#endif // _WIN32

    // We recommend at least 115200 for the baudrate on our devices
    static constexpr uint32_t BAUDRATE = 115200;

    try
    {
        // Create a SerialConnection with the COM port and (optional) baudrate
        mscl::Connection connection = mscl::Connection::Serial(COM_PORT, BAUDRATE);

        // Create a DisplacementNode with the connection
        mscl::DisplacementNode node(connection);

        printf("Node Information: \n");
        printf("Model Name: %s\n", node.modelName().c_str());
        printf("Model Number: %s\n", node.modelNumber().c_str());
        printf("Serial: %s\n", node.serialNumber().c_str());
        printf("Firmware: %s\n\n", node.firmwareVersion().str().c_str());

        //TODO: Uncomment the lines below to run the examples

        // Example: Get Configuration
        // getCurrentConfig(node);

        // Example: Set Configuration
        // setCurrentConfig(node);       // Warning: This example changes settings on your Node!

        // Example: Start Sampling
        // startSampling(node);

        // Example: Set to Idle
        // setToIdle(node);

        // Example: Parse Data
        // parseData(node);
    }
    catch (mscl::Error& e)
    {
        fprintf(stderr, "Error: %s\n", e.what());
    }

    printf("Press enter to continue...");
    getchar();

    return 0;
}
