using System;

namespace MSCL_Wireless_Example_CSharp
{
    class Example3
    {
        public static void setCurrentConfig(mscl.WirelessNode node)
        {
            //many other settings are available than shown below
            //reference the documentation for the full list of commands

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
            //  Note that this step is not required before applying, however the apply will throw an
            //  Error_InvalidNodeConfig exception if the config fails to verify.
            mscl.ConfigIssues issues = new mscl.ConfigIssues();
            if (!node.verifyConfig(config, issues))
            {
                Console.WriteLine("Failed to verify the configuration. The following issues were found:");

                //print out all of the issues that were found
                foreach (var issue in issues)
                {
                    Console.WriteLine(issue.description());
                }

                Console.WriteLine("Configuration will not be applied.");
            }
            else
            {
                //apply the configuration to the Node
                //  Note that if this writes multiple options to the Node.
                //  If an Error_NodeCommunication exception is thrown, it is possible that
                //  some options were successfully applied, while others failed. 
                //  It is recommended to keep calling applyConfig until no exception is thrown.
                node.applyConfig(config);
            }

            Console.WriteLine("Done.");
        }
    }
}