/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "Eeprom.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    //Title: NodeEeprom

    class ByteStream;
    class WirelessNode_Impl;

    //Struct: NodeEepromSettings
    //    The settings for the <NodeEeprom> object.
    struct NodeEepromSettings
    {
        //Variable: useGroupRead
        //    Whether to use group eeprom read or not.
        bool useGroupRead;

        //Variable: numRetries
        //    The number of retries to use for reading and writing.
        uint8 numRetries;

        //Variable: useEepromCache
        //    Whether to use the eeprom cache for reads and writes.
        bool useEepromCache;

        NodeEepromSettings():
            useGroupRead(true),
            numRetries(0),
            useEepromCache(true)
        {
        }
    };

    //Class: NodeEeprom
    //    Used to read and write to Wireless Nodes' eeproms and provide caching functionality.
    class NodeEeprom : public Eeprom
    {
    private:
        static const uint16 PAGE_0_MAX_EEPROM = 262;    //the max eeprom location that is in page 0 (from the node page download command)
        static const uint16 PAGE_1_MAX_EEPROM = 526;    //the max eeprom location that is in page 1 (from the node page download command)
        static const uint16 EEPROMS_PER_PAGE = 264;        //the number of eeprom locations per page (from the node page download command)

    public:
        //Constructor: Eeprom
        //    Creates an Eeprom object.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to access the Eeprom of.
        //    base - The <BaseStation> to use for communicating with the Node.
        //    settings - The <NodeEepromSettings> to use.
        NodeEeprom(const WirelessNode_Impl* node, const BaseStation& base, const NodeEepromSettings& settings);

        virtual ~NodeEeprom() {};

    protected:
        const WirelessNode_Impl* m_node;

        //Variable: m_baseStation
        //    The <BaseStation> to use for communication with the Node.
        BaseStation m_baseStation;

        //Variable: m_useGroupRead
        //    Whether we can use a group eeprom read when reading from eeprom.
        bool m_useGroupRead;

    protected:
        //Function: updateCacheFromDevice
        //    Attempts to update the cache by reading the value from the Node with the nodeAddress given at initialization.
        //    Any values that are read from the Node will be updated in the cache.
        //
        //Parameters:
        //    location - The eeprom location to read from the device and update in the cache.
        //
        //Returns:
        //    true if the value was read from the device and the cache has been updated, false otherwise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        virtual bool updateCacheFromDevice(uint16 location) final;

    private:
        //Function: parseEepromPage
        //    Parses a page download result containing eeprom values. 
        //    The eeprom cache will be updated with all the parsed values.
        //
        //Parameters:
        //    pageData - The <ByteStream> that contains the data read from the page download command
        //    pageIndex - The 0-based index that was used to download the page
        virtual void parseEepromPage(const ByteStream& pageData, uint16 pageIndex);

        //Function: parseBatchEepromResult
        //  Parses the response from a Batch Node Eeprom Read command.
        //  The eeprom cache will be updated with all the parsed values.
        //
        //Parameters:
        //  eepromMap - The eeprom location/value map read from the batch node eeprom read command.
        virtual void parseBatchEepromResult(const std::map<uint16, uint16> eepromMap);

    public:
        using Eeprom::readEeprom;
        using Eeprom::writeEeprom;

        //Function: updateSettings
        //    Changes the settings for this eeprom object.
        void updateSettings(const NodeEepromSettings& settings);

        //Function: setBaseStation
        //    Updates the BaseStation object that is set for use in communicating with the Node.
        void setBaseStation(const BaseStation& base);

        //Function: readEeprom
        //    Attempts to read an eeprom value from the Node.
        //    If caching is enabled and there is a previously cached value available, this will 
        //    just return the value from the cache and will not communicate with the Node.
        //
        //Parameters:
        //    location - The eeprom location to read from the Node and update in the cache.
        //
        //Returns:
        //    The eeprom value for the requested location.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual uint16 readEeprom(uint16 location) override;

        //Function: writeEeprom
        //    Attempts to write an eeprom value to the Node.
        //    If successful, the cache will be updated with the changed value as well.
        //    If caching is enabled and the value in the cache is the same as that attempting to be written,
        //    nothing will be written to the Node and this function will have no affect.
        //
        //Parameters:
        //    location - The eeprom location to write to on the Node and update in the cache.
        //    value - The value to write to the eeprom on the Node and update in the cache.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual void writeEeprom(uint16 location, uint16 value) override;
    };
}