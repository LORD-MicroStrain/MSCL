/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_sglink200oem
    //    Contains information on features for the SG-Link-200-OEM nodes. Inherits from <NodeFeatures>.
    class NodeFeatures_sglink200oem: public NodeFeatures_200series
    {
        NodeFeatures_sglink200oem();    //disabled default constructor

    public:
        ~NodeFeatures_sglink200oem() override = default;

        //Constructor: NodeFeatures_sglink200oem
        //    Creates a NodeFeatures_sglink200oem object.
        NodeFeatures_sglink200oem(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::DerivedChannelMasks channelsPerDerivedCategory() const override;

        const WirelessTypes::Filters lowPassFilters() const override;

        WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const override;

        const WirelessTypes::Voltages excitationVoltages() const override;

        WirelessTypes::VoltageType adcVoltageInputType() const override;

        bool supportsPullUpResistor() const override;

        bool supportsExcitationVoltageConfig() const override;

        bool supportsPoll() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
} // namespace mscl
