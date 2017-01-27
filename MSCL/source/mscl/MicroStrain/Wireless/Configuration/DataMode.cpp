/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "DataMode.h"

namespace mscl
{
    DataMode::DataMode(bool rawMode/*=true*/, bool derivedMode/*=true*/):
        m_rawModeEnabled(rawMode),
        m_derivedModeEnabled(derivedMode)
    {
    }

    bool DataMode::rawModeEnabled() const
    {
        return m_rawModeEnabled;
    }

    void DataMode::enableRawMode(bool enable)
    {
        m_rawModeEnabled = enable;
    }

    bool DataMode::derivedModeEnabled() const
    {
        return m_derivedModeEnabled;
    }

    void DataMode::enableDerivedMode(bool enable)
    {
        m_derivedModeEnabled = enable;
    }

    BitMask DataMode::toMask() const
    {
        BitMask result;

        if(m_rawModeEnabled)
        {
            result.enable(dataModeBitPos_raw, true);
        }

        if(m_derivedModeEnabled)
        {
            result.enable(dataModeBitPos_derived, true);
        }

        return result;
    }

    DataMode DataMode::FromMask(const BitMask& mask)
    {
        bool rawEnabled = mask.enabled(dataModeBitPos_raw);
        bool derivedEnabled = mask.enabled(dataModeBitPos_derived);

        return DataMode(rawEnabled, derivedEnabled);
    }
}