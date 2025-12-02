// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Wireless/BaseStation.h>
#include <mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h>
#include <mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/SyncSamplingNetwork.h>
#include <mscl/MicroStrain/Wireless/WirelessNode.h>

////////////////////////////////////////////////////////////////////////////////
// TODO: Modify any of these options according to your use case

// Toggle certain parts of the example on/off
#define PING_NODE             true
#define SET_TO_IDLE           true
#define GET_CURRENT_CONFIG    true
#define SET_CURRENT_CONFIG    true
#define START_SYNC_SAMPLING   true
#define PARSE_DATA            true
#define ENABLE_DISABLE_BEACON true

// Update the communication port
#ifdef _WIN32
static constexpr const char* COM_PORT = "COM1";
#elif __linux__
static constexpr const char* COM_PORT = "/dev/tty/ACM0";
#endif // _WIN32

// Basestations use a baudrate of 3000000
static constexpr uint32_t BAUDRATE = 3000000;

// Add more node addresses to this list as needed
static constexpr int NODE_ADDRESSES[] = {
    12345
};
////////////////////////////////////////////////////////////////////////////////

// Forward declarations
#if PING_NODE
static void pingNode(mscl::WirelessNode& node);
#endif // PING_NODE

#if SET_TO_IDLE
static void setToIdle(mscl::WirelessNode& node);
#endif // SET_TO_IDLE

#if GET_CURRENT_CONFIG
static void getCurrentConfig(mscl::WirelessNode& node);
#endif // GET_CURRENT_CONFIG

#if SET_CURRENT_CONFIG
static void setCurrentConfig(mscl::WirelessNode& node);
#endif // SET_CURRENT_CONFIG

#if START_SYNC_SAMPLING
static void startSyncSampling(mscl::BaseStation& baseStation, std::vector<mscl::WirelessNode> nodes);
#endif // START_SYNC_SAMPLING

#if PARSE_DATA
static void parseData(mscl::BaseStation& baseStation);
#endif // PARSE_DATA

#if ENABLE_DISABLE_BEACON
static void enableDisableBeacon(mscl::BaseStation& baseStation);
#endif // ENABLE_DISABLE_BEACON

int main(int, char**)
{
    // Mark printf operations as unbuffered to flush with every operation
    setvbuf(stdout, NULL, _IONBF, 0);

    try
    {
        // Create a SerialConnection with the COM port and (optional) baudrate
        mscl::Connection connection = mscl::Connection::Serial(COM_PORT, BAUDRATE);

        // Create a BaseStation with the SerialConnection
        mscl::BaseStation baseStation(connection);

        // Due to the nature of wireless devices, it is possible to lose packets over the air.
        // MSCL has a built-in way of performing retries whenever an eeprom address is attempted to be read.
        // By default, this value is set to 0. You may wish to keep it at 0 and handle retries yourself depending on your application.
        baseStation.readWriteRetries(3);

#if START_SYNC_SAMPLING
        std::vector<mscl::WirelessNode> networkNodes;
#endif // START_SYNC_SAMPLING

        for (size_t index = 0; index < sizeof(NODE_ADDRESSES) / sizeof(NODE_ADDRESSES[0]); ++index)
        {
            const int NODE_ADDRESS = NODE_ADDRESSES[index];

            // Create a Wireless Node with the BaseStation
            mscl::WirelessNode node(NODE_ADDRESS, baseStation);

#if START_SYNC_SAMPLING
            networkNodes.push_back(node);
#endif // START_SYNC_SAMPLING

            node.readWriteRetries(3);

#if PING_NODE
            // Example: Ping Node
            pingNode(node);
#endif // PING_NODE

#if SET_TO_IDLE
            // Example: Set to Idle
            setToIdle(node);
#endif // SET_TO_IDLE

#if GET_CURRENT_CONFIG
            // Example: Get Configuration
            getCurrentConfig(node);
#endif // GET_CURRENT_CONFIG

#if SET_CURRENT_CONFIG
            // Example: Set Configuration
            setCurrentConfig(node);       // Warning: this example changes settings on your Node!
#endif // SET_CURRENT_CONFIG
        }

#if START_SYNC_SAMPLING
        // Example: Start Sampling
        startSyncSampling(baseStation, networkNodes);
#endif // START_SYNC_SAMPLING

#if PARSE_DATA
        // Example: Parse Data
        parseData(baseStation);
#endif // PARSE_DATA

#if ENABLE_DISABLE_BEACON
        // Example: Enable and Disable beacon
        enableDisableBeacon(baseStation);
#endif // ENABLE_DISABLE_BEACON
    }
    catch (mscl::Error& e)
    {
        fprintf(stderr, "Error: %s\n", e.what());
    }

    printf("Press enter to continue...");
    getchar();

    return 0;
}

