/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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