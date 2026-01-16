using System;
using System.Collections.Generic;
using System.Threading;

// Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  - Both MSCL_Managed.dll and MSCL.dll need to be in the same directory as the executable
//  -'MSCL.dll' needs to be copied into the executable directory manually in most cases

namespace MSCL_Wireless_Example_CSharp
{
    class Program
    {
        ////////////////////////////////////////////////////////////////////////////////
        // TODO: Modify any of these options according to your use case

        // Toggle certain parts of the example on/off
        static readonly bool PING_NODE             = true;
        static readonly bool SET_TO_IDLE           = true;
        static readonly bool GET_CURRENT_CONFIG    = true;
        static readonly bool SET_CURRENT_CONFIG    = true;
        static readonly bool START_SYNC_SAMPLING   = true;
        static readonly bool PARSE_DATA            = true;
        static readonly bool ENABLE_DISABLE_BEACON = true;

        // Update the communication port
        static readonly string COM_PORT = "COM1";

        // Basestations use a baudrate of 3000000
        static readonly uint BAUDRATE = 3000000;

        // Add more node addresses to this list as needed
        static readonly uint[] NODE_ADDRESSES = {
            12345
        };
        ////////////////////////////////////////////////////////////////////////////////

        static void Main(string[] args)
        {
            try
            {
                // Create a SerialConnection with the COM port and (optional) baudrate
                mscl.Connection connection = mscl.Connection.Serial(COM_PORT, BAUDRATE);

                // Create a BaseStation with the SerialConnection
                mscl.BaseStation baseStation = new mscl.BaseStation(connection);

                // Due to the nature of wireless devices, it is possible to lose packets over the air.
                // MSCL has a built-in way of performing retries whenever an eeprom address is attempted to be read.
                // By default, this value is set to 0. You may wish to keep it at 0 and handle retries yourself depending on your application.
                baseStation.readWriteRetries(3);

                List<mscl.WirelessNode> networkNodes = new List<mscl.WirelessNode>();

                foreach (uint nodeAddress in NODE_ADDRESSES)
                {
                    // Create a Wireless Node with the BaseStation
                    mscl.WirelessNode node = new mscl.WirelessNode(nodeAddress, baseStation);

                    networkNodes.Add(node);

                    node.readWriteRetries(3);

                    if (PING_NODE)
                    {
                        // Example: Ping Node
                        PingNode(node);
                    }

                    if (SET_TO_IDLE)
                    {
                        // Example: Set to Idle
                        SetToIdle(node);
                    }

                    if (GET_CURRENT_CONFIG)
                    {
                        // Example: Get Configuration
                        GetCurrentConfig(node);
                    }

                    if (SET_CURRENT_CONFIG)
                    {
                        // Example: Set Configuration
                        SetCurrentConfig(node);       // Warning: this example changes settings on your Node!
                    }
                }

                if (START_SYNC_SAMPLING)
                {
                    // Example: Start Sampling
                    StartSyncSampling(baseStation, networkNodes);
                }

                if (PARSE_DATA)
                {
                    // Example: Parse Data
                    ParseData(baseStation);
                }

                if (ENABLE_DISABLE_BEACON)
                {
                    // Example: Enable and Disable beacon
                    EnableDisableBeacon(baseStation);
                }
            }
            catch (mscl.Error e)
            {
                Console.Error.WriteLine("Error: " + e.Message);
            }

            Console.WriteLine("Press enter to continue...");
            Console.Read();
        }

        public static void PingNode(mscl.WirelessNode node)
        {
            mscl.PingResponse response = node.ping();

            if (response.success())
            {
                // Get some details from the response
                Console.WriteLine("Successfully pinged Node " + node.nodeAddress());
                Console.WriteLine("Base Station RSSI: " + response.baseRssi());
                Console.WriteLine("Node RSSI: " + response.nodeRssi());

                // We can talk to the Node, so let's get some more info
                Console.WriteLine("Node Information: ");
                Console.WriteLine("Model Number: " + node.model());
                Console.WriteLine("Serial: " + node.serial());
                Console.WriteLine("Firmware: " + node.firmwareVersion());
            }
            else
            {
                // Note: To communicate with a Wireless Node, all the following must be true:
                //  - The Node is powered on, and within range of the BaseStation
                //  - The Node is on the same frequency as the BaseStation
                //  - The Node is in Idle Mode (not sampling, and not sleeping)
                //  - The Node is on the same communication protocol as the BaseStation (LXRS vs LXRS+)
                Console.WriteLine("Failed to ping Node " + node.nodeAddress() + ".");
            }
        }

