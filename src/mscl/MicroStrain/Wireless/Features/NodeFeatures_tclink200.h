/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_tclink200
    //    Contains information on features for the TC-Link 1CH Node.
    class NodeFeatures_tclink200 : public NodeFeatures_200series
    {
    public:
        ~NodeFeatures_tclink200() override = default;

        //Constructor: NodeFeatures_tclink200
        //    Creates a NodeFeatures_tclink200 object.
        NodeFeatures_tclink200(const NodeInfo& info);

        const WirelessTypes::SamplingModes samplingModes() const override;

        const WirelessTypes::TransducerTypes transducerTypes() const override;

        const WirelessTypes::DataFormats dataFormats() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        const WirelessTypes::Filters lowPassFilters() const override;

        WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const override;

    private:
        static const WirelessTypes::WirelessSampleRate maxRateForFilter(WirelessTypes::Filter lowPassFilter, const ChannelMask& channels);

    protected:
        bool supportsNewTransmitPowers() const override;

        bool supportsLowBatteryThresholdConfig() const override;
    };
} // namespace mscl
