/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_sglinkoemHermetic.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/Utils.h"

namespace mscl
{
    NodeFeatures_sglinkoemHermetic::NodeFeatures_sglinkoemHermetic(const NodeInfo& info):
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Battery", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
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
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential");
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_battery, "Battery");
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_temperature, "Internal Temperature");
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_singleEnded, "Single-ended");
    }

    bool NodeFeatures_sglinkoemHermetic::supportsSensorDelayConfig() const
    {
        return true;
    }

    bool NodeFeatures_sglinkoemHermetic::supportsSensorDelayAlwaysOn() const
    {
        return false;
    }
}