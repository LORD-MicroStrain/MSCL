#pragma once

#include "mscl/mscl.h"

static void getCurrentConfig(mscl::WirelessNode& node)
{
    cout << "Current Configuration Settings" << endl;

    //read some of the current configuration settings on the node
    cout << "# of Triggers: " << node.getNumDatalogSessions() << endl;
    cout << "User Inactivity Timeout: " << node.getInactivityTimeout() << " seconds" << endl;
    cout << "Total active channels: " << static_cast<int>(node.getActiveChannels().count()) << endl;
    cout << "# of sweeps: " << node.getNumSweeps() << endl;

    //If a configuration function requires a ChannelMask parameter, this indicates that the
    //option may affect 1 or more channels on the Node. For instance, a hardware gain may
    //affect ch1 and ch2 with just 1 setting. If you know the mask for your Node, you can just provide
    //that mask when asking for the configuration. If you want to programatically determine
    //the mask for each setting, you can ask for the Node's ChannelGroups. See below.

    //get the ChannelGroups that the node supports
    mscl::ChannelGroups chGroups = node.features().channelGroups();

    //iterate over each channel group
    for(const auto& group : chGroups)
    {
        //get all of the settings for this group (ie. may contain linear equation and hardware gain).
        mscl::WirelessTypes::ChannelGroupSettings groupSettings = group.settings();

        //iterate over each setting for this group
        for(auto setting : groupSettings)
        {
            //if the group contains the linear equation setting
            if(setting == mscl::WirelessTypes::chSetting_linearEquation)
            {
                //we can now pass the channel mask (group.channels()) for this group to the node.getLinearEquation function.
                //Note: once this channel mask is known for a specific node (+ fw version), it should never change
                mscl::LinearEquation le = node.getLinearEquation(group.channels());

                cout << "Linear Equation for: " << group.name() << endl;
                cout << "Slope: " << le.slope() << endl;
                cout << "Offset: " << le.offset() << endl;
            }
        }
    }
}