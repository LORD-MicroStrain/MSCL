// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Displacement/DisplacementNode.h>
#include <mscl/MicroStrain/LinearEquation.h>

////////////////////////////////////////////////////////////////////////////////
// TODO: Modify any of these options according to your use case

// Toggle certain parts of the example on/off
#define GET_CURRENT_CONFIG true
#define SET_CURRENT_CONFIG true
#define START_SAMPLING     true
#define SET_TO_IDLE        true
#define PARSE_DATA         true

// Update the communication port
#ifdef _WIN32
static constexpr const char* COM_PORT = "COM1";
#elif __linux__
static constexpr const char* COM_PORT = "/dev/tty/ACM0";
#endif // _WIN32

// We recommend at least 115200 for the baudrate on our devices
static constexpr uint32_t BAUDRATE = 115200;
////////////////////////////////////////////////////////////////////////////////

// Forward declarations
#if GET_CURRENT_CONFIG
static void getCurrentConfig(mscl::DisplacementNode& node);
#endif // GET_CURRENT_CONFIG

#if SET_CURRENT_CONFIG
static void setCurrentConfig(mscl::DisplacementNode& node);
#endif // SET_CURRENT_CONFIG

#if START_SAMPLING
static void startSampling(mscl::DisplacementNode& node);
#endif // START_SAMPLING

#if SET_TO_IDLE
static void setToIdle(mscl::DisplacementNode& node);
#endif // SET_TO_IDLE

#if PARSE_DATA
static void parseData(mscl::DisplacementNode& node);
#endif // PARSE_DATA

int main(int, char**)
{
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

#if GET_CURRENT_CONFIG
        // Example: Get Configuration
        getCurrentConfig(node);
#endif // GET_CURRENT_CONFIG

#if SET_CURRENT_CONFIG
        // Example: Set Configuration
        setCurrentConfig(node);       // Warning: this example changes settings on your Node!
#endif // SET_CURRENT_CONFIG

#if START_SAMPLING
        // Example: Start Sampling
        startSampling(node);
#endif // START_SAMPLING

#if SET_TO_IDLE
        // Example: Set to Idle
        setToIdle(node);
#endif // SET_TO_IDLE

#if PARSE_DATA
        // Example: Parse Data
        parseData(node);
#endif // PARSE_DATA
    }
    catch (mscl::Error& e)
    {
        fprintf(stderr, "Error: %s\n", e.what());
    }

    printf("Press enter to continue...");
    getchar();

    return 0;
}

#if GET_CURRENT_CONFIG
// Example: Get Current Configuration
//  Shows how to read current configuration settings a Displacement Device.
static void getCurrentConfig(mscl::DisplacementNode& node)
{
    mscl::LinearEquation cals = node.getAnalogToDisplacementCal();

    printf("Analog to Displacement Cal: Slope: %000.03f Offset: %000.03f\n", cals.slope(), cals.offset());
    printf("Output Data Rate: %s\n", node.getDisplacementOutputDataRate().prettyStr().c_str());
}
#endif // GET_CURRENT_CONFIG

#if SET_CURRENT_CONFIG
static void setCurrentConfig(mscl::DisplacementNode& node)
{
    // Seed the device time with the current PC time
    // Note: you can pass your own time to this function as a
    //      parameter in nanoseconds since unix epoch
    node.setDeviceTime();
}
#endif // SET_CURRENT_CONFIG

#if START_SAMPLING
static void startSampling(mscl::DisplacementNode& node)
{
    node.resume();
}
#endif // START_SAMPLING

#if SET_TO_IDLE
static void setToIdle(mscl::DisplacementNode& node)
{
    node.setToIdle();
}
#endif // SET_TO_IDLE

#if PARSE_DATA
// Example: Parse Data
//  Shows how to parse incoming data from a Displacement Device.
//  Note that this example does not start a Node sampling (assumes it already is).
static void parseData(mscl::DisplacementNode& node)
{
    // Endless loop of reading in data
    while (true)
    {
        // Loop through all the data packets from the node, with a timeout of 500 milliseconds
        for (const mscl::MipDataPacket& packet : node.getDataPackets(500))
        {
            // Print out the data
            printf("Packet Received: ");

            // Loop through all the data points in the packet
            for (const mscl::MipDataPoint& dataPoint : packet.data())
            {
                printf("%s: ", dataPoint.channelName().c_str());

                // Print out the channel data
                // Note: The as_string() function is being used here for simplicity.
                //      Other methods (i.e., as_float, as_uint16, as_Vector) are also available.
                //      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                printf("%s ", dataPoint.as_string().c_str());

                // If the dataPoint is invalid
                if (!dataPoint.valid())
                {
                    printf("[Invalid] ");
                }
            }

            printf("\n");
        }
    }
}
#endif // PARSE_DATA
