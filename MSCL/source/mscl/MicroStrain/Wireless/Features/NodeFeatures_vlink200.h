/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_vlink200
    //    Contains information on features for the V-Link2 node. Inherits from <NodeFeatures>.
    class NodeFeatures_vlink200 : public NodeFeatures_200series
    {
    private:
        NodeFeatures_vlink200();    //disabled default constructor

    public:
        virtual ~NodeFeatures_vlink200(){};

        //Constructor: NodeFeatures_vlink200
        //    Creates a NodeFeatures_vlink200 object.
        NodeFeatures_vlink200(const NodeInfo& info);

    public:
        virtual bool supportsSensorDelayConfig() const override;

        virtual bool supportsPoll() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual const WirelessTypes::Filters antiAliasingFilters() const override;
    };
}