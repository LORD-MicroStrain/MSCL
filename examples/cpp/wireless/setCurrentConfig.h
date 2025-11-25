#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h>
#include <mscl/MicroStrain/Wireless/WirelessNode.h>

static void setCurrentConfig(mscl::WirelessNode& node)
{
    // Just changing a small subset of settings for this example.
    // More settings are available. Please reference the documentation for the full list of functions.

    printf("\nChanging configuration settings...");

    // Create a WirelessNodeConfig which is used to set all node configuration options
    mscl::WirelessNodeConfig config;

    // Set the configuration options that we want to change
    config.defaultMode(mscl::WirelessTypes::defaultMode_idle);
    config.inactivityTimeout(7200);
    config.samplingMode(mscl::WirelessTypes::samplingMode_sync);
    config.sampleRate(mscl::WirelessTypes::sampleRate_256Hz);
    config.unlimitedDuration(true);

    // Attempt to verify the configuration with the Node we want to apply it to
    //  Note that this step is not required before applying; however, the apply will throw an
    //  Error_InvalidNodeConfig exception if the config fails to verify.
    mscl::ConfigIssues issues;

    if (!node.verifyConfig(config, issues))
    {
        printf("Failed to verify the configuration. The following issues were found:\n");

        // Print out all the issues that were found
        for (const mscl::ConfigIssue& issue : issues)
        {
            printf("%s\n", issue.description().c_str());
        }

        printf("Configuration will not be applied.\n");
    }
    else
    {
        // Apply the configuration to the Node
        //  Note that this writes multiple options to the Node.
        //  If an Error_NodeCommunication exception is thrown, it is possible that
        //  some options were successfully applied, while others failed.
        //  It is recommended to keep calling applyConfig until no exception is thrown.
        node.applyConfig(config);
    }

    printf("Done.\n");
}
