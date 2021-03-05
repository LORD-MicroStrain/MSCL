/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <mutex>

#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/Types.h"
#include "mscl/Value.h"
#include "EepromLocation.h"

namespace mscl
{
    //Class: Eeprom
    //    The abstract base class for reading and writing to Wireless devices' eeproms.
    class Eeprom
    {
    public:
        //Constructor: Eeprom
        //    Creates an Eeprom object.
        //
        //Parameters:
        //    useCache - Whether or not to use the eeprom cache.
        //    numRetries - The number of retries to use for reads and writes.
        explicit Eeprom(bool useCache, uint8 numRetries);

        virtual ~Eeprom() {};

    protected:
        //Variable: m_eepromCache
        //    The <WirelessTypes::EepromMap> contianing all cached values that have previously been read from a device.
        WirelessTypes::EepromMap m_eepromCache;

        //Variable: m_useCache
        //    Whether or not the cache should be used.
        bool m_useCache;

        //Variable: m_numRetries
        //    The number of retries to use when reading and writing eeproms.
        uint8 m_numRetries;

        //Variable: m_hasWritten
        //  A flag used by <resetHasWritten> and <didWrite> to help determine when
        //  an eeprom was actually written, instead of just using the cache.
        bool m_hasWritten;

        //Variable: m_cacheMutex
        //  Mutex for controlling access to the cache.
        mutable std::recursive_mutex m_cacheMutex;

    public:
        //Function: useCache
        //    Enables or disables use of the eeprom cache. Once disabled, all eeprom reads will go to the Node.
        //
        //Parameters:
        //    enable - Whether to enable (true) or disable (false) the eeprom cache.
        void useCache(bool enable);

        //Function: clearCache
        //    Clears the entire eeprom cache.
        void clearCache();

        //Function: clearCacheLocation
        //    Clears a specific location from the eeprom cache, if it exists.
        //
        //Parameters:
        //    location - The location to clear from the cache.
        void clearCacheLocation(uint16 location);

        //Function: setNumRetries
        //    Sets the number of retries to use when reading and writing eeproms.
        //    By default, this configuration is set to 0, meaning no retries are performed.
        //
        //Parameters:
        //    retries - The number of retries to use.
        void setNumRetries(uint8 retries);

        //Function: getNumRetries
        //    Gets the number of retries currently set for reading and writing eeproms.
        //
        //Returns:
        //    The number of retries currently set.
        uint8 getNumRetries() const;

        //Function: getCache
        //  Gets a copy of the <WirelessTypes::EepromMap> containing the cache of eeprom location/value pairs.
        //
        //Returns:
        //  A <WirelessTypes::EepromMap> of the cache.
        WirelessTypes::EepromMap getCache() const;

        //Function: importCache
        //  Imports an existing EEPROM 
        void importCache(const WirelessTypes::EepromMap& eepromMap);

    protected:
        //Function: readCache
        //    Attempts to read a value from the eeprom cache.
        //
        //Parameters:
        //    location - The eeprom location to get the value for.
        //    result - Holds the result value read from the cache if successful.
        //
        //Returns:
        //    true if the value was read from the cache, false if the value was not found in the cache.
        bool readCache(uint16 location, uint16& result);

        //Function: updateCache
        //    Adds a value to the eeprom cache at the given location, or updates it if a value for that location already exists.
        //
        //Parameters:
        //    location - The location to store the value for in the cache.
        //    value - The eeprom value to store in the cache.
        void updateCache(uint16 location, uint16 value);

        //Function: updateCacheFromDevice
        //    Attempts to update the cache by reading the value from a device.
        //    Any values that are read from the device will be updated in the cache.
        //
        //Parameters:
        //    location - The eeprom location to read from the device and update in the cache.
        //
        //Returns:
        //    true if the value was read from the device and the cache has been updated, false otherwise.
        virtual bool updateCacheFromDevice(uint16 location) = 0;

    public:
        //Function: resetHasWritten
        //  Resets the m_hasWritten flag to false.
        //  It will be changed back to true when a successful write is performed.
        void resetHasWritten();

        //Function: didWrite
        //  Gets the m_hasWritten flag indicating if an eeprom has been written on the device (not using the cache).
        //
        //Returns:
        //  true if an eeprom has been written, false if it has not (cache may have been used).
        bool didWrite() const;

