/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include <vector>

namespace mscl
{
    //API Class: BitMask
    //  Represents a bitmask.
    class BitMask
    {
    private:
        //Variable: m_numBits
        //  The number of bits that are being represented in the bitmask.
        uint8 m_numBits;

        //Variable: m_mask
        //  An array of bools holding the bitmask.
        std::vector<bool> m_mask;

    public:
        //API Constructor: BitMask
        //  Creates an BitMask object given a uint16 value.
        //
        //Parameters:
        //  val - A uint16 value to represent as a bitmask.
        explicit BitMask(uint16 val);

        //API Constructor: BitMask
        //  The default constructor for creating a BitMask object, which sets all the bits to inactive.
        BitMask();

        //API Destructor: ~BitMask
        //  Destroys a BitMask object.
        virtual ~BitMask() {};

        //API Operator: ==
        //  Equal operator for comparing BitMasks.
        virtual bool operator==(const BitMask& other) const;

        //API Operator: !=
        //  Not Equal operator for comparing BitMasks.
        virtual bool operator!=(const BitMask& other) const;

        //API Operator: <
        //  Less Than operator for comparing BitMasks.
        virtual bool operator<(const BitMask& other) const;

        //API Operator: >
        //  Greater Than operator for comparing BitMasks.
        virtual bool operator>(const BitMask& other) const;

        //API Function: fromMask
        //  Initializes the BitMask object from a uint16.
        //
        //Parameters:
        //  val - A uint16 value to represent as a bitmask.
        virtual void fromMask(uint16 val);

        //API Function: toMask
        //  Gets the uint16 value of the current BitMask object.
        //
        //Returns:
        //  The BitMask object represented as a uint16.
        virtual uint16 toMask() const;

        //API Function: enabledCount
        //  Gets the total number of enabled bits in the current BitMask object.
        //
        //Returns:
        //  The total number of enabled bits.
        virtual uint8 enabledCount() const;

        //API Function: enabled
        //  Checks whether a certain bit is enabled or disabled.
        //
        //Parameters:
        //  bitIndex - The bit index to check if enabled or disabled.
        //
        //Returns:
        //  true if the channel is enabled, false if the channel is disabled
        virtual bool enabled(uint8 bitIndex) const;

        //API Function: enable
        //  Enables or disables a specified bit.
        //
        //Parameters:
        //  bitIndex - The bit index to enable or disable.
        //  enable - Set to true to enable the bit, false to disable the bit.
        virtual void enable(uint8 bitIndex, bool enable = true);

        //API Function: lastBitEnabled
        //  Finds the highest bit that is enabled in the mask.
        //  This is useful when looping over the BitMask object and performing an action on all enabled bits.
        //
        //Returns:
        //  The bit index of the highest bit enabled. -1 if no channels are enabled.
        virtual int16 lastBitEnabled() const;
    };
}