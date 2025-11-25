using System;

namespace MSCL_Displacement_Example_CSharp
{
    class Example5
    {
        public static void parseData(mscl.DisplacementNode node)
        {
            //endless loop of reading in data
            while (true)
            {
                //get all of the next data packet from the node, with a timeout of 500 milliseconds
                mscl.MipDataPackets packets = node.getDataPackets(500);

                foreach (mscl.MipDataPacket packet in packets)
                {
                    //print out the data
                    Console.Write("Packet Received: ");

                    //iterate over all the data points in the packet
                    foreach (mscl.MipDataPoint dataPoint in packet.data())
                    {
                        Console.Write(dataPoint.channelName() + ":");

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