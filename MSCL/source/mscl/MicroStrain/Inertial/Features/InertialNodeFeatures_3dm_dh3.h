/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "InertialNodeFeatures.h"

namespace mscl
{
    //Class: InertialNodeFeatures_3dm_dh3
    //    Contains information on features for the 3DM-DH3 Node. Inherits from <InertialNodeFeatures>.
    class InertialNodeFeatures_3dm_dh3: public InertialNodeFeatures
    {
    public:
        virtual ~InertialNodeFeatures_3dm_dh3() {};

        //Constructor: InertialNodeFeatures_3dm_dh3
        //    Creates a InertialNodeFeatures_3dm_dh3 object.
        InertialNodeFeatures_3dm_dh3(const InertialNodeInfo& info);
    };
}