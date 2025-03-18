/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_torqueLink200_3ch
    //    Contains information on features for the Torque-Link-200-3ch nodes. Inherits from <NodeFeatures>.
    class NodeFeatures_torqueLink200_3ch : public NodeFeatures_200series
    {
        NodeFeatures_torqueLink200_3ch();    //disabled default constructor

    public:
        ~NodeFeatures_torqueLink200_3ch() override = default;

        //Constructor: NodeFeatures_torqueLink200_3ch
        //    Creates a NodeFeatures_torqueLink200_3ch object.
        //Parameters:
        //  info - NodeInfo object for reference features
        //  ext - bool indicating whether this is being called from a child class (default false)
        NodeFeatures_torqueLink200_3ch(const NodeInfo& info, bool ext = false);

        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::DerivedChannelMasks channelsPerDerivedCategory() const override;

        const WirelessTypes::Filters lowPassFilters() const override;

        WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const override;

        const WirelessTypes::Voltages excitationVoltages() const override;

        const WirelessTypes::VoltageType adcVoltageInputType() const override;

        bool supportsPullUpResistor() const override;

        bool supportsExcitationVoltageConfig() const override;

        bool supportsPoll() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}
