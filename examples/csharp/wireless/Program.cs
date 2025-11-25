using System;
using System.Collections.Generic;

//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

namespace MSCL_Wireless_Example_CSharp
{
    class Program
    {
        //TODO: change these constants to match your setup
        const string COM_PORT = "COM3";
        const int NODE_ADDRESS = 65364;

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

                //TODO: add as many other WirelessNode objects here as you want (used in the startSyncSampling example)
                List<mscl.WirelessNode> networkNodes = new List<mscl.WirelessNode>();
                networkNodes.Add(node);

                //due to the nature of wireless devices, it is possible to lose packets over the air.
                //MSCL has a built in way of performing retries whenever an eeprom address is attempted to be read.
                //By default, this value is set to 0. You may wish to keep it at 0 and handle retries yourself depending on your application.
                baseStation.readWriteRetries(3);
                node.readWriteRetries(3);

                //TODO: Uncomment the lines below to run the examples

                //Example: Ping Node
                //Example1.pingNode(node);

                //Example: Get Configuration
                //Example2.getCurrentConfig(node);

                //Example: Set Configuration
                //Example3.setCurrentConfig(node); //Warning: this example changes settings on your Node!

                //Example: Start Sampling
                //Example4.startSyncSampling(baseStation, networkNodes);

                //Example: Set to Idle
                //Example5.setToIdle(node);

                //Example: Parse Data
                //Example6.parseData(baseStation);

                //Example: Enable and Disable Beacon
                //Example7.enableDisableBeacon(baseStation);
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
