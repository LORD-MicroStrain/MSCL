/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkoemHermetic
    //    Contains information on features for the SG-Link-OEM node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkoemHermetic : public NodeFeatures
    {
        NodeFeatures_sglinkoemHermetic();    //disabled default constructor

    public:
        ~NodeFeatures_sglinkoemHermetic() override = default;

        //Constructor: NodeFeatures_sglinkoemHermetic
        //    Creates a NodeFeatures_sglinkoemHermetic object.
        NodeFeatures_sglinkoemHermetic(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        bool supportsSensorDelayAlwaysOn() const override;
    };
} // namespace mscl
