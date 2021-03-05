/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "Eeprom.h"

namespace mscl
{
    class ByteStream;
    class BaseStation_Impl;

    //Class: BaseStationEeprom
    //    Used to read and write to BaseStations' eeproms and provide caching functionality.
    class BaseStationEeprom : public Eeprom
    {
    public:
        //Constructor: BaseStationEeprom
        //    Creates a BaseStationEeprom object. 
        //
        //Parameters:
        //    nodeAddress - The address of the Node to access the Eeprom of.
        //    base - The <BaseStation_Impl> to use for communication. This reference must stay alive for the life of this object.
        //    useCache - Whether or not to use the eeprom cache.
        explicit BaseStationEeprom(BaseStation_Impl* base);

        virtual ~BaseStationEeprom() {};

    private:
        BaseStationEeprom();                                    //default constructor disabled
        BaseStationEeprom(const BaseStationEeprom&);            //copy constructor disabled
        BaseStationEeprom& operator=(const BaseStationEeprom&);    //assignment operator disabled

    private:
        //Variable: m_baseStation
        //    The <BaseStation_Impl> to use for communication.
        BaseStation_Impl* m_baseStation;

    protected:
        //Function: updateCacheFromDevice
        //    Attempts to update the cache by reading the value from the BaseStation.
        //    Any values that are read from the Node will be updated in the cache.
        //
        //Parameters:
        //    location - The eeprom location to read from the device and update in the cache.
        //
        //Returns:
        //    true if the value was read from the device and the cache has been updated, false otherwise.
        virtual bool updateCacheFromDevice(uint16 location) override;

    public:
        using Eeprom::readEeprom;
        using Eeprom::writeEeprom;

        //Function: readEeprom
        //    Attempts to read an eeprom value from the BaseStation.
        //    If caching is enabled and there is a previously cached value available, this will 
        //    just return the value from the cache and will not communicate with the BaseStation.
        //
        //Parameters:
        //    location - The eeprom location to read from the BaseStation and update in the cache.
        //
        //Returns:
        //    The eeprom value for the requested location.
        //
        //Exceptions:
        //    - <Error_Connection>: Failed to read the value from the BaseStation.
        //                             A connection error has occurred with the BaseStation.
        virtual uint16 readEeprom(uint16 location) override;

        //Function: writeEeprom
        //    Attempts to write an eeprom value to the BaseStation.
        //    If successful, the cache will be updated with the changed value as well.
        //    If caching is enabled and the value in the cache is the same as that attempting to be written,
        //    nothing will be written to the Node and this function will have no affect.
        //
        //Parameters:
        //    location - The eeprom location to write to on the BaseStation and update in the cache.
        //    value - The value to write to the eeprom on the Node and update in the cache.
        //
        //Exceptions:
        //    - <Error_Connection>: Failed to read the value from the BaseStation.
        //                             A connection error has occurred with the BaseStation.
        virtual void writeEeprom(uint16 location, uint16 value) override;
    };
}