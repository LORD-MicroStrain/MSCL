using System;

// Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  - Both MSCL_Managed.dll and MSCL.dll need to be in the same directory as the executable
//  -'MSCL.dll' needs to be copied into the executable directory manually in most cases

namespace MSCL_CSharp_Inertial_Example
{
    class Program
    {
        ////////////////////////////////////////////////////////////////////////////////
        // TODO: Modify any of these options according to your use case

        // Toggle certain parts of the example on/off
        static readonly bool SET_TO_IDLE        = true;
        static readonly bool GET_CURRENT_CONFIG = true;
        static readonly bool SET_CURRENT_CONFIG = true;
        static readonly bool START_SAMPLING     = true;
        static readonly bool PARSE_DATA         = true;

        // Update the communication port
        static readonly string COM_PORT = "COM1";

        // We recommend at least 115200 for the baudrate on our devices
        static readonly uint BAUDRATE = 115200;
        ////////////////////////////////////////////////////////////////////////////////

        static void Main(string[] args)
        {
            try
            {
                // Create a SerialConnection with the COM port and (optional) baudrate
                mscl.Connection connection = mscl.Connection.Serial(COM_PORT, BAUDRATE);

                // Create an InertialNode with the connection
                mscl.InertialNode node = new mscl.InertialNode(connection);

                Console.WriteLine("Node Information:");
                Console.WriteLine("Model Name: " + node.modelName());
                Console.WriteLine("Model Number: " + node.modelNumber());
                Console.WriteLine("Serial: "  + node.serialNumber());
                Console.WriteLine("Firmware: " + node.firmwareVersion().ToString());
                Console.WriteLine();

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

                if (START_SAMPLING)
                {
                    // Example: Start Sampling
                    StartSampling(node);
                }

                if (PARSE_DATA)
                {
                    // Example: Parse Data
                    ParseData(node);
                }
            }
            catch (mscl.Error e)
            {
                Console.Error.WriteLine("Error: " + e.Message);
            }

            Console.WriteLine("Press enter to continue...");
            Console.Read();
        }

        public static void SetToIdle(mscl.InertialNode node)
        {
            node.setToIdle();

            // Note: you can also disable the datastream for each class/category
            //      separately if desired, by using the enableDataStream command shown in
            //      the startSampling example, but passing a second parameter of 'false'
        }

        // Example: Get Current Configuration
        //  Shows how to read current configuration settings an Inertial Device.
        public static void GetCurrentConfig(mscl.InertialNode node)
        {
            // Many other settings are available than shown below
            // Reference the documentation for the full list of commands

            // If the node supports AHRS/IMU
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_AHRS_IMU))
            {
                // Get a list of the AHRS/IMU channels currently active on the Node
                mscl.MipChannels ahrsImuActiveChs = node.getActiveChannelFields(mscl.MipTypes.DataClass.CLASS_AHRS_IMU);

                Console.WriteLine("AHRS/IMU Channels");
                Console.WriteLine("-----------------");

                foreach (mscl.MipChannel channel in ahrsImuActiveChs)
                {
                    Console.WriteLine("Channel Field: 0x" + ((int)channel.channelField()).ToString("X4"));
                    Console.WriteLine("Sample Rate: " + channel.sampleRate().prettyStr());
                }
            }

