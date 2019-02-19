using System;

//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

namespace MSCL_Displacement_Example_CSharp
{
    class Program
    {
        //TODO: change these constants to match your setup
        const string COM_PORT = "COM4";

        static void Main(string[] args)
        {
            try
            {
                //create a Serial Connection with the specified COM Port, default baud rate of 921600
                mscl.Connection connection = mscl.Connection.Serial(COM_PORT, 11500);

                //create a DisplacementNode with the connection
                mscl.DisplacementNode node = new mscl.DisplacementNode(connection);

                //TODO: Uncomment the lines below to run the examples

                //Example: Get Configuration
                //Example1.getCurrentConfig(node);

                //Example: Set Configuration
                //Example2.setCurrentConfig(node); //Warning: this example changes settings on your Node!

                //Example: Start Sampling
                //Example3.startSampling(node);

                //Example: Set to Idle
                //Example4.setToIdle(node);

                //Example: Parse Data
                //Example5.parseData(node);
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
