/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_torqueLink
    //    Contains information on features for the SG-Link-Micro node. Inherits from <NodeFeatures>.
    class NodeFeatures_torqueLink : public NodeFeatures
    {
        NodeFeatures_torqueLink();    //disabled default constructor

    public:
        ~NodeFeatures_torqueLink() override = default;

        //Constructor: NodeFeatures_torqueLink
        //    Creates a NodeFeatures_torqueLink object.
        NodeFeatures_torqueLink(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::SamplingModes samplingModes() const override;
    };
} // namespace mscl
