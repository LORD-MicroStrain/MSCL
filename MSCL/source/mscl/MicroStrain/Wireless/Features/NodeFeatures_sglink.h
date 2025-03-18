/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglink
    //    Contains information on features for the SG-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglink : public NodeFeatures
    {
        NodeFeatures_sglink();    //disabled default constructor

    public:
        ~NodeFeatures_sglink() override = default;

        //Constructor: NodeFeatures_sglink
        //    Creates a NodeFeatures_sglink object.
        NodeFeatures_sglink(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        const uint32 minSensorDelay() const override;

        const uint32 maxSensorDelay() const override;

        const uint32 defaultSensorDelay() const override;
    };
}
