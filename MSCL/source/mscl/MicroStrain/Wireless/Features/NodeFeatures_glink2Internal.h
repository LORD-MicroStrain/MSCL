/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_glink2Internal
    //    Contains information on features for the G-Link 2 (Internal Accels) nodes.
    class NodeFeatures_glink2Internal : public NodeFeatures
    {
    public:
        ~NodeFeatures_glink2Internal() override = default;

        //Constructor: NodeFeatures_glink2Internal
        //    Creates a NodeFeatures_glink2Internal object.
        NodeFeatures_glink2Internal(const NodeInfo& info);

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        const WirelessTypes::Filters antiAliasingFilters() const override;
    };
}
