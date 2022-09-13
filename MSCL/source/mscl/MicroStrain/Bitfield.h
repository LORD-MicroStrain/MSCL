/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "mscl/Types.h"

namespace mscl
{
    //Class: Bitfield
    class Bitfield
    {
    public:
        //Constructor: Bitfield
        //  Constructs Bitfield object with value 0
        Bitfield() {};

        //Constructor: Bitfield
        //  Constructs Bitfield object with indicated value
        //
        //Parameters:
        //  val - uint64 bitfield value
        Bitfield(uint64 val) :
            m_value(val)
        {};

        //Destructor: ~Bitfield
        //  Default destructor for the Bitfield object
        virtual ~Bitfield() {};

    private:
        //Variable: m_value
        //  The bitfield value
        uint64 m_value;

    public:
        //Function: value
        //  Gets or sets the entire underlying bitfield value
        uint64 value() const { return m_value; }
        void value(uint64 val) { m_value = val; }

        //Function: get
        //  Gets the value of only the bits masked by the indicated mask.
        //
        //Parameters:
        //  mask - uint64 indicating which bits to evaluate
        //  shiftToLsb - true: return the masked bits shifted all the way to the right, false: return the masked bits in their original position
        //
        //Returns:
        //  uint64 - the masked value
        uint64 get(uint64 mask, bool shiftToLsb = true) const;

        //Function: set
        //  Sets the provided value to the position indicated by the indicated mask
        //
        //Parameters:
        //  mask - uint64 indicating the position to place the value
        //  value - uint64 value to set
        //  shiftRequired - true: provided value needs to be shifted to the masked position before being set, false: provided value already in the correct position within the bitfield
        void set(uint64 mask, uint64 value, bool shiftRequired = true);

        //Function: checkBit
        //  Gets the value of the bit at the specified index.
        //
        //Parameters:
        //  bitIndex - index of the bit to check
        //  indexBase - default 0 - index of the first bit, this will be subtracted from bitIndex to get the 0-based index to use.
        //              This is useful if each bit is associated with sequential IDs that are not 0-based (i.e. inertial GPIO pin IDs).
        //
        //Returns:
        //  bool - true if bit is 1, false if 0
        bool checkBit(uint8 bitIndex, uint8 indexBase = 0) const;

        //Function: setBit
        //  Sets the value of the bit at the specified index.
        //
        //Parameters:
        //  bitIndex - index of the bit to set
        //  value - bool value to set
        //  indexBase - default 0 - index of the first bit, this will be subtracted from bitIndex to get the 0-based index to use.
        //              This is useful if each bit is associated with sequential IDs that are not 0-based (i.e. inertial GPIO pin IDs).
        void setBit(uint8 bitIndex, bool value, uint8 indexBase = 0);

    protected:
        //Function: clear
        //  Sets all bits under the indicated mask to 0.
        //
        //Parameters:
        // mask - uint64 mask indicating the position of the bits to clear
        void clear(uint64 mask);

    private:
        //Function shiftCount
        //  Calculate the number of bits to shift the mask value so that the least significant bit is 1 (mask shifted all the way to the right).
        //
        //Parameters:
        //  mask - uint64 mask to calculate shift count for
        static uint8 shiftCount(uint64 mask);
    };
}