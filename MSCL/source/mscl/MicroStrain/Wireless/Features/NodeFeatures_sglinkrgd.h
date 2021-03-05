/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkrgd
    //    Contains information on features for the SG-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkrgd : public NodeFeatures
    {
    private:
        NodeFeatures_sglinkrgd();    //disabled default constructor

    public:
        virtual ~NodeFeatures_sglinkrgd(){};

        //Constructor: NodeFeatures_sglinkrgd
        //    Creates a NodeFeatures_sglinkrgd object.
        NodeFeatures_sglinkrgd(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;

        virtual bool supportsSensorDelayAlwaysOn() const override;
    };
}