/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_glink2External
    //    Contains information on features for the G-Link 2 (External Accel) nodes.
    class NodeFeatures_glink2External : public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_glink2External(){};

        //Constructor: NodeFeatures_glink2External
        //    Creates a NodeFeatures_glink2External object.
        NodeFeatures_glink2External(const NodeInfo& info);

    public:
        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual const WirelessTypes::Filters antiAliasingFilters() const override;
    };
}