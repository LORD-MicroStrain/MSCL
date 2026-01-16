/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkrgd
    //    Contains information on features for the SG-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkrgd : public NodeFeatures
    {
        NodeFeatures_sglinkrgd();    //disabled default constructor

    public:
        ~NodeFeatures_sglinkrgd() override = default;

        //Constructor: NodeFeatures_sglinkrgd
        //    Creates a NodeFeatures_sglinkrgd object.
        NodeFeatures_sglinkrgd(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        bool supportsSensorDelayAlwaysOn() const override;
    };
} // namespace mscl
