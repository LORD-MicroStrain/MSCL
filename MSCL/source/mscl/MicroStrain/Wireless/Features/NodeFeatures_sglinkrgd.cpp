/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_sglinkrgd.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/Utils.h"

namespace mscl
{
	NodeFeatures_sglinkrgd::NodeFeatures_sglinkrgd(const NodeInfo& info):
		NodeFeatures(info)
	{
		addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
		addCalCoeffChannelGroup(2, NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
		addCalCoeffChannelGroup(3, NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
		addCalCoeffChannelGroup(4, NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);
		addCalCoeffChannelGroup(5, NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
		addCalCoeffChannelGroup(6, NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
		addCalCoeffChannelGroup(7, NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
		addCalCoeffChannelGroup(8, NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);

		static const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00001111));	//ch1-ch4

		m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential Channels",
									 ChannelGroup::SettingsMap{
										 {WirelessTypes::chSetting_hardwareGain, NodeEepromMap::HW_GAIN_1}}
		);

		//Channels
		m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_acceleration);		//accel x
		m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_acceleration);		//accel y
		m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_acceleration);		//accel z
		m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_temperature);		//temp

		
	}
}