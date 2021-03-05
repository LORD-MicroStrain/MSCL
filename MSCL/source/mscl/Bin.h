/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "Value.h"

namespace mscl
{
    //API Class: Bin
    //    Represents a single bin, which has a start, end, and count.
    class Bin
    {
    public:
        //API Constructor: Bin
        //    Creates a Bin object.
        //
        //Parameters:
        //    start - The start of the range of the bin.
        //    end - The end of the range of the bin.
        //    count - The number of values that fall within the range of this bin.
        Bin(const Value& start, const Value& end, const Value& count);

    private:
        Bin() = delete; //default constructor disabled

    private:
        //Variable: m_start
        //    The start of the range of the bin.
        Value m_start;

        //Variable: m_end
        //    The end of the range of the bin.
        Value m_end;

        //Variable: m_count
        //    The number of values that fall within the range of this bin.
        Value m_count;

    public:
        //API Function: start
        //    Gets the start of the range of the bin.
        //
        //Returns:
        //     The start of the range of the bin, as a <Value> object.
        Value start() const;

        //API Function: end
        //    Gets the end of the range of the bin.
        //
        //Returns:
        //    The end of the range of the bin, as a <Value> object.
        Value end() const;

        //API Function: count
        //    Gets the number of values that fall within the range of this bin.
        //
        //Returns:
        //    The number of values that fall within the range of this bin.
        Value count() const;
    };

    //API Typedef: Bins
    //    Typedef for a vector of <Bin> objects.
    typedef std::vector<Bin> Bins;
}