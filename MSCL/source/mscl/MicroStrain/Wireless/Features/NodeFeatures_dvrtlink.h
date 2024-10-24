/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_dvrtlink
    //    Contains information on features for the DVRT-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_dvrtlink : public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_dvrtlink(){};

        //Constructor: NodeFeatures_dvrtlink
        //    Creates a NodeFeatures_dvrtlink object.
        NodeFeatures_dvrtlink(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;
    };
}
