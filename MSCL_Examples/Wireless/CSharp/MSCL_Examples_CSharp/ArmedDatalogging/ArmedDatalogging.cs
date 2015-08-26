//MSCL Example: SynchronizedSampling
//   This example shows how to create and start an Armed Datalogging sampling network.
//
//Updated: 09/30/2014

//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

using System;

namespace ArmedDatalogging
{
    class ArmedDatalogging
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

                //create an ArmedDataloggingNetwork object, giving it the BaseStation that will be the master BaseStation for the network
                mscl.ArmedDataloggingNetwork network = new mscl.ArmedDataloggingNetwork(baseStation);

                //add a WirelessNode to the network
                //	Note: The Node must already be configured for Armed Datalogging before adding to the network, or else Error_InvalidConfig will be thrown.
                //TODO: Repeat this for all WirelessNodes that you want in the network
                Console.Write("Adding node to the network...");
                network.addNode(node, "This is an optional <50-char message.");
                Console.WriteLine("Done.");

                //start all the nodes in the network sampling.
                Console.Write("Starting the network...");
                network.startSampling();
                Console.WriteLine("Done.");
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
