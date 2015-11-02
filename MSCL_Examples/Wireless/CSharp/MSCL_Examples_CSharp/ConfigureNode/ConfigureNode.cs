//MSCL Example: ConfigureNode
//	This example shows how to get and set the configuration options for a Wireless Node.
//	Warning: Running this example will change the configuration on the Wireless Node.
//
//Updated: 11/02/2015

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

            //If a configuration function requires a ChannelMask parameter, this indicates that the
            //option may affect 1 or more channels on the Node. For instance, a hardware gain may
            //affect ch1 and ch2 with just 1 setting. If you know the mask for your Node, you can just provide
            //that mask when asking for the configuration. If you want to programatically determine
            //the mask for each setting, you can ask for the Node's ChannelGroups. See below.

            mscl.ChannelGroups chGroups = node.features().channelGroups();

            //iterate over each channel group
	        foreach(var group in chGroups)
	        {
		        //get all of the settings for this group (ie. may contain linear equation and hardware gain).
		        mscl.ChannelGroupSettings groupSettings = group.settings();

		        //iterate over each setting for this group
		        foreach(var setting in groupSettings)
		        {
			        //if the group contains the linear equation setting
			        if(setting == mscl.WirelessTypes.ChannelGroupSetting.chSetting_linearEquation)
			        {
				        //we can now pass the channel mask (group.channels()) for this group to the node.getLinearEquation function.
				        //Note: once this channel mask is known for a specific node (+ fw version), it should never change
				        mscl.LinearEquation le = node.getLinearEquation(group.channels());

				        Console.WriteLine("Linear Equation for: " + group.name());
				        Console.WriteLine("Slope: " + le.slope());
				        Console.WriteLine("Offset: " + le.offset());
			        }
		        }
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
            config.defaultMode(mscl.WirelessTypes.DefaultMode.defaultMode_idle);
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
