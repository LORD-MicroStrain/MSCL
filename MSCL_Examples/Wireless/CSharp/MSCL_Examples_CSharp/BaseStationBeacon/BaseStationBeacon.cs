//MSCL Example: BaseStationBeacon
//	This example shows how to Enable and Disable the 
//	beacon (used for Synchronized Sampling) on a BaseStation
//
//Updated: 10/01/2014

//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

using System;
using System.Threading;

namespace BaseStationBeacon
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

                //make sure we can ping the base station
                if (!baseStation.ping())
                {
                    Console.WriteLine("Failed to ping the Base Station");
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
            catch (mscl.Error e)
            {
                Console.WriteLine("Error: " + e.Message);
            }

            Console.WriteLine("Press Enter to quit...");
            Console.Read();
        }
    }
}
