//MSCL Example: SynchronizedSampling
//   This example shows how to create and start a Synchronized Sampling network.
//
//Updated: 05/16/2017

//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

using System;

namespace SynchronizedSampling
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

                //create a SyncSamplingNetwork object, giving it the BaseStation that will be the master BaseStation for the network
                mscl.SyncSamplingNetwork network = new mscl.SyncSamplingNetwork(baseStation);

                //add a WirelessNode to the network
                //	Note: The Node must already be configured for Sync Sampling before adding to the network, or else Error_InvalidConfig will be thrown.
                //TODO: Repeat this for all WirelessNodes that you want in the network
                Console.Write("Adding node to the network...");
                network.addNode(node);
                Console.WriteLine("Done.");

                //can get information about the network
                Console.WriteLine("Network info: ");
                Console.WriteLine("Network OK: " + network.ok().ToString());
                Console.WriteLine("Percent of Bandwidth: " + network.percentBandwidth().ToString() + "%");
                Console.WriteLine("Lossless Enabled: " + network.lossless().ToString());

                //apply the network configuration to every node in the network
                Console.Write("Applying network configuration...");
                network.applyConfiguration();
                Console.WriteLine("Done.");

                //start all the nodes in the network sampling. The master BaseStation's beacon will be enabled with the system time.
                //	Note: if you wish to provide your own start time (not use the system time), pass a mscl::Timestamp object as a second parameter to this function.
                //	Note: if you do not want to enable a beacon at this time, use the startSampling_noBeacon() function. (A beacon is required for the nodes to actually start sending data).
                Console.Write("Starting the network...");
                network.startSampling();
                Console.WriteLine("Done.");

                //=======================================================================================
                //Many other functions are available for the SyncSamplingNetwork:
                //
                //network.lossless()			//enable or disable "lossless" mode for the network (default of enabled).
                //network.ok()					//check whether or not the network is "OK" meaning all nodes fit in the network and have communicated successfully.
                //network.percentBandwidth()	//get the percent of bandwidth for the entire network.
                //network.refresh()				//refreshes the entire network. Should be called any time a change is made to the node after it has been added to the network.
                //network.removeNode()			//remove a node from the network.
                //network.getNodeNetworkInfo()	//get network information for an individual node in the network (TDMA address, percent bandwidth, etc.)
                //=======================================================================================
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
