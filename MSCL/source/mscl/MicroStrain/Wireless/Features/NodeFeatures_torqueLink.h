/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_torqueLink
    //    Contains information on features for the SG-Link-Micro node. Inherits from <NodeFeatures>.
    class NodeFeatures_torqueLink: public NodeFeatures
    {
    private:
        NodeFeatures_torqueLink();    //disabled default constructor

    public:
        virtual ~NodeFeatures_torqueLink() {};

        //Constructor: NodeFeatures_torqueLink
        //    Creates a NodeFeatures_torqueLink object.
        NodeFeatures_torqueLink(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;

        virtual const WirelessTypes::SamplingModes samplingModes() const override;
    };
}