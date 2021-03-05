/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_glink
    //    Contains information on features for the G-Link nodes.
    class NodeFeatures_glink : public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_glink(){};

        //Constructor: NodeFeatures_glink
        //    Creates a NodeFeatures_glink object.
        NodeFeatures_glink(const NodeInfo& info);
    };
}