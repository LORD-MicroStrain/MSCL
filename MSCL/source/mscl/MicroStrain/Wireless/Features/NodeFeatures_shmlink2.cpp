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
#include "NodeFeatures_shmlink2.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/Utils.h"

namespace mscl
{
	NodeFeatures_shmlink2::NodeFeatures_shmlink2(const NodeInfo& info):
		NodeFeatures(info)
	{
		addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
		addCalCoeffChannelGroup(2, NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
		addCalCoeffChannelGroup(3, NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
		addCalCoeffChannelGroup(5, NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
		addCalCoeffChannelGroup(6, NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
		addCalCoeffChannelGroup(7, NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
		addCalCoeffChannelGroup(8, NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);

		//Channels
		m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_acceleration);		//accel x
		m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_acceleration);		//accel y
		m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_acceleration);		//accel z
		m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_temperature);		//temp
	}

	const WirelessTypes::DefaultModes NodeFeatures_shmlink2::defaultModes() const
	{
		//build and return the boot modes that are supported (all for generic)
		WirelessTypes::DefaultModes result;

		result.push_back(WirelessTypes::defaultMode_idle);
		result.push_back(WirelessTypes::defaultMode_ldc);
		result.push_back(WirelessTypes::defaultMode_sleep);

		return result;
	}

	const WirelessTypes::DataCollectionMethods NodeFeatures_shmlink2::dataCollectionMethods() const
	{
		//build and return the data collection methods that are supported
		WirelessTypes::DataCollectionMethods result;
		result.push_back(WirelessTypes::collectionMethod_transmitOnly);
		return result;
	}

	const WirelessTypes::DataFormats NodeFeatures_shmlink2::dataFormats() const
	{
		//build and return the data formats that are supported
		WirelessTypes::DataFormats result;
		result.push_back(WirelessTypes::dataFormat_4byte_float);
		return result;
	}

	bool NodeFeatures_shmlink2::supportsFatigueConfig() const
	{
		return true;
	}

	bool NodeFeatures_shmlink2::supportsYoungsModConfig() const
	{
		return true;
	}

	bool NodeFeatures_shmlink2::supportsPoissonsRatioConfig() const
	{
		return true;
	}

	bool NodeFeatures_shmlink2::supportsFatigueRawModeConfig() const
	{
		return true;
	}

	bool NodeFeatures_shmlink2::supportsHistogramConfig() const
	{
		return true;
	}

	bool NodeFeatures_shmlink2::supportsHistogramRateConfig() const
	{
		return true;
	}

	bool NodeFeatures_shmlink2::supportsAutoCal() const
	{
		return true;
	}

	uint8 NodeFeatures_shmlink2::numDamageAngles() const
	{
		return 3;
	}

	uint8 NodeFeatures_shmlink2::numSnCurveSegments() const
	{
		return 3;
	}

	const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink2::histogramTransmitRates() const
	{
		static const WirelessTypes::WirelessSampleRates HistogramRates = {
			{WirelessTypes::sampleRate_1Hz},
			{WirelessTypes::sampleRate_2Sec},
			{WirelessTypes::sampleRate_5Sec},
			{WirelessTypes::sampleRate_10Sec},
			{WirelessTypes::sampleRate_30Sec},
			{WirelessTypes::sampleRate_1Min},
			{WirelessTypes::sampleRate_2Min},
			{WirelessTypes::sampleRate_5Min},
			{WirelessTypes::sampleRate_10Min},
			{WirelessTypes::sampleRate_30Min},
			{WirelessTypes::sampleRate_60Min}};

		return HistogramRates;
	}
}