/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_sglink200oem.h"

namespace mscl
{
    //Class: NodeFeatures_sglink200oem_256hz
    //    Contains information on features for the SG-Link-200-OEM nodes with 256Hz filter
    class NodeFeatures_sglink200oem_256hz: public NodeFeatures_sglink200oem
    {
    public:
        ~NodeFeatures_sglink200oem_256hz() override = default;

        //Constructor: NodeFeatures_sglink200oem_256hz
        //    Creates a NodeFeatures_sglink200oem_256hz object.
        NodeFeatures_sglink200oem_256hz(const NodeInfo& info);

        const WirelessTypes::Filters lowPassFilters() const override;
    };
} // namespace mscl