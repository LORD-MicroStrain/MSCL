/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "EepromLocation.h"

namespace mscl
{
    uint16 EepromLocation::m_nextId = 0;

    EepromLocation::EepromLocation(uint16 location, ValueType valueType, const std::string& description):
        m_id(m_nextId++),        //set the id to the next id, then increment the value
        m_location(location),
        m_valueType(valueType),
        m_description(description)
    {}

    EepromLocation::EepromLocation(uint16 idCopy, uint16 location, ValueType valueType, const std::string& description):
        m_id(idCopy),
        m_location(location),
        m_valueType(valueType),
        m_description(description)
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

    std::string EepromLocation::description() const
    {
        return m_description + " (EEPROM " + Utils::toStr(m_location) + ")";
    }
}