/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_vlink2
    //    Contains information on features for the V-Link2 node. Inherits from <NodeFeatures>.
    class NodeFeatures_vlink2 : public NodeFeatures
    {
    private:
        NodeFeatures_vlink2();    //disabled default constructor

    public:
        virtual ~NodeFeatures_vlink2(){};

        //Constructor: NodeFeatures_vlink2
        //    Creates a NodeFeatures_vlink2 object.
        NodeFeatures_vlink2(const NodeInfo& info);

    public:
        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;
    };
}