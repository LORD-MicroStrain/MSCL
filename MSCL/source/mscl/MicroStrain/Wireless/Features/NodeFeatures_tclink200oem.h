/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_tclink200oem
    //    Contains information on features for the TC-Link 1CH Node.
    class NodeFeatures_tclink200oem : public NodeFeatures_200series
    {
    public:
        ~NodeFeatures_tclink200oem() override = default;

        //Constructor: NodeFeatures_tclink200oem
        //    Creates a NodeFeatures_tclink200oem object.
        NodeFeatures_tclink200oem(const NodeInfo& info);

        const WirelessTypes::SamplingModes samplingModes() const override;

        const WirelessTypes::TransducerTypes transducerTypes() const override;

        const WirelessTypes::DataFormats dataFormats() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        const WirelessTypes::Filters lowPassFilters() const override;

        WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const override;
    };
}
