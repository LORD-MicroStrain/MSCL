/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglink
    //    Contains information on features for the SG-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglink : public NodeFeatures
    {
    private:
        NodeFeatures_sglink();    //disabled default constructor

    public:
        virtual ~NodeFeatures_sglink(){};

        //Constructor: NodeFeatures_sglink
        //    Creates a NodeFeatures_sglink object.
        NodeFeatures_sglink(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;

        const uint32 minSensorDelay() const override;

        const uint32 maxSensorDelay() const override;

        const uint32 defaultSensorDelay() const override;
    };
}
