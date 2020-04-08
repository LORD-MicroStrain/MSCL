/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "DataModeMask.h"

namespace mscl
{
    DataModeMask::DataModeMask(WirelessTypes::DataMode mode):
        rawModeEnabled(false),
        derivedModeEnabled(false)
    {
        switch(mode)
        {
            case WirelessTypes::dataMode_raw:
                rawModeEnabled = true;
                break;

            case WirelessTypes::dataMode_derived:
                derivedModeEnabled = true;
                break;

            case WirelessTypes::dataMode_raw_derived:
                rawModeEnabled = true;
                derivedModeEnabled = true;
                break;

            case WirelessTypes::dataMode_none:
            default:
                break;
        }
    }

    DataModeMask::DataModeMask(const BitMask& mask):
        rawModeEnabled(mask.enabled(dataModeBitPos_raw)),
        derivedModeEnabled(mask.enabled(dataModeBitPos_derived))
    {
    }

    BitMask DataModeMask::toMask() const
    {
        BitMask result;

        if(rawModeEnabled)
        {
            result.enable(dataModeBitPos_raw, true);
        }

        if(derivedModeEnabled)
        {
            result.enable(dataModeBitPos_derived, true);
        }

        return result;
    }

    WirelessTypes::DataMode DataModeMask::toDataModeEnum() const
    {
        if(rawModeEnabled)
        {
            if(derivedModeEnabled)
            {
                return WirelessTypes::dataMode_raw_derived;
            }

            return WirelessTypes::dataMode_raw;
        }

        if(derivedModeEnabled)
        {
            return WirelessTypes::dataMode_derived;
        }

        return WirelessTypes::dataMode_none;
    }
}