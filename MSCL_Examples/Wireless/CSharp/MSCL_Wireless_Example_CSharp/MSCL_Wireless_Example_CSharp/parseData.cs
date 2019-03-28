using System;

namespace MSCL_Wireless_Example_CSharp
{
    class Example6
    {
        public static void parseData(mscl.BaseStation baseStation)
        {
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

                        //print out the channel data
                        //Note: The as_string() function is being used here for simplicity. 
                        //      Other methods (ie. as_float, as_uint16, as_Vector) are also available.
                        //      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                        Console.Write(dataPoint.as_string() + " ");
                    }
                    Console.WriteLine();
                }
            }
        }
    }
}