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

#include "mscl/Types.h"

namespace mscl
{
	//API Class: RadioFeatures
	//	Represents radio features of a <WirelessNode>.
	class RadioFeatures
	{
	private:
		//Variable: m_extendedRange
		//	Whether or not the radio is XR capable
		bool m_extendedRange;

	public:
		//API Default Constructor: RadioFeatures
		//	Creates a default RadioFeatures object
		RadioFeatures();

		//API Constructor: RadioFeatures
		//	Creates a RadioFeatures object from the eeprom value
		//
		//Parameters:
		//	eepromValue - The value from eeprom that determines the radio features
		RadioFeatures(uint16 eepromValue);

	public:
		//API Function: extendedRange
		//	Gets whether or not the Node is XR (has an extended range radio)
		//
		//Returns:
		//	true if the Node has an XR radio, false otherwise
		bool extendedRange();

	private:
		//Function: init
		//	Sets all the radio features from the given eeprom value
		//
		//Parameters:
		//	eepromValue - The value from eeprom that determines the radio features
		void init(uint16 eepromValue);
	};
}