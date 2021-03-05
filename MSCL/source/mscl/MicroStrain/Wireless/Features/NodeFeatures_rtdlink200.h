/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_rtdlink200
    //    Contains information on features for the RTD-Link-200 Node.
    class NodeFeatures_rtdlink200 : public NodeFeatures_200series
    {
    public:
        virtual ~NodeFeatures_rtdlink200() {};

        //Constructor: NodeFeatures_rtdlink200
        //    Creates a NodeFeatures_rtdlink200 object.
        NodeFeatures_rtdlink200(const NodeInfo& info);

        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        virtual const WirelessTypes::TransducerTypes transducerTypes() const override;

        virtual const WirelessTypes::DataFormats dataFormats() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
        
        virtual const WirelessTypes::Filters lowPassFilters() const override;

        virtual WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const override;

    private:
        static const WirelessTypes::WirelessSampleRate maxRateForFilter(WirelessTypes::Filter lowPassFilter, const ChannelMask& channels);

    protected:
        virtual bool supportsNewTransmitPowers() const override;

        virtual bool supportsLowBatteryThresholdConfig() const override;
    };
}