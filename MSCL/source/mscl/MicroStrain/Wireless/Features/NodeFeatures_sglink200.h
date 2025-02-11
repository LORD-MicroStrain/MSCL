/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_sglink200
    //    Contains information on features for the SG-Link-200 nodes. Inherits from <NodeFeatures>.
    class NodeFeatures_sglink200: public NodeFeatures_200series
    {
    private:
        NodeFeatures_sglink200();    //disabled default constructor

    public:
        virtual ~NodeFeatures_sglink200(){};

        //Constructor: NodeFeatures_sglink200
        //    Creates a NodeFeatures_sglink200 object.
        NodeFeatures_sglink200(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;

        virtual const WirelessTypes::DerivedChannelMasks channelsPerDerivedCategory() const override;

        virtual const WirelessTypes::Filters lowPassFilters() const override;

        virtual WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const override;

        virtual WirelessTypes::WirelessSampleRate maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual const WirelessTypes::Voltages excitationVoltages() const override;

        virtual const WirelessTypes::VoltageType adcVoltageInputType() const override;

        virtual bool supportsPullUpResistor() const override;

        virtual bool supportsExcitationVoltageConfig() const override;

        virtual bool supportsPoll() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}
