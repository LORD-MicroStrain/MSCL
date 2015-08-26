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
#include "NodeFeatures_sglinkoem.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/Utils.h"

namespace mscl
{
	NodeFeatures_sglinkoem::NodeFeatures_sglinkoem(const NodeInfo& info):
		NodeFeatures(info)
	{
		addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
		addCalCoeffChannelGroup(3, NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
		addCalCoeffChannelGroup(4, NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);

		static const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00000001));	//ch1

		m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential Channels",
									 ChannelGroup::SettingsMap{
										 {WirelessTypes::chSetting_hardwareGain, NodeEepromMap::HW_GAIN_1}}
		);

		//Channels
		m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_temperature);		//temperature
		m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_voltage);			//voltage

		
	}
}