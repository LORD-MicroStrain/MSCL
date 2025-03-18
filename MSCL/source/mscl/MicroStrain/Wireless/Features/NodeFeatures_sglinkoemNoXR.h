/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkoemNoXR
    //    Contains information on features for the SG-Link-OEM node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkoemNoXR : public NodeFeatures
    {
        NodeFeatures_sglinkoemNoXR();    //disabled default constructor

    public:
        ~NodeFeatures_sglinkoemNoXR() override = default;

        //Constructor: NodeFeatures_sglinkoemNoXR
        //    Creates a NodeFeatures_sglinkoemNoXR object.
        NodeFeatures_sglinkoemNoXR(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;
    };
}
