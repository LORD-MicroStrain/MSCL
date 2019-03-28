#pragma once

#include "mscl/mscl.h"

static void startSampling(mscl::DisplacementNode& node)
{
    node.resume();
}