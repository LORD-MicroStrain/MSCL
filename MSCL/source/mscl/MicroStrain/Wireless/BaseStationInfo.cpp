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
#include "BaseStationInfo.h"
#include "BaseStation_Impl.h"

namespace mscl
{
	//read the required information from the BaseStation and store in the BaseStationInfo
	BaseStationInfo::BaseStationInfo(const BaseStation_Impl& base) :
		firmwareVersion(base.firmwareVersion()),
		model(base.model()),
		regionCode(base.regionCode())
	{
	}

	BaseStationInfo::BaseStationInfo(Version fw, WirelessModels::BaseModel model, WirelessTypes::RegionCode region):
		firmwareVersion(fw),
		model(model),
		regionCode(region)
	{
	}
}