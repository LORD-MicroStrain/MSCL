#pragma once

#include "mscl/mscl.h"

//Example: Get Current Configuration
//  Shows how to read current configuration settings a Displacement Device.
static void getCurrentConfig(mscl::DisplacementNode& node)
{
    mscl::LinearEquation cals = node.getAnalogToDisplacementCal();

    cout << "Analog to Displacement Cal: " << "Slope: " << cals.slope() << " Offset: " << cals.offset() << endl;

    cout << "Output Data Rate: " << node.getDisplacementOutputDataRate().prettyStr() << endl;
}