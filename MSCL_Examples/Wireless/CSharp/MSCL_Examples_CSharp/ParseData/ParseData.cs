//MSCL Example: ParseData
//	This example shows how to parse incoming data from a Wireless Node.
//	This example does not start a Node sampling. To receive data, a Node
//	must be put into a sampling mode (Sync Sampling, Low Duty Cycle, etc.)
//
//Updated: 11/02/2015

//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

using System;

namespace ParseData
{
    class Program
    {
        //TODO: change these constants to match your setup
        const String COM_PORT = "COM3";

        static void Main(string[] args)
        {
            try
            {
                //create a Serial Connection with the specified COM Port, default baud rate of 921600
                mscl.Connection connection = mscl.Connection.Serial(COM_PORT);

                //create a BaseStation with the connection
                mscl.BaseStation baseStation = new mscl.BaseStation(connection);

                //endless loop of reading in data
                while (true)
                {
                    //get all of the data sweeps that have been collected by the BaseStation, with a timeout of 500 milliseconds
                    mscl.DataSweeps sweeps = baseStation.getData(500);

                    foreach (mscl.DataSweep sweep in sweeps)
                    {
                        //print out information about the sweep
                        Console.Write("Packet Received: ");
                        Console.Write("Node " + sweep.nodeAddress() + " ");
                        Console.Write("Timestamp: " + sweep.timestamp().ToString() + " ");
                        Console.Write("Tick: " + sweep.tick() + " ");
                        Console.Write("Sample Rate: " + sweep.sampleRate().prettyStr() + " ");
                        Console.Write("Base RSSI: " + sweep.baseRssi() + " ");
                        Console.Write("Node RSSI: " + sweep.nodeRssi() + " ");

                        //get the container of data in the sweep
                        mscl.ChannelData data = sweep.data();

                        Console.Write("DATA: ");
                        //iterate over each point in the sweep
                        foreach (mscl.WirelessDataPoint dataPoint in data)
                        {
                            //print out the channel name
                            Console.Write(dataPoint.channelName() + ": ");

                            //Print out the channel data as a string. Other methods (ie. as_float, as_uint16) are also available.
                            //Note: The storedAs() function describes how the data is actually stored
                            Console.Write(dataPoint.as_string() + " ");
                        }
                        Console.WriteLine();
                    }
                }
            }
            catch (mscl.Error e)
            {
                Console.WriteLine("Error: " + e);
            }

            Console.WriteLine("Press Enter to quit...");
            Console.Read();
        }
    }
}
