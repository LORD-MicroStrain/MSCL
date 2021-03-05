/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_tclink200oem
    //    Contains information on features for the TC-Link 1CH Node.
    class NodeFeatures_tclink200oem : public NodeFeatures_200series
    {
    public:
        virtual ~NodeFeatures_tclink200oem() {};

        //Constructor: NodeFeatures_tclink200oem
        //    Creates a NodeFeatures_tclink200oem object.
        NodeFeatures_tclink200oem(const NodeInfo& info);

        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        virtual const WirelessTypes::TransducerTypes transducerTypes() const override;

        virtual const WirelessTypes::DataFormats dataFormats() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
        
        virtual const WirelessTypes::Filters lowPassFilters() const override;

        virtual WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const override;
    };
}