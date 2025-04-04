/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_glink
    //    Contains information on features for the G-Link nodes.
    class NodeFeatures_glink : public NodeFeatures
    {
    public:
        ~NodeFeatures_glink() override = default;

        //Constructor: NodeFeatures_glink
        //    Creates a NodeFeatures_glink object.
        NodeFeatures_glink(const NodeInfo& info);
    };
} // namespace mscl
