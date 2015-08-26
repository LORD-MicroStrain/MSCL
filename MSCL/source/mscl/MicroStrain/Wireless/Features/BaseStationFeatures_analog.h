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
#pragma once

#include "BaseStationFeatures.h"

namespace mscl
{	
	//Class: BaseStationFeatures_analog
	//	Contains information on features for the analog BaseStation.
	class BaseStationFeatures_analog : public BaseStationFeatures
	{
	public:
		virtual ~BaseStationFeatures_analog() {}

		//Constructor: BaseStationFeatures_analog
		//	Creates a BaseStationFeatures_analog object.
		//
		//Parameters:
		//	info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
		BaseStationFeatures_analog(BaseStationInfo& info);

		//Function: buttonCount
		//	Gets the total number of buttons that are supported.
		//
		//Returns:
		//	The total number of buttons that are supported.
		virtual uint8 buttonCount() const override;

		//Function: analogPortCount
		//	Gets the total number of analog ports that are supported.
		//
		//Returns:
		//	The total number of analog ports that are supported.
		virtual uint8 analogPortCount() const override;
	};
}