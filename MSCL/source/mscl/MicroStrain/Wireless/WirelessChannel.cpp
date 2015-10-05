/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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
			case channel_hcl_rawStrain_BL30:	return "hcl_rawStrain_BL30";
			case channel_hcl_rawStrain_BL120:	return "hcl_rawStrain_BL120";
			case channel_hcl_rawStrain_A60:		return "hcl_rawStrain_A60";
			case channel_hcl_rawStrain_A150:	return "hcl_rawStrain_A150";
			case channel_hcl_rawStrain_AL30:	return "hcl_rawStrain_AL30";
			case channel_hcl_rawStrain_AL120:	return "hcl_rawStrain_AL120";
			case channel_hcl_rawStrain_BR60:	return "hcl_rawStrain_BR60";
			case channel_hcl_rawStrain_BR150:	return "hcl_rawStrain_BR150";
			case channel_hcl_rawStrain_B30:		return "hcl_rawStrain_B30";
			case channel_hcl_rawStrain_T120:	return "hcl_rawStrain_T120";
			case channel_hcl_rawStrain_AR60:	return "hcl_rawStrain_AR60";
			case channel_hcl_rawStrain_AR150:	return "hcl_rawStrain_AR150";
			case channel_hcl_rawStrain_A30:		return "hcl_rawStrain_A30";
			case channel_hcl_rawStrain_A120:	return "hcl_rawStrain_A120";
			case channel_hcl_rawStrain_BL90:	return "hcl_rawStrain_BL90";
			case channel_hcl_rawStrain_BL180:	return "hcl_rawStrain_BL180";
			case channel_hcl_rawStrain_BR30:	return "hcl_rawStrain_BR30";
			case channel_hcl_rawStrain_BR120:	return "hcl_rawStrain_BR120";
			case channel_hcl_rawStrain_AL90:	return "hcl_rawStrain_AL90";
			case channel_hcl_rawStrain_AL180:	return "hcl_rawStrain_AL180";
			case channel_hcl_rawStrain_AR30:	return "hcl_rawStrain_AR30";
			case channel_hcl_rawStrain_AR120:	return "hcl_rawStrain_AR120";
			case channel_hcl_rawStrain_B90:		return "hcl_rawStrain_B90";
			case channel_hcl_rawStrain_T0:		return "hcl_rawStrain_T0";
			case channel_hcl_rawStrain_BL60:	return "hcl_rawStrain_BL60";
			case channel_hcl_rawStrain_BL150:	return "hcl_rawStrain_BL150";
			case channel_hcl_rawStrain_A90:		return "hcl_rawStrain_A90";
			case channel_hcl_rawStrain_A0:		return "hcl_rawStrain_A0";
			case channel_hcl_rawStrain_AL60:	return "hcl_rawStrain_AL60";
			case channel_hcl_rawStrain_AL150:	return "hcl_rawStrain_AL150";
			case channel_hcl_rawStrain_BR90:	return "hcl_rawStrain_BR90";
			case channel_hcl_rawStrain_BR0:		return "hcl_rawStrain_BR0";
			case channel_hcl_rawStrain_T60:		return "hcl_rawStrain_T60";
			case channel_hcl_rawStrain_B150:	return "hcl_rawStrain_B150";
			case channel_hcl_rawStrain_AR90:	return "hcl_rawStrain_AR90";
			case channel_hcl_rawStrain_AR0:		return "hcl_rawStrain_AR0";
			case channel_hcl_rawInertial_accel1: return "hcl_rawInertial_accel1";
			case channel_hcl_rawInertial_accel2: return "hcl_rawInertial_accel2";
			case channel_hcl_rawInertial_accel3: return "hcl_rawInertial_accel3";
			case channel_hcl_rawInertial_accel4: return "hcl_rawInertial_accel4";
			case channel_hcl_rawInertial_accel5: return "hcl_rawInertial_accel5";
			case channel_hcl_rawInertial_accel6: return "hcl_rawInertial_accel6";
			case channel_hcl_rawInertial_accel7: return "hcl_rawInertial_accel7";
			case channel_hcl_rawInertial_accel8: return "hcl_rawInertial_accel8";
			case channel_hcl_rawInertial_gyroX: return "hcl_rawInertial_gyroX";
			case channel_hcl_rawInertial_gyroY: return "hcl_rawInertial_gyroY";
			case channel_hcl_rawInertial_gyroZ: return "hcl_rawInertial_gyroZ";

			case channel_error_code:			return "errorCode";

			default:
				assert(false);
				return "unknown_" + Utils::toStr(channelId);
		}
	}
}