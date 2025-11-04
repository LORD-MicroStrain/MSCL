using System;

namespace MSCL_Wireless_Example_CSharp
{
    class Example2
    {
        public static void getCurrentConfig(mscl.WirelessNode node)
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
            foreach (var group in chGroups)
            {
                //get all of the settings for this group (ie. may contain linear equation and hardware gain).
                mscl.ChannelGroupSettings groupSettings = group.settings();

                //iterate over each setting for this group
                foreach (var setting in groupSettings)
                {
                    //if the group contains the linear equation setting
                    if (setting == mscl.WirelessTypes.ChannelGroupSetting.chSetting_linearEquation)
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
    }
}