/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "BaseStationEeprom.h"
#include "BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"
#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"
#include "mscl/Utils.h"

namespace mscl
{
    BaseStationEeprom::BaseStationEeprom(BaseStation_Impl* base):
        Eeprom(true, 2),
        m_baseStation(base)
    { }

    bool BaseStationEeprom::updateCacheFromDevice(uint16 location)
    {
        uint16 eepromVal;

        uint8 retryCount = 0;

        do
        {
            //attempt to read the eeprom from the base station
            if(m_baseStation->read(location, eepromVal))
            {
                //update the map value with the value we read from eeprom
                updateCache(location, eepromVal);

                return true;
            }
        }
        while(retryCount++ < m_numRetries);

        //all the attempts to read the eeprom failed
        return false;
    }

    uint16 BaseStationEeprom::readEeprom(uint16 location)
    {
        uint16 result;

        if(location >= 1024)
        {
            //verify we can read eeproms 1024 and above (otherwise Node will wrap around)
            if(!m_baseStation->features().supportsEeprom1024AndAbove())
            {
                throw Error_NotSupported("EEPROM " + Utils::toStr(location) + " is not supported.");
            }
        }

        //if we want to pull from the cache
        if(m_useCache && BaseStationEepromMap::canUseCache_read(location))
        {
            //attempt to read the value from the cache
            if(readCache(location, result))
            {
                //the value was found in the cache, just return the result
                return result;
            }
        }

        //we didn't get a value from the cache

        rec_mutex_lock_guard lock(m_cacheMutex);    //locking here so cache doesn't change between updateCacheFromDevice and readCache

        //attempt to read the value from the device
        if(updateCacheFromDevice(location))
        {
            //successfully read from the device, the cache has been updated so read from it
            readCache(location, result);

            return result;
        }

        //we failed to read the eeprom value from the cache or the device
        throw Error_Communication("Failed to read EEPROM " + Utils::toStr(location) + " from the BaseStation.");
    }

    void BaseStationEeprom::writeEeprom(uint16 location, uint16 value)
    {
        if(location >= 1024)
        {
            //verify we can read eeproms 1024 and above (otherwise Node will wrap around)
            if(!m_baseStation->features().supportsEeprom1024AndAbove())
            {
                throw Error_NotSupported("EEPROM " + Utils::toStr(location) + " is not supported.");
            }
        }

        //if we want to check the cache
        if(m_useCache && BaseStationEepromMap::canUseCache_write(location))
        {
            //attempt to read the value from the cache
            uint16 valInCache;
            if(readCache(location, valInCache))
            {
                //if the value in the cache is the same we are trying to write
                if(valInCache == value)
                {
                    //do not need to write anything, just return
                    return;
                }
            }
        }

        //if we made it here, we want to actually write to the device

        try
        {
            uint8 retryCount = 0;

            do
            {
                //attempt to write the value to the BaseStation
                if(m_baseStation->write(location, value))
                {
                    //successfully wrote to the BaseStation, update the cache
                    m_hasWritten = true;
                    updateCache(location, value);

                    return;
                }
            }
            while(retryCount++ < m_numRetries);
        }
        catch(...)
        {
            //clear the eeprom cache for this location if we have one, just to be safe
            clearCacheLocation(location);

            //rethrow the exception
            throw;
        }

        //we failed to write the value to the BaseStation

        //clear the eeprom cache for this location if we have one
        clearCacheLocation(location);

        throw Error_Communication("Failed to write EEPROM " + Utils::toStr(location) + " to the BaseStation.");
    }
}
