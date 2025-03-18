/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_vlink_legacy
    //    Contains information on features for the V-Link (legacy) node. Inherits from <NodeFeatures>.
    class NodeFeatures_vlink_legacy : public NodeFeatures
    {
        NodeFeatures_vlink_legacy();    //disabled default constructor

    public:
        ~NodeFeatures_vlink_legacy() override = default;

        //Constructor: NodeFeatures_vlink_legacy
        //    Creates a NodeFeatures_vlink_legacy object.
        NodeFeatures_vlink_legacy(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}
