//MSCL Example: StopNode
//	This example shows how to "stop" a Wireless Node, taking the Node
//	out of its sampling or sleeping mode and putting it into its
//	idle state so that it can be communicated with. 
//	Note: Stopping a Node may take up to a maximum of 2 minutes.
//
//Updated: 11/02/2015


//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

using System;

namespace StopNode
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

                //call the set to idle function and get the resulting SetToIdleStatus object
                mscl.SetToIdleStatus status = node.setToIdle();

                Console.Write("Setting Node to Idle");

                //using the SetToIdleStatus object, check if the Set to Idle operation is complete.
                //	Note: we are specifying a timeout of 300 milliseconds here which is the maximum
                //		  amount of time that the complete function will block if the Set to Idle
                //		  operation has not finished. Leaving this blank defaults to a timeout of 10ms.
                while (!status.complete(300))
                {
                    //Note: the Set to Idle operation can be canceled by calling status.cancel()
                    Console.Write(".");
                }

                //at this point, the Set to Idle operation has completed

                //check the result of the Set to Idle operation
                switch (status.result())
                {
                    //completed successfully
                    case mscl.SetToIdleStatus.SetToIdleResult.setToIdleResult_success:
                        Console.WriteLine("Successfully set to idle!");
                        break;

                    //canceled by the user
                    case mscl.SetToIdleStatus.SetToIdleResult.setToIdleResult_canceled:
                        Console.WriteLine("Set to Idle was canceled!");
                        break;

                    //Failed to perform the operation
                    case mscl.SetToIdleStatus.SetToIdleResult.setToIdleResult_failed:
                    default:
                        Console.WriteLine("Set to Idle has failed!");
                        break;
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
