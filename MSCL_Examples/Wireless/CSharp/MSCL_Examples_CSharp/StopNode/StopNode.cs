//MSCL Example: StopNode
//	This example shows how to "stop" a Wireless Node, taking the Node
//	out of its sampling or sleeping mode and putting it into its
//	idle state so that it can be communicated with. 
//	Note: Stopping a Node may take up to a maximum of 2 minutes.
//
//Updated: 09/15/2014


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

                //call the stop function and get the resulting StopNodeStatus object
                mscl.StopNodeStatus stopStatus = node.stop();

                Console.Write("Stopping Node");

                //using the StopNodeStatus object, check if the Stop Node operation is complete.
                //	Note: we are specifying a timeout of 300 milliseconds here which is the maximum
                //		  amount of time that the complete function will block if the Stop Node
                //		  operation has not finished. Leaving this blank defaults to a timeout of 10ms.
                while (!stopStatus.complete(300))
                {
                    //Note: the Stop Node operation can be canceled by calling stopStatus.cancel()
                    Console.Write(".");
                }

                //at this point, the Stop Node operation has completed

                //check the result of the Stop Node operation
                switch (stopStatus.result())
                {
                    //Stop Node completed successfully
                    case mscl.StopNodeStatus.StopNodeResult.stopNodeResult_success:
                        Console.WriteLine("Successfully stopped the Node!");
                        break;

                    //Stop Node has been canceled by the user
                    case mscl.StopNodeStatus.StopNodeResult.stopNodeResult_canceled:
                        Console.WriteLine("Stop Node was canceled!");
                        break;

                    //Failed to perform the Stop Node operation
                    case mscl.StopNodeStatus.StopNodeResult.stopNodeResult_failed:
                    default:
                        Console.WriteLine("Stop Node has failed!");
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
