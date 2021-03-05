/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_torqueLink200
    //    Contains information on features for the Torque-Link-200 nodes. Inherits from <NodeFeatures>.
    class NodeFeatures_torqueLink200: public NodeFeatures_200series
    {
    private:
        NodeFeatures_torqueLink200();    //disabled default constructor

    public:
        virtual ~NodeFeatures_torqueLink200(){};

        //Constructor: NodeFeatures_torqueLink200
        //    Creates a NodeFeatures_torqueLink200 object.
        NodeFeatures_torqueLink200(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;

        virtual const WirelessTypes::DerivedChannelMasks channelsPerDerivedCategory() const override;

        virtual const WirelessTypes::Filters lowPassFilters() const override;

        virtual WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const override;

        virtual const WirelessTypes::Voltages excitationVoltages() const override;

        virtual const WirelessTypes::VoltageType adcVoltageInputType() const override;

        virtual bool supportsPullUpResistor() const override;

        virtual bool supportsExcitationVoltageConfig() const override;

        virtual bool supportsPoll() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}

