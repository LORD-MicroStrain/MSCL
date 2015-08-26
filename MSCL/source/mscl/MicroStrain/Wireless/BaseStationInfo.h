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

#include "mscl/Version.h"
#include "WirelessModels.h"
#include "WirelessTypes.h"
#include "RadioFeatures.h"

namespace mscl
{
	class BaseStation_Impl;	//forward declarations

	//Struct: BaseStationInfo
	//	Holds information (read from eeprom) about a <BaseStation>.
	struct BaseStationInfo
	{
	public:
		//Constructor: BaseStationInfo
		//	Creates a BaseStationInfo object from a <BaseStation>.
		//
		//Parameters:
		//	base - The <BaseStation_Impl> to get the info for.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		BaseStationInfo(const BaseStation_Impl& base);
		
		//Constructor: BaseStationInfo
		//	Creates a BaseStationInfo object.
		//
		//Parameters:
		//	fw - The firmware <Version> of the BaseStation.
		//	model - The <WirelessModels::BaseModel> of the BaseStation.
		//	region - The <WirelessTypes::RegionCode> of the BaseStation.
		BaseStationInfo(Version fw, WirelessModels::BaseModel model, WirelessTypes::RegionCode region);

	private:
		BaseStationInfo();	//disabled default constructor

	public:
		//Variable: firmwareVersion
		//	The firmware <Version> of the BaseStation.
		Version firmwareVersion;

		//Variable: model
		//	The <WirelessModels::BaseModel> of the BaseStation.
		WirelessModels::BaseModel model;

		//Variable: regionCode
		//	The <WirelessTypes::RegionCode> of the BaseStation.
		WirelessTypes::RegionCode regionCode;
	};
}