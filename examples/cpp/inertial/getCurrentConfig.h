#pragma once

// MSCL common code header (used as precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Inertial/InertialNode.h>
#include <mscl/MicroStrain/MIP/MipNodeFeatures.h>

// Example: Get Current Configuration
//  Shows how to read current configuration settings an Inertial Device.
static void getCurrentConfig(mscl::InertialNode& node)
{
    // Many other settings are available than shown below
    // Reference the documentation for the full list of commands

    // If the node supports AHRS/IMU
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_AHRS_IMU))
    {
        // Get a list of the AHRS/IMU channels currently active on the Node
        const mscl::MipChannels ahrsImuActiveChs = node.getActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU);

        printf("AHRS/IMU Channels\n");
        printf("-----------------\n");

        for (const mscl::MipChannel& channel : ahrsImuActiveChs)
        {
            printf("Channel Field: 0x%04X\n", channel.channelField());
            printf("Sample Rate: %s\n\n", channel.sampleRate().prettyStr().c_str());
        }
    }

    // If the node supports Estimation Filter
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_ESTFILTER))
    {
        // Get a list of the Estimation Filter channels currently active on the Node
        const mscl::MipChannels estFilterActiveChs = node.getActiveChannelFields(mscl::MipTypes::CLASS_ESTFILTER);

        printf("\nEstimation Filter Channels\n");
        printf("--------------------------\n");

        for (const mscl::MipChannel& channel : estFilterActiveChs)
        {
            printf("Channel Field: 0x%04X\n", channel.channelField());
            printf("Sample Rate: %s\n\n", channel.sampleRate().prettyStr().c_str());
        }
    }

    // If the node supports GNSS
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_GNSS))
    {
        // Get a list of the GNSS channels currently active on the Node
        const mscl::MipChannels gnssActiveChs = node.getActiveChannelFields(mscl::MipTypes::CLASS_GNSS);

        printf("\nGNSS Channels\n");
        printf("-------------\n");

        for (const mscl::MipChannel& channel : gnssActiveChs)
        {
            printf("Channel Field: 0x%04X\n", channel.channelField());
            printf("Sample Rate: %s\n\n", channel.sampleRate().prettyStr().c_str());
        }
    }

    printf("Altitude Aiding enabled?: %s\n", node.getAltitudeAid() ? "TRUE" : "FALSE");

    const mscl::PositionOffset offset = node.getAntennaOffset();
    printf("Antenna Offset: X = %000.03f Y = %000.03f Z = %000.03f\n", offset.x(), offset.y(), offset.z());

    printf("Pitch/Roll Aiding enabled?: %s\n", node.getPitchRollAid() ? "TRUE" : "FALSE");
}
