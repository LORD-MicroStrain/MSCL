/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_sglink200oem.h"

namespace mscl
{
    //Class: NodeFeatures_sglink200oem_128hz
    //    Contains information on features for the SG-Link-200-OEM nodes with 128Hz filter
    class NodeFeatures_sglink200oem_128hz: public NodeFeatures_sglink200oem
    {
    public:
        ~NodeFeatures_sglink200oem_128hz() override = default;

        //Constructor: NodeFeatures_sglink200oem_128hz
        //    Creates a NodeFeatures_sglink200oem_128hz object.
        NodeFeatures_sglink200oem_128hz(const NodeInfo& info);

        const WirelessTypes::Filters lowPassFilters() const override;
    };
} // namespace mscl