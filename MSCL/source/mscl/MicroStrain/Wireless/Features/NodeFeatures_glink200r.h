/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_glink200r
    //    Contains information on features for the G-Link-200-R.
    class NodeFeatures_glink200r: public NodeFeatures_200series
    {
    public:
        ~NodeFeatures_glink200r() override = default;

        //Constructor: NodeFeatures_glink200
        //    Creates a NodeFeatures_glink200 object.
        NodeFeatures_glink200r(const NodeInfo& info);

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
        const WirelessTypes::SamplingModes samplingModes() const override;
        const WirelessTypes::DataFormats dataFormats() const override;
        const WirelessTypes::CfcFilters cfcFilters() const override;
    };
}
