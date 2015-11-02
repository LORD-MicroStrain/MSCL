/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_sglinkMicro.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/Utils.h"

namespace mscl
{
	NodeFeatures_sglinkMicro::NodeFeatures_sglinkMicro(const NodeInfo& info):
		NodeFeatures(info)
	{
		addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
		addCalCoeffChannelGroup(3, NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);

		static const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00000001));	//ch1

		m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential Channels",
									 ChannelGroup::SettingsMap{
										 {WirelessTypes::chSetting_hardwareGain, NodeEepromMap::HW_GAIN_1},
										 {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_1},
										 {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_1}}
		);

		//Channels
		m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential);	//full diff
		m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_temperature);		//temperature
	}

	const WirelessTypes::DataCollectionMethods NodeFeatures_sglinkMicro::dataCollectionMethods() const
	{
		WirelessTypes::DataCollectionMethods result;

		result.push_back(WirelessTypes::collectionMethod_transmitOnly);

		//no log only
		//no log and transmit

		return result;
	}

	const WirelessTypes::DataFormats NodeFeatures_sglinkMicro::dataFormats() const
	{
		//build and return the data formats that are supported (all for generic)
		WirelessTypes::DataFormats result;

		result.push_back(WirelessTypes::dataFormat_4byte_float);

		//no uint16

		return result;
	}

	const WirelessTypes::SamplingModes NodeFeatures_sglinkMicro::samplingModes() const
	{
		//build and return the sampling modes that are supported (all for generic)
		WirelessTypes::SamplingModes result;

		result.push_back(WirelessTypes::samplingMode_sync);
		result.push_back(WirelessTypes::samplingMode_nonSync);
		result.push_back(WirelessTypes::samplingMode_armedDatalog);

		//no burst

		return result;
	}
}