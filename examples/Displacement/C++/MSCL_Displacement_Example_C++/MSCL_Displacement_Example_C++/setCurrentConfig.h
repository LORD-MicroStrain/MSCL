#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Displacement/DisplacementNode.h>

static void setCurrentConfig(mscl::DisplacementNode& node)
{
    // Seed the device time with the current PC time
    // Note: you can pass your own time to this function as a
    //      parameter in nanoseconds since unix epoch
    node.setDeviceTime();
}
