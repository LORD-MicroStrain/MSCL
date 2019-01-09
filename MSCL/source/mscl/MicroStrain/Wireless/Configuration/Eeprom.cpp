/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Eeprom.h"
#include "mscl/Utils.h"

namespace mscl
{
    Eeprom::Eeprom(bool useCache, uint8 numRetries) :
        m_useCache(useCache),
        m_numRetries(numRetries),
        m_hasWritten(false)
    { }

    void Eeprom::useCache(bool enable)
    {
        m_useCache = enable;
    }

    void Eeprom::clearCache()
    {
        rec_mutex_lock_guard lock(m_cacheMutex);
        m_eepromCache.clear();
    }

    void Eeprom::clearCacheLocation(uint16 location)
    {
        rec_mutex_lock_guard lock(m_cacheMutex);

        //try to find the value in the map to verify it exists
        WirelessTypes::EepromMap::iterator itr = m_eepromCache.find(location);

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

    uint8 Eeprom::getNumRetries() const
    {
        return m_numRetries;
    }

    WirelessTypes::EepromMap Eeprom::getCache() const
    {
        rec_mutex_lock_guard lock(m_cacheMutex);
        return m_eepromCache;
    }

    void Eeprom::importCache(const WirelessTypes::EepromMap& eepromMap)
    {
        rec_mutex_lock_guard lock(m_cacheMutex);

        //keeps the old cache data for eeproms that aren't in the new eeprom map
        
        for(const auto& i : eepromMap)
        {
            //update or add locations from the passed in eepromMap
            m_eepromCache[i.first] = i.second;
        }
    }

    bool Eeprom::readCache(uint16 location, uint16& result)
    {
        rec_mutex_lock_guard lock(m_cacheMutex);

        WirelessTypes::EepromMap::iterator itr;

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
        rec_mutex_lock_guard lock(m_cacheMutex);

        //try to find the value in the map to see if it already exists
        WirelessTypes::EepromMap::iterator itr = m_eepromCache.find(location);

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

    void Eeprom::resetHasWritten()
    {
        m_hasWritten = false;
    }

    bool Eeprom::didWrite() const
    {
        return m_hasWritten;
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
        return Utils::make_float(b1, b2, b3, b4, Utils::littleEndian);    //note that this just swapped endianness by passing the msb as the lsb
    }

    uint32 Eeprom::readEeprom_uint32(uint16 location)
    {
        //try to read the first part of the float
        uint16 msw = readEeprom(location);

        //try to read the second part of the float
        uint16 lsw = readEeprom(location + 2);

        //make a uint32 and return
        return Utils::make_uint32(Utils::msb(msw), Utils::lsb(msw), Utils::msb(lsw), Utils::lsb(lsw));
    }

    int16 Eeprom::readEeprom_int16(uint16 location)
    {
        return static_cast<int16>(readEeprom(location));
    }

    void Eeprom::writeEeprom_float(uint16 location, float value)
    {
        //Note: floats in EEPROM for Wireless devices are in Little Endian

        uint8 b1, b2, b3, b4;

        //split the float into its 4 bytes (in little endian)
        Utils::split_float(value, b1, b2, b3, b4, Utils::littleEndian);

        //write the first eeprom location
        writeEeprom(location, Utils::make_uint16(b1, b2));

        //write the second eeprom location
        writeEeprom(location + 2, Utils::make_uint16(b3, b4)); //TODO: possibly throw a custom exception if this throws? We wrote the msw but not the lsw
    }

    void Eeprom::writeEeprom_uint32(uint16 location, uint32 value)
    {
        uint8 low = 0;
        uint8 b2 = 0;
        uint8 b3 = 0;
        uint8 high = 0;

        //split the uint32 into 2 parts
        Utils::split_uint32(value, low, b2, b3, high);

        //try to write the msw
        writeEeprom(location, Utils::make_uint16(low, b2));

        //try to write the lsw
        writeEeprom(location + 2, Utils::make_uint16(b3, high));    //TODO: possibly throw a custom exception if this throws? We wrote the msw but not the lsw
    }

    void Eeprom::writeEeprom_int16(uint16 location, int16 value)
    {
        writeEeprom(location, static_cast<uint16>(value));
    }
}