        //Function: readEeprom
        //    Attempts to read an eeprom value from a device.
        //    If caching is enabled and there is a previously cached value available, this will 
        //    just return the value from the cache and will not communicate with the device.
        //
        //Parameters:
        //    location - The eeprom location to read from the device and update in the cache.
        //
        //Returns:
        //    The eeprom value for the requested location.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual uint16 readEeprom(uint16 location) = 0;

        //Function: writeEeprom
        //    Attempts to write an eeprom value to a device.
        //    If successful, the cache will be updated with the changed value as well.
        //    If caching is enabled and the value in the cache is the same as that attempting to be written,
        //    nothing will be written to the device and this function will have no affect.
        //
        //Parameters:
        //    location - The eeprom location to write to on the device and update in the cache.
        //    value - The value to write to the eeprom on the device and update in the cache.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual void writeEeprom(uint16 location, uint16 value) = 0;

        //Function: readEeprom
        //    Attempts to read an eeprom value from a device.
        //    If caching is enabled and there is a previously cached value available, this will 
        //    just return the value from the cache and will not communicate with the device.
        //
        //Parameters:
        //    location - The <EepromLocation> to read from the device and update in the cache.
        //
        //Returns:
        //    A <Value> object containing the eeprom value for the requested location.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation. 
        Value readEeprom(const EepromLocation& location);

        //Function: writeEeprom
        //    Attempts to write an eeprom value to a device.
        //    If successful, the cache will be updated with the changed value as well.
        //    If caching is enabled and the value in the cache is the same as that attempting to be written,
        //    nothing will be written to the device and this function will have no affect.
        //
        //Parameters:
        //    location - The <EepromLocation> to write to on the device and update in the cache.
        //    value - The <Value> to write to the eeprom on the device and update in the cache.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void writeEeprom(const EepromLocation& location, const Value& val);

    private:
        //Function: readEeprom_float
        //    Attempts to read 2 eeprom values from a device and build them into a float.
        //    If caching is enabled and there is a previously cached value available, this will 
        //    just return the value from the cache and will not communicate with the device.
        //
        //Parameters:
        //    location - The eeprom location to read from the device and update in the cache.
        //
        //Returns:
        //    The eeprom value for the requested location.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual float readEeprom_float(uint16 location);

        //Function: readEeprom_uint32
        //    Attempts to read 2 eeprom values from a device and build them into a uint32.
        //    If caching is enabled and there is a previously cached value available, this will 
        //    just return the value from the cache and will not communicate with the device.
        //
        //Parameters:
        //    location - The eeprom location to read from the device and update in the cache.
        //
        //Returns:
        //    The eeprom value for the requested location.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual uint32 readEeprom_uint32(uint16 location);

        //Function: readEeprom_int16
        //    Attempts to read an eeprom value from a device as a signed int16.
        //    If caching is enabled and there is a previously cached value available, this will 
        //    just return the value from the cache and will not communicate with the device.
        //
        //Parameters:
        //    location - The eeprom location to read from the device and update in the cache.
        //
        //Returns:
        //    The eeprom value for the requested location.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual int16 readEeprom_int16(uint16 location);

        //Function: writeEeprom_float
        //    Attempts to write 2 eeprom values to a device as a float.
        //    If successful, the cache will be updated with the changed value as well.
        //    If caching is enabled and the value in the cache is the same as that attempting to be written,
        //    nothing will be written to the device and this function will have no affect.
        //
        //Parameters:
        //    location - The eeprom location to write to on the device and update in the cache.
        //    value - The value to write to the eeprom on the device and update in the cache.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual void writeEeprom_float(uint16 location, float value);

        //Function: writeEeprom_uint32
        //    Attempts to write 2 eeprom values to a device as a uint32.
        //    If successful, the cache will be updated with the changed value as well.
        //    If caching is enabled and the value in the cache is the same as that attempting to be written,
        //    nothing will be written to the device and this function will have no affect.
        //
        //Parameters:
        //    location - The <EepromLocation> to write to on the device and update in the cache.
        //    value - The value to write to the eeprom on the device and update in the cache.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual void writeEeprom_uint32(uint16 location, uint32 value);

        //Function: writeEeprom_int16
        //    Attempts to write an eeprom value to a device from a signed int16.
        //    If successful, the cache will be updated with the changed value as well.
        //    If caching is enabled and the value in the cache is the same as that attempting to be written,
        //    nothing will be written to the device and this function will have no affect.
        //
        //Parameters:
        //    location - The eeprom location to write to on the device and update in the cache.
        //    value - The value to write to the eeprom on the device and update in the cache.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual void writeEeprom_int16(uint16 location, int16 value);
    };
}