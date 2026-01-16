/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Bitfield.h"

namespace mscl
{
    uint64 Bitfield::get(uint64 mask, bool shiftToLsb) const
    {
        uint64 getVal = m_value & mask;

        if (!shiftToLsb)
        {
            return getVal;
        }

        return getVal >> shiftCount(mask);
    }

    void Bitfield::set(uint64 mask, uint64 value, bool shiftRequired)
    {
        clear(mask);

        // if value was 0, just need to clear
        if (value == 0)
        {
            return;
        }

        // bitshift value to put it in the right spot in the bitfield
        uint64 setVal = value;

        if (shiftRequired)
        {
            setVal = setVal << shiftCount(mask);
        }

        // or the set value into the complete value now that it's in the correct place
        m_value = m_value | setVal;
    }

    bool Bitfield::checkBit(uint8 bitIndex, uint8 indexBase /* = 0 */) const
    {
        uint8 shift = bitIndex < indexBase ? 0 : bitIndex - indexBase;
        uint8 mask = 1 << shift;
        return get(mask) > 0;
    }

    void Bitfield::setBit(uint8 bitIndex, bool value, uint8 indexBase /* = 0 */)
    {
        uint8 shift = bitIndex < indexBase ? 0 : bitIndex - indexBase;
        uint8 mask = 1 << shift;
        uint8 val = value ? 1 : 0;
        set(mask, val);
    }

    void Bitfield::clear(uint64 mask)
    {
        uint64 clearMap = 0xFFFFFFFFFFFFFFFF ^ mask;
        m_value = m_value & clearMap;
    }

    uint8 Bitfield::shiftCount(uint64 mask)
    {
        // shift until all zeros removed from right-hand side of map (least significant bit is 1)
        uint64 shiftMap = mask;
        uint8 count = 0;

        if (shiftMap == 0)
        {
            throw Error_NoData("The bitfield mask is unset");
        }

        while (shiftMap % 2 != 1)
        {
            shiftMap = shiftMap >> 1;
            count++;
        }

        return count;
    }
} // namespace mscl
