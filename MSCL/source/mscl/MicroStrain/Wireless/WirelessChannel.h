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
		//	channel_unknown				- 0	- Unknown Channel
		//	channel_1					- 1 - Channel 1
		//	channel_2					- 2 - Channel 2
		//	channel_3					- 3 - Channel 3
		//	channel_4					- 4 - Channel 4
		//	channel_5					- 5 - Channel 5
		//	channel_6					- 6 - Channel 6
		//	channel_7					- 7 - Channel 7
		//	channel_8					- 8 - Channel 8
		//	channel_9					- 9 - Channel 9
		//	channel_10					- 10 - Channel 10
		//	channel_11					- 11 - Channel 11
		//	channel_12					- 12 - Channel 12
		//	channel_13					- 13 - Channel 13
		//	channel_14					- 14 - Channel 14
		//	channel_15					- 15 - Channel 15
		//	channel_16					- 16 - Channel 16
		//	channel_digital_1			- 17 - Digital Channel 1
		//	channel_digital_2			- 18 - Digital Channel 2
		//	channel_digital_3			- 19 - Digital Channel 3
		//	channel_digital_4			- 20 - Digital Channel 4
		//	channel_digital_5			- 21 - Digital Channel 5
		//	channel_digital_6			- 22 - Digital Channel 6
		//	channel_digital_7			- 23 - Digital Channel 7
		//	channel_digital_8			- 24 - Digital Channel 8
		//	channel_digital_9			- 25 - Digital Channel 9
		//	channel_digital_10			- 26 - Digital Channel 10
		//	channel_digital_11			- 27 - Digital Channel 11
		//	channel_digital_12			- 28 - Digital Channel 12
		//	channel_digital_13			- 29 - Digital Channel 13
		//	channel_digital_14			- 30 - Digital Channel 14
		//	channel_digital_15			- 31 - Digital Channel 15
		//	channel_digital_16			- 32 - Digital Channel 16
		//	channel_structuralHealth	- 33 - Structural Health Channel
		//	channel_hcl_rawBase_mag1_x	- 34 - HCL Smart Bearing Raw Base - Mag 1 - x
		//	channel_hcl_rawBase_mag1_y	- 35 - HCL Smart Bearing Raw Base - Mag 1 - y
		//	channel_hcl_rawBase_mag1_z	- 36 - HCL Smart Bearing Raw Base - Mag 1 - z
		//	channel_hcl_rawBase_mag2_x	- 37 - HCL Smart Bearing Raw Base - Mag 2 - x
		//	channel_hcl_rawBase_mag2_y	- 38 - HCL Smart Bearing Raw Base - Mag 2 - y
		//	channel_hcl_rawBase_mag2_z	- 39 - HCL Smart Bearing Raw Base - Mag 2 - z
		//	channel_hcl_rawBase_mag3_x	- 40 - HCL Smart Bearing Raw Base - Mag 3 - x
		//	channel_hcl_rawBase_mag3_y	- 41 - HCL Smart Bearing Raw Base - Mag 3 - y
		//	channel_hcl_rawBase_mag3_z	- 42 - HCL Smart Bearing Raw Base - Mag 3 - z
		//	channel_hcl_rawBase_mag4_x	- 43 - HCL Smart Bearing Raw Base - Mag 4 - x
		//	channel_hcl_rawBase_mag4_y	- 44 - HCL Smart Bearing Raw Base - Mag 4 - y
		//	channel_hcl_rawBase_mag4_z	- 45 - HCL Smart Bearing Raw Base - Mag 4 - z
		//	channel_hcl_rawBase_mag5_x	- 46 - HCL Smart Bearing Raw Base - Mag 5 - x
		//	channel_hcl_rawBase_mag5_y	- 47 - HCL Smart Bearing Raw Base - Mag 5 - y
		//	channel_hcl_rawBase_mag5_z	- 48 - HCL Smart Bearing Raw Base - Mag 5 - z
		//	channel_hcl_rawBase_mag6_x	- 49 - HCL Smart Bearing Raw Base - Mag 6 - x
		//	channel_hcl_rawBase_mag6_y	- 50 - HCL Smart Bearing Raw Base - Mag 6 - y
		//	channel_hcl_rawBase_mag6_z	- 51 - HCL Smart Bearing Raw Base - Mag 6 - z
		//	channel_hcl_rawBase_mag7_x	- 52 - HCL Smart Bearing Raw Base - Mag 7 - x
		//	channel_hcl_rawBase_mag7_y	- 53 - HCL Smart Bearing Raw Base - Mag 7 - y
		//	channel_hcl_rawBase_mag7_z	- 54 - HCL Smart Bearing Raw Base - Mag 7 - z
		//	channel_hcl_rawBase_mag8_x	- 55 - HCL Smart Bearing Raw Base - Mag 8 - x
		//	channel_hcl_rawBase_mag8_y	- 56 - HCL Smart Bearing Raw Base - Mag 8 - y
		//	channel_hcl_rawBase_mag8_z	- 57 - HCL Smart Bearing Raw Base - Mag 8 - z
		//	channel_hcl_rawBase_gyro_x	- 58 - HCL Smart Bearing Raw Base - Gyro - x
		//	channel_hcl_rawBase_gyro_y	- 59 - HCL Smart Bearing Raw Base - Gyro - y
		//	channel_hcl_rawBase_gyro_z	- 60 - HCL Smart Bearing Raw Base - Gyro - z
		//	channel_error_code			- 61 - Error Code
		//=====================================================================================================
		enum ChannelId
		{
			channel_unknown				= 0,
			channel_1					= 1,
			channel_2					= 2,
			channel_3					= 3,
			channel_4					= 4,
			channel_5					= 5,
			channel_6					= 6,
			channel_7					= 7,
			channel_8					= 8,
			channel_9					= 9,
			channel_10					= 10,
			channel_11					= 11,
			channel_12					= 12,
			channel_13					= 13,
			channel_14					= 14,
			channel_15					= 15,
			channel_16					= 16,
			channel_digital_1			= 17,
			channel_digital_2			= 18,
			channel_digital_3			= 19,
			channel_digital_4			= 20,
			channel_digital_5			= 21,
			channel_digital_6			= 22,
			channel_digital_7			= 23,
			channel_digital_8			= 24,
			channel_digital_9			= 25,
			channel_digital_10			= 26,
			channel_digital_11			= 27,
			channel_digital_12			= 28,
			channel_digital_13			= 29,
			channel_digital_14			= 30,
			channel_digital_15			= 31,
			channel_digital_16			= 32,
			channel_structuralHealth	= 33,
			channel_hcl_rawBase_mag1_x	= 34,
			channel_hcl_rawBase_mag1_y	= 35,
			channel_hcl_rawBase_mag1_z	= 36,
			channel_hcl_rawBase_mag2_x	= 37,
			channel_hcl_rawBase_mag2_y	= 38,
			channel_hcl_rawBase_mag2_z	= 39,
			channel_hcl_rawBase_mag3_x	= 40,
			channel_hcl_rawBase_mag3_y	= 41,
			channel_hcl_rawBase_mag3_z	= 42,
			channel_hcl_rawBase_mag4_x	= 43,
			channel_hcl_rawBase_mag4_y	= 44,
			channel_hcl_rawBase_mag4_z	= 45,
			channel_hcl_rawBase_mag5_x	= 46,
			channel_hcl_rawBase_mag5_y	= 47,
			channel_hcl_rawBase_mag5_z	= 48,
			channel_hcl_rawBase_mag6_x	= 49,
			channel_hcl_rawBase_mag6_y	= 50,
			channel_hcl_rawBase_mag6_z	= 51,
			channel_hcl_rawBase_mag7_x	= 52,
			channel_hcl_rawBase_mag7_y	= 53,
			channel_hcl_rawBase_mag7_z	= 54,
			channel_hcl_rawBase_mag8_x	= 55,
			channel_hcl_rawBase_mag8_y	= 56,
			channel_hcl_rawBase_mag8_z	= 57,
			channel_hcl_rawBase_gyro_x	= 58,
			channel_hcl_rawBase_gyro_y	= 59,
			channel_hcl_rawBase_gyro_z	= 60,
			channel_error_code			= 61
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