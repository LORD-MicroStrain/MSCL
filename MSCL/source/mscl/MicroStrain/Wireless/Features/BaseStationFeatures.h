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

#include <map>
#include <memory>
#include "mscl/MicroStrain/Wireless/BaseStationInfo.h"

namespace mscl
{	
	//API Class: BaseStationFeatures
	//	Contains information on which features are supported by a <BaseStation>.
	class BaseStationFeatures
	{
		friend class BaseStationEepromHelper;

	public:
		virtual ~BaseStationFeatures() {};

	private:
		BaseStationFeatures();	//disabled default constructor

	protected:
		//Variable: m_baseInfo
		//	The <BaseStationInfo> object containing basic information retrieved from eeprom about the BaseStation.
		BaseStationInfo m_baseInfo;

	public:
#ifndef SWIG
		//Constructor: BaseStationFeatures
		//	Creates a BaseStationFeatures object.
		//
		//Parameters:
		//	info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
		BaseStationFeatures(BaseStationInfo& info);

		//Function: create
		//	Builds and returns a BaseStationFeatures pointer based on the given parameters.
		//
		//Parameters:
		//	info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
		//
		//Returns:
		//	A BaseStationFeatures unique_ptr.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation model is not supported by MSCL.
		static std::unique_ptr<BaseStationFeatures> create(BaseStationInfo& info);
#endif

	public:
		//API Function: supportsTransmitPower
		//	Checks if a <WirelessTypes::TransmitPower> is supported by this BaseStation.
		//
		//Parameters:
		//	power - The <WirelessTypes::TransmitPower> to check if supported.
		//
		//Returns:
		//	true if the transmit power is supported, false otherwise.
		bool supportsTransmitPower(WirelessTypes::TransmitPower power) const;

		//API Function: supportsButtons
		//	Checks if the BaseStation supports Button configuration.
		//	
		//Returns:
		//	true if the BaseStation supports Button configuration, false otherwise.
		bool supportsButtons() const;

		//API Function: supportsAnalogPairing
		//	Checks if the BaseStation supports Analog Pairing configuration.
		//
		//Returns:
		//	true if the BaseStation supports Analog Pairing, false otherwise.
		bool supportsAnalogPairing() const;

		//API Function: supportsBeaconStatus
		//	Checks if the BaseStation support the beaconStatus command.
		//
		//Returns:
		//	true if the BaseStation supports the beacon status command, false otherwise.
		bool supportsBeaconStatus() const;

		//API Function: buttonCount
		//	Gets the total number of buttons that are supported.
		//
		//Returns:
		//	The total number of buttons that are supported.
		virtual uint8 buttonCount() const;

		//API Function: analogPortCount
		//	Gets the total number of analog ports that are supported.
		//
		//Returns:
		//	The total number of analog ports that are supported.
		virtual uint8 analogPortCount() const;

		//API Function: transmitPowers
		//	Gets a list of the <WirelessTypes::TransmitPowers> that are supported by this BaseStation.
		//
		//Returns:
		//	A vector of <WirelessTypes::TransmitPowers> that are supported by this BaseStation.
		virtual const WirelessTypes::TransmitPowers transmitPowers() const;
	};
}