//MSCL Example: ConfigureNode
//	This example shows how to get and set the configuration options for a Wireless Node.
//	Warning: Running this example will change the configuration on the Wireless Node.
//
//Updated: 04/01/2015

//Note: If you are having 'PINVOKE' errors, please make sure the following is true:
//  -'MSCL_Managed' is added as a Refence for the project (add 'MSCL_Managed.dll')
//  -'MSCL.dll' is sitting next to the executable
//  -Your 'Platform Target' is set to x86

using System;

namespace ConfigureNode
{
    class Program
    {
        //TODO: change these constants to match your setup
        const String COM_PORT = "COM3";
        const int NODE_ADDRESS = 31849;


        //Function: getCurrentConfig
        //	This function demonstrates how to obtain the current configuration
        //	settings of a Wireless Node with MSCL.
        //
        //	Note:	More settings are available than are demoed here. 
        //			Reference the documentation for the full list of functions.
        static void getCurrentConfig(ref mscl.WirelessNode node)
        {
            Console.WriteLine("Current Configuration Settings");

	        //read some of the current node configuration settings
	        Console.WriteLine("# of Triggers: " + node.getNumDatalogSessions());
	        Console.WriteLine("User Inactivity Timeout: " + node.getInactivityTimeout() + " seconds");
            Console.WriteLine("Total active channels: " + node.getActiveChannels().count());
            Console.WriteLine("# of sweeps: " + node.getNumSweeps());

            //get a list of the supported channels
            mscl.WirelessChannels supportedChannels = node.channels();

            //loop through all of the channels
            foreach(var channel in supportedChannels)
            {
                //print out some information about the channels
                Console.WriteLine("Channel #: " + channel.Key);
                Console.WriteLine("Slope: " + channel.Value.getLinearEquation().slope());
                Console.WriteLine("Offset: " + channel.Value.getLinearEquation().offset());
            }
        }

        //Function: setCurrentConfig
        //	This function demonstrates how to change the configuration
        //	settings of a Wireless Node with MSCL.
        //
        //	Note:	More settings are available than are demoed here. 
        //			Reference the documentation for the full list of functions.
        static void setCurrentConfig(ref mscl.WirelessNode node)
        {
            Console.WriteLine("Changing configuration settings.");

            //create a WirelessNodeConfig which is used to set all node configuration options
            mscl.WirelessNodeConfig config = new mscl.WirelessNodeConfig();

            //set some of the node's configuration options
            config.bootMode(mscl.WirelessTypes.BootMode.bootMode_normal);
            config.inactivityTimeout(7200);
	        config.samplingMode(mscl.WirelessTypes.SamplingMode.samplingMode_sync);
	        config.sampleRate(mscl.WirelessTypes.WirelessSampleRate.sampleRate_256Hz);
	        config.unlimitedDuration(true);

            //attempt to verify the configuration with the Node we want to apply it to
            //	Note that this step is not required before applying, however the apply will throw an
            //	Error_InvalidNodeConfig exception if the config fails to verify.
            mscl.ConfigIssues issues = new mscl.ConfigIssues();
	        if(!node.verifyConfig(config, issues))
	        {
		        Console.WriteLine("Failed to verify the configuration. The following issues were found:");

		        //print out all of the issues that were found
		        foreach(var issue in issues)
		        {
			        Console.WriteLine(issue.description());
		        }

		        Console.WriteLine("Configuration will not be applied.");
	        }
            else
            {
                //apply the configuration to the Node
                //	Note that if this writes multiple options to the Node.
                //	If an Error_NodeCommunication exception is thrown, it is possible that
                //	some options were successfully applied, while others failed. 
                //	It is recommended to keep calling applyConfig until no exception is thrown.
                node.applyConfig(config);
            }

            Console.WriteLine("Done.");
        }

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

                //run the example showing how to retrieve the Node's current configuration
                getCurrentConfig(ref node);

                //run the example showing how to update/change the Node's current configuration
                setCurrentConfig(ref node);
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
