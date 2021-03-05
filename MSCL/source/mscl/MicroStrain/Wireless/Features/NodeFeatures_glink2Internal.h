/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_glink2Internal
    //    Contains information on features for the G-Link 2 (Internal Accels) nodes.
    class NodeFeatures_glink2Internal : public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_glink2Internal(){};

        //Constructor: NodeFeatures_glink2Internal
        //    Creates a NodeFeatures_glink2Internal object.
        NodeFeatures_glink2Internal(const NodeInfo& info);

    public:
        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual const WirelessTypes::Filters antiAliasingFilters() const override;
    };
}