/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_sglinkoemNoXR.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/Utils.h"

namespace mscl
{
    NodeFeatures_sglinkoemNoXR::NodeFeatures_sglinkoemNoXR(const NodeInfo& info):
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(3, "Internal Temperature", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(4, "Single-ended", NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);

        static const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00000001));    //ch1

        m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_legacyShuntCal, NodeEepromMap::CH_ACTION_SLOPE_1}}
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential", 12);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_temperature, "Internal Temperature");
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_singleEnded, "Single-ended", 12);
    }

    bool NodeFeatures_sglinkoemNoXR::supportsSensorDelayConfig() const
    {
        return true;
    }
}