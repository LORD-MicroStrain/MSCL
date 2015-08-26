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
#include "NodeFeatures_glink2Internal.h"

#include "mscl/Exceptions.h"
#include "AvailableSampleRates.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

namespace mscl
{
	NodeFeatures_glink2Internal::NodeFeatures_glink2Internal(const NodeInfo& info):
		NodeFeatures(info)
	{
		addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
		addCalCoeffChannelGroup(2, NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
		addCalCoeffChannelGroup(3, NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
		addCalCoeffChannelGroup(4, NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);

		//Channels
		m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration);	//accel x
		m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_acceleration);	//accel y
		m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_acceleration);	//accel z
		m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_temperature);	//internal temp
	}

	const WirelessTypes::WirelessSampleRates NodeFeatures_glink2Internal::sampleRates(WirelessTypes::SamplingMode samplingMode) const
	{
		//the list of sample rates varies for each sampling mode
		switch(samplingMode)
		{
		case WirelessTypes::samplingMode_nonSync:
		case WirelessTypes::samplingMode_sync:
			return AvailableSampleRates::continuous_glink2;
		
		case WirelessTypes::samplingMode_syncBurst:
			return AvailableSampleRates::burst_glink2;

		case WirelessTypes::samplingMode_armedDatalog:
			return AvailableSampleRates::armedDatalog_glink2;

		default:
			throw Error("Invalid SamplingMode");
		}
	}
}