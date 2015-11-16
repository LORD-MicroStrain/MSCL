/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "InertialNodeFeatures.h"

namespace mscl
{
    //Class: InertialNodeFeatures_3dm_gx4_25
    //    Contains information on features for the 3DM-GX4-25 Node. Inherits from <InertialNodeFeatures>.
    class InertialNodeFeatures_3dm_gx4_25: public InertialNodeFeatures
    {
    public:
        virtual ~InertialNodeFeatures_3dm_gx4_25() {};

        //Constructor: InertialNodeFeatures_3dm_gx4_25
        //    Creates a InertialNodeFeatures_3dm_gx4_25 object.
        InertialNodeFeatures_3dm_gx4_25(const InertialNodeInfo& info);
    };
}