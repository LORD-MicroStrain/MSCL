/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "EepromLocation.h"

namespace mscl
{
	uint16 EepromLocation::m_nextId = 0;

	EepromLocation::EepromLocation(uint16 location, ValueType valueType):
		m_id(m_nextId++),		//set the id to the next id, then increment the value
		m_location(location),
		m_valueType(valueType)
	{}

	EepromLocation::EepromLocation(uint16 idCopy, uint16 location, ValueType valueType):
		m_id(idCopy),
		m_location(location),
		m_valueType(valueType)
	{}

	bool EepromLocation::operator<(const EepromLocation& other) const
	{
		return m_id < other.m_id;
	}

	bool EepromLocation::operator==(const EepromLocation& other) const
	{
		return m_id == other.m_id;
	}

	uint16 EepromLocation::id() const
	{
		return m_id;
	}

	uint16 EepromLocation::location() const
	{
		return m_location;
	}

	ValueType EepromLocation::valueType() const
	{
		return m_valueType;
	}
}