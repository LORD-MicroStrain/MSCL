/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeEeprom.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/Utils.h"
#include "NodeEepromMap.h"

namespace mscl
{
    NodeEeprom::NodeEeprom(NodeAddress nodeAddress, const BaseStation& base, const WirelessProtocol& protocol, const NodeEepromSettings& settings):
        Eeprom(settings.useEepromCache, settings.numRetries),
        m_nodeAddress(nodeAddress),
        m_baseStation(base),
        m_useGroupRead(settings.useGroupRead),
        m_protocol(&protocol)
    { }

    bool NodeEeprom::updateCacheFromDevice(uint16 location)
    {
        //if we can use the page download command
        if(m_useGroupRead)
        {
            //if the location is able to be read via a page download command
            if(location <= PAGE_1_MAX_EEPROM)
            {
                uint16 pageIndex;

                //if the eeprom value can be found in downloading page 0
                if(location <= PAGE_0_MAX_EEPROM)
                {
                    pageIndex = 0;
                }
                //if the eeprom value can be found in downloading page 1
                else
                {
                    pageIndex = 1;
                }

                //attempt to download the page from the Node
                ByteStream downloadResult;
                if(m_baseStation.node_pageDownload(*m_protocol, m_nodeAddress, pageIndex, downloadResult))
                {
                    //parse the info out of the eeprom page, which updates the map values
                    parseEepromPage(downloadResult, pageIndex);

                    //successfully got the value
                    return true;
                }
            }
        }

        //if we got here, we need to read the eeprom value individually    from the node
        uint16 eepromVal;

        uint8 retryCount = 0;

        do
        {
            //attempt to read the individual eeprom from the node
            if(m_baseStation.node_readEeprom(*m_protocol, m_nodeAddress, location, eepromVal))
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

    void NodeEeprom::parseEepromPage(const ByteStream& pageData, uint16 pageIndex)
    {
        //get the number of bytes in the page ByteStream
        uint16 dataLength = static_cast<uint16>(pageData.size());
        uint16 mapLocation;

        //loop through all the data in the page
        for(uint16 pos = 0; pos < dataLength; pos += 2)
        {
            //calculate the eeprom location that this value should be stored in in the map
            mapLocation = pos + (EEPROMS_PER_PAGE * pageIndex);

            //just storing everything as uint16 
            uint16 eepromVal = pageData.read_uint16(pos);

            //update the cache value
            updateCache(mapLocation, eepromVal);
        }
    }

    void NodeEeprom::updateSettings(const NodeEepromSettings& settings)
    {
        //update all of the provided settings
        m_useGroupRead = settings.useGroupRead;
        setNumRetries(settings.numRetries);
        useCache(settings.useEepromCache);
    }

    void NodeEeprom::setBaseStation(const BaseStation& base)
    {
        m_baseStation = base;
    }

    uint16 NodeEeprom::readEeprom(uint16 location)
    {
        uint16 result;

        bool canCacheEeprom = NodeEepromMap::canUseCache_read(location);

        //if we want to pull from the cache
        if(m_useCache && canCacheEeprom)
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
        throw Error_NodeCommunication(m_nodeAddress, "Failed to read EEPROM " + Utils::toStr(location) + " from Node " + Utils::toStr(m_nodeAddress));
    }

    void NodeEeprom::writeEeprom(uint16 location, uint16 value)
    {
        //if we want to check the cache
        if(m_useCache && NodeEepromMap::canUseCache_write(location))
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
        
        //clear the eeprom cache for this location if we have one, just to be safe
        clearCacheLocation(location);

        uint8 retryCount = 0;

        do
        {
            //attempt to write the value to the Node
            if(m_baseStation.node_writeEeprom(*m_protocol, m_nodeAddress, location, value))
            {
                //successfully wrote to the Node, update the cache
                updateCache(location, value);

                return;
            }
        }
        while(retryCount++ < m_numRetries);

        //we failed to write the value to the Node

        throw Error_NodeCommunication(m_nodeAddress, "Failed to write EEPROM " + Utils::toStr(location) + " to Node " + Utils::toStr(m_nodeAddress));
    }
}