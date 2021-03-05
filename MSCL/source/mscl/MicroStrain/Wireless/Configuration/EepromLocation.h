/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"

namespace mscl
{
    //Class: EepromLocation
    //    Represents a single Eeprom Location.
    class EepromLocation
    {
    private:
        //Variable: m_nextId
        //    Used for setting a unique id for every EepromLocation that is created.
        static uint16 m_nextId;

    private:
        //Variable: m_id
        //    A unique id for this EepromLocation object.
        uint16 m_id;

        //Variable: m_location
        //    The actual EEPROM location on the device.
        uint16 m_location;

        //Variable: m_valueType
        //    The <ValueType> of this value in EEPROM.
        ValueType m_valueType;

        //Variable: m_desription
        //  The string description of the EEPROM location.
        std::string m_description;

    public:
        //Constructor: EepromLocation
        //    Creates an EepromLocation object. The id is assigned automatically.
        EepromLocation(uint16 location, ValueType valueType, const std::string& description);

        //Constructor: EepromLocation
        //    Creates an EepromLocation object with a specific id.
        //    Note: this should be used only when making a copy of an EepromLocation if you know the id, location, and type.
        EepromLocation(uint16 idCopy, uint16 location, ValueType valueType, const std::string& description);

        //Operator: <
        //    Less than operator for comparing Eeprom Locations (ids).
        bool operator<(const EepromLocation& other) const;

        //Operator: ==
        //    Equal operator for comparing Eeprom Locations (ids).
        bool operator==(const EepromLocation& other) const;

    private:
        EepromLocation() = delete; //disabled default constructor 

    public:
        //Function: id
        //    Gets the id of the EepromLocation..
        uint16 id() const;

        //Function: location
        //    Gets the actual EEPROM location on the device.
        uint16 location() const;

        //Function: valueType
        //    Gets the <ValueType> of this value in EEPROM.
        ValueType valueType() const;

        //Function: description
        //  Gets a description of this EEPROM location.
        std::string description() const;
    };
}