// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Inertial/InertialNode.h>
#include <mscl/MicroStrain/MIP/MipNodeFeatures.h>

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
static void getCurrentConfig(mscl::InertialNode& node);
#endif // GET_CURRENT_CONFIG

#if SET_CURRENT_CONFIG
static void setCurrentConfig(mscl::InertialNode& node);
#endif // SET_CURRENT_CONFIG

#if START_SAMPLING
static void startSampling(mscl::InertialNode& node);
#endif // START_SAMPLING

#if SET_TO_IDLE
static void setToIdle(mscl::InertialNode& node);
#endif // SET_TO_IDLE

#if PARSE_DATA
static void parseData(mscl::InertialNode& node);
#endif // PARSE_DATA

int main(int, char**)
{
    try
    {
        // Create a SerialConnection with the COM port and (optional) baudrate
        mscl::Connection connection = mscl::Connection::Serial(COM_PORT, BAUDRATE);

        // Create an InertialNode with the connection
        mscl::InertialNode node(connection);

        printf("Node Information:\n");
        printf("Model Name: %s\n", node.modelName().c_str());
        printf("Model Number: %s\n", node.modelNumber().c_str());
        printf("Serial: %s\n", node.serialNumber().c_str());
        printf("Firmware: %s\n\n", node.firmwareVersion().str().c_str());

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

    printf("Press enter to continue...\n");
    getchar();

    return 0;
}

#if GET_CURRENT_CONFIG
// Example: Get Current Configuration
//  Shows how to read current configuration settings an Inertial Device.
static void getCurrentConfig(mscl::InertialNode& node)
{
    // Many other settings are available than shown below
    // Reference the documentation for the full list of commands

    // If the node supports AHRS/IMU
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_AHRS_IMU))
    {
        // Get a list of the AHRS/IMU channels currently active on the Node
        const mscl::MipChannels ahrsImuActiveChs = node.getActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU);

        printf("AHRS/IMU Channels\n");
        printf("-----------------\n");

        for (const mscl::MipChannel& channel : ahrsImuActiveChs)
        {
            printf("Channel Field: 0x%04X\n", channel.channelField());
            printf("Sample Rate: %s\n\n", channel.sampleRate().prettyStr().c_str());
        }
    }

    // If the node supports Estimation Filter
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_ESTFILTER))
    {
        // Get a list of the Estimation Filter channels currently active on the Node
        const mscl::MipChannels estFilterActiveChs = node.getActiveChannelFields(mscl::MipTypes::CLASS_ESTFILTER);

        printf("\nEstimation Filter Channels\n");
        printf("--------------------------\n");

        for (const mscl::MipChannel& channel : estFilterActiveChs)
        {
            printf("Channel Field: 0x%04X\n", channel.channelField());
            printf("Sample Rate: %s\n\n", channel.sampleRate().prettyStr().c_str());
        }
    }

    // If the node supports GNSS
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_GNSS))
    {
        // Get a list of the GNSS channels currently active on the Node
        const mscl::MipChannels gnssActiveChs = node.getActiveChannelFields(mscl::MipTypes::CLASS_GNSS);

        printf("\nGNSS Channels\n");
        printf("-------------\n");

        for (const mscl::MipChannel& channel : gnssActiveChs)
        {
            printf("Channel Field: 0x%04X\n", channel.channelField());
            printf("Sample Rate: %s\n\n", channel.sampleRate().prettyStr().c_str());
        }
    }

    printf("Altitude Aiding enabled?: %s\n", node.getAltitudeAid() ? "TRUE" : "FALSE");

    const mscl::PositionOffset offset = node.getAntennaOffset();
    printf("Antenna Offset: X = %000.03f Y = %000.03f Z = %000.03f\n", offset.x(), offset.y(), offset.z());

    printf("Pitch/Roll Aiding enabled?: %s\n", node.getPitchRollAid() ? "TRUE" : "FALSE");
}
#endif // GET_CURRENT_CONFIG

#if SET_CURRENT_CONFIG
static void setCurrentConfig(mscl::InertialNode& node)
{
    // Many other settings are available than shown below
    // Reference the documentation for the full list of commands

    // If the node supports AHRS/IMU
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_AHRS_IMU))
    {
        mscl::MipChannels ahrsImuChs;
        ahrsImuChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC, mscl::SampleRate::Hertz(500)));
        ahrsImuChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC, mscl::SampleRate::Hertz(100)));

        // Apply to the node
        node.setActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU, ahrsImuChs);
    }

    // If the node supports Estimation Filter
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_ESTFILTER))
    {
        mscl::MipChannels estFilterChs;
        estFilterChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS, mscl::SampleRate::Hertz(100)));

        // Apply to the node
        node.setActiveChannelFields(mscl::MipTypes::CLASS_ESTFILTER, estFilterChs);
    }

    // If the node supports GNSS
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_GNSS))
    {
        mscl::MipChannels gnssChs;
        gnssChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_GNSS_LLH_POSITION, mscl::SampleRate::Hertz(1)));

        // Apply to the node
        node.setActiveChannelFields(mscl::MipTypes::CLASS_GNSS, gnssChs);
    }

    node.setPitchRollAid(true);

    node.setAltitudeAid(false);

    mscl::PositionOffset offset(0.0f, 0.0f, 0.0f);
    node.setAntennaOffset(offset);
}
#endif // SET_CURRENT_CONFIG

#if START_SAMPLING
static void startSampling(mscl::InertialNode& node)
{
    // Each class/category is separated into its own command.
    // You can enable them individually if, say, you only want the Estimation Filter channels to be streamed

    if (node.features().supportsCategory(mscl::MipTypes::CLASS_AHRS_IMU))
    {
        node.enableDataStream(mscl::MipTypes::CLASS_AHRS_IMU);
    }

    if (node.features().supportsCategory(mscl::MipTypes::CLASS_ESTFILTER))
    {
        node.enableDataStream(mscl::MipTypes::CLASS_ESTFILTER);
    }

    if (node.features().supportsCategory(mscl::MipTypes::CLASS_GNSS))
    {
        node.enableDataStream(mscl::MipTypes::CLASS_GNSS);
    }
}
#endif // START_SAMPLING

#if SET_TO_IDLE
static void setToIdle(mscl::InertialNode& node)
{
    node.setToIdle();

    // Note: you can also disable the datastream for each class/category
    //      separately if desired, by using the enableDataStream command shown in
    //      the startSampling example, but passing a second parameter of 'false'
}
#endif // SET_TO_IDLE

#if PARSE_DATA
//Example: Parse Data
//  Shows how to parse incoming data from an Inertial Device.
//  Note that this example does not start a Node sampling (assumes it already is).
static void parseData(mscl::InertialNode& node)
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
