/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkoemNoXR
    //    Contains information on features for the SG-Link-OEM node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkoemNoXR : public NodeFeatures
    {
    private:
        NodeFeatures_sglinkoemNoXR();    //disabled default constructor

    public:
        virtual ~NodeFeatures_sglinkoemNoXR(){};

        //Constructor: NodeFeatures_sglinkoemNoXR
        //    Creates a NodeFeatures_sglinkoemNoXR object.
        NodeFeatures_sglinkoemNoXR(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;
    };
}