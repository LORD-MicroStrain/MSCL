/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkoemHermetic
    //    Contains information on features for the SG-Link-OEM node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkoemHermetic : public NodeFeatures
    {
    private:
        NodeFeatures_sglinkoemHermetic();    //disabled default constructor

    public:
        virtual ~NodeFeatures_sglinkoemHermetic(){};

        //Constructor: NodeFeatures_sglinkoemHermetic
        //    Creates a NodeFeatures_sglinkoemHermetic object.
        NodeFeatures_sglinkoemHermetic(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;

        virtual bool supportsSensorDelayAlwaysOn() const override;
    };
}