        public static void SetToIdle(mscl.WirelessNode node)
        {
            // Call the set to idle function and get the resulting SetToIdleStatus object
            //  Note: This starts the set to idle node command, which is an ongoing operation. The SetToIdleStatus should be queried for progress.
            mscl.SetToIdleStatus status = node.setToIdle();

            Console.Write("Setting Node to Idle");

            // Using the SetToIdleStatus object, check if the Set to Idle operation is complete.
            // Note: we are specifying a timeout of 300 milliseconds here, which is the maximum
            //      amount of time that the complete function will block if the Set to Idle
            //      operation has not finished. Leaving this blank defaults to a timeout of 10ms.
            while (!status.complete(300))
            {
                // Note: the Set to Idle operation can be canceled by calling status.cancel()
                Console.Write(".");
            }

            // At this point, the Set to Idle operation has completed

            // Check the result of the Set to Idle operation
            switch (status.result())
            {
                // Completed successfully
                case mscl.SetToIdleStatus.SetToIdleResult.setToIdleResult_success:
                {
                    Console.WriteLine("Successfully set to idle!");
                    break;
                }
                // Canceled by the user
                case mscl.SetToIdleStatus.SetToIdleResult.setToIdleResult_canceled:
                {
                    Console.WriteLine("Set to Idle was canceled!");
                    break;
                }
                // Failed to perform the operation
                case mscl.SetToIdleStatus.SetToIdleResult.setToIdleResult_failed:
                default:
                {
                    Console.WriteLine("Set to Idle has failed!");
                    break;
                }
            }
        }

        public static void GetCurrentConfig(mscl.WirelessNode node)
        {
            Console.WriteLine("Current Configuration Settings");

            // Read some of the current configuration settings on the node
            Console.WriteLine("# of Triggers: " + node.getNumDatalogSessions());
            Console.WriteLine("User Inactivity Timeout: " + node.getInactivityTimeout() + " seconds");
            Console.WriteLine("Total active channels: " + node.getActiveChannels().count());
            Console.WriteLine("# of sweeps: " + node.getNumSweeps());

            // If a configuration function requires a ChannelMask parameter, this indicates that the
            // option may affect 1 or more channels on the Node. For instance, a hardware gain may
            // affect ch1 and ch2 with just 1 setting. If you know the mask for your Node, you can provide
            // that mask when asking for the configuration. If you want to programmatically determine
            // the mask for each setting, you can ask for the Node's ChannelGroups. See below.

            // Get the ChannelGroups that the node supports
            mscl.ChannelGroups chGroups = node.features().channelGroups();

            // Iterate over each channel group
            foreach (mscl.ChannelGroup group in chGroups)
            {
                // Get all the settings for this group (i.e., may contain linear equation and hardware gain).
                mscl.ChannelGroupSettings groupSettings = group.settings();

                // Iterate over each setting for this group
                foreach (mscl.WirelessTypes.ChannelGroupSetting setting in groupSettings)
                {
                    // If the group contains the linear equation setting
                    if (setting == mscl.WirelessTypes.ChannelGroupSetting.chSetting_linearEquation)
                    {
                        // We can now pass the channel mask (group.channels()) for this group to the node.getLinearEquation function.
                        // Note: once this channel mask is known for a specific node (+ fw version), it should never change
                        mscl.LinearEquation le = node.getLinearEquation(group.channels());

                        Console.WriteLine("Linear Equation for: " + group.name());
                        Console.WriteLine("Slope: " + le.slope().ToString("F3"));
                        Console.WriteLine("Offset: " + le.offset().ToString("F3"));
                    }
                }
            }
        }

