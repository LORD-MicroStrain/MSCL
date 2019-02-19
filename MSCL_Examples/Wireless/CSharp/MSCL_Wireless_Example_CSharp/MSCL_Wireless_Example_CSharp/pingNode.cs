using System;

namespace MSCL_Wireless_Example_CSharp
{
    class Example1
    {
        public static void pingNode(mscl.WirelessNode node)
        {
            mscl.PingResponse response = node.ping();

            if (response.success())
            {
                //get some details from the response
                Console.WriteLine("Successfully pinged Node " + node.nodeAddress());
                Console.WriteLine("Base Station RSSI: " + response.baseRssi());
                Console.WriteLine("Node RSSI: " + response.nodeRssi());

                //we can talk to the Node, so let's get some more info
                Console.WriteLine("Node Information: ");
                Console.WriteLine("Model Number: " + node.model());
                Console.WriteLine("Serial: " + node.serial());
                Console.WriteLine("Firmware: " + node.firmwareVersion());
            }
            else
            {
                //Note: In order to communicate with a Wireless Node, all of the following must be true:
                //  - The Node is powered on, and within range of the BaseStation
                //  - The Node is on the same frequency as the BaseStation
                //  - The Node is in Idle Mode (not sampling, and not sleeping)
                //  - The Node is on the same communication protocol as the BaseStation (LXRS vs LXRS+)
                Console.WriteLine("Failed to ping Node " + node.nodeAddress() + ".");
            }
        }
    }
}