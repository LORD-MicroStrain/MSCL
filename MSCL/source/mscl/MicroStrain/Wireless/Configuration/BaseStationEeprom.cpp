/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationEeprom.h"
#include "BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"
#include "mscl/Utils.h"

namespace mscl
{
    BaseStationEeprom::BaseStationEeprom(BaseStation_Impl* base):
        Eeprom(true, 0),
        m_baseStation(base)
    { }

    bool BaseStationEeprom::updateCacheFromDevice(uint16 location)
    {
        uint16 eepromVal;

        //attempt to read the eeprom from the base station
        if(m_baseStation->read(location, eepromVal))
        {
            //update the map value with the value we read from eeprom
            updateCache(location, eepromVal);

            return true;
        }

        //all the attempts to read the eeprom failed
        return false;
    }

    uint16 BaseStationEeprom::readEeprom(uint16 location)
    {
        uint16 result;

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

        //attempt to write the value to the BaseStation
        if(m_baseStation->write(location, value))
        {
            //successfully wrote to the BaseStation, update the cache
            updateCache(location, value);

            return;
        }

        //we failed to write the value to the BaseStation

        //clear the eeprom cache for this location if we have one, just to be safe
        clearCacheLocation(location);

        throw Error_Communication("Failed to write EEPROM " + Utils::toStr(location) + " to the BaseStation.");
    }
}