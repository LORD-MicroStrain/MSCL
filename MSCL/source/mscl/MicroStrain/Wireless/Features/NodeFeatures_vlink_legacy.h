/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_vlink_legacy
    //    Contains information on features for the V-Link (legacy) node. Inherits from <NodeFeatures>.
    class NodeFeatures_vlink_legacy : public NodeFeatures
    {
    private:
        NodeFeatures_vlink_legacy();    //disabled default constructor

    public:
        virtual ~NodeFeatures_vlink_legacy(){};

        //Constructor: NodeFeatures_vlink_legacy
        //    Creates a NodeFeatures_vlink_legacy object.
        NodeFeatures_vlink_legacy(const NodeInfo& info);

    public:
        virtual bool supportsSensorDelayConfig() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}