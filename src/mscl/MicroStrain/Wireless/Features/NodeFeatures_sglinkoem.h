/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkoem
    //    Contains information on features for the SG-Link-OEM node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkoem : public NodeFeatures
    {
        NodeFeatures_sglinkoem();    //disabled default constructor

    public:
        ~NodeFeatures_sglinkoem() override = default;

        //Constructor: NodeFeatures_sglinkoem
        //    Creates a NodeFeatures_sglinkoem object.
        NodeFeatures_sglinkoem(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        uint32 minSensorDelay() const override;

        uint32 maxSensorDelay() const override;

        uint32 defaultSensorDelay() const override;
    };
} // namespace mscl
