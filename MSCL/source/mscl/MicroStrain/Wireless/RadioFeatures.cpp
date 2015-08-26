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
#include "RadioFeatures.h"

namespace mscl
{
	RadioFeatures::RadioFeatures():
		m_extendedRange(false)
	{
	}

	RadioFeatures::RadioFeatures(uint16 eepromValue)
	{
		//initialze all the features
		init(eepromValue);
	}

	void RadioFeatures::init(uint16 eepromValue)
	{
		bool xr = false;

		//if the eeprom is uninitialized
		if(eepromValue == 0xFFFF)
		{
			//we assume it doesn't know about this feature, so set to 0
			eepromValue = 0;
		}

		//bit 0 represents whether it is xr or not
		if((eepromValue >> 0) & 1)
		{
			xr = true;
		}

		//set the extended range option
		m_extendedRange = xr;
	}

	bool RadioFeatures::extendedRange()
	{
		return m_extendedRange;
	}
}