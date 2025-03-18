/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_glink2External
    //    Contains information on features for the G-Link 2 (External Accel) nodes.
    class NodeFeatures_glink2External : public NodeFeatures
    {
    public:
        ~NodeFeatures_glink2External() override = default;

        //Constructor: NodeFeatures_glink2External
        //    Creates a NodeFeatures_glink2External object.
        NodeFeatures_glink2External(const NodeInfo& info);

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        const WirelessTypes::Filters antiAliasingFilters() const override;
    };
}
