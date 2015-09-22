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
#pragma once

#include "mscl/Types.h"
#include "mscl/Value.h"
#include "EepromLocation.h"

namespace mscl
{
	//Class: Eeprom
	//	The abstract base class for reading and writing to Wireless devices' eeproms.
	class Eeprom
	{
	protected:
		//Typedef: EepromMap
		//	typedef for a map of eeprom locations to eeprom values
		typedef std::map<uint16, uint16> EepromMap;

	public:
		//Constructor: Eeprom
		//	Creates an Eeprom object.
		//
		//Parameters:
		//	useCache - Whether or not to use the eeprom cache.
		explicit Eeprom(bool useCache);

		virtual ~Eeprom() {};

	protected:
		//Variable: m_eepromCache
		//	The <EepromMap> contianing all cached values that have previously been read from a device.
		EepromMap m_eepromCache;

		//Variable: m_useCache
		//	Whether or not the cache should be used.
		bool m_useCache;

	public:
		//Function: useCache
		//	Enables or disables use of the eeprom cache. Once disabled, all eeprom reads will go to the Node.
		//
		//Parameters:
		//	enable - Whether to enable (true) or disable (false) the eeprom cache.
		void useCache(bool enable);

		//Function: clearCache
		//	Clears the entire eeprom cache.
		void clearCache();

		//Function: clearCacheLocation
		//	Clears a specific location from the eeprom cache, if it exists.
		//
		//Parameters:
		//	location - The location to clear from the cache.
		void clearCacheLocation(uint16 location);

	protected:
		//Function: readCache
		//	Attempts to read a value from the eeprom cache.
		//
		//Parameters:
		//	location - The eeprom location to get the value for.
		//	result - Holds the result value read from the cache if successful.
		//
		//Returns:
		//	true if the value was read from the cache, false if the value was not found in the cache.
		bool readCache(uint16 location, uint16& result);

		//Function: updateCache
		//	Adds a value to the eeprom cache at the given location, or updates it if a value for that location already exists.
		//
		//Parameters:
		//	location - The location to store the value for in the cache.
		//	value - The eeprom value to store in the cache.
		void updateCache(uint16 location, uint16 value);

		//Function: updateCacheFromDevice
		//	Attempts to update the cache by reading the value from a device.
		//	Any values that are read from the device will be updated in the cache.
		//
		//Parameters:
		//	location - The eeprom location to read from the device and update in the cache.
		//	canUseGroupDownload - Whether or not the devices can download a group of eeproms when available. If this is false, a single eeprom read will be used.
		//
		//Returns:
		//	true if the value was read from the device and the cache has been updated, false otherwise.
		virtual bool updateCacheFromDevice(uint16 location, bool canUseGroupDownload = true) = 0;

	public:
		//Function: readEeprom
		//	Attempts to read an eeprom value from a device.
		//	If caching is enabled and there is a previously cached value available, this will 
		//	just return the value from the cache and will not communicate with the device.
		//
		//Parameters:
		//	location - The eeprom location to read from the device and update in the cache.
		//
		//Returns:
		//	The eeprom value for the requested location.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual uint16 readEeprom(uint16 location) = 0;

		//Function: writeEeprom
		//	Attempts to write an eeprom value to a device.
		//	If successful, the cache will be updated with the changed value as well.
		//	If caching is enabled and the value in the cache is the same as that attempting to be written,
		//	nothing will be written to the device and this function will have no affect.
		//
		//Parameters:
		//	location - The eeprom location to write to on the device and update in the cache.
		//	value - The value to write to the eeprom on the device and update in the cache.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void writeEeprom(uint16 location, uint16 value) = 0;

		//Function: readEeprom
		//	Attempts to read an eeprom value from a device.
		//	If caching is enabled and there is a previously cached value available, this will 
		//	just return the value from the cache and will not communicate with the device.
		//
		//Parameters:
		//	location - The <EepromLocation> to read from the device and update in the cache.
		//
		//Returns:
		//	A <Value> object containing the eeprom value for the requested location.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation. 
		Value readEeprom(const EepromLocation& location);

		//Function: writeEeprom
		//	Attempts to write an eeprom value to a device.
		//	If successful, the cache will be updated with the changed value as well.
		//	If caching is enabled and the value in the cache is the same as that attempting to be written,
		//	nothing will be written to the device and this function will have no affect.
		//
		//Parameters:
		//	location - The <EepromLocation> to write to on the device and update in the cache.
		//	value - The <Value> to write to the eeprom on the device and update in the cache.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		void writeEeprom(const EepromLocation& location, const Value& val);

