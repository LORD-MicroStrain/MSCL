/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/BitMask.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    //Class: DataModeMask
    //  Helper class for the DataMode bitmask used in Node Eeproms.
    class DataModeMask
    {
        friend class NodeEepromHelper;
        friend class WirelessNodeConfig;

    private:
        //Enum: DataModeBitPos
        //  The bit position for the Data Mode bitmask.
        enum DataModeBitPos
        {
            dataModeBitPos_raw = 0,
            dataModeBitPos_derived = 1
        };

    public:
        //Constructor: DataModeMask
        //  Creates a DataModeMask object.
        //
        //Parameters:
        //  mode - The <WirelessTypes::DataMode> to represent.
        DataModeMask(WirelessTypes::DataMode mode);

        //Constructor: DataModeMask
        //  Creates a DataModeMask from a <BitMask>.
        //
        //Parameters:
        //  mask - The <BitMask> representing the DataMode as stored in EEPROM.
        DataModeMask(const BitMask& mask);

        //Function: toMask
        //  Creates a BitMask from the DataMode object.
        //
        //Returns:
        //  A <BitMask> representing the DataMode object as stored in EEPROM.
        BitMask toMask() const;

        //Function: toDataModeEnum
        //  Creates a <WirelessTypes::DataMode> from the DataModeMask object.
        //
        //Returns:
        //  A <WirelessTypes::DataMode> representing the DataModeMask object.
        WirelessTypes::DataMode toDataModeEnum() const;

    public:
        //Variable: rawModeEnabled
        //  Whether raw data mode is enabled or disabled.
        bool rawModeEnabled;

        //Variable: derivedModeEnabled
        //  Whether derived data mode is enabled or disabled.
        bool derivedModeEnabled;
    };
}