#if PING_NODE
static void pingNode(mscl::WirelessNode& node)
{
    const mscl::PingResponse response = node.ping();

    if (response.success())
    {
        // Get some details from the response
        printf("Successfully pinged Node %d\n", node.nodeAddress());
        printf("Base Station RSSI: %d\n", response.baseRssi());
        printf("Node RSSI: %d\n\n", response.nodeRssi());

        // We can talk to the Node, so let's get some more info
        printf("Node Information: \n");
        printf("Model Number: %d\n", node.model());
        printf("Serial: %s\n", node.serial().c_str());
        printf("Firmware: %s\n\n", node.firmwareVersion().str().c_str());
    }
    else
    {
        // Note: To communicate with a Wireless Node, all the following must be true:
        //  - The Node is powered on, and within range of the BaseStation
        //  - The Node is on the same frequency as the BaseStation
        //  - The Node is in Idle Mode (not sampling, and not sleeping)
        //  - The Node is on the same communication protocol as the BaseStation (LXRS vs LXRS+)
        printf("Failed to ping Node %d.\n", node.nodeAddress());
    }
}
#endif // PING_NODE

#if SET_TO_IDLE
static void setToIdle(mscl::WirelessNode& node)
{
    // Call the set to idle function and get the resulting SetToIdleStatus object
    //  Note: This starts the set to idle node command, which is an ongoing operation. The SetToIdleStatus should be queried for progress.
    mscl::SetToIdleStatus status = node.setToIdle();

    printf("Setting Node to Idle");

    // Using the SetToIdleStatus object, check if the Set to Idle operation is complete.
    // Note: we are specifying a timeout of 300 milliseconds here, which is the maximum
    //      amount of time that the complete function will block if the Set to Idle
    //      operation has not finished. Leaving this blank defaults to a timeout of 10ms.
    while (!status.complete(300))
    {
        // Note: the Set to Idle operation can be canceled by calling status.cancel()
        printf(".");
    }

    // At this point, the Set to Idle operation has completed

    // Check the result of the Set to Idle operation
    switch (status.result())
    {
        // Completed successfully
        case mscl::SetToIdleStatus::setToIdleResult_success:
        {
            printf("Successfully set to idle!\n");
            break;
        }
        // Canceled by the user
        case mscl::SetToIdleStatus::setToIdleResult_canceled:
        {
            printf("Set to Idle was canceled!\n");
            break;
        }
        // Failed to perform the operation
        case mscl::SetToIdleStatus::setToIdleResult_failed:
        default:
        {
            printf("Set to Idle has failed!\n");
            break;
        }
    }
}
#endif // SET_TO_IDLE

