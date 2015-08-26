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
#include "WirelessChannel.h"
#include "mscl/Utils.h"

namespace mscl
{
	WirelessChannel::WirelessChannel():
		m_chNumber(0),
		m_id(WirelessChannel::channel_unknown),
		m_type(WirelessTypes::chType_none)
	{
	}

	WirelessChannel::WirelessChannel(uint8 chNumber, WirelessChannel::ChannelId id, WirelessTypes::ChannelType type):
		m_chNumber(chNumber),
		m_id(id),
		m_type(type)
	{
	}

	uint8 WirelessChannel::channelNumber() const
	{
		return m_chNumber;
	}

	WirelessChannel::ChannelId WirelessChannel::id() const
	{
		return m_id;
	}

	WirelessTypes::ChannelType WirelessChannel::type() const
	{
		return m_type;
	}

	std::string WirelessChannel::name() const
	{
		return channelName(id());
	}

	std::string WirelessChannel::channelName(WirelessChannel::ChannelId channelId)
	{
		switch(channelId)
		{
			case channel_1:		return "ch1";
			case channel_2:		return "ch2";
			case channel_3:		return "ch3";
			case channel_4:		return "ch4";
			case channel_5:		return "ch5";
			case channel_6:		return "ch6";
			case channel_7:		return "ch7";
			case channel_8:		return "ch8";
			case channel_9:		return "ch9";
			case channel_10:	return "ch10";
			case channel_11:	return "ch11";
			case channel_12:	return "ch12";
			case channel_13:	return "ch13";
			case channel_14:	return "ch14";
			case channel_15:	return "ch15";
			case channel_16:	return "ch16";

			case channel_digital_1:		return "digital1";
			case channel_digital_2:		return "digital2";
			case channel_digital_3:		return "digital3";
			case channel_digital_4:		return "digital4";
			case channel_digital_5:		return "digital5";
			case channel_digital_6:		return "digital6";
			case channel_digital_7:		return "digital7";
			case channel_digital_8:		return "digital8";
			case channel_digital_9:		return "digital9";
			case channel_digital_10:	return "digital10";
			case channel_digital_11:	return "digital11";
			case channel_digital_12:	return "digital12";
			case channel_digital_13:	return "digital13";
			case channel_digital_14:	return "digital14";
			case channel_digital_15:	return "digital15";
			case channel_digital_16:	return "digital16";

			case channel_structuralHealth:		return "structuralHealth";
			
			case channel_hcl_rawBase_mag1_x:	return "hcl_rawBase_mag1_x";
			case channel_hcl_rawBase_mag1_y:	return "hcl_rawBase_mag1_y";
			case channel_hcl_rawBase_mag1_z:	return "hcl_rawBase_mag1_z";
			case channel_hcl_rawBase_mag2_x:	return "hcl_rawBase_mag2_x";
			case channel_hcl_rawBase_mag2_y:	return "hcl_rawBase_mag2_y";
			case channel_hcl_rawBase_mag2_z:	return "hcl_rawBase_mag2_z";
			case channel_hcl_rawBase_mag3_x:	return "hcl_rawBase_mag3_x";
			case channel_hcl_rawBase_mag3_y:	return "hcl_rawBase_mag3_y";
			case channel_hcl_rawBase_mag3_z:	return "hcl_rawBase_mag3_z";
			case channel_hcl_rawBase_mag4_x:	return "hcl_rawBase_mag4_x";
			case channel_hcl_rawBase_mag4_y:	return "hcl_rawBase_mag4_y";
			case channel_hcl_rawBase_mag4_z:	return "hcl_rawBase_mag4_z";
			case channel_hcl_rawBase_mag5_x:	return "hcl_rawBase_mag5_x";
			case channel_hcl_rawBase_mag5_y:	return "hcl_rawBase_mag5_y";
			case channel_hcl_rawBase_mag5_z:	return "hcl_rawBase_mag5_z";
			case channel_hcl_rawBase_mag6_x:	return "hcl_rawBase_mag6_x";
			case channel_hcl_rawBase_mag6_y:	return "hcl_rawBase_mag6_y";
			case channel_hcl_rawBase_mag6_z:	return "hcl_rawBase_mag6_z";
			case channel_hcl_rawBase_mag7_x:	return "hcl_rawBase_mag7_x";
			case channel_hcl_rawBase_mag7_y:	return "hcl_rawBase_mag7_y";
			case channel_hcl_rawBase_mag7_z:	return "hcl_rawBase_mag7_z";
			case channel_hcl_rawBase_mag8_x:	return "hcl_rawBase_mag8_x";
			case channel_hcl_rawBase_mag8_y:	return "hcl_rawBase_mag8_y";
			case channel_hcl_rawBase_mag8_z:	return "hcl_rawBase_mag8_z";
			case channel_hcl_rawBase_gyro_x:	return "hcl_rawBase_gyro_x";
			case channel_hcl_rawBase_gyro_y:	return "hcl_rawBase_gyro_y";
			case channel_hcl_rawBase_gyro_z:	return "hcl_rawBase_gyro_z";

			case channel_error_code:			return "errorCode";

			default:
				assert(false);
				return "unknown_" + Utils::toStr(channelId);
		}
	}
}