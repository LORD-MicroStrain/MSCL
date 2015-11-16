/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Eeprom.h"
#include "mscl/Utils.h"

namespace mscl
{
    Eeprom::Eeprom(bool useCache, uint8 numRetries) :
        m_useCache(useCache),
        m_numRetries(numRetries)
    { }

    void Eeprom::useCache(bool enable)
    {
        m_useCache = enable;
    }

    void Eeprom::clearCache()
    {
        m_eepromCache.clear();
    }

    void Eeprom::clearCacheLocation(uint16 location)
    {
        //try to find the value in the map to verify it exists
        EepromMap::iterator itr = m_eepromCache.find(location);

        //if the location does exist in the map
        if(itr != m_eepromCache.end())
        {
            //remove the value from the map
            m_eepromCache.erase(itr);
        }
    }

    void Eeprom::setNumRetries(uint8 retries)
    {
        m_numRetries = retries;
    }

    uint8 Eeprom::getNumRetries()
    {
        return m_numRetries;
    }

    bool Eeprom::readCache(uint16 location, uint16& result)
    {
        EepromMap::iterator itr;

        //look up the eeprom in the cache
        itr = m_eepromCache.find(location);

        //if we found the eeprom in the cache
        if(itr != m_eepromCache.end())
        {
            //store the result
            result = itr->second;

            return true;
        }
        
        //we failed to find the eeprom in the cache
        return false;
    }

    void Eeprom::updateCache(uint16 location, uint16 value)
    {
        //try to find the value in the map to see if it already exists
        EepromMap::iterator itr = m_eepromCache.find(location);

        //if we couldn't find the value in the map
        if(itr == m_eepromCache.end())
        {
            //insert the value into the map
            m_eepromCache.insert(std::pair<uint16, uint16>(location, value));
        }
        //if we found the value in the map
        else
        {
            //update the value in the map
            itr->second = value;
        }
    }

    Value Eeprom::readEeprom(const EepromLocation& location)
    {
        //get the type and location from the EepromLocation object
        ValueType type = location.valueType();
        uint16 eepromLoc = location.location();

        //determine which readEeprom function to call, based on the valueType
        switch(type)
        {
            case valueType_uint16:
                return Value(type, readEeprom(eepromLoc));

            case valueType_float:
                return Value(type, readEeprom_float(eepromLoc));

            case valueType_uint32:
                return Value(type, readEeprom_uint32(eepromLoc));

            case valueType_int16:
                return Value(type, readEeprom_int16(eepromLoc));

            default:
                assert(false);    //we are trying to read a value with an invalid type? 
                return Value(type, readEeprom(eepromLoc));    //just default to uint16
        }
    }

    void Eeprom::writeEeprom(const EepromLocation& location, const Value& val)
    {
        //get the type and location from the EepromLocation object
        ValueType type = location.valueType();
        uint16 eepromLoc = location.location();

        //determine which writeEeprom function to call, based on the valueType
        switch(type)
        {
            case valueType_uint16:
                writeEeprom(eepromLoc, val.as_uint16());
                break;

            case valueType_float:
                writeEeprom_float(eepromLoc, val.as_float());
                break;

            case valueType_uint32:
                writeEeprom_uint32(eepromLoc, val.as_uint32());
                break;

            case valueType_int16:
                writeEeprom_int16(eepromLoc, val.as_int16());
                break;

            default:
                assert(false);    //we are trying to write a value with an invalid type? 
                writeEeprom(eepromLoc, val.as_uint16());    //just default to uint16
        }
    }

    float Eeprom::readEeprom_float(uint16 location)
    {
        //try to read the first part of the float
        uint16 msw = readEeprom(location);

        //try to read the second part of the float
        uint16 lsw = readEeprom(location + 2);

        //split the words into bytes
        uint8 b1, b2, b3, b4;
        Utils::split_uint16(msw, b1, b2);
        Utils::split_uint16(lsw, b3, b4);

        //convert the values into a float and return
        return Utils::make_float_little_endian(b1, b2, b3, b4);    //note that this just swapped endianness by passing the msb as the lsb
    }

    uint32 Eeprom::readEeprom_uint32(uint16 location)
    {
        //try to read the first part of the float
        uint16 msw = readEeprom(location);

        //try to read the second part of the float
        uint16 lsw = readEeprom(location + 2);

        //make a uint32 and return
        return Utils::make_uint32(msw, lsw);
    }

    int16 Eeprom::readEeprom_int16(uint16 location)
    {
        return static_cast<int16>(readEeprom(location));
    }

    void Eeprom::writeEeprom_float(uint16 location, float value)
    {
        uint8 b1, b2, b3, b4;

        //split the float into its 4 bytes (in little endian)
        Utils::split_float_little_endian(value, b1, b2, b3, b4);

        //write the first eeprom location
        writeEeprom(location, Utils::make_uint16(b1, b2));

        //write the second eeprom location
        writeEeprom(location + 2, Utils::make_uint16(b3, b4)); //TODO: possibly throw a custom exception if this throws? We wrote the msw but not the lsw
    }

    void Eeprom::writeEeprom_uint32(uint16 location, uint32 value)
    {
        uint16 msw = 0;
        uint16 lsw = 0;

        //split the uint32 into 2 parts
        Utils::split_uint32(value, msw, lsw);

        //try to write the msw
        writeEeprom(location, msw);

        //try to write the lsw
        writeEeprom(location + 2, lsw);    //TODO: possibly throw a custom exception if this throws? We wrote the msw but not the lsw
    }

    void Eeprom::writeEeprom_int16(uint16 location, int16 value)
    {
        writeEeprom(location, static_cast<uint16>(value));
    }
}