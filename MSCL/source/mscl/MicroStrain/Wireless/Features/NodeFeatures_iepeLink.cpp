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
#include "NodeFeatures_iepeLink.h"

#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "AvailableSampleRates.h"

namespace mscl
{
	NodeFeatures_iepeLink::NodeFeatures_iepeLink(const NodeInfo& info):
		NodeFeatures(info)
	{
		addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
		addCalCoeffChannelGroup(4, NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);

		//Channels
		//	Note: Channel 4 is unique in that it doesn't follow the sample rate of the node. 
		//		  Instead, it is sent once every burst, with a provided sample rate of once every 24 hours.
		m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration);	//accel
		m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_temperature);	//temp	
	}

	const WirelessTypes::DefaultModes NodeFeatures_iepeLink::defaultModes() const
	{
		//build and return the boot modes that are supported (all for generic)
		WirelessTypes::DefaultModes result;

		result.push_back(WirelessTypes::defaultMode_idle);
		result.push_back(WirelessTypes::defaultMode_sleep);
		result.push_back(WirelessTypes::defaultMode_sync);

		//no support for LDC
		//no support for Armed Datalogging

		return result;
	}

	const WirelessTypes::SamplingModes NodeFeatures_iepeLink::samplingModes() const
	{
		//build and return the sampling modes that are supported
		WirelessTypes::SamplingModes result;

		result.push_back(WirelessTypes::samplingMode_syncBurst);

		//no support for sync continuous
		//no support for non sync
		//no support for armed datalogging

		return result;
	}

	const WirelessTypes::DataFormats NodeFeatures_iepeLink::dataFormats() const
	{
		//build and return the data formats that are supported
		WirelessTypes::DataFormats result;

		result.push_back(WirelessTypes::dataFormat_4byte_float);

		//no support for uint16

		return result;
	}

	const WirelessTypes::WirelessSampleRates NodeFeatures_iepeLink::sampleRates(WirelessTypes::SamplingMode samplingMode) const
	{
		//the list of sample rates varies for each sampling mode
		switch(samplingMode)
		{		
		case WirelessTypes::samplingMode_syncBurst:
			return AvailableSampleRates::burst_iepeLink;

		default:
			throw Error("Invalid SamplingMode");
		}
	}

	uint32 NodeFeatures_iepeLink::maxSweepsPerBurst(WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const
	{
		//the max number of bytes per burst
		static const uint32 maxBytes = 600000;

		//get the number of bytes per sample
		uint8 bytesPerSample = WirelessTypes::dataFormatSize(dataFormat);

		//calculate and return the max number of sweeps per burst
		return (maxBytes / (bytesPerSample * channels.count()));
	}
}