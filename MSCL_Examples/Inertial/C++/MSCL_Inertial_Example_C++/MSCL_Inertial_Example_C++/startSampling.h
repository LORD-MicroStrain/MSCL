#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Inertial/InertialNode.h>

static void startSampling(mscl::InertialNode& node)
{
    // Each class/category is separated into its own command.
    // You can enable them individually if, say, you only want the Estimation Filter channels to be streamed

    if (node.features().supportsCategory(mscl::MipTypes::CLASS_AHRS_IMU))
    {
        node.enableDataStream(mscl::MipTypes::CLASS_AHRS_IMU);
    }

    if (node.features().supportsCategory(mscl::MipTypes::CLASS_ESTFILTER))
    {
        node.enableDataStream(mscl::MipTypes::CLASS_ESTFILTER);
    }

    if (node.features().supportsCategory(mscl::MipTypes::CLASS_GNSS))
    {
        node.enableDataStream(mscl::MipTypes::CLASS_GNSS);
    }
}
