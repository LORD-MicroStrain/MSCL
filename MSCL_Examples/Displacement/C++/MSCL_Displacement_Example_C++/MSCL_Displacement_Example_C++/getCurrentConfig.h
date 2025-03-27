#pragma once

// MSCL common code header (used as precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Displacement/DisplacementNode.h>
#include <mscl/MicroStrain/LinearEquation.h>

// Example: Get Current Configuration
//  Shows how to read current configuration settings a Displacement Device.
static void getCurrentConfig(mscl::DisplacementNode& node)
{
    mscl::LinearEquation cals = node.getAnalogToDisplacementCal();

    printf("Analog to Displacement Cal: Slope: %000.03f Offset: %000.03f\n", cals.slope(), cals.offset());
    printf("Output Data Rate: %s\n", node.getDisplacementOutputDataRate().prettyStr().c_str());
}
