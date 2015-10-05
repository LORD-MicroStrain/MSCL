/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include "WirelessTypes.h"

#include <string>
#include <vector>

namespace mscl
{
	//API Class: WirelessChannel
	//	Represents a channel on a WirelessNode. This can be used to gain information about the channel, view current settings that are applied, and update settings on the Node.
	class WirelessChannel
	{
	public:
		//=====================================================================================================
		//API Enums: ChannelId
		//	channel_unknown						- 0	- Unknown Channel
		//	channel_1							- 1 - Channel 1
		//	channel_2							- 2 - Channel 2
		//	channel_3							- 3 - Channel 3
		//	channel_4							- 4 - Channel 4
		//	channel_5							- 5 - Channel 5
		//	channel_6							- 6 - Channel 6
		//	channel_7							- 7 - Channel 7
		//	channel_8							- 8 - Channel 8
		//	channel_9							- 9 - Channel 9
		//	channel_10							- 10 - Channel 10
		//	channel_11							- 11 - Channel 11
		//	channel_12							- 12 - Channel 12
		//	channel_13							- 13 - Channel 13
		//	channel_14							- 14 - Channel 14
		//	channel_15							- 15 - Channel 15
		//	channel_16							- 16 - Channel 16
		//	channel_digital_1					- 17 - Digital Channel 1
		//	channel_digital_2					- 18 - Digital Channel 2
		//	channel_digital_3					- 19 - Digital Channel 3
		//	channel_digital_4					- 20 - Digital Channel 4
		//	channel_digital_5					- 21 - Digital Channel 5
		//	channel_digital_6					- 22 - Digital Channel 6
		//	channel_digital_7					- 23 - Digital Channel 7
		//	channel_digital_8					- 24 - Digital Channel 8
		//	channel_digital_9					- 25 - Digital Channel 9
		//	channel_digital_10					- 26 - Digital Channel 10
		//	channel_digital_11					- 27 - Digital Channel 11
		//	channel_digital_12					- 28 - Digital Channel 12
		//	channel_digital_13					- 29 - Digital Channel 13
		//	channel_digital_14					- 30 - Digital Channel 14
		//	channel_digital_15					- 31 - Digital Channel 15
		//	channel_digital_16					- 32 - Digital Channel 16
		//	channel_structuralHealth			- 33 - Structural Health Channel
		//	channel_hcl_rawBase_mag1_x			- 34 - HCL Smart Bearing Raw Base - Mag 1 - x
		//	channel_hcl_rawBase_mag1_y			- 35 - HCL Smart Bearing Raw Base - Mag 1 - y
		//	channel_hcl_rawBase_mag1_z			- 36 - HCL Smart Bearing Raw Base - Mag 1 - z
		//	channel_hcl_rawBase_mag2_x			- 37 - HCL Smart Bearing Raw Base - Mag 2 - x
		//	channel_hcl_rawBase_mag2_y			- 38 - HCL Smart Bearing Raw Base - Mag 2 - y
		//	channel_hcl_rawBase_mag2_z			- 39 - HCL Smart Bearing Raw Base - Mag 2 - z
		//	channel_hcl_rawBase_mag3_x			- 40 - HCL Smart Bearing Raw Base - Mag 3 - x
		//	channel_hcl_rawBase_mag3_y			- 41 - HCL Smart Bearing Raw Base - Mag 3 - y
		//	channel_hcl_rawBase_mag3_z			- 42 - HCL Smart Bearing Raw Base - Mag 3 - z
		//	channel_hcl_rawBase_mag4_x			- 43 - HCL Smart Bearing Raw Base - Mag 4 - x
		//	channel_hcl_rawBase_mag4_y			- 44 - HCL Smart Bearing Raw Base - Mag 4 - y
		//	channel_hcl_rawBase_mag4_z			- 45 - HCL Smart Bearing Raw Base - Mag 4 - z
		//	channel_hcl_rawBase_mag5_x			- 46 - HCL Smart Bearing Raw Base - Mag 5 - x
		//	channel_hcl_rawBase_mag5_y			- 47 - HCL Smart Bearing Raw Base - Mag 5 - y
		//	channel_hcl_rawBase_mag5_z			- 48 - HCL Smart Bearing Raw Base - Mag 5 - z
		//	channel_hcl_rawBase_mag6_x			- 49 - HCL Smart Bearing Raw Base - Mag 6 - x
		//	channel_hcl_rawBase_mag6_y			- 50 - HCL Smart Bearing Raw Base - Mag 6 - y
		//	channel_hcl_rawBase_mag6_z			- 51 - HCL Smart Bearing Raw Base - Mag 6 - z
		//	channel_hcl_rawBase_mag7_x			- 52 - HCL Smart Bearing Raw Base - Mag 7 - x
		//	channel_hcl_rawBase_mag7_y			- 53 - HCL Smart Bearing Raw Base - Mag 7 - y
		//	channel_hcl_rawBase_mag7_z			- 54 - HCL Smart Bearing Raw Base - Mag 7 - z
		//	channel_hcl_rawBase_mag8_x			- 55 - HCL Smart Bearing Raw Base - Mag 8 - x
		//	channel_hcl_rawBase_mag8_y			- 56 - HCL Smart Bearing Raw Base - Mag 8 - y
		//	channel_hcl_rawBase_mag8_z			- 57 - HCL Smart Bearing Raw Base - Mag 8 - z
		//	channel_hcl_rawBase_gyro_x			- 58 - HCL Smart Bearing Raw Base - Gyro - x
		//	channel_hcl_rawBase_gyro_y			- 59 - HCL Smart Bearing Raw Base - Gyro - y
		//	channel_hcl_rawBase_gyro_z			- 60 - HCL Smart Bearing Raw Base - Gyro - z
		//	channel_error_code					- 61 - Error Code
		//	channel_hcl_rawStrain_BL30			- 62 - HCL Smart Bearing Raw Strain - BL30
		//	channel_hcl_rawStrain_BL120			- 63 - HCL Smart Bearing Raw Strain - BL120
		//	channel_hcl_rawStrain_A60			- 64 - HCL Smart Bearing Raw Strain - A60
		//	channel_hcl_rawStrain_A150			- 65 - HCL Smart Bearing Raw Strain - A150
		//	channel_hcl_rawStrain_AL30			- 66 - HCL Smart Bearing Raw Strain - AL30
		//	channel_hcl_rawStrain_AL120			- 67 - HCL Smart Bearing Raw Strain - AL120
		//	channel_hcl_rawStrain_BR60			- 68 - HCL Smart Bearing Raw Strain - BR60
		//	channel_hcl_rawStrain_BR150			- 69 - HCL Smart Bearing Raw Strain - BR150
		//	channel_hcl_rawStrain_B30			- 70 - HCL Smart Bearing Raw Strain - B30
		//	channel_hcl_rawStrain_T120			- 71 - HCL Smart Bearing Raw Strain - T120
		//	channel_hcl_rawStrain_AR60			- 72 - HCL Smart Bearing Raw Strain - AR60
		//	channel_hcl_rawStrain_AR150			- 73 - HCL Smart Bearing Raw Strain - AR150
		//	channel_hcl_rawStrain_A30			- 74 - HCL Smart Bearing Raw Strain - A30
		//	channel_hcl_rawStrain_A120			- 75 - HCL Smart Bearing Raw Strain - A120
		//	channel_hcl_rawStrain_BL90			- 76 - HCL Smart Bearing Raw Strain - BL90
		//	channel_hcl_rawStrain_BL180			- 77 - HCL Smart Bearing Raw Strain - BL180
		//	channel_hcl_rawStrain_BR30			- 78 - HCL Smart Bearing Raw Strain - BR30
		//	channel_hcl_rawStrain_BR120			- 79 - HCL Smart Bearing Raw Strain - BR120
		//	channel_hcl_rawStrain_AL90			- 80 - HCL Smart Bearing Raw Strain - AL90
		//	channel_hcl_rawStrain_AL180			- 81 - HCL Smart Bearing Raw Strain - AL180
		//	channel_hcl_rawStrain_AR30			- 82 - HCL Smart Bearing Raw Strain - AR30
		//	channel_hcl_rawStrain_AR120			- 83 - HCL Smart Bearing Raw Strain - AR120
		//	channel_hcl_rawStrain_B90			- 84 - HCL Smart Bearing Raw Strain - B90
		//	channel_hcl_rawStrain_T0			- 85 - HCL Smart Bearing Raw Strain - T0
		//	channel_hcl_rawStrain_BL60			- 86 - HCL Smart Bearing Raw Strain - BL60
		//	channel_hcl_rawStrain_BL150			- 87 - HCL Smart Bearing Raw Strain - BL150
		//	channel_hcl_rawStrain_A90			- 88 - HCL Smart Bearing Raw Strain - A90
		//	channel_hcl_rawStrain_A0			- 89 - HCL Smart Bearing Raw Strain - A0
		//	channel_hcl_rawStrain_AL60			- 90 - HCL Smart Bearing Raw Strain - AL60
		//	channel_hcl_rawStrain_AL150			- 91 - HCL Smart Bearing Raw Strain - AL150
		//	channel_hcl_rawStrain_BR90			- 92 - HCL Smart Bearing Raw Strain - BR90
		//	channel_hcl_rawStrain_BR0			- 93 - HCL Smart Bearing Raw Strain - BR0
		//	channel_hcl_rawStrain_T60			- 94 - HCL Smart Bearing Raw Strain - T60
		//	channel_hcl_rawStrain_B150			- 95 - HCL Smart Bearing Raw Strain - B150
		//	channel_hcl_rawStrain_AR90			- 96 - HCL Smart Bearing Raw Strain - AR90
		//	channel_hcl_rawStrain_AR0			- 97 - HCL Smart Bearing Raw Strain - AR0
		//	channel_hcl_rawInertial_accel1		- 98 - HCL Smart Bearing Raw Inertial - accel 1
		//	channel_hcl_rawInertial_accel2		- 99 - HCL Smart Bearing Raw Inertial - accel 2
		//	channel_hcl_rawInertial_accel3		- 100 - HCL Smart Bearing Raw Inertial - accel 3
		//	channel_hcl_rawInertial_accel4		- 101 - HCL Smart Bearing Raw Inertial - accel 4
		//	channel_hcl_rawInertial_accel5		- 102 - HCL Smart Bearing Raw Inertial - accel 5
		//	channel_hcl_rawInertial_accel6		- 103 - HCL Smart Bearing Raw Inertial - accel 6
		//	channel_hcl_rawInertial_accel7		- 104 - HCL Smart Bearing Raw Inertial - accel 7
		//	channel_hcl_rawInertial_accel8		- 105 - HCL Smart Bearing Raw Inertial - accel 8
		//	channel_hcl_rawInertial_gyroX		- 106 - HCL Smart Bearing Raw Inertial - gyro X
		//	channel_hcl_rawInertial_gyroY		- 107 - HCL Smart Bearing Raw Inertial - gyro Y
		//	channel_hcl_rawInertial_gyroZ		- 108 - HCL Smart Bearing Raw Inertial - gyro Z
		//=====================================================================================================
		enum ChannelId
		{
			channel_unknown					= 0,
			channel_1						= 1,
			channel_2						= 2,
			channel_3						= 3,
			channel_4						= 4,
			channel_5						= 5,
			channel_6						= 6,
			channel_7						= 7,
			channel_8						= 8,
			channel_9						= 9,
			channel_10						= 10,
			channel_11						= 11,
			channel_12						= 12,
			channel_13						= 13,
			channel_14						= 14,
			channel_15						= 15,
			channel_16						= 16,
			channel_digital_1				= 17,
			channel_digital_2				= 18,
			channel_digital_3				= 19,
			channel_digital_4				= 20,
			channel_digital_5				= 21,
			channel_digital_6				= 22,
			channel_digital_7				= 23,
			channel_digital_8				= 24,
			channel_digital_9				= 25,
			channel_digital_10				= 26,
			channel_digital_11				= 27,
			channel_digital_12				= 28,
			channel_digital_13				= 29,
			channel_digital_14				= 30,
			channel_digital_15				= 31,
			channel_digital_16				= 32,
			channel_structuralHealth		= 33,
			channel_hcl_rawBase_mag1_x		= 34,
			channel_hcl_rawBase_mag1_y		= 35,
			channel_hcl_rawBase_mag1_z		= 36,
			channel_hcl_rawBase_mag2_x		= 37,
			channel_hcl_rawBase_mag2_y		= 38,
			channel_hcl_rawBase_mag2_z		= 39,
			channel_hcl_rawBase_mag3_x		= 40,
			channel_hcl_rawBase_mag3_y		= 41,
			channel_hcl_rawBase_mag3_z		= 42,
			channel_hcl_rawBase_mag4_x		= 43,
			channel_hcl_rawBase_mag4_y		= 44,
			channel_hcl_rawBase_mag4_z		= 45,
			channel_hcl_rawBase_mag5_x		= 46,
			channel_hcl_rawBase_mag5_y		= 47,
			channel_hcl_rawBase_mag5_z		= 48,
			channel_hcl_rawBase_mag6_x		= 49,
			channel_hcl_rawBase_mag6_y		= 50,
			channel_hcl_rawBase_mag6_z		= 51,
			channel_hcl_rawBase_mag7_x		= 52,
			channel_hcl_rawBase_mag7_y		= 53,
			channel_hcl_rawBase_mag7_z		= 54,
			channel_hcl_rawBase_mag8_x		= 55,
			channel_hcl_rawBase_mag8_y		= 56,
			channel_hcl_rawBase_mag8_z		= 57,
			channel_hcl_rawBase_gyro_x		= 58,
			channel_hcl_rawBase_gyro_y		= 59,
			channel_hcl_rawBase_gyro_z		= 60,
			channel_error_code				= 61,
			channel_hcl_rawStrain_BL30		= 62,
			channel_hcl_rawStrain_BL120		= 63,
			channel_hcl_rawStrain_A60		= 64,
			channel_hcl_rawStrain_A150		= 65,
			channel_hcl_rawStrain_AL30		= 66,
			channel_hcl_rawStrain_AL120		= 67,
			channel_hcl_rawStrain_BR60		= 68,
			channel_hcl_rawStrain_BR150		= 69,
			channel_hcl_rawStrain_B30		= 70,
			channel_hcl_rawStrain_T120		= 71,
			channel_hcl_rawStrain_AR60		= 72,
			channel_hcl_rawStrain_AR150		= 73,
			channel_hcl_rawStrain_A30		= 74,
			channel_hcl_rawStrain_A120		= 75,
			channel_hcl_rawStrain_BL90		= 76,
			channel_hcl_rawStrain_BL180		= 77,
			channel_hcl_rawStrain_BR30		= 78,
			channel_hcl_rawStrain_BR120		= 79,
			channel_hcl_rawStrain_AL90		= 80,
			channel_hcl_rawStrain_AL180		= 81,
			channel_hcl_rawStrain_AR30		= 82,
			channel_hcl_rawStrain_AR120		= 83,
			channel_hcl_rawStrain_B90		= 84,
			channel_hcl_rawStrain_T0		= 85,
			channel_hcl_rawStrain_BL60		= 86,
			channel_hcl_rawStrain_BL150		= 87,
			channel_hcl_rawStrain_A90		= 88,
			channel_hcl_rawStrain_A0		= 89,
			channel_hcl_rawStrain_AL60		= 90,
			channel_hcl_rawStrain_AL150		= 91,
			channel_hcl_rawStrain_BR90		= 92,
			channel_hcl_rawStrain_BR0		= 93,
			channel_hcl_rawStrain_T60		= 94,
			channel_hcl_rawStrain_B150		= 95,
			channel_hcl_rawStrain_AR90		= 96,
			channel_hcl_rawStrain_AR0		= 97,
			channel_hcl_rawInertial_accel1	= 98,
			channel_hcl_rawInertial_accel2	= 99,
			channel_hcl_rawInertial_accel3	= 100,
			channel_hcl_rawInertial_accel4	= 101,
			channel_hcl_rawInertial_accel5	= 102,
			channel_hcl_rawInertial_accel6	= 103,
			channel_hcl_rawInertial_accel7	= 104,
			channel_hcl_rawInertial_accel8	= 105,
			channel_hcl_rawInertial_gyroX	= 106,
			channel_hcl_rawInertial_gyroY	= 107,
			channel_hcl_rawInertial_gyroZ	= 108
		};