#if GET_CURRENT_CONFIG
static void getCurrentConfig(mscl::WirelessNode& node)
{
    printf("Current Configuration Settings\n");

    // Read some of the current configuration settings on the node
    printf("# of Triggers: %d\n", node.getNumDatalogSessions());
    printf("User Inactivity Timeout: %d seconds\n", node.getInactivityTimeout());
    printf("Total active channels: %d\n", node.getActiveChannels().count());
    printf("# of sweeps: %d\n", node.getNumSweeps());

    // If a configuration function requires a ChannelMask parameter, this indicates that the
    // option may affect 1 or more channels on the Node. For instance, a hardware gain may
    // affect ch1 and ch2 with just 1 setting. If you know the mask for your Node, you can provide
    // that mask when asking for the configuration. If you want to programmatically determine
    // the mask for each setting, you can ask for the Node's ChannelGroups. See below.

    // Get the ChannelGroups that the node supports
    const mscl::ChannelGroups chGroups = node.features().channelGroups();

    // Iterate over each channel group
    for (const mscl::ChannelGroup& group: chGroups)
    {
        // Get all the settings for this group (i.e., may contain linear equation and hardware gain).
        const mscl::WirelessTypes::ChannelGroupSettings groupSettings = group.settings();

        // Iterate over each setting for this group
        for (const mscl::WirelessTypes::ChannelGroupSetting& setting: groupSettings)
        {
            // If the group contains the linear equation setting
            if (setting == mscl::WirelessTypes::chSetting_linearEquation)
            {
                // We can now pass the channel mask (group.channels()) for this group to the node.getLinearEquation function.
                // Note: once this channel mask is known for a specific node (+ fw version), it should never change
                mscl::LinearEquation le = node.getLinearEquation(group.channels());

                printf("Linear Equation for: %s\n", group.name().c_str());
                printf("Slope: %06.03f\n", le.slope());
                printf("Offset: %06.03f\n", le.offset());
            }
        }
    }
}
#endif // GET_CURRENT_CONFIG

#if SET_CURRENT_CONFIG
static void setCurrentConfig(mscl::WirelessNode& node)
{
    // Just changing a small subset of settings for this example.
    // More settings are available. Please reference the documentation for the full list of functions.

    printf("\nChanging configuration settings...");

    // Create a WirelessNodeConfig which is used to set all node configuration options
    mscl::WirelessNodeConfig config;

    // Set the configuration options that we want to change
    config.defaultMode(mscl::WirelessTypes::defaultMode_idle);
    config.inactivityTimeout(7200);
    config.samplingMode(mscl::WirelessTypes::samplingMode_sync);
    config.sampleRate(mscl::WirelessTypes::sampleRate_256Hz);
    config.unlimitedDuration(true);

    // Attempt to verify the configuration with the Node we want to apply it to
    //  Note that this step is not required before applying; however, the apply will throw an
    //  Error_InvalidNodeConfig exception if the config fails to verify.
    mscl::ConfigIssues issues;

    if (!node.verifyConfig(config, issues))
    {
        printf("Failed to verify the configuration. The following issues were found:\n");

        // Print out all the issues that were found
        for (const mscl::ConfigIssue& issue : issues)
        {
            printf("%s\n", issue.description().c_str());
        }

        printf("Configuration will not be applied.\n");
    }
    else
    {
        // Apply the configuration to the Node
        //  Note that this writes multiple options to the Node.
        //  If an Error_NodeCommunication exception is thrown, it is possible that
        //  some options were successfully applied, while others failed.
        //  It is recommended to keep calling applyConfig until no exception is thrown.
        node.applyConfig(config);
    }

    printf("Done.\n");
}
#endif // SET_CURRENT_CONFIG