        public static void SetCurrentConfig(mscl.WirelessNode node)
        {
            // Just changing a small subset of settings for this example.
            // More settings are available. Please reference the documentation for the full list of functions.

            Console.WriteLine();
            Console.Write("Changing configuration settings...");

            // Create a WirelessNodeConfig which is used to set all node configuration options
            mscl.WirelessNodeConfig config = new mscl.WirelessNodeConfig();

            // Set the configuration options that we want to change
            config.defaultMode(mscl.WirelessTypes.DefaultMode.defaultMode_idle);
            config.inactivityTimeout(7200);
            config.samplingMode(mscl.WirelessTypes.SamplingMode.samplingMode_sync);
            config.sampleRate(mscl.WirelessTypes.WirelessSampleRate.sampleRate_256Hz);
            config.unlimitedDuration(true);

            // Attempt to verify the configuration with the Node we want to apply it to
            //  Note that this step is not required before applying; however, the apply will throw an
            //  Error_InvalidNodeConfig exception if the config fails to verify.
            mscl.ConfigIssues issues = new mscl.ConfigIssues();

            if (!node.verifyConfig(config, issues))
            {
                Console.WriteLine();
                Console.WriteLine("Failed to verify the configuration. The following issues were found:");

                // Print out all the issues that were found
                foreach (mscl.ConfigIssue issue in issues)
                {
                    Console.WriteLine(issue.description());
                }

                Console.WriteLine("Configuration will not be applied.");
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

            Console.WriteLine("Done.");
        }

        public static void StartSyncSampling(mscl.BaseStation baseStation, List<mscl.WirelessNode> nodes)
        {
            // Create a SyncSamplingNetwork object, giving it the BaseStation that will be the master BaseStation for the network.
            mscl.SyncSamplingNetwork network = new mscl.SyncSamplingNetwork(baseStation);

            // Add the WirelessNodes to the network.
            // Note: The Nodes must already be configured for Sync Sampling before adding to the network, or else Error_InvalidNodeConfig will be thrown.
            foreach (mscl.WirelessNode node in nodes)
            {
                Console.Write("Adding node " + node.nodeAddress().ToString() + " to the network...");
                network.addNode(node);
                Console.WriteLine("Done.");
            }

            // Can get information about the network
            Console.WriteLine("Network info:");
            Console.WriteLine("Network OK: " + (network.ok() ? "TRUE" : "FALSE"));
            Console.WriteLine("Percent of Bandwidth: " + network.percentBandwidth().ToString("F2") + "%");
            Console.WriteLine("Lossless Enabled: " + (network.lossless() ? "TRUE" : "FALSE"));

            // Apply the network configuration to every node in the network
            Console.Write("Applying network configuration...");
            network.applyConfiguration();
            Console.WriteLine("Done.");

            // Start all the nodes in the network sampling. The master BaseStation's beacon will be enabled with the system time.
            //  Note: if you wish to provide your own start time (not use the system time), pass a mscl::Timestamp object as a second parameter to this function.
            //  Note: if you do not want to enable a beacon at this time, use the startSampling_noBeacon() function. (The nodes will wait until they hear a beacon to start sampling).
            Console.Write("Starting the network...");
            network.startSampling();
            Console.WriteLine("Done.");

            //=======================================================================================
            // Many other functions are available for the SyncSamplingNetwork:
            //
            // network.lossless()                        // enable or disable "lossless" mode for the network (default of enabled).
            // network.ok()                              // check whether the network is "OK" meaning all nodes fit in the network and have communicated successfully.
            // network.percentBandwidth()                // get the percentage of bandwidth for the entire network.
            // network.refresh()                         // refreshes the entire network. Should be called any time a change is made to the node after it has been added to the network.
            // network.removeNode()                      // remove a node from the network.
            // network.getNodeNetworkInfo(nodeAddress)   // get network information for an individual node in the network (TDMA address, percent bandwidth, etc.)
            //=======================================================================================
        }

        public static void ParseData(mscl.BaseStation baseStation)
        {
            // Endless loop of reading in data
            while (true)
            {
                // Loop through all the data sweeps that have been collected by the BaseStation, with a timeout of 10 milliseconds
                foreach (mscl.DataSweep sweep in baseStation.getData(10))
                {
                    // Print out information about the sweep
                    Console.Write("Packet Received: ");
                    Console.Write("Node " + sweep.nodeAddress() + " ");
                    Console.Write("Timestamp: " + sweep.timestamp().ToString() + " ");
                    Console.Write("Tick: " + sweep.tick() + " ");
                    Console.Write("Sample Rate: " + sweep.sampleRate().prettyStr() + " ");
                    Console.Write("Base RSSI: " + sweep.baseRssi() + " ");
                    Console.Write("Node RSSI: " + sweep.nodeRssi() + " ");

                    Console.Write("DATA: ");

                    // Iterate over each point in the sweep
                    foreach (mscl.WirelessDataPoint dataPoint in sweep.data())
                    {
                        // Print out the channel name
                        Console.Write(dataPoint.channelName() + ": ");

                        // Print out the channel data
                        // Note: The as_string() function is being used here for simplicity.
                        //      Other methods (i.e., as_float, as_uint16, as_Vector) are also available.
                        //      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                        Console.Write(dataPoint.as_string() + " ");
                    }

                    Console.WriteLine();
                }
            }
        }

        public static void EnableDisableBeacon(mscl.BaseStation baseStation)
        {
            // Make sure we can ping the base station
            if (!baseStation.ping())
            {
                Console.WriteLine("Failed to ping the Base Station");
            }

            if (baseStation.features().supportsBeaconStatus())
            {
                mscl.BeaconStatus status = baseStation.beaconStatus();
                Console.Write("Beacon current status: Enabled?: " + (status.enabled() ? "TRUE" : "FALSE"));
                Console.WriteLine(" Time: " + status.timestamp());
            }

            Console.WriteLine("Attempting to enable the beacon...");

            // Enable the beacon on the Base Station using the PC time
            mscl.Timestamp beaconTime = baseStation.enableBeacon();

            // If we got here, no exception was thrown, so enableBeacon was successful
            Console.WriteLine("Successfully enabled the beacon on the Base Station");
            Console.WriteLine("Beacon's initial Timestamp: " + beaconTime.ToString());

            Console.WriteLine("Beacon is active");
            Console.WriteLine("Sleeping for 3 seconds...");

            Thread.Sleep(3000);

            // Disable the beacon on the Base Station
            baseStation.disableBeacon();

            // If we got here, no exception was thrown, so disableBeacon was successful
            Console.WriteLine("Successfully disabled the beacon on the Base Station");
        }
    }
}