		WirelessChannel();	//default constructor

		//Constructor: WirelessChannel
		//	Creates a WirelessChannel object.
		//
		//Parameters:
		//	chNumber - The channel number (ch1 = 1) of the channel.
		//	id - The <WirelessChannel::ChannelId> of the channel.
		//	type - The <WirelessTypes::ChannelType> of the channel.
		WirelessChannel(uint8 chNumber, WirelessChannel::ChannelId id, WirelessTypes::ChannelType type);

	private:
		

		//Variable: m_chNumber
		//	The channel number (ch1 = 1) of the channel.
		uint8 m_chNumber;

		//Variable: m_id
		//	The <WirelessChannel::ChannelId> of the channel.
		WirelessChannel::ChannelId m_id;

		//Variable: m_type
		//	The <WirelessTypes::ChannelType> of the channel.
		WirelessTypes::ChannelType m_type;

	public:
		//API Function: channelNumber
		//	Gets the channel number of this channel on the Node.
		//
		//Returns:
		//	The channel number of this channel on the Node.
		uint8 channelNumber() const;

		//API Function: id
		//	Gets the <WirelessChannel::ChannelId> of this channel.
		//	
		//Returns:
		//	The <WirelessChannel::ChannelId> of this channel.
		WirelessChannel::ChannelId id() const;

		//API Function: type
		//	Gets the <WirelessTypes::ChannelType> of this channel.
		//	
		//Returns:
		//	The <WirelessTypes::ChannelType> of this channel.
		WirelessTypes::ChannelType type() const;

		//API Function: name
		//	Gets the name of this channel. 
		//	This is the universal name that should be used for uploading to SensorCloud.
		//
		//Returns:
		//	The name of this channel.
		//
		//Exceptions:
		//	- <Error>: Unknown channel.
		std::string name() const;

#ifndef SWIG
		//Function: channelName
		//	Gets the name of the channel. 
		//	This is the universal name that should be used for uploading to SensorCloud.
		//
		//Returns:
		//	The name of the channel.
		//
		//Exceptions:
		//	- <Error>: Unknown channel.
		static std::string channelName(WirelessChannel::ChannelId channelId);
#endif
	};
	
	//API Typedef: WirelessChannels
	//	A typedef for a vector of <WirelessChannel> objects.
	typedef std::vector<WirelessChannel> WirelessChannels;
}