#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <mscl/MicroStrain/Wireless/WirelessNode.h>

static void getCurrentConfig(mscl::WirelessNode& node)
{
    printf("Current Configuration Settings\n");

    // Read some of the current configuration settings on the node
    printf("# of Triggers: %d\n", node.getNumDatalogSessions());
    printf("User Inactivity Timeout: %d seconds\n", node.getInactivityTimeout());
    printf("Total active channels: %d\n", node.getActiveChannels().count());
    printf("# of sweeps: %d\n", node.getNumSweeps());

    // If a configuration function requires a ChannelMask parameter, this indicates that the
    // option may affect 1 or more channels on the Node. For instance, a hardware gain may
    // affect ch1 and ch2 with just 1 setting. If you know the mask for your Node, you can provide
    // that mask when asking for the configuration. If you want to programmatically determine
    // the mask for each setting, you can ask for the Node's ChannelGroups. See below.

    // Get the ChannelGroups that the node supports
    const mscl::ChannelGroups chGroups = node.features().channelGroups();

    // Iterate over each channel group
    for (const mscl::ChannelGroup& group: chGroups)
    {
        // Get all the settings for this group (i.e., may contain linear equation and hardware gain).
        const mscl::WirelessTypes::ChannelGroupSettings groupSettings = group.settings();

        // Iterate over each setting for this group
        for (const mscl::WirelessTypes::ChannelGroupSetting& setting: groupSettings)
        {
            // If the group contains the linear equation setting
            if (setting == mscl::WirelessTypes::chSetting_linearEquation)
            {
                // We can now pass the channel mask (group.channels()) for this group to the node.getLinearEquation function.
                // Note: once this channel mask is known for a specific node (+ fw version), it should never change
                mscl::LinearEquation le = node.getLinearEquation(group.channels());

                printf("Linear Equation for: %s\n", group.name().c_str());
                printf("Slope: %000.03f\n", le.slope());
                printf("Offset: %000.03f\n", le.offset());
            }
        }
    }
}
