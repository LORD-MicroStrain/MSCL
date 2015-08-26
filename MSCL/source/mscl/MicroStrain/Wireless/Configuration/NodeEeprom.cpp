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
#include "stdafx.h"
#include "NodeEeprom.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/Utils.h"
#include "NodeEepromMap.h"

namespace mscl
{
	NodeEeprom::NodeEeprom(NodeAddress nodeAddress, const BaseStation& base, bool useCache) : //useCache=true
		Eeprom(useCache),
		m_nodeAddress(nodeAddress),
		m_readWriteVersion(0),
		m_baseStation(base)
	{ }

	bool NodeEeprom::determineReadWriteVersion()
	{
		uint8 originalVersion = m_readWriteVersion;

		uint16 fwVersionEeprom = NodeEepromMap::FIRMWARE_VER.location();
		uint16 fwValue = 0;

		//check if the value is already in the cache
		if(m_eepromCache.find(fwVersionEeprom) == m_eepromCache.end())
		{
			//value was not found in the cache

			//set the version to 2
			m_readWriteVersion = 2;

			//try to read using v2
			if(!updateCacheFromDevice(fwVersionEeprom))
			{
				//failed to read with version 2

				//set the version to 1
				m_readWriteVersion = 1;

				//try to read using v1
				if(!updateCacheFromDevice(fwVersionEeprom, false))
				{
					//failed to read with version 1

					//set the read/write version back to its original value
					m_readWriteVersion = originalVersion;

					return false;
				}
			}
		}

		//if we got here, we successfully got the firmware version somewhere

		//value was updated in the cache successfully, now read it out
		readCache(fwVersionEeprom, fwValue);

		//build the fw version currently found on the node
		Version fwVersion(Utils::msb(fwValue), Utils::lsb(fwValue));

		static const Version MIN_FW_EEPROM2(8, 21);

		if(fwVersion >= MIN_FW_EEPROM2)
		{
			m_readWriteVersion = 2;
		}
		else
		{
			m_readWriteVersion = 1;
		}

		return true;
	}

	bool NodeEeprom::updateCacheFromDevice(uint16 location, bool canUseGroupDownload)
	{
		//if we can use the page download command
		if(canUseGroupDownload)
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
				if(m_baseStation.node_pageDownload(m_nodeAddress, pageIndex, downloadResult))
				{
					//parse the info out of the eeprom page, which updates the map values
					parseEepromPage(downloadResult, pageIndex);

					//successfully got the value
					return true;
				}
			}
		}

		//if we got here, we need to read the eeprom value individually	from the node
		uint16 eepromVal;

		//if the read/write version is unknown
		if(m_readWriteVersion == 0)
		{
			//try to determine the version of the read/write eeprom cmd
			if(!determineReadWriteVersion())
			{
				//failed to get the read/write version

				return false;
			}
		}

		//attempt to read the individual eeprom from the node
		if(m_baseStation.node_readEeprom(m_readWriteVersion, m_nodeAddress, location, eepromVal))
		{
			//update the map value with the value we read from eeprom
			updateCache(location, eepromVal);

			return true;
		}

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
		if(updateCacheFromDevice(location, canCacheEeprom))
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

		//if the read/write version is unknown
		if(m_readWriteVersion == 0)
		{
			//try to determine the version of the read/write eeprom cmd
			if(!determineReadWriteVersion())
			{
				//failed to get the read/write version
				throw Error_NodeCommunication(m_nodeAddress, "Failed to write EEPROM " + Utils::toStr(location) + " to Node " + Utils::toStr(m_nodeAddress));
			}
		}

		//attempt to write the value to the Node
		if(m_baseStation.node_writeEeprom(m_readWriteVersion, m_nodeAddress, location, value))
		{
			//successfully wrote to the Node, update the cache
			updateCache(location, value);

			return;
		}

		//we failed to write the value to the Node

		//clear the eeprom cache for this location if we have one, just to be safe
		clearCacheLocation(location);

		throw Error_NodeCommunication(m_nodeAddress, "Failed to write EEPROM " + Utils::toStr(location) + " to Node " + Utils::toStr(m_nodeAddress));
	}
}