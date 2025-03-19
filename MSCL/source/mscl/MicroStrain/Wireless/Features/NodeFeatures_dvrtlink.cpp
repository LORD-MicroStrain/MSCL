/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_dvrtlink.h"

#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"

namespace mscl
{
    NodeFeatures_dvrtlink::NodeFeatures_dvrtlink(const NodeInfo& info) :
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(3, "Internal Temperature", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(4, "Displacement", NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);

        //Channels
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_temperature, "Internal Temperature");
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_displacement, "Displacement", 12);
    }

    bool NodeFeatures_dvrtlink::supportsSensorDelayConfig() const
    {
        return true;
    }
} // namespace mscl
