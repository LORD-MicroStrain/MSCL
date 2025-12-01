using System;

// Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  - Both MSCL_Managed.dll and MSCL.dll need to be in the same directory as the executable
//  -'MSCL.dll' needs to be copied into the executable directory manually in most cases

namespace MSCL_CSharp_Displacement_Example
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

                // Create a DisplacementNode with the connection
                mscl.DisplacementNode node = new mscl.DisplacementNode(connection);

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

        public static void SetToIdle(mscl.DisplacementNode node)
        {
            node.setToIdle();
        }

        // Example: Get Current Configuration
        //  Shows how to read current configuration settings a Displacement Device.
        public static void GetCurrentConfig(mscl.DisplacementNode node)
        {
            mscl.LinearEquation cals = node.getAnalogToDisplacementCal();

            Console.WriteLine("Analog to Displacement Cal: Slope: " + cals.slope().ToString("F3") + " Offset: " + cals.offset().ToString("F3"));
            Console.WriteLine("Output Data Rate: " + node.getDisplacementOutputDataRate().prettyStr());
        }

        public static void SetCurrentConfig(mscl.DisplacementNode node)
        {
            // Seed the device time with the current PC time
            // Note: you can pass your own time to this function as a
            //      parameter in nanoseconds since unix epoch
            node.setDeviceTime();
        }

        public static void StartSampling(mscl.DisplacementNode node)
        {
            node.resume();
        }

        // Example: Parse Data
        //  Shows how to parse incoming data from a Displacement Device.
        //  Note that this example does not start a Node sampling (assumes it already is).
        public static void ParseData(mscl.DisplacementNode node)
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
                        Console.Write(dataPoint.channelName() + ":");

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
