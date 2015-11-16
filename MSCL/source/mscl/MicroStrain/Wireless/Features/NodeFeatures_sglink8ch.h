/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglink8ch
    //    Contains information on features for the SG-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglink8ch : public NodeFeatures
    {
    private:
        NodeFeatures_sglink8ch();    //disabled default constructor

    public:
        virtual ~NodeFeatures_sglink8ch(){};

        //Constructor: NodeFeatures_sglink8ch
        //    Creates a NodeFeatures_sglink8ch object.
        NodeFeatures_sglink8ch(const NodeInfo& info);
    };
}