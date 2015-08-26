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
#include "NodeFeatures_vlink.h"
#include "AvailableSampleRates.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"

namespace mscl
{
	NodeFeatures_vlink::NodeFeatures_vlink(const NodeInfo& info):
		NodeFeatures(info)
	{
		//Channels
		m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_voltage);			//voltage 
		m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_voltage);			//voltage 
		m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_voltage);			//voltage 
		m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_temperature);		//temp


		//Channel Groups
		static const ChannelMask DIFFERENTIAL_CH1(BOOST_BINARY(00000001));	//ch1
		static const ChannelMask DIFFERENTIAL_CH2(BOOST_BINARY(00000010));	//ch2
		static const ChannelMask DIFFERENTIAL_CH3(BOOST_BINARY(00000100));	//ch3
		static const ChannelMask DIFFERENTIAL_CH4(BOOST_BINARY(00001000));	//ch4

		m_channelGroups.emplace_back(DIFFERENTIAL_CH1, "Differential Channel 1",
									 ChannelGroup::SettingsMap{
										 {WirelessTypes::chSetting_hardwareGain, NodeEepromMap::HW_GAIN_1},
										 {WirelessTypes::chSetting_linearEquation, NodeEepromMap::CH_ACTION_SLOPE_1},
										 {WirelessTypes::chSetting_unit, NodeEepromMap::CH_ACTION_ID_1},
										 {WirelessTypes::chSetting_equationType, NodeEepromMap::CH_ACTION_ID_1}}
		);

		m_channelGroups.emplace_back(DIFFERENTIAL_CH2, "Differential Channel 2",
									 ChannelGroup::SettingsMap{
										 {WirelessTypes::chSetting_hardwareGain, NodeEepromMap::HW_GAIN_2},
										 {WirelessTypes::chSetting_linearEquation, NodeEepromMap::CH_ACTION_SLOPE_2},
										 {WirelessTypes::chSetting_unit, NodeEepromMap::CH_ACTION_ID_2},
										 {WirelessTypes::chSetting_equationType, NodeEepromMap::CH_ACTION_ID_2}}
		);

		m_channelGroups.emplace_back(DIFFERENTIAL_CH3, "Differential Channel 3",
									 ChannelGroup::SettingsMap{
										 {WirelessTypes::chSetting_hardwareGain, NodeEepromMap::HW_GAIN_3},
										 {WirelessTypes::chSetting_linearEquation, NodeEepromMap::CH_ACTION_SLOPE_3},
										 {WirelessTypes::chSetting_unit, NodeEepromMap::CH_ACTION_ID_3},
										 {WirelessTypes::chSetting_equationType, NodeEepromMap::CH_ACTION_ID_3}}
		);

		m_channelGroups.emplace_back(DIFFERENTIAL_CH4, "Differential Channel 4",
									 ChannelGroup::SettingsMap{
										 {WirelessTypes::chSetting_hardwareGain, NodeEepromMap::HW_GAIN_4},
										 {WirelessTypes::chSetting_linearEquation, NodeEepromMap::CH_ACTION_SLOPE_4},
										 {WirelessTypes::chSetting_unit, NodeEepromMap::CH_ACTION_ID_4},
										 {WirelessTypes::chSetting_equationType, NodeEepromMap::CH_ACTION_ID_4}}
		);

		//Note: already added ch1-ch5 cal coeff above
		addCalCoeffChannelGroup(5, NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
		addCalCoeffChannelGroup(6, NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
		addCalCoeffChannelGroup(7, NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
		addCalCoeffChannelGroup(8, NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);
	}

	const WirelessTypes::WirelessSampleRates NodeFeatures_vlink::sampleRates(WirelessTypes::SamplingMode samplingMode) const
	{
		//the list of sample rates varies for each sampling mode
		switch(samplingMode)
		{
		case WirelessTypes::samplingMode_nonSync:
		case WirelessTypes::samplingMode_sync:
			return AvailableSampleRates::continuous;
		
		case WirelessTypes::samplingMode_syncBurst:
			return AvailableSampleRates::burst_vlink;

		case WirelessTypes::samplingMode_armedDatalog:
			return AvailableSampleRates::armedDatalog_vlink;

		default:
			throw Error("Invalid SamplingMode");
		}
	}

	WirelessTypes::WirelessSampleRate NodeFeatures_vlink::maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels) const
	{
		bool channelLimit = false;

		//determine if the number of active channels affects the max sample rate
		switch(samplingMode)
		{
			//modes that the sample rate is limited by the number of channels active
			case WirelessTypes::samplingMode_syncBurst:
			case WirelessTypes::samplingMode_armedDatalog:
				channelLimit = true;
				break;

			default:
				channelLimit = false;
				break;
		}

		//if the number of active channels affects the max sample rate
		if(channelLimit)
		{
			uint16 channelCount = channels.count();

			//determine the actual max rate based on the # of active channels
			switch(channelCount)
			{
				case 1:
					return WirelessTypes::sampleRate_10kHz;
				case 2:
					return WirelessTypes::sampleRate_9kHz;
				case 3:
					return WirelessTypes::sampleRate_7kHz;
				case 4:
					return WirelessTypes::sampleRate_6kHz;
				case 5:
					return WirelessTypes::sampleRate_5kHz;
				case 6:
					return WirelessTypes::sampleRate_4kHz;
				case 7:
					return WirelessTypes::sampleRate_3kHz;
				default:
					return WirelessTypes::sampleRate_2kHz;
			}
		}
		//number of channels has no affect on sample rate
		else
		{
			//just return the result of the parent class' function
			return NodeFeatures::maxSampleRate(samplingMode, channels);
		}
	}
}