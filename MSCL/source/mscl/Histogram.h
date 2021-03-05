/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "Value.h"
#include "Bin.h"

namespace mscl
{    
    //API Class: Histogram
    //    Represents a Histogram object.
    class Histogram
    {
    private:
        Histogram();    //disable default constructor

    public:
        //API Constructor: Histogram
        //    Creates a Histogram object with no bins.
        //
        //Parameters:
        //  binsStart - The start value of the first Bin.
        //  binsSize - The size of each Bin.
        Histogram(const Value& binsStart, const Value& binsSize);

    private:
        //Variable: m_binsStart
        //    The value of the start of the first Bin in the Histogram.
        Value m_binsStart;
        
        //Variable: m_binsSize
        //    The size of each Bin in the Histogram.
        Value m_binsSize;

        //Variable: m_bins
        //    The <Bins> that are contained within this Histogram.
        Bins m_bins;

    public:
        //API Function: binsStart
        //    Gets the value of the start of the first Bin in the Histogram.
        //
        //Returns:
        //    The start of the first Bin in the Histogram.
        Value binsStart() const;

        //API Function: binsSize
        //    Gets the size of each Bin in the Histogram.
        //
        //Returns:
        //    The size of each Bin in the Histogram.
        Value binsSize() const;

        //API Function: bins
        //    Gets the <Bins> contained within this Histogram.
        //
        //Returns:
        //    A <Bins> object containing each bin within this Histogram.
        Bins bins() const;

        //API Function: addBin
        //    Adds a single <Bin> to the Histogram.
        //    The first Bin's start value should match the binsStart used in the constructor.
        //    Every Bin added should have the same size which matches the binsSize used in the constructor.
        //
        //Parameters:
        //    bin - The <Bin> to add to the Histogram.
        void addBin(const Bin& bin);
    };
}