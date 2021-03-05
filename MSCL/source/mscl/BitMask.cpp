/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BitMask.h"

namespace mscl
{
    BitMask::BitMask(uint16 val):
        m_numBits(16)   //for now, this class always uses 16 bits
    {
        fromMask(val);
    }

    BitMask::BitMask():
        m_numBits(16)   //for now, this class always uses 16 bits
    {
        //initialize all the bits to inactive
        fromMask(0);
    }

    bool BitMask::operator==(const BitMask& other) const
    {
        //loop through all the bits possible
        for(uint8 i = 0; i < m_numBits; i++)
        {
            //if we find any differences for active/inactive bits
            if(m_mask.at(i) != other.m_mask.at(i))
            {
                return false;
            }
        }

        return true;
    }

    bool BitMask::operator!=(const BitMask& other) const
    {
        //loop through all the bits possible
        for(uint8 i = 0; i < m_numBits; i++)
        {
            //if we find any differences for active/inactive bits
            if(m_mask.at(i) != other.m_mask.at(i))
            {
                return true;
            }
        }

        return false;
    }
    
    bool BitMask::operator<(const BitMask& other) const
    {
        return toMask() < other.toMask();
    }

    bool BitMask::operator>(const BitMask& other) const
    {
        return toMask() > other.toMask();
    }

    void BitMask::fromMask(uint16 val)
    {
        m_mask.clear();

        //loop through all the bits possible
        for(uint8 i = 0; i < m_numBits; i++)
        {
            //check each bit in the value to see if it is active (1)
            m_mask.push_back((val & (1 << i)) != 0);
        }
    }

    uint16 BitMask::toMask() const
    {
        uint16 mask = 0;

        //loop through all the bits possible
        for(uint8 i = 0; i < m_numBits; i++)
        {
            //if the bit is active
            if(m_mask.at(i))
            {
                mask |= (1 << i);    
            }
        }

        return mask;
    }

    uint8 BitMask::enabledCount() const
    {
        uint8 count = 0;

        //loop through all the channels possible
        for(uint8 i = 0; i < m_numBits; i++)
        {
            //if the channel is active
            if(m_mask.at(i))
            {
                //increment the count
                count++;    
            }
        }

        return count;
    }

    bool BitMask::enabled(uint8 bitIndex) const
    {
        //if the bit index is out of range
        if(bitIndex > m_numBits - 1)
        {
            return false;
        }

        return m_mask.at(bitIndex);
    }

    void BitMask::enable(uint8 bitIndex, bool enable)
    {
        //verify the bit index is within range
        if(bitIndex < m_numBits)
        {
            m_mask.at(bitIndex) = enable;
        }
    }

    int16 BitMask::lastBitEnabled() const
    {
        uint8 itr = m_numBits;

        //loop over the bits backwards
        for(; itr >= 1; --itr)
        {
            //if we find a bit that is enabled
            if(m_mask.at(itr - 1))
            {
                //we can stop looking and return the bit index
                return itr - 1;
            }
        }

        //no bits were found to be enabled
        return -1;
    }
}