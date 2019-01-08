//MSCL Example: NodePing
//   This examples shows how to open a connection with a BaseStation,
//   ping a Node, and get the result and its information.
//
//Updated: 09/15/2014

//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

using System;

namespace NodePing
{
    class Program
    {
        //TODO: change these constants to match your setup
        const String COM_PORT = "COM3";
        const int NODE_ADDRESS = 31849;

        static void Main(string[] args)
        {
            try
            {
                //create a Serial Connection with the specified COM Port, default baud rate of 921600
                mscl.Connection connection = mscl.Connection.Serial(COM_PORT);

                //create a BaseStation with the connection
                mscl.BaseStation baseStation = new mscl.BaseStation(connection);

                //create a WirelessNode with the BaseStation we created
                mscl.WirelessNode node = new mscl.WirelessNode(NODE_ADDRESS, baseStation);

                Console.WriteLine("Attempting to ping the Node...");

                //ping the Node
                mscl.PingResponse response = node.ping();

                //if the ping response was a success
                if (response.success())
                {
                    Console.WriteLine("Successfully pinged Node " + NODE_ADDRESS);
                    Console.WriteLine("Base Station RSSI: " + response.baseRssi());
                    Console.WriteLine("Node RSSI: " + response.nodeRssi());
                }
                else
                {
                    Console.WriteLine("Failed to ping Node " + NODE_ADDRESS);
                }
            }
            catch (mscl.Error e)
            {
                Console.WriteLine("Error: " + e.Message);
            }

            Console.WriteLine("Press Enter to quit...");
            Console.Read();
        }
    }
}
