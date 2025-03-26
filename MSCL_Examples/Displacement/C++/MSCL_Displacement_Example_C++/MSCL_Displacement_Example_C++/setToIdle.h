#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Displacement/DisplacementNode.h>

static void setToIdle(mscl::DisplacementNode& node)
{
    node.setToIdle();
}