#if START_SYNC_SAMPLING
static void startSyncSampling(mscl::BaseStation& baseStation, std::vector<mscl::WirelessNode> nodes)
{
    // Create a SyncSamplingNetwork object, giving it the BaseStation that will be the master BaseStation for the network.
    mscl::SyncSamplingNetwork network(baseStation);

    // Add the WirelessNodes to the network.
    // Note: The Nodes must already be configured for Sync Sampling before adding to the network, or else Error_InvalidNodeConfig will be thrown.
    for (mscl::WirelessNode& node : nodes)
    {
        printf("Adding Node %d to the network...", node.nodeAddress());
        network.addNode(node);
        printf("Done.\n");
    }

    // Can get information about the network
    printf("Network info: \n");
    printf("Network OK: %s\n", network.ok() ? "TRUE" : "FALSE");
    printf("Percent of Bandwidth: %04.02f%%\n", network.percentBandwidth());
    printf("Lossless Enabled: %s\n", network.lossless() ? "TRUE" : "FALSE");

    // Apply the network configuration to every node in the network
    printf("Applying network configuration...");
    network.applyConfiguration();
    printf("Done.\n");

    // Start all the nodes in the network sampling. The master BaseStation's beacon will be enabled with the system time.
    //  Note: if you wish to provide your own start time (not use the system time), pass a mscl::Timestamp object as a second parameter to this function.
    //  Note: if you do not want to enable a beacon at this time, use the startSampling_noBeacon() function. (The nodes will wait until they hear a beacon to start sampling).
    printf("Starting the network...");
    network.startSampling();
    printf("Done.\n");

    //=======================================================================================
    // Many other functions are available for the SyncSamplingNetwork:
    //
    // network.lossless()                        //enable or disable "lossless" mode for the network (default of enabled).
    // network.ok()                              //check whether the network is "OK" meaning all nodes fit in the network and have communicated successfully.
    // network.percentBandwidth()                //get the percentage of bandwidth for the entire network.
    // network.refresh()                         //refreshes the entire network. Should be called any time a change is made to the node after it has been added to the network.
    // network.removeNode()                      //remove a node from the network.
    // network.getNodeNetworkInfo(nodeAddress)   //get network information for an individual node in the network (TDMA address, percent bandwidth, etc.)
    //=======================================================================================
}
#endif // START_SYNC_SAMPLING

#if PARSE_DATA
static void parseData(mscl::BaseStation& baseStation)
{
    // Endless loop of reading in data
    while (true)
    {
        // Loop through all the data sweeps that have been collected by the BaseStation, with a timeout of 10 milliseconds
        for (const mscl::DataSweep& sweep : baseStation.getData(10))
        {
            // Print out information about the sweep
            printf("Packet Received: ");
            printf("Node %d ", sweep.nodeAddress());
            printf("Timestamp: %s ", sweep.timestamp().str().c_str());
            printf("Tick: %d ", sweep.tick());
            printf("Sample Rate: %s ", sweep.sampleRate().prettyStr().c_str());
            printf("Base RSSI: %d ", sweep.baseRssi());
            printf("Node RSSI: %d ", sweep.nodeRssi());

            printf("DATA: ");

            // Iterate over each point in the sweep
            for (const mscl::WirelessDataPoint& dataPoint: sweep.data())
            {
                // Print out the channel name
                printf("%s: ", dataPoint.channelName().c_str());

                // Print out the channel data
                // Note: The as_string() function is being used here for simplicity.
                //      Other methods (i.e., as_float, as_uint16, as_Vector) are also available.
                //      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                printf("%s ", dataPoint.as_string().c_str());
            }

            printf("\n");
        }
    }
}
#endif // PARSE_DATA

#if ENABLE_DISABLE_BEACON
static void enableDisableBeacon(mscl::BaseStation& baseStation)
{
    // Make sure we can ping the base station
    if (!baseStation.ping())
    {
        printf("Failed to ping the Base Station\n");
    }

    if (baseStation.features().supportsBeaconStatus())
    {
        mscl::BeaconStatus status = baseStation.beaconStatus();
        printf("Beacon current status: Enabled?: %s", status.enabled() ? "TRUE" : "FALSE");
        printf(" Time: %s\n", status.timestamp().str().c_str());
    }

    printf("Attempting to enable the beacon...\n");

    // Enable the beacon on the Base Station using the PC time
    mscl::Timestamp beaconTime = baseStation.enableBeacon();

    // If we got here, no exception was thrown, so enableBeacon was successful
    printf("Successfully enabled the beacon on the Base Station\n");
    printf("Beacon's initial Timestamp: %s\n", beaconTime.str().c_str());

    printf("Beacon is active\n");
    printf("Sleeping for 3 seconds...\n");

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Disable the beacon on the Base Station
    baseStation.disableBeacon();

    // If we got here, no exception was thrown, so disableBeacon was successful
    printf("Successfully disabled the beacon on the Base Station\n");
}
#endif // ENABLE_DISABLE_BEACON
