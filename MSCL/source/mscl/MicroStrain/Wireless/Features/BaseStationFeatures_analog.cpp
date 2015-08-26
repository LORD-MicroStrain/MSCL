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
#include "BaseStationFeatures_analog.h"

namespace mscl
{
	BaseStationFeatures_analog::BaseStationFeatures_analog(BaseStationInfo& info):
		BaseStationFeatures(info)
	{
	}

	uint8 BaseStationFeatures_analog::buttonCount() const
	{
		return 2;	//supports 2 buttons
	}

	uint8 BaseStationFeatures_analog::analogPortCount() const
	{
		return 8;	//supports 8 analog out ports
	}
}