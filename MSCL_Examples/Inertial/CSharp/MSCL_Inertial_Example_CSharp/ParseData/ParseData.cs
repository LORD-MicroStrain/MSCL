//MSCL Example: ParseData
//  This example shows how to parse incoming data from an Inertial Device.
//  This example does not start a Node sampling. To receive data, a Node
//  must be put into a sampling mode.
//
//Updated: 01/06/2015

//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

using System;

namespace ParseData
{
    class Program
    {
        //TODO: change these constants to match your setup
        const String COM_PORT = "COM15";

        static void Main(string[] args)
        {
            try
            {
                //create a Serial Connection with the specified COM Port, default baud rate of 921600
                mscl.Connection connection = mscl.Connection.Serial(COM_PORT);

                //create an InertialNode with the connection
                mscl.InertialNode node = new mscl.InertialNode(connection);

                //endless loop of reading in data
                while (true)
                {
                    try
                    {
                        //This example uses the "getNextDataPacket()" command. This command gets the next InertialDataPacket in the buffer and throws an exception if no data exists.
                        //Alternatively, you may use the "getDataPackets()" command to get ALL the InertialDataPackets available in the buffer. If the returned container is empty, no data exists.
                    
                        //get the next data packet from the node, with a timeout of 500 milliseconds
                        mscl.InertialDataPacket packet = node.getNextDataPacket(500);

                        //print out the data
                        Console.Write("Packet Received: ");
                        
                        //iterate over all the data points in the packet
                        foreach (mscl.InertialDataPoint dataPoint in packet.data())
                        {
                            //print out the channel data
                            Console.Write(dataPoint.ToString() + ": ");
                            Console.Write(dataPoint.as_string() + " "); //Just printing this out as a string. Other methods (ie. as_float, as_uint16, as_Vector) are also available.

                            //if the dataPoint is invalid
                            if (!dataPoint.valid())
                            {
                                //print out that it is invalid
                                Console.Write("[Invalid] ");
                            }
                        }
                        Console.WriteLine();
                    }
                    catch (mscl.Error_NoData noData)
                    {
                        Console.WriteLine(noData.Message);
                    }
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
