/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_glink200
    //    Contains information on features for the G-Link 200 node.
    class NodeFeatures_glink200: public NodeFeatures_200series
    {
    public:
        virtual ~NodeFeatures_glink200(){};

        //Constructor: NodeFeatures_glink200
        //    Creates a NodeFeatures_glink200 object.
        NodeFeatures_glink200(const NodeInfo& info);

    public:
        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual const WirelessTypes::DataFormats dataFormats() const override;

        virtual const WirelessTypes::Filters lowPassFilters() const override;

        virtual const WirelessTypes::HighPassFilters highPassFilters() const override;

        virtual const WirelessTypes::DerivedChannelTypes derivedChannelTypes() const override;
    };
}