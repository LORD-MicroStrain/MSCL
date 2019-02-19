using System;
using System.Threading;

namespace MSCL_Wireless_Example_CSharp
{
    class Example7
    {
        public static void enableDisableBeacon(mscl.BaseStation baseStation)
        {
            //make sure we can ping the base station
            if (!baseStation.ping())
            {
                Console.WriteLine("Failed to ping the Base Station");
            }

            if (baseStation.features().supportsBeaconStatus())
            {
                mscl.BeaconStatus status = baseStation.beaconStatus();
                Console.WriteLine("Beacon current status: Enabled?: " + status.enabled().ToString() + " Time: " + status.timestamp());
            }

            Console.WriteLine("Attempting to enable the beacon...");

            //enable the beacon on the Base Station using the PC time
            mscl.Timestamp beaconTime = baseStation.enableBeacon();

            //if we got here, no exception was thrown, so enableBeacon was successful
            Console.WriteLine("Successfully enabled the beacon on the Base Station");
            Console.WriteLine("Beacon's initial Timestamp: " + beaconTime.ToString());

            Console.WriteLine("Beacon is active");
            Console.WriteLine("Sleeping for 3 seconds...");
            Thread.Sleep(3000);

            //disable the beacon on the Base Station
            baseStation.disableBeacon();

            //if we got here, no exception was thrown, so disableBeacon was successful
            Console.WriteLine("Successfully disabled the beacon on the Base Station");
        }
    }
}