            // If the node supports Estimation Filter
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_ESTFILTER))
            {
                // Get a list of the Estimation Filter channels currently active on the Node
                mscl.MipChannels estFilterActiveChs = node.getActiveChannelFields(mscl.MipTypes.DataClass.CLASS_ESTFILTER);

                Console.WriteLine();
                Console.WriteLine("Estimation Filter Channels");
                Console.WriteLine("--------------------------");

                foreach (mscl.MipChannel channel in estFilterActiveChs)
                {
                    Console.WriteLine("Channel Field: 0x" + ((int)channel.channelField()).ToString("X4"));
                    Console.WriteLine("Sample Rate: " + channel.sampleRate().prettyStr());
                }
            }

            // If the node supports GNSS
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_GNSS))
            {
                // Get a list of the GNSS channels currently active on the Node
                mscl.MipChannels gnssActiveChs = node.getActiveChannelFields(mscl.MipTypes.DataClass.CLASS_GNSS);

                Console.WriteLine();
                Console.WriteLine("GNSS Channels");
                Console.WriteLine("--------------------------");

                foreach (mscl.MipChannel channel in gnssActiveChs)
                {
                    Console.WriteLine("Channel Field: 0x" + ((int)channel.channelField()).ToString("X4"));
                    Console.WriteLine("Sample Rate: " + channel.sampleRate().prettyStr());
                }
            }

            if (node.features().supportsCommand(mscl.MipTypes.Command.CMD_EF_ALTITUDE_AID_CTRL))
            {
                Console.WriteLine("Altitude Aiding enabled?: " + (node.getAltitudeAid() ? "TRUE" : "FALSE"));
            }

            if (node.features().supportsCommand(mscl.MipTypes.Command.CMD_EF_ANTENNA_OFFSET))
            {
                mscl.PositionOffset offset = node.getAntennaOffset();
                Console.WriteLine("Antenna Offset: X = " + offset.x().ToString("F3") + " Y = " + offset.y().ToString("F3") + " Z = " + offset.z().ToString("F3"));
            }
            else if (node.features().supportsCommand(mscl.MipTypes.Command.CMD_EF_MULTI_ANTENNA_OFFSET))
            {
                foreach (mscl.GnssReceiverInfo gnssReceiverInfo in node.features().gnssReceiverInfo())
                {
                    mscl.PositionOffset offset = node.getMultiAntennaOffset(gnssReceiverInfo.id);
                    Console.WriteLine("Antenna " + gnssReceiverInfo.id + " Offset: X = " + offset.x().ToString("F3") + " Y = " + offset.y().ToString("F3") + " Z = " + offset.z().ToString("F3"));
                }
            }

            if (node.features().supportsCommand(mscl.MipTypes.Command.CMD_EF_PITCH_ROLL_AID_CTRL))
            {
                Console.WriteLine("Pitch/Roll Aiding enabled?: " + (node.getPitchRollAid() ? "TRUE" : "FALSE"));
            }
        }

        public static void SetCurrentConfig(mscl.InertialNode node)
        {
            // Many other settings are available than shown below
            // Reference the documentation for the full list of commands

            // If the node supports AHRS/IMU
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_AHRS_IMU))
            {
                mscl.MipChannels ahrsImuChs = new mscl.MipChannels();
                ahrsImuChs.Add(new mscl.MipChannel(mscl.MipTypes.ChannelField.CH_FIELD_SENSOR_SCALED_ACCEL_VEC, mscl.SampleRate.Hertz(500)));
                ahrsImuChs.Add(new mscl.MipChannel(mscl.MipTypes.ChannelField.CH_FIELD_SENSOR_SCALED_GYRO_VEC, mscl.SampleRate.Hertz(100)));

                // Apply to the node
                node.setActiveChannelFields(mscl.MipTypes.DataClass.CLASS_AHRS_IMU, ahrsImuChs);
            }

            // If the node supports Estimation Filter
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_ESTFILTER))
            {
                mscl.MipChannels estFilterChs = new mscl.MipChannels();
                estFilterChs.Add(new mscl.MipChannel(mscl.MipTypes.ChannelField.CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS, mscl.SampleRate.Hertz(100)));

                // Apply to the node
                node.setActiveChannelFields(mscl.MipTypes.DataClass.CLASS_ESTFILTER, estFilterChs);
            }

            // If the node supports GNSS
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_GNSS))
            {
                mscl.MipChannels gnssChs = new mscl.MipChannels();
                gnssChs.Add(new mscl.MipChannel(mscl.MipTypes.ChannelField.CH_FIELD_GNSS_LLH_POSITION, mscl.SampleRate.Hertz(1)));

                // Apply to the node
                node.setActiveChannelFields(mscl.MipTypes.DataClass.CLASS_GNSS, gnssChs);
            }

            if (node.features().supportsCommand(mscl.MipTypes.Command.CMD_EF_ALTITUDE_AID_CTRL))
            {
                node.setAltitudeAid(false);
            }

            if (node.features().supportsCommand(mscl.MipTypes.Command.CMD_EF_ANTENNA_OFFSET))
            {
                mscl.PositionOffset offset = new mscl.PositionOffset(0.0f, 0.0f, 0.0f);
                node.setAntennaOffset(offset);
            }
            else if (node.features().supportsCommand(mscl.MipTypes.Command.CMD_EF_MULTI_ANTENNA_OFFSET))
            {
                mscl.PositionOffset offset = new mscl.PositionOffset(0.0f, 0.0f, 0.0f);

                foreach (mscl.GnssReceiverInfo gnssReceiverInfo in node.features().gnssReceiverInfo())
                {
                    node.setMultiAntennaOffset(gnssReceiverInfo.id, offset);
                }
            }

            if (node.features().supportsCommand(mscl.MipTypes.Command.CMD_EF_PITCH_ROLL_AID_CTRL))
            {
                node.setPitchRollAid(true);
            }
        }

        public static void StartSampling(mscl.InertialNode node)
        {
            // Each class/category is separated into its own command.
            // You can enable them individually if, say, you only want the Estimation Filter channels to be streamed

            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_AHRS_IMU))
            {
                node.enableDataStream(mscl.MipTypes.DataClass.CLASS_AHRS_IMU);
            }

            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_ESTFILTER))
            {
                node.enableDataStream(mscl.MipTypes.DataClass.CLASS_ESTFILTER);
            }

            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_GNSS))
            {
                node.enableDataStream(mscl.MipTypes.DataClass.CLASS_GNSS);
            }
        }

        // Example: Parse Data
        //  Shows how to parse incoming data from an Inertial Device.
        //  Note that this example does not start a Node sampling (assumes it already is).
        public static void ParseData(mscl.InertialNode node)
        {
            // Endless loop of reading in data
            while (true)
            {
                // Loop through all the data packets from the node, with a timeout of 500 milliseconds
                foreach (mscl.MipDataPacket packet in node.getDataPackets(500))
                {
                    // Print out the data
                    Console.Write("Packet Received: ");

                    // Loop through all the data points in the packet
                    foreach (mscl.MipDataPoint dataPoint in packet.data())
                    {
                        Console.Write(dataPoint.channelName() + ": ");

                        // Print out the channel data
                        // Note: The as_string() function is being used here for simplicity.
                        //      Other methods (i.e., as_float, as_uint16, as_Vector) are also available.
                        //      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                        Console.Write(dataPoint.as_string() + " ");

                        // If the dataPoint is invalid
                        if (!dataPoint.valid())
                        {
                            Console.Write("[Invalid] ");
                        }
                    }

                    Console.WriteLine();
                }
            }
        }
    }
}
