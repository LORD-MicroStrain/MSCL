/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "InertialNodeFeatures.h"

namespace mscl
{
    //Class: InertialNodeFeatures_fasA
    //    Contains information on features for the FAS-A Node. Inherits from <InertialNodeFeatures>.
    class InertialNodeFeatures_fasA: public InertialNodeFeatures
    {
    public:
        virtual ~InertialNodeFeatures_fasA() {};

        //Constructor: InertialNodeFeatures_fasA
        //    Creates a InertialNodeFeatures_fasA object.
        InertialNodeFeatures_fasA(const InertialNodeInfo& info);
    };
}