		//Function: readEeprom_float
		//	Attempts to read 2 eeprom values from a device and build them into a float.
		//	If caching is enabled and there is a previously cached value available, this will 
		//	just return the value from the cache and will not communicate with the device.
		//
		//Parameters:
		//	location - The eeprom location to read from the device and update in the cache.
		//
		//Returns:
		//	The eeprom value for the requested location.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual float readEeprom_float(uint16 location);

		//Function: readEeprom_uint32
		//	Attempts to read 2 eeprom values from a device and build them into a uint32.
		//	If caching is enabled and there is a previously cached value available, this will 
		//	just return the value from the cache and will not communicate with the device.
		//
		//Parameters:
		//	location - The eeprom location to read from the device and update in the cache.
		//
		//Returns:
		//	The eeprom value for the requested location.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual uint32 readEeprom_uint32(uint16 location);

		//Function: readEeprom
		//	Attempts to read an eeprom value from a device.
		//	If caching is enabled and there is a previously cached value available, this will 
		//	just return the value from the cache and will not communicate with the device.
		//
		//Parameters:
		//	location - The <EepromLocation> to read from the device and update in the cache.
		//
		//Returns:
		//	The eeprom value for the requested location.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual uint16 readEeprom_uint16(EepromLocation location);

		//Function: readEeprom_float
		//	Attempts to read 2 eeprom values from a device and build them into a float.
		//	If caching is enabled and there is a previously cached value available, this will 
		//	just return the value from the cache and will not communicate with the device.
		//
		//Parameters:
		//	location - The <EepromLocation> to read from the device and update in the cache.
		//
		//Returns:
		//	The eeprom value for the requested location.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual float readEeprom_float(EepromLocation location);

		//Function: readEeprom_uint32
		//	Attempts to read 2 eeprom values from a device and build them into a uint32.
		//	If caching is enabled and there is a previously cached value available, this will 
		//	just return the value from the cache and will not communicate with the device.
		//
		//Parameters:
		//	location - The <EepromLocation> to read from the device and update in the cache.
		//
		//Returns:
		//	The eeprom value for the requested location.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual uint32 readEeprom_uint32(EepromLocation location);

		//Function: writeEeprom_float
		//	Attempts to write 2 eeprom values to a device as a float.
		//	If successful, the cache will be updated with the changed value as well.
		//	If caching is enabled and the value in the cache is the same as that attempting to be written,
		//	nothing will be written to the device and this function will have no affect.
		//
		//Parameters:
		//	location - The eeprom location to write to on the device and update in the cache.
		//	value - The value to write to the eeprom on the device and update in the cache.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void writeEeprom_float(uint16 location, float value);

		//Function: writeEeprom
		//	Attempts to write an eeprom value to a device.
		//	If successful, the cache will be updated with the changed value as well.
		//	If caching is enabled and the value in the cache is the same as that attempting to be written,
		//	nothing will be written to the device and this function will have no affect.
		//
		//Parameters:
		//	location - The <EepromLocation> to write to on the device and update in the cache.
		//	value - The value to write to the eeprom on the device and update in the cache.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void writeEeprom_uint16(EepromLocation location, uint16 value);

		//Function: writeEeprom_float
		//	Attempts to write 2 eeprom values to a device as a float.
		//	If successful, the cache will be updated with the changed value as well.
		//	If caching is enabled and the value in the cache is the same as that attempting to be written,
		//	nothing will be written to the device and this function will have no affect.
		//
		//Parameters:
		//	location - The <EepromLocation> to write to on the device and update in the cache.
		//	value - The value to write to the eeprom on the device and update in the cache.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void writeEeprom_float(EepromLocation location, float value);

		//Function: writeEeprom
		//	Attempts to write 2 eeprom values to a device as a uint32.
		//	If successful, the cache will be updated with the changed value as well.
		//	If caching is enabled and the value in the cache is the same as that attempting to be written,
		//	nothing will be written to the device and this function will have no affect.
		//
		//Parameters:
		//	location - The <EepromLocation> to write to on the device and update in the cache.
		//	value - The value to write to the eeprom on the device and update in the cache.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void writeEeprom_uint32(uint16 location, uint32 value);
	};
}