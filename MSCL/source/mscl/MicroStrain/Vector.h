/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "Matrix.h"

namespace mscl
{
    //API Class: Vector
    //    Represents a Vector of values
    class Vector : public Matrix
    {
    public:
        //Default Constructor: Vector
        //    Create a Vector object with default values
        Vector();

#ifndef SWIG
        //Constructor: Vector
        //    Creates a Vector object given its data
        Vector(ValueType storedAs, const ByteStream& data);
#endif

    private:
        //Constant: ROW_POS = 0
        //    The column position for all (row,column) Matrix functions
        static const uint16 ROW_POS = 0;

    public:
        //API Function: size
        //    Gets how many values are within the Vector
        //
        //Returns:
        //    The number of values within the Vector
        uint16 size() const;

        //API Function: as_doubleAt
        //    Gets the value stored at the given 0-based index, as an 8-byte double
        //
        //Parameters:
        //    index - The 0-based index of which to get the value
        //
        //Returns:
        //    The value stored at the given index, as a double
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        double as_doubleAt(uint16 index) const;

        //API Function: as_floatAt
        //    Gets the value stored at the given 0-based index, as a 4-byte float
        //
        //Parameters:
        //    index - The 0-based index of which to get the value
        //
        //Returns:
        //    The value stored at the given index, as a float
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        float as_floatAt(uint16 index) const;

        //API Function: as_uint16At
        //    Gets the value stored at the given 0-based index, as a 2-byte unsigned integer
        //
        //Parameters:
        //    index - The 0-based index of which to get the value
        //
        //Returns:
        //    The value stored at the given index, as an uint16
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        uint16 as_uint16At(uint16 index) const;

        //API Function: as_uint8At
        //    Gets the value stored at the given 0-based index, as a 1-byte uint8
        //
        //Parameters:
        //    index - The 0-based index of which to get the value
        //
        //Returns:
        //    The value stored at the given index, as an uint8
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        uint8 as_uint8At(uint16 index) const;
    };
}