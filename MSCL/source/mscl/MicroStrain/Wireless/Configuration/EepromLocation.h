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
	//Class: EepromLocation
	//	Represents a single Eeprom Location.
	class EepromLocation
	{
	private:
		//Variable: m_nextId
		//	Used for setting a unique id for every EepromLocation that is created.
		static uint16 m_nextId;

	private:
		//Variable: m_id
		//	A unique id for this EepromLocation object.
		uint16 m_id;

		//Variable: m_location
		//	The actual EEPROM location on the device.
		uint16 m_location;

		//Variable: m_valueType
		//	The <ValueType> of this value in EEPROM.
		ValueType m_valueType;

	public:
		//Constructor: EepromLocation
		//	Creates an EepromLocation object. The id is assigned automatically.
		EepromLocation(uint16 location, ValueType valueType);

		//Constructor: EepromLocation
		//	Creates an EepromLocation object with a specific id.
		//	Note: this should be used only when making a copy of an EepromLocation if you know the id, location, and type.
		EepromLocation(uint16 idCopy, uint16 location, ValueType valueType);

		//Operator: <
		//	Less than operator for comparing Eeprom Locations (ids).
		bool operator<(const EepromLocation& other) const;

		//Operator: ==
		//	Equal operator for comparing Eeprom Locations (ids).
		bool operator==(const EepromLocation& other) const;

	private:
		EepromLocation(); //disabled default constructor 

	public:
		//Function: id
		//	Gets the id of the EepromLocation..
		uint16 id() const;

		//Function: location
		//	Gets the actual EEPROM location on the device.
		uint16 location() const;

		//Function: valueType
		//	Gets the <ValueType> of this value in EEPROM.
		ValueType valueType() const;
	};
}