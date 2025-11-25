#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Inertial/InertialNode.h>

static void setToIdle(mscl::InertialNode& node)
{
    node.setToIdle();

    // Note: you can also disable the datastream for each class/category
    //      separately if desired, by using the enableDataStream command shown in
    //      the startSampling example, but passing a second parameter of 'false'
}
