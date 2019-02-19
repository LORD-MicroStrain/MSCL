#pragma once

#include "mscl/mscl.h"

static void setToIdle(mscl::InertialNode& node)
{
    node.setToIdle();

    //Note: you can also disable the datastream for each class/category
    //      seperately if desired, by using the enableDataStream command shown in
    //      the startSampling example, but passing a second parameter of 'false'
}