/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_ptlink200
    //    Contains information on features for the PT-Link-200 nodes. Inherits from <NodeFeatures>.
    class NodeFeatures_ptlink200: public NodeFeatures_200series
    {
        NodeFeatures_ptlink200();    //disabled default constructor

    public:
        ~NodeFeatures_ptlink200() override = default;

        //Constructor: NodeFeatures_ptlink200
        //    Creates a NodeFeatures_ptlink200 object.
        NodeFeatures_ptlink200(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::DerivedChannelMasks channelsPerDerivedCategory() const override;

        const WirelessTypes::Filters lowPassFilters() const override;

        WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const override;

        WirelessTypes::VoltageType adcVoltageInputType() const override;

        bool supportsPoll() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        uint32 minSensorDelay() const override;

        uint32 defaultSensorDelay() const override;
    };
} // namespace mscl
