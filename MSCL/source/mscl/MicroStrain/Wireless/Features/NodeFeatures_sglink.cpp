/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_sglink.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/Utils.h"

namespace mscl
{
	NodeFeatures_sglink::NodeFeatures_sglink(const NodeInfo& info):
		NodeFeatures(info)
	{
		static const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00000001));	//ch1

		m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential Channels",
									 ChannelGroup::SettingsMap{
										 {WirelessTypes::chSetting_hardwareGain, NodeEepromMap::HW_GAIN_1},
										 {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_1},
										 {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_1}}
		);

		addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
		addCalCoeffChannelGroup(3, NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
		addCalCoeffChannelGroup(4, NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);

		//Channels
		m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_temperature);		//internal temp
		m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_voltage);			//voltage
	}
}