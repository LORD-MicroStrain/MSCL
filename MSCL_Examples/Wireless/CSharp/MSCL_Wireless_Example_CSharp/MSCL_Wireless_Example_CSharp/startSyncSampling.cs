using System;
using System.Collections.Generic;

namespace MSCL_Wireless_Example_CSharp
{
    class Example4
    {
        public static void startSyncSampling(mscl.BaseStation baseStation, List<mscl.WirelessNode> nodes)
        {
            //create a SyncSamplingNetwork object, giving it the BaseStation that will be the master BaseStation for the network
            mscl.SyncSamplingNetwork network = new mscl.SyncSamplingNetwork(baseStation);

            //add a WirelessNode to the network
            //Note: The Node must already be configured for Sync Sampling before adding to the network, or else Error_InvalidConfig will be thrown.
            foreach(mscl.WirelessNode node in nodes)
            {
                Console.Write("Adding node to the network...");
                network.addNode(node);
                Console.WriteLine("Done.");
            }

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
            //  Note: if you wish to provide your own start time (not use the system time), pass a mscl::Timestamp object as a second parameter to this function.
            //  Note: if you do not want to enable a beacon at this time, use the startSampling_noBeacon() function. (A beacon is required for the nodes to actually start sending data).
            Console.Write("Starting the network...");
            network.startSampling();
            Console.WriteLine("Done.");

            //=======================================================================================
            //Many other functions are available for the SyncSamplingNetwork:
            //
            //network.lossless()                        //enable or disable "lossless" mode for the network (default of enabled).
            //network.ok()                              //check whether or not the network is "OK" meaning all nodes fit in the network and have communicated successfully.
            //network.percentBandwidth()                //get the percent of bandwidth for the entire network.
            //network.refresh()                         //refreshes the entire network. Should be called any time a change is made to the node after it has been added to the network.
            //network.removeNode()                      //remove a node from the network.
            //network.getNodeNetworkInfo(nodeAddress)   //get network information for an individual node in the network (TDMA address, percent bandwidth, etc.)
            //=======================================================================================
        }
    }
}