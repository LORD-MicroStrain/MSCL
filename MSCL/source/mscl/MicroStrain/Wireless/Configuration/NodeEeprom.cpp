/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeEeprom.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/Utils.h"
#include "NodeEepromMap.h"

namespace mscl
{
    NodeEeprom::NodeEeprom(const WirelessNode_Impl* node, const BaseStation& base, const NodeEepromSettings& settings):
        Eeprom(settings.useEepromCache, settings.numRetries),
        m_node(node),
        m_baseStation(base),
        m_useGroupRead(settings.useGroupRead)
    { }

    bool NodeEeprom::updateCacheFromDevice(uint16 location)
    {
        uint8 retryCount = 0;

        //if we can use the page download command
        if(m_useCache && m_useGroupRead)    //if m_useCache is disabled, not much point in doing a group read...revert to single read eeprom
        {
            const WirelessProtocol& nodeProtocol = m_node->protocol(m_baseStation.communicationProtocol());

            retryCount++;   //lets count the group read as a try

            //use Batch EEPROM read if supported
            if(nodeProtocol.supportsBatchEepromRead())
            {
                std::map<uint16, uint16> eepromMap;
                if(m_baseStation.node_batchEepromRead(nodeProtocol, m_node->nodeAddress(), location, eepromMap))
                {
                    parseBatchEepromResult(eepromMap);

                    //successfully got the value
                    return true;
                }
            }
            else
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

                    //attempt to download the page from the Node (use the protocol mode the BaseStation is currently in)
                    ByteStream downloadResult;
                    if(m_baseStation.node_pageDownload(nodeProtocol, m_node->nodeAddress(), pageIndex, downloadResult))
                    {
                        //parse the info out of the eeprom page, which updates the map values
                        parseEepromPage(downloadResult, pageIndex);

                        //successfully got the value
                        return true;
                    }
                }
            }
        }

        //if we got here, we need to read the eeprom value individually from the node
        uint16 eepromVal;

        do
        {
            //attempt to read the individual eeprom from the node (use the protocol mode the BaseStation is currently in)
            if(m_baseStation.node_readEeprom(m_node->protocol(m_baseStation.communicationProtocol()), m_node->nodeAddress(), location, eepromVal))
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
        rec_mutex_lock_guard lock(m_cacheMutex);    //don't allow accessing cache until we have updated all the new values

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

    void NodeEeprom::parseBatchEepromResult(const std::map<uint16, uint16> eepromMap)
    {
        rec_mutex_lock_guard lock(m_cacheMutex);    //don't allow accessing cache until we have updated all the new values

        //loop through all eeprom locations and values and update the cache
        for(const auto& i : eepromMap)
        {
            updateCache(i.first, i.second);
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

        if(location >= 1024)
        {
            //verify we can read eeproms 1024 and above (otherwise Node will wrap around)
            if(!m_node->features().supportsEeprom1024AndAbove())
            {
                throw Error_NotSupported("EEPROM " + Utils::toStr(location) + " is not supported.");
            }
        }

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

        rec_mutex_lock_guard lock(m_cacheMutex);    //locking here so cache doesn't change between updateCacheFromDevice and readCache

        //attempt to read the value from the device 
        if(updateCacheFromDevice(location))
        {
            //successfully read from the device, the cache has been updated so read from it
            if(readCache(location, result))
            {
                return result;
            }
        }

        //we failed to read the eeprom value from the cache or the device
        throw Error_NodeCommunication(m_node->nodeAddress(), "Failed to read EEPROM " + Utils::toStr(location) + " from Node " + Utils::toStr(m_node->nodeAddress()));
    }

    void NodeEeprom::writeEeprom(uint16 location, uint16 value)
    {
        if(location >= 1024)
        {
            //verify we can read eeproms 1024 and above (otherwise Node will wrap around)
            if(!m_node->features().supportsEeprom1024AndAbove())
            {
                throw Error_NotSupported("EEPROM " + Utils::toStr(location) + " is not supported.");
            }
        }

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
        
        try
        {
            uint8 retryCount = 0;

            do
            {
                //attempt to write the value to the Node (use the protocol mode the BaseStation is currently in)
                if(m_baseStation.node_writeEeprom(m_node->protocol(m_baseStation.communicationProtocol()), m_node->nodeAddress(), location, value))
                {
                    //successfully wrote to the Node, update the cache
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

        //we failed to write the value to the Node

        //clear the eeprom cache for this location if we have one, just to be safe
        clearCacheLocation(location);

        throw Error_NodeCommunication(m_node->nodeAddress(), "Failed to write EEPROM " + Utils::toStr(location) + " to Node " + Utils::toStr(m_node->nodeAddress()));
    }
}