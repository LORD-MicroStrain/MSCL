/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

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
        //Function: sampleRates
        //    Gets a list of the <WirelessTypes::WirelessSampleRates> that are supported by this Node for the given sampling mode.
        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;
    };
}