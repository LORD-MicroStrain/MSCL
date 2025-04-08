/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_sglink200oem_256hz.h"

namespace mscl
{
    NodeFeatures_sglink200oem_256hz::NodeFeatures_sglink200oem_256hz(const NodeInfo& info) :
        NodeFeatures_sglink200oem(info)
    {
    }

    const WirelessTypes::Filters NodeFeatures_sglink200oem_256hz::lowPassFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_256hz}
        };
        return filters;
    }
} // namespace mscl