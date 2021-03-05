/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_vlink
    //    Contains information on features for the V-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_vlink : public NodeFeatures
    {
    private:
        NodeFeatures_vlink();    //disabled default constructor

    public:
        virtual ~NodeFeatures_vlink(){};

        //Constructor: NodeFeatures_vlink
        //    Creates a NodeFeatures_vlink object.
        NodeFeatures_vlink(const NodeInfo& info);

    public:
        virtual bool supportsSensorDelayConfig() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual WirelessTypes::WirelessSampleRate maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}