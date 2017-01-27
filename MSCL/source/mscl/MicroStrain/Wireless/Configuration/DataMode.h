/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/BitMask.h"

namespace mscl
{
    //API Class: DataMode
    //  Used to get and set the Data Modes that are available on a Wireless Node.
    class DataMode
    {
        friend class NodeEepromHelper;
        friend class WirelessNodeConfig;

    protected:
        //Enum: DataModeBitPos
        //  The bit position for the Data Mode bitmask.
        enum DataModeBitPos
        {
            dataModeBitPos_raw = 0,
            dataModeBitPos_derived = 1
        };

        //Function: toMask
        //  Creates a BitMask from the DataMode object.
        //
        //Returns:
        //  A <BitMask> representing the DataMode object.
        BitMask toMask() const;
        
        //Function: FromMask
        //  A static function to create a DataMode object from a <BitMask>.
        //
        //Parameters:
        //  mask - The <BitMask> to create the DataMode object with.
        //
        //Returns:
        //  A DataMode object.
        static DataMode FromMask(const BitMask& mask);

    public:
        //API Constructor: DataMode
        //  Creates a DataMode object.
        //
        //Parameters:
        //  rawMode - Whether raw mode should be enabled (true) or disabled (false). Defaults to true.
        //  derivedMode - Whether derived mode should be enabled (true) or disabled (false). Defaults to true.
        DataMode(bool rawMode=true, bool derivedMode=true);

    private:
        //Variable: m_rawModeEnabled
        //  Whether raw data mode is enabled or disabled.
        bool m_rawModeEnabled;

        //Variable: m_derivedModeEnabled
        //  Whether derived data mode is enabled or disabled.
        bool m_derivedModeEnabled;

    public:
        //API Function: rawModeEnabled
        //  Gets whether raw data mode is enabled or disabled in this object.
        //
        //Returns:
        //  true if raw data mode is enabled in this object, false if it is disabled.
        bool rawModeEnabled() const;

        //API function: enableRawMode
        //  Sets whether raw data mode is enabled or disabled in this object.
        //
        //Parameters:
        //  enable - Whether to enable (true) or disable (false) raw data mode in this object.
        void enableRawMode(bool enable);

        //API Function: derivedModeEnabled
        //  Gets whether derived data mode is enabled or disabled in this object.
        //
        //Returns:
        //  true if derived data mode is enabled in this object, false if it is disabled.
        bool derivedModeEnabled() const;

        //API function: enableDerivedMode
        //  Sets whether derived data mode is enabled or disabled in this object.
        //
        //Parameters:
        //  enable - Whether to enable (true) or disable (false) derived data mode in this object.
        void enableDerivedMode(bool enable);
    };
}